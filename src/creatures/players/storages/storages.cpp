/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "creatures/players/storages/storages.hpp"

#include "config/configmanager.h"

bool Storages::loadFromXML() {
	pugi::xml_document doc;
	auto folder = g_configManager().getString(CORE_DIRECTORY) + "/XML/storages.xml";
	pugi::xml_parse_result result = doc.load_file(folder.c_str());

	if (!result) {
		spdlog::error("[{}] parsed with errors");
		spdlog::warn("Error description: {}", result.description());
		spdlog::warn("Error offset: ", result.offset);
		return false;
	}

	for (pugi::xml_node range : doc.child("storages").children("range")) {
		uint32_t start = range.attribute("start").as_uint();
		uint32_t end = range.attribute("end").as_uint();

		// TODO: Check if this range conflicts with any previously defined range

		for (pugi::xml_node storage : range.children("storage")) {
			std::string name = storage.attribute("name").as_string();
			uint32_t key = storage.attribute("key").as_uint();

			for (char c : name) {
				if (std::isupper(c)) {
					spdlog::warn("[{}] Storage from storages.xml with name: {}, contains uppercase letters. Please use dot notation pattern", __func__, name);
					break;
				}
			}

			// Add the start of the range to the key
			key += start;

			if (key > end) {
				spdlog::error("[{}] Storage from storages.xml with name: {}, has key outside of its range", __func__, name);
				continue;
			}

			m_storageMap[name] = key;
		}
	}

	return true;
}

const std::map<std::string, uint32_t> &Storages::getStorageMap() const {
	return m_storageMap;
}
