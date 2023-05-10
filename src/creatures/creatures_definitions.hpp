/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_CREATURES_CREATURES_DEFINITIONS_HPP_
#define SRC_CREATURES_CREATURES_DEFINITIONS_HPP_

// Enum

enum SkillsId_t {
	SKILLVALUE_LEVEL = 0,
	SKILLVALUE_TRIES = 1,
	SKILLVALUE_PERCENT = 2,
};

enum MatrixOperation_t {
	MATRIXOPERATION_COPY,
	MATRIXOPERATION_MIRROR,
	MATRIXOPERATION_FLIP,
	MATRIXOPERATION_ROTATE90,
	MATRIXOPERATION_ROTATE180,
	MATRIXOPERATION_ROTATE270,
};

enum ConditionAttr_t {
	CONDITIONATTR_TYPE = 1,
	CONDITIONATTR_ID,
	CONDITIONATTR_TICKS,
	CONDITIONATTR_HEALTHTICKS,
	CONDITIONATTR_HEALTHGAIN,
	CONDITIONATTR_MANATICKS,
	CONDITIONATTR_MANAGAIN,
	CONDITIONATTR_DELAYED,
	CONDITIONATTR_OWNER,
	CONDITIONATTR_INTERVALDATA,
	CONDITIONATTR_SPEEDDELTA,
	CONDITIONATTR_FORMULA_MINA,
	CONDITIONATTR_FORMULA_MINB,
	CONDITIONATTR_FORMULA_MAXA,
	CONDITIONATTR_FORMULA_MAXB,
	CONDITIONATTR_LIGHTCOLOR,
	CONDITIONATTR_LIGHTLEVEL,
	CONDITIONATTR_LIGHTTICKS,
	CONDITIONATTR_LIGHTINTERVAL,
	CONDITIONATTR_SOULTICKS,
	CONDITIONATTR_SOULGAIN,
	CONDITIONATTR_SKILLS,
	CONDITIONATTR_STATS,
	CONDITIONATTR_BUFFS,
	CONDITIONATTR_OUTFIT,
	CONDITIONATTR_PERIODDAMAGE,
	CONDITIONATTR_ISBUFF,
	CONDITIONATTR_SUBID,
	CONDITIONATTR_MANASHIELD,
	CONDITIONATTR_ADDSOUND,
	CONDITIONATTR_TICKSOUND,

	// reserved for serialization
	CONDITIONATTR_END = 254,
};

enum ConditionType_t {
	CONDITION_NONE,

	CONDITION_POISON = 1 << 0,
	CONDITION_FIRE = 1 << 1,
	CONDITION_ENERGY = 1 << 2,
	CONDITION_BLEEDING = 1 << 3,
	CONDITION_HASTE = 1 << 4,
	CONDITION_PARALYZE = 1 << 5,
	CONDITION_OUTFIT = 1 << 6,
	CONDITION_INVISIBLE = 1 << 7,
	CONDITION_LIGHT = 1 << 8,
	CONDITION_MANASHIELD = 1 << 9,
	CONDITION_INFIGHT = 1 << 10,
	CONDITION_DRUNK = 1 << 11,
	CONDITION_EXHAUST = 1 << 12, // unused
	CONDITION_REGENERATION = 1 << 13,
	CONDITION_SOUL = 1 << 14,
	CONDITION_DROWN = 1 << 15,
	CONDITION_MUTED = 1 << 16,
	CONDITION_CHANNELMUTEDTICKS = 1 << 17,
	CONDITION_YELLTICKS = 1 << 18,
	CONDITION_ATTRIBUTES = 1 << 19,
	CONDITION_FREEZING = 1 << 20,
	CONDITION_DAZZLED = 1 << 21,
	CONDITION_CURSED = 1 << 22,
	CONDITION_EXHAUST_COMBAT = 1 << 23, // unused
	CONDITION_EXHAUST_HEAL = 1 << 24, // unused
	CONDITION_PACIFIED = 1 << 25,
	CONDITION_SPELLCOOLDOWN = 1 << 26,
	CONDITION_SPELLGROUPCOOLDOWN = 1 << 27,
	CONDITION_ROOTED = 1 << 28,
};

enum ConditionParam_t {
	CONDITION_PARAM_OWNER = 1,
	CONDITION_PARAM_TICKS = 2,
	// CONDITION_PARAM_OUTFIT = 3,
	CONDITION_PARAM_HEALTHGAIN = 4,
	CONDITION_PARAM_HEALTHTICKS = 5,
	CONDITION_PARAM_MANAGAIN = 6,
	CONDITION_PARAM_MANATICKS = 7,
	CONDITION_PARAM_DELAYED = 8,
	CONDITION_PARAM_SPEED = 9,
	CONDITION_PARAM_LIGHT_LEVEL = 10,
	CONDITION_PARAM_LIGHT_COLOR = 11,
	CONDITION_PARAM_SOULGAIN = 12,
	CONDITION_PARAM_SOULTICKS = 13,
	CONDITION_PARAM_MINVALUE = 14,
	CONDITION_PARAM_MAXVALUE = 15,
	CONDITION_PARAM_STARTVALUE = 16,
	CONDITION_PARAM_TICKINTERVAL = 17,
	CONDITION_PARAM_FORCEUPDATE = 18,
	CONDITION_PARAM_SKILL_MELEE = 19,
	CONDITION_PARAM_SKILL_FIST = 20,
	CONDITION_PARAM_SKILL_CLUB = 21,
	CONDITION_PARAM_SKILL_SWORD = 22,
	CONDITION_PARAM_SKILL_AXE = 23,
	CONDITION_PARAM_SKILL_DISTANCE = 24,
	CONDITION_PARAM_SKILL_SHIELD = 25,
	CONDITION_PARAM_SKILL_FISHING = 26,
	CONDITION_PARAM_STAT_MAXHITPOINTS = 27,
	CONDITION_PARAM_STAT_MAXMANAPOINTS = 28,
	// CONDITION_PARAM_STAT_SOULPOINTS = 29,
	CONDITION_PARAM_STAT_MAGICPOINTS = 30,
	CONDITION_PARAM_STAT_MAXHITPOINTSPERCENT = 31,
	CONDITION_PARAM_STAT_MAXMANAPOINTSPERCENT = 32,
	// CONDITION_PARAM_STAT_SOULPOINTSPERCENT = 33,
	CONDITION_PARAM_STAT_MAGICPOINTSPERCENT = 34,
	CONDITION_PARAM_PERIODICDAMAGE = 35,
	CONDITION_PARAM_SKILL_MELEEPERCENT = 36,
	CONDITION_PARAM_SKILL_FISTPERCENT = 37,
	CONDITION_PARAM_SKILL_CLUBPERCENT = 38,
	CONDITION_PARAM_SKILL_SWORDPERCENT = 39,
	CONDITION_PARAM_SKILL_AXEPERCENT = 40,
	CONDITION_PARAM_SKILL_DISTANCEPERCENT = 41,
	CONDITION_PARAM_SKILL_SHIELDPERCENT = 42,
	CONDITION_PARAM_SKILL_FISHINGPERCENT = 43,
	CONDITION_PARAM_BUFF_SPELL = 44,
	CONDITION_PARAM_SUBID = 45,
	CONDITION_PARAM_FIELD = 46,
	CONDITION_PARAM_SKILL_CRITICAL_HIT_CHANCE = 47,
	CONDITION_PARAM_SKILL_CRITICAL_HIT_DAMAGE = 48,
	CONDITION_PARAM_SKILL_LIFE_LEECH_CHANCE = 49,
	CONDITION_PARAM_SKILL_LIFE_LEECH_AMOUNT = 50,
	CONDITION_PARAM_SKILL_MANA_LEECH_CHANCE = 51,
	CONDITION_PARAM_SKILL_MANA_LEECH_AMOUNT = 52,
	CONDITION_PARAM_DISABLE_DEFENSE = 53,
	CONDITION_PARAM_STAT_CAPACITYPERCENT = 54,
	CONDITION_PARAM_MANASHIELD = 55,
	CONDITION_PARAM_BUFF_DAMAGEDEALT = 56,
	CONDITION_PARAM_BUFF_DAMAGERECEIVED = 57,
	CONDITION_PARAM_SOUND_TICK = 58,
	CONDITION_PARAM_SOUND_ADD = 59,
};

enum stats_t {
	STAT_MAXHITPOINTS,
	STAT_MAXMANAPOINTS,
	STAT_SOULPOINTS, // unused
	STAT_MAGICPOINTS,
	STAT_CAPACITY,

	STAT_FIRST = STAT_MAXHITPOINTS,
	STAT_LAST = STAT_CAPACITY
};

enum buffs_t {
	BUFF_DAMAGEDEALT,
	BUFF_DAMAGERECEIVED,

	BUFF_FIRST = BUFF_DAMAGEDEALT,
	BUFF_LAST = BUFF_DAMAGERECEIVED,
};

enum formulaType_t {
	COMBAT_FORMULA_UNDEFINED,
	COMBAT_FORMULA_LEVELMAGIC,
	COMBAT_FORMULA_SKILL,
	COMBAT_FORMULA_DAMAGE,
};

enum CombatParam_t {
	COMBAT_PARAM_TYPE,
	COMBAT_PARAM_EFFECT,
	COMBAT_PARAM_DISTANCEEFFECT,
	COMBAT_PARAM_BLOCKSHIELD,
	COMBAT_PARAM_BLOCKARMOR,
	COMBAT_PARAM_TARGETCASTERORTOPMOST,
	COMBAT_PARAM_CREATEITEM,
	COMBAT_PARAM_AGGRESSIVE,
	COMBAT_PARAM_DISPEL,
	COMBAT_PARAM_USECHARGES,
	COMBAT_PARAM_CASTSOUND,
	COMBAT_PARAM_IMPACTSOUND,
};

enum CombatOrigin {
	ORIGIN_NONE,
	ORIGIN_CONDITION,
	ORIGIN_SPELL,
	ORIGIN_MELEE,
	ORIGIN_RANGED,
	ORIGIN_REFLECT,
};

enum CallBackParam_t {
	CALLBACK_PARAM_LEVELMAGICVALUE,
	CALLBACK_PARAM_SKILLVALUE,
	CALLBACK_PARAM_TARGETTILE,
	CALLBACK_PARAM_TARGETCREATURE,
};

enum charm_t {
	CHARM_UNDEFINED = 0,
	CHARM_OFFENSIVE = 1,
	CHARM_DEFENSIVE = 2,
	CHARM_PASSIVE = 3,
};

enum SpeechBubble_t {
	SPEECHBUBBLE_NONE = 0,
	SPEECHBUBBLE_NORMAL = 1,
	SPEECHBUBBLE_TRADE = 2,
	SPEECHBUBBLE_QUEST = 3,
	SPEECHBUBBLE_QUESTTRADER = 4,
	SPEECHBUBBLE_HIRELING = 7,
};

enum MarketAction_t {
	MARKETACTION_BUY = 0,
	MARKETACTION_SELL = 1,
};

enum MarketRequest_t {
	MARKETREQUEST_OWN_HISTORY = 1,
	MARKETREQUEST_OWN_OFFERS = 2,
	MARKETREQUEST_ITEM_BROWSE = 3,
	MARKETREQUEST_OWN_OFFERS_OLD = 0xFFFE,
	MARKETREQUEST_OWN_HISTORY_OLD = 0xFFFF,
};

enum MarketOfferState_t {
	OFFERSTATE_ACTIVE = 0,
	OFFERSTATE_CANCELLED = 1,
	OFFERSTATE_EXPIRED = 2,
	OFFERSTATE_ACCEPTED = 3,

	OFFERSTATE_ACCEPTEDEX = 255,
};

enum ObjectCategory_t {
	OBJECTCATEGORY_NONE = 0,
	OBJECTCATEGORY_ARMORS = 1,
	OBJECTCATEGORY_NECKLACES = 2,
	OBJECTCATEGORY_BOOTS = 3,
	OBJECTCATEGORY_CONTAINERS = 4,
	OBJECTCATEGORY_DECORATION = 5,
	OBJECTCATEGORY_FOOD = 6,
	OBJECTCATEGORY_HELMETS = 7,
	OBJECTCATEGORY_LEGS = 8,
	OBJECTCATEGORY_OTHERS = 9,
	OBJECTCATEGORY_POTIONS = 10,
	OBJECTCATEGORY_RINGS = 11,
	OBJECTCATEGORY_RUNES = 12,
	OBJECTCATEGORY_SHIELDS = 13,
	OBJECTCATEGORY_TOOLS = 14,
	OBJECTCATEGORY_VALUABLES = 15,
	OBJECTCATEGORY_AMMO = 16,
	OBJECTCATEGORY_AXES = 17,
	OBJECTCATEGORY_CLUBS = 18,
	OBJECTCATEGORY_DISTANCEWEAPONS = 19,
	OBJECTCATEGORY_SWORDS = 20,
	OBJECTCATEGORY_WANDS = 21,
	OBJECTCATEGORY_PREMIUMSCROLLS = 22, // not used in quickloot
	OBJECTCATEGORY_TIBIACOINS = 23, // not used in quickloot
	OBJECTCATEGORY_CREATUREPRODUCTS = 24,
	OBJECTCATEGORY_STASHRETRIEVE = 27,
	OBJECTCATEGORY_GOLD = 30,
	OBJECTCATEGORY_DEFAULT = 31, // unassigned loot

	OBJECTCATEGORY_FIRST = OBJECTCATEGORY_ARMORS,
	OBJECTCATEGORY_LAST = OBJECTCATEGORY_DEFAULT,
};

enum RespawnPeriod_t {
	RESPAWNPERIOD_ALL,
	RESPAWNPERIOD_DAY,
	RESPAWNPERIOD_NIGHT
};

enum Slots_t : uint8_t {
	CONST_SLOT_WHEREEVER = 0,
	CONST_SLOT_HEAD = 1,
	CONST_SLOT_NECKLACE = 2,
	CONST_SLOT_BACKPACK = 3,
	CONST_SLOT_ARMOR = 4,
	CONST_SLOT_RIGHT = 5,
	CONST_SLOT_LEFT = 6,
	CONST_SLOT_LEGS = 7,
	CONST_SLOT_FEET = 8,
	CONST_SLOT_RING = 9,
	CONST_SLOT_AMMO = 10,
	CONST_SLOT_STORE_INBOX = 11,

	CONST_SLOT_FIRST = CONST_SLOT_HEAD,
	CONST_SLOT_LAST = CONST_SLOT_STORE_INBOX,
};

enum charmRune_t : int8_t {
	CHARM_NONE = -1,
	CHARM_WOUND = 0,
	CHARM_ENFLAME = 1,
	CHARM_POISON = 2,
	CHARM_FREEZE = 3,
	CHARM_ZAP = 4,
	CHARM_CURSE = 5,
	CHARM_CRIPPLE = 6,
	CHARM_PARRY = 7,
	CHARM_DODGE = 8,
	CHARM_ADRENALINE = 9,
	CHARM_NUMB = 10,
	CHARM_CLEANSE = 11,
	CHARM_BLESS = 12,
	CHARM_SCAVENGE = 13,
	CHARM_GUT = 14,
	CHARM_LOW = 15,
	CHARM_DIVINE = 16,
	CHARM_VAMP = 17,
	CHARM_VOID = 18,

	CHARM_LAST = CHARM_VOID,
};

enum ConditionId_t : int8_t {
	CONDITIONID_DEFAULT = -1,
	CONDITIONID_COMBAT,
	CONDITIONID_HEAD,
	CONDITIONID_NECKLACE,
	CONDITIONID_BACKPACK,
	CONDITIONID_ARMOR,
	CONDITIONID_RIGHT,
	CONDITIONID_LEFT,
	CONDITIONID_LEGS,
	CONDITIONID_FEET,
	CONDITIONID_RING,
	CONDITIONID_AMMO,
};

enum PlayerSex_t : uint8_t {
	PLAYERSEX_FEMALE = 0,
	PLAYERSEX_MALE = 1,

	PLAYERSEX_LAST = PLAYERSEX_MALE
};

enum skills_t : int8_t {
	SKILL_NONE = -1,
	SKILL_FIST = 0,
	SKILL_CLUB = 1,
	SKILL_SWORD = 2,
	SKILL_AXE = 3,
	SKILL_DISTANCE = 4,
	SKILL_SHIELD = 5,
	SKILL_FISHING = 6,
	SKILL_CRITICAL_HIT_CHANCE = 7,
	SKILL_CRITICAL_HIT_DAMAGE = 8,
	SKILL_LIFE_LEECH_CHANCE = 9,
	SKILL_LIFE_LEECH_AMOUNT = 10,
	SKILL_MANA_LEECH_CHANCE = 11,
	SKILL_MANA_LEECH_AMOUNT = 12,

	SKILL_MAGLEVEL = 13,
	SKILL_LEVEL = 14,

	SKILL_FIRST = SKILL_FIST,
	SKILL_LAST = SKILL_MANA_LEECH_AMOUNT
};

enum CreatureType_t : uint8_t {
	CREATURETYPE_PLAYER = 0,
	CREATURETYPE_MONSTER = 1,
	CREATURETYPE_NPC = 2,
	CREATURETYPE_SUMMON_PLAYER = 3,
	CREATURETYPE_SUMMON_OTHERS = 4,
	CREATURETYPE_HIDDEN = 5,
};

enum SpellType_t : uint8_t {
	SPELL_UNDEFINED = 0,
	SPELL_INSTANT = 1,
	SPELL_RUNE = 2,
};

enum RaceType_t : uint8_t {
	RACE_NONE,
	RACE_VENOM,
	RACE_BLOOD,
	RACE_UNDEAD,
	RACE_FIRE,
	RACE_ENERGY,
	RACE_INK,
};

enum BlockType_t : uint8_t {
	BLOCK_NONE,
	BLOCK_DEFENSE,
	BLOCK_ARMOR,
	BLOCK_IMMUNITY,
	BLOCK_DODGE
};

enum BestiaryType_t : uint8_t {
	BESTY_RACE_NONE = 0,

	BESTY_RACE_AMPHIBIC = 1,
	BESTY_RACE_AQUATIC = 2,
	BESTY_RACE_BIRD = 3,
	BESTY_RACE_CONSTRUCT = 4,
	BESTY_RACE_DEMON = 5,
	BESTY_RACE_DRAGON = 6,
	BESTY_RACE_ELEMENTAL = 7,
	BESTY_RACE_EXTRA_DIMENSIONAL = 8,
	BESTY_RACE_FEY = 9,
	BESTY_RACE_GIANT = 10,
	BESTY_RACE_HUMAN = 11,
	BESTY_RACE_HUMANOID = 12,
	BESTY_RACE_LYCANTHROPE = 13,
	BESTY_RACE_MAGICAL = 14,
	BESTY_RACE_MAMMAL = 15,
	BESTY_RACE_PLANT = 16,
	BESTY_RACE_REPTILE = 17,
	BESTY_RACE_SLIME = 18,
	BESTY_RACE_UNDEAD = 19,
	BESTY_RACE_VERMIN = 20,

	BESTY_RACE_FIRST = BESTY_RACE_AMPHIBIC,
	BESTY_RACE_LAST = BESTY_RACE_VERMIN,
};

enum MonstersEvent_t : uint8_t {
	MONSTERS_EVENT_NONE = 0,
	MONSTERS_EVENT_THINK = 1,
	MONSTERS_EVENT_APPEAR = 2,
	MONSTERS_EVENT_DISAPPEAR = 3,
	MONSTERS_EVENT_MOVE = 4,
	MONSTERS_EVENT_SAY = 5,
};

enum NpcsEvent_t : uint8_t {
	NPCS_EVENT_NONE = 0,
	NPCS_EVENT_THINK = 1,
	NPCS_EVENT_APPEAR = 2,
	NPCS_EVENT_DISAPPEAR = 3,
	NPCS_EVENT_MOVE = 4,
	NPCS_EVENT_SAY = 5,
	NPCS_EVENT_PLAYER_BUY = 6,
	NPCS_EVENT_PLAYER_SELL = 7,
	NPCS_EVENT_PLAYER_CHECK_ITEM = 8,
	NPCS_EVENT_PLAYER_CLOSE_CHANNEL = 9
};

enum DailyRewardBonus : uint8_t {
	DAILY_REWARD_FIRST = 2,

	DAILY_REWARD_HP_REGENERATION = 2,
	DAILY_REWARD_MP_REGENERATION = 3,
	DAILY_REWARD_STAMINA_REGENERATION = 4,
	DAILY_REWARD_DOUBLE_HP_REGENERATION = 5,
	DAILY_REWARD_DOUBLE_MP_REGENERATION = 6,
	DAILY_REWARD_SOUL_REGENERATION = 7,

	DAILY_REWARD_LAST = 7,
};

enum DailyRewardStatus : uint8_t {
	DAILY_REWARD_COLLECTED = 0,
	DAILY_REWARD_NOTCOLLECTED = 1,
	DAILY_REWARD_NOTAVAILABLE = 2
};

enum class ForgeClassifications_t : uint8_t {
	FORGE_NORMAL_MONSTER = 0,
	FORGE_INFLUENCED_MONSTER = 1,
	FORGE_FIENDISH_MONSTER = 2,
};

enum OperatingSystem_t : uint8_t {
	CLIENTOS_NONE = 0,

	CLIENTOS_LINUX = 1,
	CLIENTOS_WINDOWS = 2,
	CLIENTOS_FLASH = 3,
	CLIENTOS_NEW_LINUX = 4,
	CLIENTOS_NEW_WINDOWS = 5,
	CLIENTOS_NEW_MAC = 6,

	CLIENTOS_OTCLIENT_LINUX = 10,
	CLIENTOS_OTCLIENT_WINDOWS = 11,
	CLIENTOS_OTCLIENT_MAC = 12,
};

enum SpellGroup_t : uint8_t {
	SPELLGROUP_NONE = 0,
	SPELLGROUP_ATTACK = 1,
	SPELLGROUP_HEALING = 2,
	SPELLGROUP_SUPPORT = 3,
	SPELLGROUP_SPECIAL = 4,
	SPELLGROUP_CONJURE = 5, // Deprecated
	SPELLGROUP_CRIPPLING = 6,
	SPELLGROUP_FOCUS = 7,
	SPELLGROUP_ULTIMATESTRIKES = 8,
};

enum ChannelEvent_t : uint8_t {
	CHANNELEVENT_JOIN = 0,
	CHANNELEVENT_LEAVE = 1,
	CHANNELEVENT_INVITE = 2,
	CHANNELEVENT_EXCLUDE = 3,
};

enum VipStatus_t : uint8_t {
	VIPSTATUS_OFFLINE = 0,
	VIPSTATUS_ONLINE = 1,
	VIPSTATUS_PENDING = 2,
	VIPSTATUS_TRAINING = 3
};

enum Vocation_t : uint16_t {
	VOCATION_NONE = 0,
	VOCATION_SORCERER = 1,
	VOCATION_DRUID = 2,
	VOCATION_PALADIN = 3,
	VOCATION_KNIGHT = 4,
	VOCATION_MASTER_SORCERER = 5,
	VOCATION_ELDER_DRUID = 6,
	VOCATION_ROYAL_PALADIN = 7,
	VOCATION_ELITE_KNIGHT = 8,
	VOCATION_LAST = VOCATION_ELITE_KNIGHT
};

enum FightMode_t : uint8_t {
	FIGHTMODE_ATTACK = 1,
	FIGHTMODE_BALANCED = 2,
	FIGHTMODE_DEFENSE = 3,
};

enum PvpMode_t : uint8_t {
	PVP_MODE_DOVE = 0,
	PVP_MODE_WHITE_HAND = 1,
	PVP_MODE_YELLOW_HAND = 2,
	PVP_MODE_RED_FIST = 3,
};

enum TradeState_t : uint8_t {
	TRADE_NONE,
	TRADE_INITIATED,
	TRADE_ACCEPT,
	TRADE_ACKNOWLEDGE,
	TRADE_TRANSFER,
};

enum CombatType_t : uint16_t {
	COMBAT_NONE = 0,

	COMBAT_PHYSICALDAMAGE = 1 << 0,
	COMBAT_ENERGYDAMAGE = 1 << 1,
	COMBAT_EARTHDAMAGE = 1 << 2,
	COMBAT_FIREDAMAGE = 1 << 3,
	COMBAT_UNDEFINEDDAMAGE = 1 << 4,
	COMBAT_LIFEDRAIN = 1 << 5,
	COMBAT_MANADRAIN = 1 << 6,
	COMBAT_HEALING = 1 << 7,
	COMBAT_DROWNDAMAGE = 1 << 8,
	COMBAT_ICEDAMAGE = 1 << 9,
	COMBAT_HOLYDAMAGE = 1 << 10,
	COMBAT_DEATHDAMAGE = 1 << 11,

	COMBAT_COUNT = 12
};

enum PlayerAsyncOngoingTaskFlags : uint64_t {
	PlayerAsyncTask_Highscore = 1 << 0,
	PlayerAsyncTask_RecentDeaths = 1 << 1,
	PlayerAsyncTask_RecentPvPKills = 1 << 2
};

enum PartyAnalyzer_t : uint8_t {
	MARKET_PRICE = 0,
	LEADER_PRICE = 1
};

enum SoundEffect_t : uint16_t {
	SILENCE = 0,
	HUMAN_CLOSE_ATK_FIST = 1,
	MONSTER_CLOSE_ATK_FIST = 2,
	MELEE_ATK_SWORD = 3,
	MELEE_ATK_CLUB = 4,
	MELEE_ATK_AXE = 5,
	DIST_ATK_BOW = 6,
	DIST_ATK_CROSSBOW = 7,
	DIST_ATK_THROW = 8,
	MAGICAL_RANGE_ATK = 9,
	SPELL_OR_RUNE = 10, // Only secondary
	OTHER = 11, // Only secondary
	PHYSICAL_RANGE_MISS = 12,
	DIST_ATK_BOW_SHOT = 13,
	DIST_ATK_CROSSBOW_SHOT = 14,
	DIST_ATK_THROW_SHOT = 15,
	DIST_ATK_ROD_SHOT = 16,
	DIST_ATK_WAND_SHOT = 17,
	BURST_ARROW_EFFECT = 18,
	DIAMOND_ARROW_EFFECT = 19,
	NO_DAMAGE = 20,
	MONSTER_MELEE_ATK_FIST = 100,
	MONSTER_MELEE_ATK_CLAW = 101,
	MONSTER_MELEE_ATK_BITE = 102,
	MONSTER_MELEE_ATK_RIP = 103,
	MONSTER_MELEE_ATK_ACID = 104,
	MONSTER_MELEE_ATK_MAGIC = 105,
	MONSTER_MELEE_ATK_ETHEREAL = 106,
	MONSTER_MELEE_ATK_CONSTRUCT = 107,
	SPELL_LIGHT_HEALING = 1001,
	SPELL_INTENSE_HEALING = 1002,
	SPELL_ULTIMATE_HEALING = 1003,
	SPELL_INTENSE_HEALING_RUNE = 1004,
	SPELL_ULTIMATE_HEALING_RUNE = 1005,
	SPELL_HASTE = 1006,
	SPELL_LIGHT_MAGIC_MISSILE_RUNE = 1007,
	SPELL_HEAVY_MAGIC_MISSILE_RUNE = 1008,
	SPELL_SUMMON_CREATURE = 1009,
	SPELL_LIGHT = 1010,
	SPELL_GREAT_LIGHT = 1011,
	SPELL_CONVINCE_CREATURE_RUNE = 1012,
	SPELL_ENERGY_WAVE = 1013,
	SPELL_CHAMELEON_RUNE = 1014,
	SPELL_FIREBALL_RUNE = 1015,
	SPELL_GREAT_FIREBALL_RUNE = 1016,
	SPELL_FIRE_BOMB_RUNE = 1017,
	SPELL_EXPLOSION_RUNE = 1018,
	SPELL_FIRE_WAVE = 1019,
	SPELL_FIND_PERSON = 1020,
	SPELL_SUDDENDEATH_RUNE = 1021,
	SPELL_ENERGY_BEAM = 1022,
	SPELL_GREAT_ENERGY_BEAM = 1023,
	SPELL_HELL_SCORE = 1024,
	SPELL_FIRE_FIELD_RUNE = 1025,
	SPELL_POISON_FIELD_RUNE = 1026,
	SPELL_ENERGY_FIELD_RUNE = 1027,
	SPELL_FIRE_WALL_RUNE = 1028,
	SPELL_CURE_POISON = 1029,
	SPELL_DESTROY_FIELD_RUNE = 1030,
	SPELL_CURE_POISON_RUNE = 1031,
	SPELL_POISON_WALL_RUNE = 1032,
	SPELL_ENERGY_WALL_RUNE = 1033,
	SPELL_SALVATION = 1036,
	SPELL_CREATURE_ILLUSION = 1038,
	SPELL_STRONG_HASTE = 1039,
	SPELL_FOOD = 1042,
	SPELL_STRONG_ICE_WAVE = 1043,
	SPELL_MAGIC_SHIELD = 1044,
	SPELL_INVISIBLE = 1045,
	SPELL_CONJURE_EXPLOSIVE_ARROW = 1049,
	SPELL_SOUL_FIRE_RUNE = 1050,
	SPELL_CONJURE_ARROW = 1051,
	SPELL_PARALYSE_RUNE = 1054,
	SPELL_ENERGY_BOMB_RUNE = 1055,
	SPELL_WRATH_OF_NATURE = 1056,
	SPELL_STRONG_ETHEREAL_SPEAR = 1057,
	SPELL_FRONT_SWEEP = 1059,
	SPELL_BRUTAL_STRIKE = 1061,
	SPELL_ANNIHILATION = 1062,
	SPELL_INVITE_GUESTS = 1071,
	SPELL_INVITE_SUBOWNERS = 1072,
	SPELL_KICK_GUEST = 1073,
	SPELL_EDIT_DOOR = 1074,
	SPELL_ULTIMATE_LIGHT = 1075,
	SPELL_MAGIC_ROPE = 1076,
	SPELL_STALAGMITE_RUNE = 1077,
	SPELL_DISINTEGRATE_RUNE = 1078,
	SPELL_BERSERK = 1080,
	SPELL_LEVITATE = 1081,
	SPELL_MASS_HEALING = 1082,
	SPELL_ANIMATE_DEAD_RUNE = 1083,
	SPELL_HEAL_FRIEND = 1084,
	SPELL_UNDEAD_LEGION = 1085,
	SPELL_MAGIC_WALL_RUNE = 1086,
	SPELL_DEATH_STRIKE = 1087,
	SPELL_ENERGY_STRIKE = 1088,
	SPELL_FLAME_STRIKE = 1089,
	SPELL_CANCEL_INVISIBILITY = 1090,
	SPELL_POISON_BOMB_RUNE = 1091,
	SPELL_CONJURE_WAND_OF_DARKNESS = 1092,
	SPELL_CHALLENGE = 1093,
	SPELL_WILD_GROWTH_RUNE = 1094,
	SPELL_FIERCE_BERSERK = 1105,
	SPELL_GROUNDSHAKER = 1106,
	SPELL_WHIRLWIND_THROW = 1107,
	SPELL_ENCHANT_SPEAR = 1110,
	SPELL_ETHEREAL_SPEAR = 1111,
	SPELL_ICE_STRIKE = 1112,
	SPELL_TERRA_STRIKE = 1113,
	SPELL_ICICLE_RUNE = 1114,
	SPELL_AVALANCHE_RUNE = 1115,
	SPELL_STONE_SHOWER_RUNE = 1116,
	SPELL_THUNDERSTORM_RUNE = 1117,
	SPELL_ETERNAL_WINTER = 1118,
	SPELL_RAGE_OF_THE_SKIES = 1119,
	SPELL_TERRA_WAVE = 1120,
	SPELL_ICE_WAVE = 1121,
	SPELL_DIVINE_MISSILE = 1122,
	SPELL_WOUND_CLEANSING = 1123,
	SPELL_DIVINE_CALDERA = 1124,
	SPELL_DIVINE_HEALING = 1125,
	SPELL_TRAIN_PARTY = 1126,
	SPELL_PROTECT_PARTY = 1127,
	SPELL_HEAL_PARTY = 1128,
	SPELL_ENCHANT_PARTY = 1129,
	SPELL_HOLY_MISSILE_RUNE = 1130,
	SPELL_CHARGE = 1131,
	SPELL_PROTECTOR = 1132,
	SPELL_BLOOD_RAGE = 1133,
	SPELL_SWIFT_FOOT = 1134,
	SPELL_SHARPSHOOTER = 1135,
	SPELL_IGNITE = 1138,
	SPELL_CURSE = 1139,
	SPELL_ELECTRIFY = 1140,
	SPELL_INFLICT_WOUND = 1141,
	SPELL_ENVENOM = 1142,
	SPELL_HOLY_FLASH = 1143,
	SPELL_CURE_BLEEDING = 1144,
	SPELL_CURE_BURNING = 1145,
	SPELL_CURE_ELECTRIFICATION = 1146,
	SPELL_CURE_CURSE = 1147,
	SPELL_PHYSICAL_STRIKE = 1148,
	SPELL_LIGHTNING = 1149,
	SPELL_STRONG_FLAME_STRIKE = 1150,
	SPELL_STRONG_ENERGY_STRIKE = 1151,
	SPELL_STRONG_ICE_STRIKE = 1152,
	SPELL_STRONG_TERRA_STRIKE = 1153,
	SPELL_ULTIMATE_FLAME_STRIKE = 1154,
	SPELL_ULTIMATE_ENERGY_STRIKE = 1155,
	SPELL_ULTIMATE_ICE_STRIKE = 1156,
	SPELL_ULTIMATE_TERRA_STRIKE = 1157,
	SPELL_INTENSE_WOUND_CLEANSING = 1158,
	SPELL_RECOVERY = 1159,
	SPELL_INTENSE_RECOVERY = 1160,
	SPELL_PRACTISE_HEALING = 1166,
	SPELL_PRACTISE_FIRE_WAVE = 1167,
	SPELL_PRACTISE_MAGIC_MISSILE_RUNE = 1168,
	SPELL_APPRENT_ICES_STRIKE = 1169,
	SPELL_MUD_ATTACK = 1172,
	SPELL_CHILL_OUT = 1173,
	SPELL_MAGIC_PATCH = 1174,
	SPELL_BRUISE_BANE = 1175,
	SPELL_ARROW_CALL = 1176,
	SPELL_BUZZ = 1177,
	SPELL_SCORCH = 1178,
	SPELL_LIGHTEST_MISSILE_RUNE = 1179,
	SPELL_LIGHT_STONE_SHOWER_RUNE = 1180,
	SPELL_SUMMON_KNIGHT_FAMILIAR = 1194,
	SPELL_SUMMON_PALADIN_FAMILIAR = 1195,
	SPELL_SUMMON_SORCERER_FAMILIAR = 1196,
	SPELL_SUMMON_DRUID_FAMILIAR = 1197,
	SPELL_CHIVALROUS_CHALLENGE = 1237,
	SPELL_DIVINE_DAZZLE = 1238,
	SPELL_FAIR_WOUND_CLEANSING = 1239,
	SPELL_GREAT_FIRE_WAVE = 1240,
	SPELL_RESTORATION = 1241,
	SPELL_NATURES_EMBRACE = 1242,
	SPELL_EXPOSE_WEAKNESS = 1243,
	SPELL_SAP_STRENGTH = 1244,
	SPELL_CANCEL_MAGIC_SHIELD = 1245,
	MONSTER_SPELL_SINGLE_TARGET_FIRE = 2002,
	MONSTER_SPELL_SINGLE_TARGET_ENERGY = 2003,
	MONSTER_SPELL_SINGLE_TARGET_EARTH = 2004,
	MONSTER_SPELL_SINGLE_TARGET_ICE = 2005,
	MONSTER_SPELL_SINGLE_TARGET_DEATH = 2006,
	MONSTER_SPELL_SINGLE_TARGET_HOLY = 2007,
	MONSTER_SPELL_SINGLE_TARGET_HIT = 2008,
	MONSTER_SPELL_SINGLE_TARGET_LIFEDRAIN = 2009,
	MONSTER_SPELL_SINGLE_TARGET_MANADRAIN = 2010,
	MONSTER_SPELL_SINGLE_TARGET_DROWNING = 2011,
	MONSTER_SPELL_SINGLE_TARGET_BLEEDING = 2012,
	MONSTER_SPELL_SINGLE_TARGET_HEALING = 2013,
	MONSTER_SPELL_SMALL_AREA_FIRE = 2015,
	MONSTER_SPELL_SMALL_AREA_ENERGY = 2016,
	MONSTER_SPELL_SMALL_AREA_EARTH = 2017,
	MONSTER_SPELL_SMALL_AREA_ICE = 2018,
	MONSTER_SPELL_SMALL_AREA_DEATH = 2019,
	MONSTER_SPELL_SMALL_AREA_HOLY = 2020,
	MONSTER_SPELL_SMALL_AREA_HIT = 2021,
	MONSTER_SPELL_SMALL_AREA_LIFEDRAIN = 2022,
	MONSTER_SPELL_SMALL_AREA_MANADRAIN = 2023,
	MONSTER_SPELL_SMALL_AREA_DROWNING = 2024,
	MONSTER_SPELL_SMALL_AREA_BLEEDING = 2025,
	MONSTER_SPELL_SMALL_AREA_HEALING = 2026,
	MONSTER_SPELL_LARGE_AREA_FIRE = 2028,
	MONSTER_SPELL_LARGE_AREA_ENERGY = 2029,
	MONSTER_SPELL_LARGE_AREA_EARTH = 2030,
	MONSTER_SPELL_LARGE_AREA_ICE = 2031,
	MONSTER_SPELL_LARGE_AREA_DEATH = 2032,
	MONSTER_SPELL_LARGE_AREA_HOLY = 2033,
	MONSTER_SPELL_LARGE_AREA_HIT = 2034,
	MONSTER_SPELL_LARGE_AREA_LIFEDRAIN = 2035,
	MONSTER_SPELL_LARGE_AREA_MANADRAIN = 2036,
	MONSTER_SPELL_LARGE_AREA_DROWNING = 2037,
	MONSTER_SPELL_LARGE_AREA_BLEEDING = 2038,
	MONSTER_SPELL_LARGE_AREA_HEALING = 2039,
	MONSTER_SPELL_WAVE_FIRE = 2041,
	MONSTER_SPELL_WAVE_ENERGY = 2042,
	MONSTER_SPELL_WAVE_EARTH = 2043,
	MONSTER_SPELL_WAVE_ICE = 2044,
	MONSTER_SPELL_WAVE_DEATH = 2045,
	MONSTER_SPELL_WAVE_HOLY = 2046,
	MONSTER_SPELL_WAVE_HIT = 2047,
	MONSTER_SPELL_WAVE_LIFEDRAIN = 2048,
	MONSTER_SPELL_WAVE_MANADRAIN = 2049,
	MONSTER_SPELL_WAVE_DROWNING = 2050,
	MONSTER_SPELL_WAVE_BLEEDING = 2051,
	MONSTER_SPELL_WAVE_HEALING = 2052,
	MONSTER_SPELL_DELETEFIELD = 2054,
	MONSTER_SPELL_CHALLENGE = 2055,
	MONSTER_SPELL_SPEED = 2056,
	MONSTER_SPELL_DRUNKEN = 2057,
	MONSTER_SPELL_STRENGTH = 2058,
	MONSTER_SPELL_OUTFIT = 2059,
	MONSTER_SPELL_SUMMON = 2060,
	MONSTER_SPELL_MAGICLEVEL = 2061,
	MONSTER_SPELL_TELEPORT = 2062,
	MONSTER_SPELL_HEX = 2063,
	MONSTER_SPELL_SUPER_DRUNKEN = 2064,
	MONSTER_SPELL_ROOT = 2065,
	MONSTER_SPELL_FEAR = 2066,
	MONSTER_SPELL_HIGHRISK_TELEPORT = 2067,
	MONSTER_SPELL_MINION = 2068,
	MONSTER_SPELL_AGONY = 2069, // No sound ingame
	AMPHIBIC_BARK = 2500,
	AQUATIC_BEAST_BARK = 2501,
	AQUATIC_CRITTER_BARK = 2502,
	AQUATIC_DEEPLING_BARK = 2503,
	AQUATIC_QUARA_BARK = 2504,
	BIRD_BARK = 2505,
	CONSTRUCT_BARK = 2506,
	DEMON_BARK = 2507,
	DRAGON_BARK = 2508,
	ELEMENTAL_EARTH_BARK = 2509,
	ELEMENTAL_ENERGY_BARK = 2510,
	ELEMENTAL_FIRE_BARK = 2511,
	ELEMENTAL_WATER_BARK = 2512,
	EXTRA_DIMENSIONAL_BEAST_BARK = 2513,
	EXTRA_DIMENSIONAL_ENERGY_BARK = 2514,
	EXTRA_DIMENSIONAL_HORROR_BARK = 2515,
	FEY_BARK = 2516,
	GIANT_BARK = 2517,
	HUMAN_FEMALE_BARK = 2518,
	HUMAN_MALE_BARK = 2519,
	HUMANOID_GOBLIN_BARK = 2520,
	HUMANOID_ORC_BARK = 2521,
	LYCANTHROPE_BARK = 2522,
	MAGICAL_ENERGY_BARK = 2523,
	MAGICAL_HORROR_BARK = 2524,
	MAMMAL_BEAR_BARK = 2525,
	MAMMAL_CRITTER_BARK = 2526,
	MAMMAL_DOG_BARK = 2527,
	MAMMAL_ELEPHANT_BARK = 2528,
	MAMMAL_FERAL_BARK = 2529,
	MAMMAL_HORSE_BARK = 2530,
	MAMMAL_MAMMOTH_BARK = 2531, // No sound ingame
	MONSTER_BARK = 2532,
	PHANTOM_BARK = 2533,
	PLANT_BARK = 2534,
	REPTILE_LARGE_BARK = 2535,
	REPTILE_SMALL_BARK = 2536,
	SLIME_BARK = 2537,
	UNDEAD_BARK = 2538,
	VERMIN_CRITTER_BARK = 2539,
	VERMIN_INSECT_BARK = 2540,
	VERMIN_ROTWORM_BARK = 2541,
	HUMAN_SAGE_BARK = 2542, //  No sound ingame
	HUMAN_CRONE_BARK = 2543, // No sound ingame
	APE_BARK = 2544, // No sound ingame
	AMPHIBIC_DEATH = 2600,
	AQUATIC_BEAST_DEATH = 2601,
	AQUATIC_CRITTER_DEATH = 2602,
	AQUATIC_DEEPLING_DEATH = 2603,
	AQUATIC_QUARA_DEATH = 2604,
	BIRD_DEATH = 2605,
	CONSTRUCT_DEATH = 2606,
	DEMON_DEATH = 2607,
	DRAGON_DEATH = 2608,
	ELEMENTAL_EARTH_DEATH = 2609,
	ELEMENTAL_ENERGY_DEATH = 2610,
	ELEMENTAL_FIRE_DEATH = 2611,
	ELEMENTAL_WATER_DEATH = 2612,
	EXTRA_DIMENSIONAL_BEAST_DEATH = 2613,
	EXTRA_DIMENSIONAL_ENERGY_DEATH = 2614,
	EXTRA_DIMENSIONAL_HORROR_DEATH = 2615,
	FEY_DEATH = 2616,
	GIANT_DEATH = 2617,
	HUMAN_FEMALE_DEATH = 2618,
	HUMAN_MALE_DEATH = 2619,
	HUMANOID_GOBLIN_DEATH = 2620,
	HUMANOID_ORC_DEATH = 2621,
	LYCANTHROPE_DEATH = 2622,
	MAGICAL_ENERGY_DEATH = 2623,
	MAGICAL_HORROR_DEATH = 2624,
	MAMMAL_BEAR_DEATH = 2625,
	MAMMAL_CRITTER_DEATH = 2626,
	MAMMAL_DOG_DEATH = 2627,
	MAMMAL_ELEPHANT_DEATH = 2628,
	MAMMAL_FERAL_DEATH = 2629,
	MAMMAL_HORSE_DEATH = 2630,
	MAMMAL_MAMMOTH_DEATH = 2631, // No sound ingame
	MONSTER_DEATH = 2632,
	PHANTOM_DEATH = 2633,
	PLANT_DEATH = 2634,
	REPTILE_LARGE_DEATH = 2635,
	REPTILE_SMALL_DEATH = 2636,
	SLIME_DEATH = 2637,
	UNDEAD_DEATH = 2638,
	VERMIN_CRITTER_DEATH = 2639,
	VERMIN_INSECT_DEATH = 2640,
	VERMIN_ROTWORM_DEATH = 2641,
	HUMAN_SAGE_DEATH = 2642,
	HUMAN_CRONE_DEATH = 2643,
	APE_DEATH = 2644,
	UNKNOWN_CREATURE_DEATH_1 = 2645,
	UNKNOWN_CREATURE_DEATH_2 = 2646,
	UNKNOWN_CREATURE_DEATH_3 = 2647,
	UNKNOWN_CREATURE_DEATH_4 = 2648,
	ACTION_HEAVY_METAL_LOUD = 2649,
	ENV_INSECTS_BIRDS = 2651,
	ENV_WIND_1 = 2652,
	ENV_WIND_CLOSE = 2653,
	ENV_WATER_DEPTH_BOAT_SURFACE = 2654,
	ENV_METALIC_SPACE = 2655,
	ENV_FROGS_INSECTS_WOODS = 2656,
	ENV_WATER_DEPTH = 2657,
	ENV_SEA_WAVE = 2658,
	ENV_WIND_2 = 2659,
	ENV_WIND_3 = 2660,
	ENV_MONKEYS = 2661,
	ENV_STORM_COMING = 2662,
	ACTION_HITTING_WOOD = 2663,
	ENV_WOOD_STICK_SMASH = 2664,
	ENV_THICK_BLOB_LIQUID_1 = 2665,
	ENV_LITTLE_BIRTS_FLOREST = 2666,
	ENV_THICK_BLOCK_LIQUID_CLOSE = 2667,
	ACTION_METAL_CHAINS_MOVING = 2668,
	ENV_CRICKET_1 = 2669,
	ENV_CRICKET_2 = 2670,
	ENV_CRICKET_3 = 2671,
	ENV_CICADA_1 = 2672,
	ENV_STONES_FALLING = 2673,
	ACTION_OPEN_DOOR = 2674,
	ACTION_CLOSE_DOOR = 2675,
	ENV_OWL = 2676,
	ENV_ELETRONIC_DEVICE = 2678,
	ENV_REPTILE_NOISE = 2679,
	ENV_FORGE_METAL_1 = 2680,
	ENV_FROG = 2681,
	ACTION_WOOD_OBJECT_USING = 2682,
	ACTION_METAL_OBJECT_HIT = 2683,
	ACTION_NAIL_HIT = 2684,
	ENV_BELL_RING = 2685,
	ENV_HOT_METAL_ON_WATER = 2686,
	ENV_WATER_SMOKE = 2687,
	ENV_WOLF_HOWL = 2688,
	ENV_WOOD_CRACKLE_CLOSE = 2689,
	ENV_LAUGHT = 2690,
	ENV_WIND_MOVING_LEAF = 2691,
	ENV_WIND_MOVING_FEW_LEAF = 2692,
	ACTION_PORTAL_CAST = 2693,
	ACTION_FIRE_MAGIC_CAST = 2694,
	ENV_TRAPDOOR_OPEN = 2695,
	ENV_NAIL_FALLING = 2696,
	ENV_LIGHT_BLOB_LIQUID = 2697,
	ENV_LION_ROAR = 2698,
	ENV_MOVING_OBJECT_BUTTON_TRIGGER = 2699,
	ENV_SNAKE_1 = 2700,
	ENV_HUMAN_SCREEN_1 = 2701,
	ENV_HUMAN_SCREEN_2 = 2702,
	ENV_SEAGUL_1 = 2703,
	ENV_FAST_FOOTSTEPS = 2704,
	ENV_SLOW_FOOTSTEPS = 2705,
	ENV_THICK_BLOB_LIQUID_2 = 2706,
	ENV_MOVING_LEAF = 2707,
	ENV_WOOD_CRACKLE_1 = 2708,
	ACTION_OBJECT_FALLING_DEPTH = 2709,
	ACTION_BUTTON_TRIGGER = 2710,
	ENV_HEAVEN_DARK_REVERB = 2711,
	ENV_WIND_4 = 2712,
	ENV_INSECT_1 = 2713,
	ENV_FLUTE_SONG = 2714,
	ENV_INSECTS_BIRDS_DEATH = 2715,
	ENV_INSECT_CREATURE_DEATH = 2716,
	ENV_LOW_ROAR = 2717,
	ENV_SINISTER_BURPH = 2718,
	ENV_CROWD_SCREEN = 2719,
	ENV_BIRDS_FLYING = 2720,
	ENV_CROWD_VOICES_1 = 2721,
	ENV_BIRD_CUCO = 2722,
	ENV_RAVINE = 2723,
	ENV_RAVINE_METALIC = 2724,
	ENV_STICKS_LEAF_STEP = 2725,
	ACTION_DISPEL_MAGIC_1 = 2726,
	ACTION_DISPEL_MAGIC_2 = 2727,
	ENV_CROWD_VOICES_2 = 2728,
	ENV_CROWD_VOICES_3 = 2729,
	ENV_CROWD_VOICES_4 = 2730,
	ACTION_METAL_OBJECT_FALL = 2731,
	ENV_HOURSE_STEPS = 2732,
	ENV_DRUMES_SINISTER_REVERB = 2733,
	ACTION_WOOD_PIECES_FALL = 2734,
	ACTION_KNIFE_CUT_FLESH = 2735,
	ENV_CROWD_VOICES_5 = 2736,
	ENV_CICADA_2 = 2738,
	ENV_FLYES = 2739,
	ENV_NOISE_WATER = 2740,
	ENV_PIG_SOUND_1 = 2741,
	ENV_PIG_SOUND_2 = 2742,
	ENV_SHEEP_SOUND_1 = 2743,
	ENV_SHEEP_SOUND_2 = 2744,
	ENV_FIRE = 2745,
	ENV_NOISE_SNOW = 2746,
	ENV_FIRE_PLACE = 2747,
	ENV_WATERFALL = 2748,
	ENV_WATER_SOURCE = 2749,
	ACTION_HAMMER_HITING_NAILS_1 = 2750,
	ACTION_HAMMER_HITING_NAILS_2 = 2751,
	ENV_QUICK_STEPS = 2752,
	ENV_HEAVY_OBJECT_FALL = 2753,
	ACTION_HITING_FORGE = 2754,
	ENV_WOOD_CRACKLE_2 = 2755,
	ACTION_WOOD_HIT = 2756,
	MUSIC_CUT_BIRDS = 2757,
	MUSIC_CUT_LITTLE_BIRDS = 2758,
	MUSIC_CUT_INSECTS_1 = 2759,
	MUSIC_CUT_INSECTS_2 = 2760,
	MUSIC_CUT_INSECTS_3 = 2761,
	MUSIC_CUT_FLUTE_WEST = 2762,
	MUSIC_CUT_CROWS_VOICES = 2763,
	MUSIC_CUT_WIND_WATER = 2764,
	MUSIC_CUT_THICK_BLOCK_DEPTH = 2765,
	ENV_CAMEL = 2766,
	UNKNOWN_CREATURE_DEATH_5 = 2767,
	ENV_CHICKEN_1 = 2768,
	ENV_CHICKEN_2 = 2769,
	ENV_THRILLER_METALLIC = 2770,
	ACTION_NOTIFICATION = 2771,
	ACTION_LEVEL_ACHIEVEMENT = 2772,
	ACTION_SCREENSHOT = 2773,
	ACTION_CLICK_ON = 2774,
	ACTION_CLICK_OFF = 2775,
	ACTION_DRUMS = 2776,
	ACTION_XYLOPHONE_SLOW_DRUM = 2777,
	ACTION_HARP_1 = 2778,
	ACTION_HARP_2 = 2779,
	ACTION_MOVING_WOOD = 2780,
	ACTION_CRATE_BREAK_MAGIC_DUST = 2781,
	ACTION_BELL_RING = 2783,
	ACTION_SELECT_OBJECT = 2785,
	ITEM_MOVE_BACKPACK = 2786,
	ITEM_USE_POTION = 2787,
	ITEM_MOVE_NECKLACES = 2788,
	ITEM_MOVE_ARMORS = 2789,
	ITEM_MOVE_METALIC = 2790,
	ITEM_MOVE_DISTANCE = 2791,
	ITEM_MOVE_WOOD = 2792,
	ITEM_MOVE_STACKABLE = 2793,
	ITEM_MOVE_DEFAULT = 2794,
	ITEM_MOVE_LEGS = 2795,
	ITEM_MOVE_HELMETS = 2796,
	ITEM_MOVE_QUIVERS = 2797,
	ITEM_MOVE_RINGS = 2798,
	ENV_FROG_OR_LIQUID = 2799,
	ACTION_WOOD_OBJECT_HIT_STORE = 2800,
	ITEM_MOVE_BOOTS = 2801,
	ACTION_SWORD_DRAWN = 2802,
	ACTION_EAT = 2803,
	ACTION_STORE_BIG_OBJECT = 2804,
	ACTION_STORE_WOOD_OBJECT = 2805,
	ACTION_VIP_LOGOUT = 2806,
	ACTION_VIP_LOGIN = 2807,
	ENV_CAT_1 = 2808,
	ENV_INSECT_2 = 2809,
	ENV_SEAGUL_2 = 2810,
	ENV_LIQUID_SPILL = 2811,
	ENV_COW_MOO_1 = 2813,
	ENV_COW_MOO_2 = 2814,
	ENV_CAT_2 = 2815,
	ACTION_REAWRD_FEY = 2816,
	ACTION_REWARD_GUITAR_1 = 2817,
	ACTION_REWARD_GUITAR_2 = 2818,
	ENV_WOODS_WATER_SOURCE = 2819,
	ENV_HYENA = 2820,
	UNKNOWN_CREATURE_DEATH_6 = 2821,
	ENV_COW_MOO_3 = 2822,
	UNKNOWN_CREATURE_DEATH_7 = 2823,
	ENV_METALIC_SPACE_ALIEN = 2824,
	ACTION_AIR_STRIKE = 2825,
	ENV_WATER = 2828,
	ENV_SNAKE_2 = 2829,
	GOD_SPELL_KILL_ALL_MONSTERS = 10001, // No sound ingame
};

enum class SourceEffect_t : uint8_t {
	GLOBAL = 0,
	OWN = 1,
	OTHERS = 2,
	CREATURES = 3,
};

// Structs
struct Position;

struct VIPEntry {
		VIPEntry(uint32_t initGuid, std::string initName, std::string initDescription, uint32_t initIcon, bool initNotify) :
			guid(initGuid),
			name(std::move(initName)),
			description(std::move(initDescription)),
			icon(initIcon),
			notify(initNotify) { }

		uint32_t guid;
		std::string name;
		std::string description;
		uint32_t icon;
		bool notify;
};

struct OutfitEntry {
		constexpr OutfitEntry(uint16_t initLookType, uint8_t initAddons) :
			lookType(initLookType), addons(initAddons) { }

		uint16_t lookType;
		uint8_t addons;
};

struct FamiliarEntry {
		constexpr explicit FamiliarEntry(uint16_t initLookType) :
			lookType(initLookType) { }
		uint16_t lookType;
};

struct Skill {
		uint64_t tries = 0;
		uint16_t level = 10;
		double_t percent = 0;
};

struct Kill {
		uint32_t target;
		time_t time;
		bool unavenged;

		Kill(uint32_t _target, time_t _time, bool _unavenged) :
			target(_target), time(_time), unavenged(_unavenged) { }
};

struct IntervalInfo {
		int32_t timeLeft;
		int32_t value;
		int32_t interval;
};

struct FindPathParams {
		bool fullPathSearch = true;
		bool clearSight = true;
		bool allowDiagonal = true;
		bool keepDistance = false;
		int32_t maxSearchDist = 0;
		int32_t minTargetDist = -1;
		int32_t maxTargetDist = -1;
};

struct RecentDeathEntry {
		RecentDeathEntry(std::string cause, uint32_t timestamp) :
			cause(std::move(cause)),
			timestamp(timestamp) { }

		std::string cause;
		uint32_t timestamp;
};

struct RecentPvPKillEntry {
		RecentPvPKillEntry(std::string description, uint32_t timestamp, uint8_t status) :
			description(std::move(description)),
			timestamp(timestamp),
			status(status) { }

		std::string description;
		uint32_t timestamp;
		uint8_t status;
};

struct MarketOffer {
		uint64_t price;
		uint32_t timestamp;
		uint16_t amount;
		uint16_t counter;
		uint16_t itemId;
		uint8_t tier;
		std::string playerName;
};

struct MarketOfferEx {
		MarketOfferEx() = default;
		MarketOfferEx(MarketOfferEx &&other) :
			id(other.id),
			playerId(other.playerId),
			timestamp(other.timestamp),
			price(other.price),
			amount(other.amount),
			counter(other.counter),
			itemId(other.itemId),
			type(other.type),
			tier(other.tier),
			playerName(std::move(other.playerName)) { }

		uint32_t id;
		uint32_t playerId;
		uint32_t timestamp;
		uint64_t price;
		uint16_t amount;
		uint16_t counter;
		uint16_t itemId;
		MarketAction_t type;
		uint8_t tier;
		std::string playerName;
};

struct HistoryMarketOffer {
		uint32_t timestamp;
		uint64_t price;
		uint16_t itemId;
		uint16_t amount;
		uint8_t tier;
		MarketOfferState_t state;
};

using MarketOfferList = std::list<MarketOffer>;
using HistoryMarketOfferList = std::list<HistoryMarketOffer>;
using StashItemList = std::map<uint16_t, uint32_t>;

using ItemsTierCountList = std::map<uint16_t, std::map<uint8_t, uint32_t>>;
/*
	> ItemsTierCountList structure:
	|- [itemID]
		|- [itemTier]
			|- Count
		| ...
	| ...
*/

struct Familiar {
		Familiar(std::string initName, uint16_t initLookType, bool initPremium, bool initUnlocked, std::string initType) :
			name(initName), lookType(initLookType),
			premium(initPremium), unlocked(initUnlocked),
			type(initType) { }

		std::string name;
		uint16_t lookType;
		bool premium;
		bool unlocked;
		std::string type;
};

struct ProtocolFamiliars {
		ProtocolFamiliars(const std::string &initName, uint16_t initLookType) :
			name(initName), lookType(initLookType) { }

		const std::string &name;
		uint16_t lookType;
};

struct LightInfo {
		uint8_t level = 0;
		uint8_t color = 215;
		constexpr LightInfo() = default;
		constexpr LightInfo(uint8_t newLevel, uint8_t newColor) :
			level(newLevel), color(newColor) { }
};

struct CombatDamage {
		struct {
				CombatType_t type;
				int32_t value;
		} primary, secondary;

		CombatOrigin origin;
		bool critical;
		int affected;
		bool extension;
		bool cleave;
		std::string exString;
		bool fatal;

		CombatDamage() {
			origin = ORIGIN_NONE;
			primary.type = secondary.type = COMBAT_NONE;
			primary.value = secondary.value = 0;
			critical = false;
			affected = 1;
			extension = false;
			cleave = false;
			exString = "";
			fatal = false;
		}
};

struct RespawnType {
		RespawnPeriod_t period;
		bool underground;
};

struct LootBlock;

struct LootBlock {
		uint16_t id;
		uint32_t countmax;
		uint32_t countmin;
		uint32_t chance;

		// optional
		int32_t subType;
		int32_t actionId;
		std::string text;
		std::string name;
		std::string article;
		int32_t attack;
		int32_t defense;
		int32_t extraDefense;
		int32_t armor;
		int32_t shootRange;
		int32_t hitChance;
		bool unique;

		std::vector<LootBlock> childLoot;
		LootBlock() {
			id = 0;
			countmax = 1;
			countmin = 1;
			chance = 0;

			subType = -1;
			actionId = -1;
			attack = -1;
			defense = -1;
			extraDefense = -1;
			armor = -1;
			shootRange = -1;
			hitChance = -1;
			unique = false;
		}
};

struct ShopBlock {
		uint16_t itemId;
		std::string itemName;
		int32_t itemSubType;
		uint32_t itemBuyPrice;
		uint32_t itemSellPrice;
		int32_t itemStorageKey;
		int32_t itemStorageValue;

		std::vector<ShopBlock> childShop;
		ShopBlock() {
			itemId = 0;
			itemName = "";
			itemSubType = 0;
			itemBuyPrice = 0;
			itemSellPrice = 0;
			itemStorageKey = 0;
			itemStorageValue = 0;
		}

		explicit ShopBlock(uint16_t newItemId, int32_t newSubType = 0, uint32_t newBuyPrice = 0, uint32_t newSellPrice = 0, int32_t newStorageKey = 0, int32_t newStorageValue = 0, std::string newName = "") :
			itemId(newItemId), itemSubType(newSubType), itemBuyPrice(newBuyPrice), itemSellPrice(newSellPrice), itemStorageKey(newStorageKey), itemStorageValue(newStorageValue), itemName(std::move(newName)) { }

		bool operator==(const ShopBlock &other) const {
			return itemId == other.itemId && itemName == other.itemName && itemSubType == other.itemSubType && itemBuyPrice == other.itemBuyPrice && itemSellPrice == other.itemSellPrice && itemStorageKey == other.itemStorageKey && itemStorageValue == other.itemStorageValue && childShop == other.childShop;
		}
};

struct summonBlock_t {
		std::string name;
		uint32_t chance;
		uint32_t speed;
		uint32_t count;
		bool force = false;
};

struct Outfit_t {
		uint16_t lookType = 0;
		uint16_t lookTypeEx = 0;
		uint16_t lookMount = 0;
		uint8_t lookHead = 0;
		uint8_t lookBody = 0;
		uint8_t lookLegs = 0;
		uint8_t lookFeet = 0;
		uint8_t lookAddons = 0;
		uint8_t lookMountHead = 0;
		uint8_t lookMountBody = 0;
		uint8_t lookMountLegs = 0;
		uint8_t lookMountFeet = 0;
		uint16_t lookFamiliarsType = 0;
};

struct voiceBlock_t {
		std::string text;
		bool yellText;
};

struct PartyAnalyzer {
		PartyAnalyzer(uint32_t playerId, std::string playerName) :
			id(playerId),
			name(std::move(playerName)) { }

		uint32_t id;

		std::string name;

		uint64_t damage = 0;
		uint64_t healing = 0;
		uint64_t lootPrice = 0;
		uint64_t supplyPrice = 0;

		std::map<uint16_t, uint64_t> lootMap; // [itemID] = amount
		std::map<uint16_t, uint64_t> supplyMap; // [itemID] = amount
};

#endif // SRC_CREATURES_CREATURES_DEFINITIONS_HPP_
