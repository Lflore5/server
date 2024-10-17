/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "io/iomarket.hpp"

#include "database/database.hpp"
#include "database/databasetasks.hpp"
#include "io/iologindata.hpp"
#include "game/game.hpp"
#include "game/scheduling/dispatcher.hpp"
#include "game/scheduling/save_manager.hpp"

MarketOfferList IOMarket::getActiveOffers(MarketAction_t action) {
	MarketOfferList offerList;

	std::string query = fmt::format(
		"SELECT `id`, `itemtype`, `amount`, `price`, `tier`, `created`, `anonymous`, "
		"(SELECT `name` FROM `players` WHERE `id` = `player_id`) AS `player_name` "
		"FROM `market_offers` WHERE `sale` = {}",
		action
	);

	DBResult_ptr result = g_database().storeQuery(query);
	if (!result) {
		return offerList;
	}

	const int32_t marketOfferDuration = g_configManager().getNumber(MARKET_OFFER_DURATION);

	do {
		MarketOffer offer;
		offer.itemId = result->getU16("itemtype");
		offer.amount = result->getU16("amount");
		offer.price = result->getU64("price");
		offer.timestamp = result->getU32("created") + marketOfferDuration;
		offer.counter = result->getU32("id") & 0xFFFF;
		if (result->getU16("anonymous") == 0) {
			offer.playerName = result->getString("player_name");
		} else {
			offer.playerName = "Anonymous";
		}
		offer.tier = result->getU8("tier");
		offerList.push_back(offer);
	} while (result->next());
	return offerList;
}

MarketOfferList IOMarket::getActiveOffers(MarketAction_t action, uint16_t itemId, uint8_t tier) {
	MarketOfferList offerList;

	std::ostringstream query;
	query << "SELECT `id`, `amount`, `price`, `tier`, `created`, `anonymous`, (SELECT `name` FROM `players` WHERE `id` = `player_id`) AS `player_name` FROM `market_offers` WHERE `sale` = " << action << " AND `itemtype` = " << itemId << " AND `tier` = " << std::to_string(tier);

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		return offerList;
	}

	const int32_t marketOfferDuration = g_configManager().getNumber(MARKET_OFFER_DURATION);

	do {
		MarketOffer offer;
		offer.itemId = itemId;
		offer.amount = result->getU16("amount");
		offer.price = result->getU64("price");
		offer.timestamp = result->getU32("created") + marketOfferDuration;
		offer.counter = result->getU32("id") & 0xFFFF;
		if (result->getU16("anonymous") == 0) {
			offer.playerName = result->getString("player_name");
		} else {
			offer.playerName = "Anonymous";
		}
		offer.tier = result->getU8("tier");
		offerList.push_back(offer);
	} while (result->next());
	return offerList;
}

MarketOfferList IOMarket::getOwnOffers(MarketAction_t action, uint32_t playerId) {
	MarketOfferList offerList;

	const int32_t marketOfferDuration = g_configManager().getNumber(MARKET_OFFER_DURATION);

	std::ostringstream query;
	query << "SELECT `id`, `amount`, `price`, `created`, `itemtype`, `tier` FROM `market_offers` WHERE `player_id` = " << playerId << " AND `sale` = " << action;

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		return offerList;
	}

	do {
		MarketOffer offer;
		offer.amount = result->getU16("amount");
		offer.price = result->getU64("price");
		offer.timestamp = result->getU32("created") + marketOfferDuration;
		offer.counter = result->getU32("id") & 0xFFFF;
		offer.itemId = result->getU16("itemtype");
		offer.tier = result->getU8("tier");
		offerList.push_back(offer);
	} while (result->next());
	return offerList;
}

HistoryMarketOfferList IOMarket::getOwnHistory(MarketAction_t action, uint32_t playerId) {
	HistoryMarketOfferList offerList;

	std::ostringstream query;
	query << "SELECT `itemtype`, `amount`, `price`, `expires_at`, `state`, `tier` FROM `market_history` WHERE `player_id` = " << playerId << " AND `sale` = " << action;

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		return offerList;
	}

	do {
		HistoryMarketOffer offer;
		offer.itemId = result->getU16("itemtype");
		offer.amount = result->getU16("amount");
		offer.price = result->getU64("price");
		offer.timestamp = result->getU32("expires_at");
		offer.tier = result->getU8("tier");

		MarketOfferState_t offerState = static_cast<MarketOfferState_t>(result->getU16("state"));
		if (offerState == OFFERSTATE_ACCEPTEDEX) {
			offerState = OFFERSTATE_ACCEPTED;
		}

		offer.state = offerState;

		offerList.push_back(offer);
	} while (result->next());
	return offerList;
}

void IOMarket::processExpiredOffers(DBResult_ptr result, bool) {
	if (!result) {
		return;
	}

	do {
		if (!IOMarket::moveOfferToHistory(result->getU32("id"), OFFERSTATE_EXPIRED)) {
			continue;
		}

		const uint32_t playerId = result->getU32("player_id");
		const uint16_t amount = result->getU16("amount");
		auto tier = result->getU8("tier");
		if (result->getU16("sale") == 1) {
			const ItemType &itemType = Item::items[result->getU16("itemtype")];
			if (itemType.id == 0) {
				continue;
			}

			std::shared_ptr<Player> player = g_game().getPlayerByGUID(playerId, true);
			if (!player) {
				continue;
			}

			if (itemType.stackable) {
				uint16_t tmpAmount = amount;
				while (tmpAmount > 0) {
					uint16_t stackCount = std::min<uint16_t>(100, tmpAmount);
					std::shared_ptr<Item> item = Item::CreateItem(itemType.id, stackCount);
					if (g_game().internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT) != RETURNVALUE_NOERROR) {
						g_logger().error("[{}] Ocurred an error to add item with id {} to player {}", __FUNCTION__, itemType.id, player->getName());

						break;
					}

					if (tier != 0) {
						item->setAttribute(ItemAttribute_t::TIER, tier);
					}

					tmpAmount -= stackCount;
				}
			} else {
				int32_t subType;
				if (itemType.charges != 0) {
					subType = itemType.charges;
				} else {
					subType = -1;
				}

				for (uint16_t i = 0; i < amount; ++i) {
					std::shared_ptr<Item> item = Item::CreateItem(itemType.id, subType);
					if (g_game().internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT) != RETURNVALUE_NOERROR) {
						break;
					}

					if (tier != 0) {
						item->setAttribute(ItemAttribute_t::TIER, tier);
					}
				}
			}

			if (player->isOffline()) {
				g_saveManager().savePlayer(player);
			}
		} else {
			uint64_t totalPrice = result->getU64("price") * amount;

			std::shared_ptr<Player> player = g_game().getPlayerByGUID(playerId);
			if (player) {
				player->setBankBalance(player->getBankBalance() + totalPrice);
			} else {
				IOLoginData::increaseBankBalance(playerId, totalPrice);
			}
		}
	} while (result->next());
}

void IOMarket::checkExpiredOffers() {
	const time_t lastExpireDate = getTimeNow() - g_configManager().getNumber(MARKET_OFFER_DURATION);

	std::ostringstream query;
	query << "SELECT `id`, `amount`, `price`, `itemtype`, `player_id`, `sale`, `tier` FROM `market_offers` WHERE `created` <= " << lastExpireDate;
	g_databaseTasks().store(query.str(), IOMarket::processExpiredOffers);

	int32_t checkExpiredMarketOffersEachMinutes = g_configManager().getNumber(CHECK_EXPIRED_MARKET_OFFERS_EACH_MINUTES);
	if (checkExpiredMarketOffersEachMinutes <= 0) {
		return;
	}

	g_dispatcher().scheduleEvent(checkExpiredMarketOffersEachMinutes * 60 * 1000, IOMarket::checkExpiredOffers, __FUNCTION__);
}

uint32_t IOMarket::getPlayerOfferCount(uint32_t playerId) {
	std::ostringstream query;
	query << "SELECT COUNT(*) AS `count` FROM `market_offers` WHERE `player_id` = " << playerId;

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		return 0;
	}
	return result->getU32("count");
}

MarketOfferEx IOMarket::getOfferByCounter(uint32_t timestamp, uint16_t counter) {
	MarketOfferEx offer;

	const int32_t created = timestamp - g_configManager().getNumber(MARKET_OFFER_DURATION);

	std::ostringstream query;
	query << "SELECT `id`, `sale`, `itemtype`, `amount`, `created`, `price`, `player_id`, `anonymous`, `tier`, (SELECT `name` FROM `players` WHERE `id` = `player_id`) AS `player_name` FROM `market_offers` WHERE `created` = " << created << " AND (`id` & 65535) = " << counter << " LIMIT 1";

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		offer.id = 0;
		return offer;
	}

	offer.id = result->getU32("id");
	offer.type = static_cast<MarketAction_t>(result->getU16("sale"));
	offer.amount = result->getU16("amount");
	offer.counter = result->getU32("id") & 0xFFFF;
	offer.timestamp = result->getU32("created");
	offer.price = result->getU64("price");
	offer.itemId = result->getU16("itemtype");
	offer.playerId = result->getU32("player_id");
	offer.tier = result->getU8("tier");
	if (result->getU16("anonymous") == 0) {
		offer.playerName = result->getString("player_name");
	} else {
		offer.playerName = "Anonymous";
	}
	return offer;
}

void IOMarket::createOffer(uint32_t playerId, MarketAction_t action, uint32_t itemId, uint16_t amount, uint64_t price, uint8_t tier, bool anonymous) {
	std::ostringstream query;
	query << "INSERT INTO `market_offers` (`player_id`, `sale`, `itemtype`, `amount`, `created`, `anonymous`, `price`, `tier`) VALUES (" << playerId << ',' << action << ',' << itemId << ',' << amount << ',' << getTimeNow() << ',' << anonymous << ',' << price << ',' << std::to_string(tier) << ')';
	Database::getInstance().executeQuery(query.str());
}

void IOMarket::acceptOffer(uint32_t offerId, uint16_t amount) {
	std::ostringstream query;
	query << "UPDATE `market_offers` SET `amount` = `amount` - " << amount << " WHERE `id` = " << offerId;
	Database::getInstance().executeQuery(query.str());
}

void IOMarket::deleteOffer(uint32_t offerId) {
	std::ostringstream query;
	query << "DELETE FROM `market_offers` WHERE `id` = " << offerId;
	Database::getInstance().executeQuery(query.str());
}

void IOMarket::appendHistory(uint32_t playerId, MarketAction_t type, uint16_t itemId, uint16_t amount, uint64_t price, time_t timestamp, uint8_t tier, MarketOfferState_t state) {
	std::ostringstream query;
	query << "INSERT INTO `market_history` (`player_id`, `sale`, `itemtype`, `amount`, `price`, `expires_at`, `inserted`, `state`, `tier`) VALUES ("
		  << playerId << ',' << type << ',' << itemId << ',' << amount << ',' << price << ','
		  << timestamp << ',' << getTimeNow() << ',' << state << ',' << std::to_string(tier) << ')';
	g_databaseTasks().execute(query.str());
}

bool IOMarket::moveOfferToHistory(uint32_t offerId, MarketOfferState_t state) {
	Database &db = Database::getInstance();

	std::ostringstream query;
	query << "SELECT `player_id`, `sale`, `itemtype`, `amount`, `price`, `created`, `tier` FROM `market_offers` WHERE `id` = " << offerId;

	DBResult_ptr result = db.storeQuery(query.str());
	if (!result) {
		return false;
	}

	query.str(std::string());
	query << "DELETE FROM `market_offers` WHERE `id` = " << offerId;
	if (!db.executeQuery(query.str())) {
		return false;
	}

	appendHistory(
		result->getU32("player_id"),
		static_cast<MarketAction_t>(result->getU16("sale")),
		result->getU16("itemtype"),
		result->getU16("amount"),
		result->getU64("price"),
		getTimeNow(),
		result->getU8("tier"),
		state
	);
	return true;
}

void IOMarket::updateStatistics() {
	auto query = fmt::format(
		"SELECT sale, itemtype, COUNT(price) AS num, MIN(price) AS min, MAX(price) AS max, SUM(price) AS sum, tier "
		"FROM market_history "
		"WHERE state = '{}' "
		"GROUP BY itemtype, sale, tier",
		OFFERSTATE_ACCEPTED
	);

	auto result = g_database().getResult(query);
	if (!result) {
		return;
	}

	for (mysqlx::Row row : result->fetchAll()) {
		MarketStatistics* statistics = nullptr;
		auto sale = Database::getU32(row[0]); // `sale` is at index 0
		uint16_t itemId = Database::getU32(row[1]); // `itemtype` is at index 1
		uint8_t tier = Database::getU8(row[6]); // `tier` is at index 6

		if (sale == MARKETACTION_BUY) {
			statistics = &purchaseStatistics[itemId][tier];
		} else {
			statistics = &saleStatistics[itemId][tier];
		}

		statistics->numTransactions = Database::getU32(row[2]); // `num` is at index 2
		statistics->lowestPrice = Database::getU64(row[3]); // `min` is at index 3
		statistics->highestPrice = Database::getU64(row[4]); // `max` is at index 4
		statistics->totalPrice = Database::getDouble(row[5]); // `sum` is at index 5
	}
}
