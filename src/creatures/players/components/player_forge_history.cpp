/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
 */

#include "creatures/players/components/player_forge_history.hpp"

#include "database/database.hpp"
#include "creatures/players/player.hpp"
#include "utils/tools.hpp"
#include "game/scheduling/save_manager.hpp"

PlayerForgeHistory::PlayerForgeHistory(Player &player) :
	m_player(player) { }

const std::vector<ForgeHistory> &PlayerForgeHistory::get() const {
	return m_history;
}

void PlayerForgeHistory::add(const ForgeHistory &history) {
	m_history.emplace_back(history);
	m_modifiedHistory.push_back(history);
}

void PlayerForgeHistory::remove(int historyId) {
	m_removedHistoryIds.push_back(historyId);
	auto it = std::ranges::remove_if(m_history, [historyId](const ForgeHistory &h) {
		return h.id == historyId;
	});
	m_history.erase(it.begin(), it.end());
}

bool PlayerForgeHistory::load() {
	auto playerGUID = m_player.getGUID();
	auto query = fmt::format("SELECT * FROM forge_history WHERE player_id = {}", playerGUID);
	const DBResult_ptr &result = g_database().storeQuery(query);
	if (!result) {
		g_logger().debug("Failed to load forge history for player with ID: {}", playerGUID);
		return false;
	}

	do {
		ForgeHistory history;
		history.id = result->getNumber<int>("id");
		history.actionType = static_cast<ForgeAction_t>(result->getNumber<uint8_t>("action_type"));
		history.description = result->getString("description");
		history.createdAt = result->getNumber<uint64_t>("done_at");
		history.success = result->getNumber<bool>("is_success");
		m_history.emplace_back(history);
	} while (result->next());

	return true;
}

bool PlayerForgeHistory::save() {
	if (m_modifiedHistory.empty() && m_removedHistoryIds.empty()) {
		return true;
	}

	auto playerGUID = m_player.getGUID();
	auto removedHistoryIds = m_removedHistoryIds;
	auto modifiedHistory = m_modifiedHistory;

	auto deleteForgeHistoryEntries = [playerGUID, removedHistoryIds]() mutable {
		if (!removedHistoryIds.empty()) {
			std::string idsToDelete = fmt::format("{}", fmt::join(removedHistoryIds, ", "));
			std::string deleteQuery = fmt::format(
				"DELETE FROM `forge_history` WHERE `player_id` = {} AND `id` IN ({})",
				playerGUID, idsToDelete
			);

			if (!g_database().executeQuery(deleteQuery)) {
				g_logger().error("[{}] failed to delete forge history entries for player with ID: {}", std::source_location::current().function_name(), playerGUID);
				return false;
			}

			removedHistoryIds.clear();
		}

		return true;
	};

	auto insertModifiedHistory = [playerGUID, modifiedHistory]() mutable {
		DBInsert insertQuery("INSERT INTO `forge_history` (`id`, `player_id`, `action_type`, `description`, `done_at`, `is_success`) VALUES ");
		insertQuery.upsert({ "action_type", "description", "done_at", "is_success" });

		for (const auto &history : modifiedHistory) {
			auto row = fmt::format("{}, {}, {}, {}, {}, {}", history.id, playerGUID, history.actionType, g_database().escapeString(history.description), history.createdAt, history.success ? 1 : 0);
			if (!insertQuery.addRow(row)) {
				g_logger().warn("[{}] failed to add forge history entry for player with ID: {}", std::source_location::current().function_name(), playerGUID);
				return false;
			}
			g_logger().debug("Added forge history entry date: {}, for player with ID: {}", formatDate(history.createdAt / 1000), playerGUID);
		}

		if (!insertQuery.execute()) {
			g_logger().error("[{}] failed to execute insertion for forge history entries for player with ID: {}", std::source_location::current().function_name(), playerGUID);
			return false;
		}

		return true;
	};

	auto forgeHistorySaveTask = [deleteForgeHistoryEntries, insertModifiedHistory]() mutable {
		if (!deleteForgeHistoryEntries()) {
			return;
		}

		if (!insertModifiedHistory()) {
			return;
		}
	};

	g_saveManager().addTask(forgeHistorySaveTask, "PlayerForgeHistory::save - forgeHistorySaveTask");
	m_modifiedHistory.clear();
	return true;
}
