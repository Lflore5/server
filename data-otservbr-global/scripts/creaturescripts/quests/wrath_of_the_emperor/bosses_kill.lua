local bosses = {
	["fury of the emperor"] = {
		position = Position(33048, 31085, 15),
		storage = GlobalStorage.WrathOfTheEmperor.Bosses.Fury,
	},
	["wrath of the emperor"] = {
		position = Position(33094, 31087, 15),
		storage = GlobalStorage.WrathOfTheEmperor.Bosses.Wrath,
	},
	["scorn of the emperor"] = {
		position = Position(33095, 31110, 15),
		storage = GlobalStorage.WrathOfTheEmperor.Bosses.Scorn,
	},
	["spite of the emperor"] = {
		position = Position(33048, 31111, 15),
		storage = GlobalStorage.WrathOfTheEmperor.Bosses.Spite,
	},
}

local bossesKill = CreatureEvent("BossesKill")
function bossesKill.onKill(creature, target)
	local targetMonster = target:getMonster()
	if not targetMonster then
		return true
	end

	local bossConfig = bosses[targetMonster:getName():lower()]
	if not bossConfig then
		return true
	end

	Game.setStorageValue(bossConfig.storage, 0)
	local tile = Tile(bossConfig.position)
	if tile then
		local thing = tile:getItemById(10797)
		if thing then
			thing:transform(11427)
		end
	end
	return true
end

bossesKill:setMonster("fury of the emperor", "wrath of the emperor", "scorn of the emperor", "spite of the emperor")
bossesKill:register()
