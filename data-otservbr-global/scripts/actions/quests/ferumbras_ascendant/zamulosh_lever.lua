local config = {
	bossName = "Zamulosh",
	timeToFightAgain = 20 * 60 * 60,
	timeToDefeatBoss = 30 * 60,
	playerPositions = {
		{ pos = Position(33680, 32741, 11), teleport = Position(33644, 32760, 11), effect = CONST_ME_TELEPORT },
		{ pos = Position(33680, 32742, 11), teleport = Position(33644, 32760, 11), effect = CONST_ME_TELEPORT },
		{ pos = Position(33680, 32743, 11), teleport = Position(33644, 32760, 11), effect = CONST_ME_TELEPORT },
		{ pos = Position(33680, 32744, 11), teleport = Position(33644, 32760, 11), effect = CONST_ME_TELEPORT },
		{ pos = Position(33680, 32745, 11), teleport = Position(33644, 32760, 11), effect = CONST_ME_TELEPORT }
	},
	bossPosition = Position(33643, 32756, 11),
	specPos = {
		from = Position(33632, 32747, 11),
		to = Position(33654, 32765, 11)
	},
	exit = Position(33319, 32318, 13),
	storage = Storage.FerumbrasAscension.ZamuloshTimer
}

local zamuloshSummons = {
	Position(33642, 32756, 11),
	Position(33642, 32756, 11),
	Position(33642, 32756, 11),
	Position(33644, 32756, 11),
	Position(33644, 32756, 11),
	Position(33644, 32756, 11)
}

local ferumbrasAscendantZamulosh = Action()
function ferumbrasAscendantZamulosh.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if CreateDefaultLeverBoss(player, config) then
		for _, pos in pairs(zamuloshSummons) do
			Game.createMonster('Zamulosh3', pos, true, true)
		end
	end
end

ferumbrasAscendantZamulosh:uid(1026)
ferumbrasAscendantZamulosh:register()
