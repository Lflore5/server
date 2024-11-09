/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
 */

#include "creatures/players/components/player_stash.hpp"

#include "database/database.hpp"
#include "items/item.hpp"
#include "creatures/players/player.hpp"
#include "game/scheduling/save_manager.hpp"

PlayerStash::PlayerStash(Player &player) :
	m_player(player) { }

void PlayerStash::add(uint16_t itemId, uint32_t amount) {
	const auto it = m_stashItems.find(itemId);
	if (it != m_stashItems.end()) {
		m_stashItems[itemId] += amount;
	} else {
		m_stashItems[itemId] = amount;
	}

	m_modifiedItems[itemId] = m_stashItems[itemId]; // Track added/modified items
	m_removedItems.erase(itemId); // Remove from removed if it was there
}

uint32_t PlayerStash::getCount(uint16_t itemId) const {
	const auto it = m_stashItems.find(itemId);
	if (it != m_stashItems.end()) {
		return it->second;
	}
	return 0;
}

bool PlayerStash::remove(uint16_t itemId, uint32_t amount) {
	auto it = m_stashItems.find(itemId);
	if (it != m_stashItems.end()) {
		if (it->second > amount) {
			m_stashItems[itemId] -= amount;
			m_modifiedItems[itemId] = m_stashItems[itemId]; // Track modified item
		} else if (it->second == amount) {
			m_stashItems.erase(itemId);
			m_removedItems.insert(itemId); // Track removed item
			m_modifiedItems.erase(itemId); // Ensure it's not in added items
		} else {
			return false;
		}
		return true;
	}
	return false;
}

bool PlayerStash::find(uint16_t itemId) const {
	return m_stashItems.find(itemId) != m_stashItems.end();
}

const std::map<uint16_t, uint32_t> &PlayerStash::getItems() const {
	return m_stashItems;
}

uint16_t PlayerStash::getSize() const {
	uint16_t size = 0;
	for (const auto &[itemId, itemCount] : m_stashItems) {
		size += ceil(itemCount / static_cast<float_t>(Item::items[itemId].stackSize));
	}
	return size;
}

bool PlayerStash::save() {
	if (m_modifiedItems.empty() && m_removedItems.empty()) {
		return true;
	}

	const auto playerGUID = m_player.getGUID();
	auto removedItems = m_removedItems;
	auto modifiedItems = m_modifiedItems;

	auto deleteStashItems = [playerGUID, removedItems = std::move(removedItems)]() mutable {
		if (!removedItems.empty()) {
			std::string removedItemIds = fmt::format("{}", fmt::join(removedItems, ", "));
			std::string deleteQuery = fmt::format(
				"DELETE FROM `player_stash` WHERE `player_id` = {} AND `item_id` IN ({})",
				playerGUID, removedItemIds
			);

			if (!g_database().executeQuery(deleteQuery)) {
				g_logger().error("[{}] failed to delete removed items for player: {}", std::source_location::current().function_name(), playerGUID);
				return false;
			}

			removedItems.clear();
		}

		return true;
	};

	auto insertModifiedStashItems = [playerGUID, modifiedItems = std::move(modifiedItems)]() mutable {
		DBInsert insertQuery("INSERT INTO `player_stash` (`player_id`, `item_id`, `item_count`) VALUES ");
		insertQuery.upsert({ "item_count" });

		for (const auto &[itemId, itemCount] : modifiedItems) {
			auto row = fmt::format("{}, {}, {}", playerGUID, itemId, itemCount);
			if (!insertQuery.addRow(row)) {
				g_logger().warn("[{}] - Failed to add row for stash item: {}", std::source_location::current().function_name(), itemId);
				return false;
			}
		}

		if (!insertQuery.execute()) {
			g_logger().error("[{}] - Failed to execute insertion for modified stash items for player: {}", std::source_location::current().function_name(), playerGUID);
			return false;
		}

		return true;
	};

	auto stashSaveTask = [deleteStashItems, insertModifiedStashItems]() mutable {
		if (!deleteStashItems()) {
			return;
		}

		if (!insertModifiedStashItems()) {
			return;
		}
	};

	g_saveManager().addTask(stashSaveTask, "PlayerStash::save - stashSaveTask");
	m_modifiedItems.clear();

	return true;
}

bool PlayerStash::load() {
	auto query = fmt::format("SELECT `item_count`, `item_id` FROM `player_stash` WHERE `player_id` = {}", m_player.getGUID());
	const DBResult_ptr &result = g_database().storeQuery(query);
	if (!result) {
		g_logger().debug("[{}] - Failed to load stash items for player: {}", std::source_location::current().function_name(), m_player.getGUID());
		return false;
	}

	do {
		int itemId = result->getNumber<uint16_t>("item_id");
		int itemCount = result->getNumber<uint32_t>("item_count");
		// The PlayerStash::add function should not be used, to avoid incrementing the add/modified maps
		m_stashItems[itemId] = itemCount;
	} while (result->next());

	return true;
}
