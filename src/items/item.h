/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
*/

#ifndef SRC_ITEMS_ITEM_H_
#define SRC_ITEMS_ITEM_H_

#include "items/cylinder.h"
#include "items/thing.h"
#include "enums/item_attribute.hpp"
#include "items/items.h"
#include "items/functions/item/attribute.hpp"
#include "lua/scripts/luascript.h"
#include "utils/tools.h"
#include "io/fileloader.h"

class Creature;
class Player;
class Container;
class Depot;
class Teleport;
class TrashHolder;
class Mailbox;
class Door;
class MagicField;
class BedItem;
class Imbuement;

// This class ItemProperties that serves as an interface to access and modify attributes of an item. The item's attributes are stored in an instance of ItemAttribute. The class ItemProperties has methods to get and set integer and string attributes, check if an attribute exists, remove an attribute, get the underlying attribute bits, and get a vector of attributes. It also has methods to get and set custom attributes, which are stored in a std::map<std::string, CustomAttribute, std::less<>>. The class has a data member attributePtr of type std::unique_ptr<ItemAttribute> that stores a pointer to the item's attributes methods.
class ItemProperties {
public:
	const int64_t& getInteger(ItemAttribute_t type) const {
		static int64_t emptyInt;
		if (!attributePtr) {
			return emptyInt;
		}

		return attributePtr->getAttributeValue(type);
	}
	const std::string& getString(ItemAttribute_t type) const {
		static std::string emptyString;
		if (!attributePtr) {
			return emptyString;
		}

		return attributePtr->getAttributeString(type);
	}
	bool hasAttribute(ItemAttribute_t type) const {
		if (!attributePtr) {
			return false;
		}

		return attributePtr->hasAttribute(type);
	}
	void removeAttribute(ItemAttribute_t type) {
		if (attributePtr) {
			attributePtr->removeAttribute(type);
		}
	}

	template<typename GenericAttribute>
	void setAttribute(ItemAttribute_t type, GenericAttribute genericAttribute) {
		getAttribute()->setAttribute(type, genericAttribute);
	}

	std::unique_ptr<ItemAttribute>& getAttribute() {
		if (!attributePtr) {
			attributePtr.reset(new ItemAttribute());
		}
	
		return attributePtr;
	}
	const std::unique_ptr<ItemAttribute>& getAttribute() const {
		if (!attributePtr) {
			std::bit_cast<ItemProperties*>(this)->attributePtr.reset(new ItemAttribute());
		}
	
		return attributePtr;
	}

	const std::underlying_type_t<ItemAttribute_t>& getAttributeBits() const {
		return attributePtr->getAttributeBits();
	}
	const std::vector<Attributes>& getAttributeVector() const {
		return attributePtr->getAttributeVector();
	}

	bool isIntAttrType(ItemAttribute_t type) const {
		if (!attributePtr) {
			return false;
		}

		return attributePtr->isIntAttrType(type);
	}

	bool isStrAttrType(ItemAttribute_t type) const {
		if (!attributePtr) {
			return false;
		}

		return attributePtr->isStrAttrType(type);
	}

	// Custom Attributes
	const std::map<std::string, CustomAttribute, std::less<>>& getCustomAttributeMap() const {
		return getAttribute()->getCustomAttributeMap();
	}
	const CustomAttribute* getCustomAttribute(const std::string& attributeName) const
	{
		return getAttribute()->getCustomAttribute(attributeName);
	}

	template<typename GenericType>
	void setCustomAttribute(const std::string &key, GenericType value) {
		getAttribute()->setCustomAttribute(key, value);
	}

	void addCustomAttribute(const std::string &key, const CustomAttribute &customAttribute)
	{
		getAttribute()->addCustomAttribute(key, customAttribute);
	}

	bool removeCustomAttribute(const std::string& attributeName) {
		return getAttribute()->removeCustomAttribute(attributeName);
	}

	uint16_t getCharges() const {
		if (!attributePtr) {
			return 0;
		}

		return static_cast<uint16_t>(getInteger(ItemAttribute_t::CHARGES));
	}

	uint32_t getCorpseOwner() const {
		return static_cast<uint32_t>(getInteger(ItemAttribute_t::CORPSEOWNER));
	}

	int32_t getDuration() const {
		ItemDecayState_t decayState = getDecaying();
		if (decayState == DECAYING_TRUE || decayState == DECAYING_STOPPING) {
			return std::max<int32_t>(0, static_cast<int32_t>(getInteger(ItemAttribute_t::DURATION_TIMESTAMP) -OTSYS_TIME()));
		} else {
			return static_cast<int32_t>(getInteger(ItemAttribute_t::DURATION));
		}
	}

	void setDecaying(ItemDecayState_t decayState) {
		setAttribute(ItemAttribute_t::DECAYSTATE, decayState);
		if (decayState == DECAYING_FALSE) {
			removeAttribute(ItemAttribute_t::DURATION_TIMESTAMP);
		}
	}
	ItemDecayState_t getDecaying() const {
		return static_cast<ItemDecayState_t>(getInteger(ItemAttribute_t::DECAYSTATE));
	}

	bool isRewardCorpse() const {
		return getCorpseOwner();
	}

	std::unique_ptr<ItemAttribute> attributePtr;
};

class Item : virtual public Thing, public ItemProperties
{
	public:
		//Factory member to create item of right type based on type
		static Item* CreateItem(const uint16_t type, uint16_t count = 0);
		static Container* CreateItemAsContainer(const uint16_t type, uint16_t size);
		static Item* CreateItem(PropStream& propStream);
		static Items items;

		// Constructor for items
		Item(const uint16_t type, uint16_t count = 0);
		Item(const Item& i);
		virtual Item* clone() const;

		virtual ~Item() = default;

		// non-assignable
		Item& operator=(const Item&) = delete;

		bool equals(const Item* otherItem) const;

		Item* getItem() override final {
			return this;
		}
		const Item* getItem() const override final {
			return this;
		}
		virtual Teleport* getTeleport() {
			return nullptr;
		}
		virtual const Teleport* getTeleport() const {
			return nullptr;
		}
		virtual TrashHolder* getTrashHolder() {
			return nullptr;
		}
		virtual const TrashHolder* getTrashHolder() const {
			return nullptr;
		}
		virtual Mailbox* getMailbox() {
			return nullptr;
		}
		virtual const Mailbox* getMailbox() const {
			return nullptr;
		}
		virtual Door* getDoor() {
			return nullptr;
		}
		virtual const Door* getDoor() const {
			return nullptr;
		}
		virtual MagicField* getMagicField() {
			return nullptr;
		}
		virtual const MagicField* getMagicField() const {
			return nullptr;
		}
		virtual BedItem* getBed() {
			return nullptr;
		}
		virtual const BedItem* getBed() const {
			return nullptr;
		}

		void setIsLootTrackeable(bool value) {
			isLootTrackeable = value;
		}

		bool getIsLootTrackeable() {
			return isLootTrackeable;
		}

		static std::string parseImbuementDescription(const Item* item);
		static std::string parseShowAttributesDescription(const Item *item, const uint16_t itemId);
		static std::string parseClassificationDescription(const Item* item);

		static std::vector<std::pair<std::string, std::string>> getDescriptions(const ItemType& it,
                                    const Item* item = nullptr);
		static std::string getDescription(const ItemType& it, int32_t lookDistance, const Item* item = nullptr, int32_t subType = -1, bool addArticle = true);
		static std::string getNameDescription(const ItemType& it, const Item* item = nullptr, int32_t subType = -1, bool addArticle = true);
		static std::string getWeightDescription(const ItemType& it, uint32_t weight, uint32_t count = 1);

		std::string getDescription(int32_t lookDistance) const override final;
		std::string getNameDescription() const;
		std::string getWeightDescription() const;

		//serialization
		virtual Attr_ReadValue readAttr(AttrTypes_t attr, PropStream& propStream);
		bool unserializeAttr(PropStream& propStream);
		virtual bool unserializeItemNode(OTB::Loader&, const OTB::Node&, PropStream& propStream);

		virtual void serializeAttr(PropWriteStream& propWriteStream) const;

		bool isPushable() const override final {
			return isMoveable();
		}
		int32_t getThrowRange() const override final {
			return (isPickupable() ? 15 : 2);
		}

		uint16_t getID() const {
			return id;
		}
		void setID(uint16_t newid);

		// Returns the player that is holding this item in his inventory
		Player* getHoldingPlayer() const;

		WeaponType_t getWeaponType() const {
			return items[id].weaponType;
		}
		Ammo_t getAmmoType() const {
			return items[id].ammoType;
		}
		uint8_t getShootRange() const {
			if (hasAttribute(ItemAttribute_t::SHOOTRANGE)) {
				return static_cast<uint8_t>(getInteger(ItemAttribute_t::SHOOTRANGE));
			}
			return items[id].shootRange;
		}

		virtual uint32_t getWeight() const;
		uint32_t getBaseWeight() const {
			if (hasAttribute(ItemAttribute_t::WEIGHT)) {
				return static_cast<uint32_t>(getInteger(ItemAttribute_t::WEIGHT));
			}
			return items[id].weight;
		}
		int32_t getAttack() const {
			if (hasAttribute(ItemAttribute_t::ATTACK)) {
				return static_cast<int32_t>(getInteger(ItemAttribute_t::ATTACK));
			}
			return items[id].attack;
		}
		int32_t getArmor() const {
			if (hasAttribute(ItemAttribute_t::ARMOR)) {
				return static_cast<int32_t>(getInteger(ItemAttribute_t::ARMOR));
			}
			return items[id].armor;
		}
		int32_t getDefense() const {
			if (hasAttribute(ItemAttribute_t::DEFENSE)) {
				return static_cast<int32_t>(getInteger(ItemAttribute_t::DEFENSE));
			}
			return items[id].defense;
		}
		int32_t getExtraDefense() const {
			if (hasAttribute(ItemAttribute_t::EXTRADEFENSE)) {
				return static_cast<int32_t>(getInteger(ItemAttribute_t::EXTRADEFENSE));
			}
			return items[id].extraDefense;
		}
		uint8_t getImbuementSlot() const {
			if (hasAttribute(ItemAttribute_t::IMBUEMENT_SLOT)) {
				return static_cast<uint8_t>(getInteger(ItemAttribute_t::IMBUEMENT_SLOT));
			}
			return items[id].imbuementSlot;
		}
		int32_t getSlotPosition() const {
			return items[id].slotPosition;
		}
		int8_t getHitChance() const {
			if (hasAttribute(ItemAttribute_t::HITCHANCE)) {
				return static_cast<int8_t>(getInteger(ItemAttribute_t::HITCHANCE));
			}
			return items[id].hitChance;
		}
		uint32_t getQuicklootAttr() const {
			if (hasAttribute(ItemAttribute_t::QUICKLOOTCONTAINER)) {
				return static_cast<uint32_t>(getInteger(ItemAttribute_t::QUICKLOOTCONTAINER));
			}
			return 0;
		}

		uint32_t getWorth() const;
		uint32_t getForgeSlivers() const;
		uint32_t getForgeCores() const;
		LightInfo getLightInfo() const;

		bool hasProperty(ItemProperty prop) const;
		bool isBlocking() const {
			return items[id].blockSolid;
		}
		bool isStackable() const {
			return items[id].stackable;
		}
		bool isStowable() const {
			return items[id].stackable && items[id].wareId > 0;
		}
		bool isAlwaysOnTop() const {
			return items[id].alwaysOnTopOrder != 0;
		}
		bool isGroundTile() const {
			return items[id].isGroundTile();
		}
		bool isMagicField() const {
			return items[id].isMagicField();
		}
		bool isWrapContainer() const {
			return items[id].wrapContainer;
		}
		bool isMoveable() const {
			return items[id].moveable;
		}
		bool isCorpse() const {
			return items[id].isCorpse;
		}
		bool isPickupable() const {
			return items[id].pickupable;
		}
		bool isMultiUse() const {
			return items[id].multiUse;
		}
		bool isHangable() const {
			return items[id].isHangable;
		}
		bool isRotatable() const {
			return items[id].rotatable && items[id].rotateTo;
		}
		bool isPodium() const {
			return items[id].isPodium;
		}
		bool isWrapable() const {
			return items[id].wrapable && items[id].wrapableTo;
		}
		bool hasWalkStack() const {
			return items[id].walkStack;
		}
		bool isQuiver() const {
			return items[id].isQuiver();
		}

		const std::string& getName() const {
			if (hasAttribute(ItemAttribute_t::NAME)) {
				return getString(ItemAttribute_t::NAME);
			}
			return items[id].name;
		}
		const std::string getPluralName() const {
			if (hasAttribute(ItemAttribute_t::PLURALNAME)) {
				return getString(ItemAttribute_t::PLURALNAME);
			}
			return items[id].getPluralName();
		}
		const std::string& getArticle() const {
			if (hasAttribute(ItemAttribute_t::ARTICLE)) {
				return getString(ItemAttribute_t::ARTICLE);
			}
			return items[id].article;
		}

		// get the number of items
		uint16_t getItemCount() const {
			return count;
		}
		void setItemCount(uint8_t n) {
			count = n;
		}

		static uint32_t countByType(const Item* item, int32_t subType) {
			if (subType == -1 || subType == item->getSubType()) {
				return item->getItemCount();
			}

			return 0;
		}

		void setDefaultSubtype();
		uint16_t getSubType() const;
		bool isItemStorable() const;
		void setSubType(uint16_t n);
		void addUniqueId(uint16_t uniqueId);

		void setDefaultDuration() {
			uint32_t duration = getDefaultDuration();
			if (duration != 0) {
				setDuration(duration);
			}
		}
		void setDuration(int32_t time) {
			setAttribute(ItemAttribute_t::DURATION, std::max<int32_t>(0, time));
		}
		uint32_t getDefaultDuration() const {
			return items[id].decayTime * 1000;
		}
		
		bool canDecay() const;

		virtual bool canRemove() const {
			return true;
		}
		virtual bool canTransform() const {
			return true;
		}
		virtual void onRemoved();
		virtual void onTradeEvent(TradeEvents_t, Player*) {}

		virtual void startDecaying();
		virtual void stopDecaying();

		bool getLoadedFromMap() const {
			return loadedFromMap;
		}

		void setLoadedFromMap(bool value) {
			loadedFromMap = value;
		}
		bool isCleanable() const {
			return !loadedFromMap && canRemove() && isPickupable() && !hasAttribute(ItemAttribute_t::UNIQUEID) && !hasAttribute(ItemAttribute_t::ACTIONID);
		}

		bool hasMarketAttributes();

		void incrementReferenceCounter() {
			++referenceCounter;
		}
		void decrementReferenceCounter() {
			if (--referenceCounter == 0) {
				delete this;
			}
		}

		Cylinder* getParent() const override {
			return parent;
		}
		void setParent(Cylinder* cylinder) override {
			parent = cylinder;
		}
		Cylinder* getTopParent();
		const Cylinder* getTopParent() const;
		Tile* getTile() override;
		const Tile* getTile() const override;
		bool isRemoved() const override {
			return !parent || parent->isRemoved();
		}

		bool isInsideDepot(bool includeInbox = false) const;

		/**
		 * @brief Get the Imbuement Info object
		 *
		 * @param slot
		 * @param imbuementInfo (Imbuement *imbuement, uint32_t duration = 0)
		 * @return true = duration is > 0 (info >> 8)
		 * @return false
		 */
		bool getImbuementInfo(uint8_t slot, ImbuementInfo *imbuementInfo) const;
		void addImbuement(uint8_t slot, uint16_t imbuementId, uint32_t duration);
		/**
		 * @brief Decay imbuement time duration, only use this for decay the imbuement time
		 * 
		 * @param slot Slot id to decay
		 * @param imbuementId Imbuement id to decay
		 * @param duration New duration
		 */
		void decayImbuementTime(uint8_t slot, uint16_t imbuementId, uint32_t duration) {
			return setImbuement(slot, imbuementId, duration);
		}
		void clearImbuement(uint8_t slot, uint16_t imbuementId) {
			return setImbuement(slot, imbuementId, 0);
		}
		bool hasImbuementType(ImbuementTypes_t imbuementType, uint16_t imbuementTier) {
			auto it = items[id].imbuementTypes.find(imbuementType);
			if (it != items[id].imbuementTypes.end()) {
				return (it->second >= imbuementTier);
			}
			return false;
		}
		bool hasImbuementCategoryId(uint16_t categoryId) const;
		bool hasImbuements() const {
			for (uint8_t slotid = 0; slotid < getImbuementSlot(); slotid++) {
				ImbuementInfo imbuementInfo;
				if (getImbuementInfo(slotid, &imbuementInfo)) {
					return true;
				}
			}

			return false;
		}

		double_t getDodgeChance() const {
			if (getTier() == 0) {
				return 0;
			}
			return (0.0307576 * getTier() * getTier()) + (0.440697 * getTier()) + 0.026;
		}

		double_t getFatalChance() const {
			if (getTier() == 0) {
				return 0;
			}
			return 0.5 * getTier() + 0.05 * ((getTier() - 1) * (getTier() - 1));
		}

		double_t getMomentumChance() const {
			if (getTier() == 0) {
				return 0;
			}
			return 2 * getTier() + 0.05 * ((getTier() - 1) * (getTier() - 1));
		}

		uint8_t getTier() const {
			if (!hasAttribute(ItemAttribute_t::TIER)) {
				return 0;
			}

			auto tier = static_cast<uint8_t>(getInteger(ItemAttribute_t::TIER));
			if (tier > g_configManager().getNumber(FORGE_MAX_ITEM_TIER)) {
				SPDLOG_ERROR("{} - Item {} have a wrong tier {}", __FUNCTION__, getName(), tier);
				return 0;
			}

			return tier;
		}
		void setTier(uint8_t tier) {
			auto configTier = g_configManager().getNumber(FORGE_MAX_ITEM_TIER);
			if (tier > configTier) {
				SPDLOG_ERROR("{} - It is not possible to set a tier higher than {}", __FUNCTION__, configTier);
				return;
			}

			if (items[id].upgradeClassification) {
				setAttribute(ItemAttribute_t::TIER, tier);
			}
		}
		uint8_t getClassification() const {
			return items[id].upgradeClassification;
		}

	protected:
		Cylinder* parent = nullptr;

		uint32_t referenceCounter = 0;

		uint16_t id;  // the same id as in ItemType
		uint8_t count = 1; // number of stacked items

		bool loadedFromMap = false;
		bool isLootTrackeable = false;
	private:
		void setImbuement(uint8_t slot, uint16_t imbuementId, uint32_t duration);
		//Don't add variables here, use the ItemAttribute class.
		std::string getWeightDescription(uint32_t weight) const;

		friend class Decay;
};

using ItemList = std::list<Item*>;
using ItemDeque = std::deque<Item*>;
using StashContainerList = std::vector<std::pair<Item*, uint32_t>>;

#endif  // SRC_ITEMS_ITEM_H_
