/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include "pch.hpp"
#include "creatures/creature.hpp"

class Player;
class Monster;
class Npc;
struct Position;

using SpectatorList = std::vector<Creature*>;

struct SpectatorsCache {
	struct FloorData {
		std::optional<SpectatorList> floor;
		std::optional<SpectatorList> multiFloor;
	};

	int32_t minRangeX { 0 };
	int32_t maxRangeX { 0 };
	int32_t minRangeY { 0 };
	int32_t maxRangeY { 0 };

	FloorData creatures;
	FloorData players;
};

class Spectators {
public:
	static void clearCache();

	template <typename T>
		requires std::is_same_v<Creature, T> || std::is_same_v<Player, T>
	Spectators find(const Position &centerPos, bool multifloor = false, int32_t minRangeX = 0, int32_t maxRangeX = 0, int32_t minRangeY = 0, int32_t maxRangeY = 0) {
		constexpr bool onlyPlayers = std::is_same_v<T, Player>;
		return find(centerPos, multifloor, onlyPlayers, minRangeX, maxRangeX, minRangeY, maxRangeY);
	}

	template <typename T>
		requires std::is_base_of_v<Creature, T>
	Spectators filter();

	bool contains(const Creature* creature) const;

	bool erase(const Creature* creature);

	template <class F>
	bool erase_if(F fnc) {
		return std::erase_if(creatures, std::move(fnc)) > 0;
	}

	Spectators insert(Creature* creature);
	Spectators insertAll(const SpectatorList &list);
	Spectators join(const Spectators &anotherSpectators) {
		return insertAll(anotherSpectators.creatures);
	}

	bool empty() const noexcept {
		return creatures.empty();
	}

	size_t size() noexcept {
		update();
		return creatures.size();
	}

	auto begin() noexcept {
		update();
		return creatures.begin();
	}

	auto end() noexcept {
		return creatures.end();
	}

	const auto &data() noexcept {
		update();
		return creatures;
	}

private:
	static phmap::flat_hash_map<Position, SpectatorsCache> spectatorsCache;

	Spectators find(const Position &centerPos, bool multifloor = false, bool onlyPlayers = false, int32_t minRangeX = 0, int32_t maxRangeX = 0, int32_t minRangeY = 0, int32_t maxRangeY = 0);
	bool checkCache(const SpectatorsCache::FloorData &specData, bool onlyPlayers, const Position &centerPos, bool checkDistance, bool multifloor, int32_t minRangeX, int32_t maxRangeX, int32_t minRangeY, int32_t maxRangeY);
	void update() noexcept;

	SpectatorList creatures;
	bool needUpdate = false;
};

template <typename T>
	requires std::is_base_of_v<Creature, T>
Spectators Spectators::filter() {
	update();
	auto specs = Spectators();
	for (const auto &c : creatures) {
		if constexpr (std::is_same_v<T, Player>) {
			if (c->getPlayer() != nullptr) {
				specs.insert(c);
			}
		} else if constexpr (std::is_same_v<T, Monster>) {
			if (c->getMonster() != nullptr) {
				specs.insert(c);
			}
		} else if constexpr (std::is_same_v<T, Npc>) {
			if (c->getNpc() != nullptr) {
				specs.insert(c);
			}
		}
	}

	return specs;
}
