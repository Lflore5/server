/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_CANARY_SERVER_HPP_
#define SRC_CANARY_SERVER_HPP_

#include "server/server.h"
#include "security/rsa.h"
#include "lib/thread/thread_pool.hpp"

class Logger;

class CanaryServer {
	public:
		explicit CanaryServer(
			Logger &logger,
			RSA &rsa,
			ServiceManager &serviceManager,
			ThreadPool &threadPool
		);

		int run();

	private:
		ServiceManager &serviceManager;
		ThreadPool &threadPool;
		Logger &logger;
		RSA &rsa;

		std::mutex g_loaderLock;
		std::condition_variable g_loaderSignal;
		std::unique_lock<std::mutex> g_loaderUniqueLock;
		bool g_loaderDone = false;

		void logInfos();

		static void toggleForceCloseButton();

		static void badAllocationHandler();

		static std::string getCompiler();

		static std::string getPlatform();

		void loadConfigLua();

		void initializeDatabase();

		void loadModules();

		void setWorldType();

		void loadMaps();

		void setupHousesRent();

		void modulesLoadHelper(bool loaded, std::string moduleName);

		void startupErrorMessage();
};

#endif // SRC_CANARY_SERVER_HPP_
