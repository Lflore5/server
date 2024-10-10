/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
 */

#pragma once

#include "enums/account_coins.hpp"
#include "enums/player_store_enums.hpp"

// Structs
struct OutfitIds {
	uint16_t maleId {};
	uint16_t femaleId {};
};

struct BannerInfo {
	std::string bannerName;
	uint32_t offerId {};
};

struct StoreHistoryDetail {
	StoreDetailType type {};
	uint32_t createdAt {};
	int32_t coinAmount {};
	int64_t totalPrice {};
	std::string description {};
	std::string playerName {};
};

struct RelatedOffer {
	uint32_t id {};
	uint32_t price {};
	uint16_t count {};
};

struct StoreHistory {
	time_t createdAt {};

	int32_t coinAmount {};
	CoinType coinType {};
	StoreDetailType type {};
	int64_t totalPrice {};

	std::string description {};
	std::string playerName {};
	bool fromMarket = false;
};

class Category;
class Offer;

class IOStore {
public:
	IOStore(const IOStore &) = delete;
	void operator=(const IOStore &) = delete;

	static IOStore &getInstance() {
		static IOStore instance;
		return instance;
	}

	bool loadFromXml();

	const std::map<std::string, OfferTypes_t> stringToOfferTypeMap = {
		{ "none", OfferTypes_t::NONE },
		{ "item", OfferTypes_t::ITEM },
		{ "stackable", OfferTypes_t::STACKABLE },
		{ "charges", OfferTypes_t::CHARGES },
		{ "looktype", OfferTypes_t::LOOKTYPE },
		{ "outfit", OfferTypes_t::OUTFIT },
		{ "mount", OfferTypes_t::MOUNT },
		{ "nameChange", OfferTypes_t::NAMECHANGE },
		{ "sexChange", OfferTypes_t::SEXCHANGE },
		{ "house", OfferTypes_t::HOUSE },
		{ "expBoost", OfferTypes_t::EXPBOOST },
		{ "preySlot", OfferTypes_t::PREYSLOT },
		{ "preyBonus", OfferTypes_t::PREYBONUS },
		{ "temple", OfferTypes_t::TEMPLE },
		{ "blessings", OfferTypes_t::BLESSINGS },
		{ "allblessings", OfferTypes_t::ALLBLESSINGS },
		{ "premium", OfferTypes_t::PREMIUM },
		{ "pouch", OfferTypes_t::POUCH },
		{ "instantReward", OfferTypes_t::INSTANT_REWARD_ACCESS },
		{ "charmExpansion", OfferTypes_t::CHARM_EXPANSION },
		{ "huntingSlot", OfferTypes_t::HUNTINGSLOT },
		{ "hireling", OfferTypes_t::HIRELING },
		{ "hirelingNameChange", OfferTypes_t::HIRELING_NAMECHANGE },
		{ "hirelingSexChange", OfferTypes_t::HIRELING_SEXCHANGE },
		{ "hirelingSkill", OfferTypes_t::HIRELING_SKILL },
		{ "hirelingOutfit", OfferTypes_t::HIRELING_OUTFIT }
	};

	const std::map<OfferTypes_t, uint16_t> offersDisableIndex = {
		{ OfferTypes_t::OUTFIT, 0 },
		{ OfferTypes_t::MOUNT, 1 },
		{ OfferTypes_t::EXPBOOST, 2 },
		{ OfferTypes_t::PREYSLOT, 3 },
		{ OfferTypes_t::HUNTINGSLOT, 3 },
		{ OfferTypes_t::PREYBONUS, 4 },
		{ OfferTypes_t::BLESSINGS, 5 },
		{ OfferTypes_t::ALLBLESSINGS, 6 },
		{ OfferTypes_t::POUCH, 7 },
		{ OfferTypes_t::INSTANT_REWARD_ACCESS, 8 },
		{ OfferTypes_t::CHARM_EXPANSION, 9 }
	};

	const std::map<std::string, States_t> stringToOfferStateMap = {
		{ "none", States_t::NONE }, { "new", States_t::NEW }, { "sale", States_t::SALE }, { "timed", States_t::TIMED }
	};

	std::vector<Category> getCategoryVector() const;
	const Category* getCategoryByName(std::string categoryName) const;
	const Category* getSubCategoryByName(std::string subCategoryName) const;
	const Offer* getOfferById(uint32_t offerId) const;

	std::vector<BannerInfo> getBannersVector() const;
	std::vector<uint32_t> getHomeOffersVector() const;
	uint32_t getBannerDelay() const;
	void setBannerDelay(uint8_t delay);

	const Category* findCategory(std::string categoryName);

	const std::vector<std::string> getOffersDisableReasonVector();

	std::vector<Offer> getOffersContainingSubstring(const std::string &searchString);
	Offer* getOfferByName(const std::string &searchString);

	static StoreHistoryDetail getStoreHistoryDetail(const std::string &playerName, uint32_t createdAt, bool hasDetail);

private:
	IOStore() = default;
	~IOStore() = default;

	// Home
	std::vector<BannerInfo> banners;
	uint8_t bannerDelay = 5;
	std::vector<uint32_t> homeOffers;

	std::vector<Category> categoryVector;
	std::vector<Category> subCategoryVector;
	std::map<uint32_t, Offer> offersMap;

	bool loadOfferFromXml(Category* category, pugi::xml_node offer);
	bool loadStoreHome(pugi::xml_node homeNode);

	void addCategory(Category newCategory);
	void addOffer(uint32_t offerId, Offer offer);

	std::vector<std::string> offersDisableReason = {
		"You already own this outfit.",
		"You already own this mount.",
		"You can't buy XP Boost for today.",
		"You already have 3 slots released.",
		"You already have maximum of prey wildcards.",
		"You reached the maximum amount for this blessing.",
		"You reached the maximum amount for some blessing.",
		"You already have a pouch.",
		"You already have maximum of reward tokens.",
		"You already have charm expansion."
	};
};

class Category { // We're gonna use the same class for Category and Subcategory
public:
	Category(const std::string& name, const std::string& icon, bool rookgaard, States_t state = States_t::NONE)
	: categoryName(name), categoryIcon(icon), canRookgaardAccess(rookgaard), categoryState(state) { }

	std::string getCategoryName() const {
		return categoryName;
	}
	std::string getCategoryIcon() const {
		return categoryIcon;
	}
	States_t getCategoryState() const {
		return categoryState;
	}
	bool getRookgaardAccess() const {
		return canRookgaardAccess;
	}
	bool isSpecialCategory() const {
		return specialCategory;
	}

	const Category* getFirstSubCategory() const;
	std::vector<Category> getSubCategoriesVector() const;
	std::vector<const Offer*> getOffersVector() const;

private:
	friend class IOStore;

	std::string categoryName;
	std::string categoryIcon;
	bool canRookgaardAccess;
	States_t categoryState = States_t::NONE;
	bool specialCategory = false;

	// Used when Category class is a Category
	std::vector<Category> subCategories;

	// Used when Category class is a Subcategory or a "Special Category"
	std::vector<const Offer*> offers;

	void addSubCategory(Category newSubCategory);
	void addOffer(const Offer* newOffer);
	void setSpecialCategory(bool state) {
		specialCategory = state;
	}
};

class Offer {
public:
	Offer(std::string parentName, std::string name, std::string icon, uint32_t id, uint32_t price, OfferTypes_t type, States_t state, uint16_t count, uint16_t duration, CoinType coin, std::string description, OutfitIds outfitIds, bool movable, std::vector<RelatedOffer> relatedOffers) :
		parentName(parentName), offerName(name), offerIcon(icon), offerId(id), offerPrice(price), offerType(type), offerState(state), offerCount(count), validUntil(duration), coinType(coin), offerDescription(description), outfitId(outfitIds), movable(movable), relatedOffers(relatedOffers) { }

	std::string getOfferName() const {
		return offerName;
	}
	std::string getOfferIcon() const {
		return offerIcon;
	}
	uint32_t getOfferId() const {
		return offerId;
	}
	uint32_t getOfferPrice() const {
		return offerPrice;
	}
	OfferTypes_t getOfferType() const {
		return offerType;
	}
	States_t getOfferState() const {
		return offerState;
	}
	uint16_t getOfferCount() const {
		return offerCount;
	}
	uint16_t getValidUntil() const {
		return validUntil;
	}
	CoinType getCoinType() const {
		return coinType;
	}
	std::string getOfferDescription() const {
		return offerDescription;
	}
	OutfitIds getOutfitIds() const {
		return outfitId;
	}
	std::string getParentName() const {
		return parentName;
	}
	ConverType_t getConverType() const;
	bool getUseConfigure() const;
	bool isMovable() const {
		return movable;
	}

	const std::vector<RelatedOffer> &getRelatedOffersVector() const;
	void addRelatedOffer(const RelatedOffer &relatedOffer);

private:
	// Mandatory
	std::string offerName;
	uint32_t offerId; // Any identifier (itemId, mountId, ...)
	uint32_t offerPrice;
	OfferTypes_t offerType = OfferTypes_t::NONE;

	// Optional
	std::string offerIcon;
	States_t offerState = States_t::NONE;
	uint16_t offerCount = 0; // Or charges
	uint16_t validUntil;
	CoinType coinType = CoinType::Normal;
	std::string offerDescription;
	OutfitIds outfitId;
	bool movable;

	// Internal
	std::string parentName;
	std::vector<RelatedOffer> relatedOffers;
};

constexpr auto g_ioStore = &IOStore::getInstance;
