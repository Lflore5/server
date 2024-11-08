/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "server/server.hpp"

#include "server/network/message/outputmessage.hpp"
#include "config/configmanager.hpp"
#include "game/scheduling/dispatcher.hpp"
#include "creatures/players/management/ban.hpp"

ServiceManager::~ServiceManager() {
	try {
		stop();
	} catch (std::exception &exception) {
		g_logger().error("{} - Catch exception error: {}", __FUNCTION__, exception.what());
	}
}

void ServiceManager::die() {
	io_service.stop();
}

void ServiceManager::run() {
	if (running) {
		g_logger().error("ServiceManager is already running!", __FUNCTION__);
		return;
	}

	assert(!running);
	running = true;
	io_service.run();
}

void ServiceManager::stop() {
	if (!running) {
		return;
	}

	running = false;

	for (auto &val : acceptors | std::views::values) {
		try {
			auto weakServicePort = std::weak_ptr(val);
			io_service.post([weakServicePort] {
				if (const auto servicePort = weakServicePort.lock()) {
					servicePort->onStopServer();
				}
			});
		} catch (const std::system_error &e) {
			g_logger().warn("[ServiceManager::stop] - Network error: {}", e.what());
		}
	}

	acceptors.clear();

	death_timer.expires_from_now(std::chrono::seconds(3));
	death_timer.async_wait([this](const std::error_code &err) {
		if (!err) {
			die();
		}
	});
}

ServicePort::~ServicePort() {
	close();
}

bool ServicePort::is_single_socket() const {
	return !services.empty() && services.front()->is_single_socket();
}

std::string ServicePort::get_protocol_names() const {
	if (services.empty()) {
		return {};
	}

	std::string str = services.front()->get_protocol_name();
	for (size_t i = 1; i < services.size(); ++i) {
		str.push_back(',');
		str.push_back(' ');
		str.append(services[i]->get_protocol_name());
	}
	return str;
}

void ServicePort::accept() {
	if (!acceptor) {
		return;
	}

	auto connection = ConnectionManager::getInstance().createConnection(io_service, shared_from_this());
	acceptor->async_accept(connection->getSocket(), [weakSelf = std::weak_ptr<ServicePort>(shared_from_this()), connection](const std::error_code &error) {
		if (const auto self = weakSelf.lock()) {
			self->onAccept(connection, error);
		}
	});
}

void ServicePort::onAccept(const Connection_ptr &connection, const std::error_code &error) {
	if (!error) {
		if (services.empty()) {
			return;
		}

		const auto remote_ip = connection->getIP();
		if (remote_ip != 0 && inject<Ban>().acceptConnection(remote_ip)) {
			const Service_ptr service = services.front();
			if (service->is_single_socket()) {
				connection->accept(service->make_protocol(connection));
			} else {
				connection->acceptInternal();
			}
		} else {
			connection->close(FORCE_CLOSE);
		}

		accept();
	} else if (error != asio::error::operation_aborted) {
		if (!pendingStart) {
			close();
			pendingStart = true;

			auto weakSelf = std::weak_ptr(shared_from_this());
			g_dispatcher().scheduleEvent(
				15000, [weakSelf, serverPort = serverPort] {
					if (auto self = weakSelf.lock()) {
						openAcceptor(weakSelf, serverPort);
					}
				},
				"ServicePort::openAcceptor"
			);
		}
	}
}

Protocol_ptr ServicePort::make_protocol(bool checksummed, NetworkMessage &msg, const Connection_ptr &connection) const {
	const uint8_t protocolID = msg.getByte();
	for (const auto &service : services) {
		if (protocolID == service->get_protocol_identifier() && ((checksummed && service->is_checksummed()) || !service->is_checksummed())) {
			return service->make_protocol(connection);
		}
	}
	return nullptr;
}

void ServicePort::onStopServer() const {
	close();
}

void ServicePort::openAcceptor(const std::weak_ptr<ServicePort> &weak_service, uint16_t port) {
	if (const auto service = weak_service.lock()) {
		service->open(port);
	}
}

void ServicePort::open(uint16_t port) {
	close();

	serverPort = port;
	pendingStart = false;

	try {
		auto endpoint = g_configManager().getBoolean(BIND_ONLY_GLOBAL_ADDRESS)
			? asio::ip::tcp::endpoint(asio::ip::address::from_string(g_configManager().getString(IP)), serverPort)
			: asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort);

		acceptor = std::make_unique<asio::ip::tcp::acceptor>(io_service, endpoint);
		acceptor->set_option(asio::ip::tcp::no_delay(true));

		accept();
	} catch (const std::system_error &e) {
		g_logger().warn("[ServicePort::open] - Failed to open acceptor, error: {}", e.what());

		pendingStart = true;
		auto weakSelf = std::weak_ptr(shared_from_this());
		g_dispatcher().scheduleEvent(
			15000,
			[weakSelf, port] {
				if (auto self = weakSelf.lock()) {
					openAcceptor(weakSelf, port);
				}
			},
			"ServicePort::openAcceptor"
		);
	}
}

void ServicePort::close() const {
	if (acceptor && acceptor->is_open()) {
		std::error_code error;
		acceptor->close(error);
		if (error) {
			g_logger().warn("[ServicePort::close] - Failed to close acceptor: {}", error.message());
		}
	}
}

bool ServicePort::add_service(const Service_ptr &new_svc) {
	if (std::ranges::any_of(services, [](const Service_ptr &svc) { return svc->is_single_socket(); })) {
		return false;
	}

	services.emplace_back(new_svc);
	return true;
}
