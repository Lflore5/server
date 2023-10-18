local mType = Game.createMonsterType("Darklight Striker")
local monster = {}

monster.description = "Darklight Striker"
monster.experience = 24550
monster.outfit = {
	lookType = 1661,
}

monster.health = 29700
monster.maxHealth = 29700
monster.race = "blood"
monster.corpse = 26133
monster.speed = 585
monster.manaCost = 0
monster.maxSummons = 8

monster.changeTarget = {
	interval = 5000,
	chance = 8,
}

monster.strategiesTarget = {
	nearest = 100,
}

monster.flags = {
	summonable = false,
	attackable = true,
	hostile = true,
	convinceable = false,
	pushable = false,
	rewardBoss = false,
	illusionable = false,
	canPushItems = true,
	canPushCreatures = true,
	staticAttackChance = 90,
	targetDistance = 1,
	runHealth = 0,
	healthHidden = false,
	isBlockable = false,
	canWalkOnEnergy = false,
	canWalkOnFire = false,
	canWalkOnPoison = false,
}

monster.light = {
	level = 0,
	color = 0,
}

monster.summon = {
}

monster.voices = {
	interval = 5000,
	chance = 10,
}

monster.loot = {
	{ name = "crystal coin", chance = 5424, maxCount = 1 },
	{ name = "unstable darklight matter", chance = 12587, maxCount = 1 },
	{ name = "darklight core (object)", chance = 10632, maxCount = 1 },
	{ name = "small topaz", chance = 14232, maxCount = 3 },
	{ name = "ice rapier", chance = 12494, maxCount = 1 },
	{ name = "dark obsidian splinter", chance = 9513, maxCount = 1 },
	{ name = "blue gem", chance = 11882, maxCount = 1 },
	{ name = "crystal mace", chance = 5960, maxCount = 1 },
	{ name = "zaoan helmet", chance = 6454, maxCount = 1 },
}

monster.attacks = {
	{ name = "melee", interval = 2000, chance = 100, minDamage = -220, maxDamage = -1000 },
	{ name = "combat", interval = 1500, chance = 15, type = COMBAT_EARTHDAMAGE, minDamage = -220, maxDamage = -900, radius = 3, shootEffect = CONST_ANI_ENVENOMEDARROW, target = true },
	{ name = "combat", interval = 1500, chance = 25, type = COMBAT_ENERGYDAMAGE, minDamage = -220, maxDamage = -850, length = 4, spread = 3, effect = CONST_ME_ENERGYHIT, target = false },
	{ name = "combat", interval = 1500, chance = 35, type = COMBAT_DEATHDAMAGE, minDamage = -220, maxDamage = -950, radius = 4, effect = CONST_ME_MORTAREA, target = false },
	{ name = "combat", interval = 1500, chance = 20, type = COMBAT_FIREDAMAGE, minDamage = -220, maxDamage = -950, radius = 4, effect = CONST_ME_FIREAREA, target = false },
}

monster.defenses = {
	defense = 20,
	armor = 42,
}

monster.elements = {
	{ type = COMBAT_PHYSICALDAMAGE, percent = 0 },
	{ type = COMBAT_ENERGYDAMAGE, percent = 0 },
	{ type = COMBAT_EARTHDAMAGE, percent = 0 },
	{ type = COMBAT_FIREDAMAGE, percent = 50 },
	{ type = COMBAT_LIFEDRAIN, percent = 0 },
	{ type = COMBAT_MANADRAIN, percent = 0 },
	{ type = COMBAT_DROWNDAMAGE, percent = 10 },
	{ type = COMBAT_ICEDAMAGE, percent = 0 },
	{ type = COMBAT_HOLYDAMAGE, percent = 0 },
	{ type = COMBAT_DEATHDAMAGE, percent = 0 },
}

monster.immunities = {
	{ type = "paralyze", condition = false },
	{ type = "outfit", condition = false },
	{ type = "invisible", condition = true },
	{ type = "bleed", condition = false },
}

mType:register(monster)
