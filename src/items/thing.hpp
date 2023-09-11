/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include "game/movement/position.hpp"

class Tile;
class Cylinder;
class Item;
class Creature;
class Container;

class Thing {
public:
	constexpr Thing() = default;
	virtual ~Thing() = default;

	// non-copyable
	Thing(const Thing &) = delete;
	Thing &operator=(const Thing &) = delete;

	virtual std::string getDescription(int32_t lookDistance) = 0;

	virtual std::shared_ptr<Cylinder> getParent() const {
		return nullptr;
	}
	virtual std::shared_ptr<Cylinder> getRealParent() const {
		return getParent();
	}

	virtual void setParent(std::shared_ptr<Cylinder>) {
		//
	}

	virtual std::shared_ptr<Tile> getTile() {
		return nullptr;
	}

	virtual const Position &getPosition();
	virtual int32_t getThrowRange() const = 0;
	virtual bool isPushable() = 0;

	virtual std::shared_ptr<Container> getContainer() {
		return nullptr;
	}
	virtual std::shared_ptr<Container> getContainer() const {
		return nullptr;
	}
	virtual std::shared_ptr<Item> getItem() {
		return nullptr;
	}
	virtual std::shared_ptr<Item> getItem() const {
		return nullptr;
	}
	virtual std::shared_ptr<Creature> getCreature() {
		return nullptr;
	}
	virtual std::shared_ptr<Creature> getCreature() const {
		return nullptr;
	}

	virtual bool isRemoved() const {
		return true;
	}
};
