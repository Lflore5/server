/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "items/containers/rewards/reward.hpp"

Reward::Reward() :
	Container(ITEM_REWARD_CONTAINER) {
	maxSize = 32;
	unlocked = false;
	pagination = true;
}

ReturnValue Reward::queryAdd(int32_t, const std::shared_ptr<Thing> &thing, uint32_t, uint32_t, std::shared_ptr<Creature> actor /* = nullptr*/) {
	if (actor) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	std::shared_ptr<Item> item = thing->getItem();
	if (!item) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (item.get() == this) {
		return RETURNVALUE_THISISIMPOSSIBLE;
	}

	if (!item->isPickupable()) {
		return RETURNVALUE_CANNOTPICKUP;
	}

	return RETURNVALUE_NOERROR;
}

void Reward::postAddNotification(std::shared_ptr<Thing> thing, std::shared_ptr<Cylinder> oldParent, int32_t index, CylinderLink_t) {
	std::shared_ptr<Cylinder> localParent = getParent();
	if (localParent != nullptr) {
		localParent->postAddNotification(thing, oldParent, index, LINK_PARENT);
	}
}

void Reward::postRemoveNotification(std::shared_ptr<Thing> thing, std::shared_ptr<Cylinder> newParent, int32_t index, CylinderLink_t) {
	std::shared_ptr<Cylinder> localParent = getParent();
	if (localParent != nullptr) {
		localParent->postRemoveNotification(thing, newParent, index, LINK_PARENT);
	}
}

std::shared_ptr<Cylinder> Reward::getParent() const {
	return parent.lock();
}
