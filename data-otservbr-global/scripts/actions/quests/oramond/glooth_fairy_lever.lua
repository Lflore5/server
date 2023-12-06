local function removeBosst(fromArea1, fromArea2, bossName)
	for x = fromArea1.x, fromArea2.x do
		for y = fromArea1.y, fromArea2.y do
			for z = fromArea1.z, fromArea2.z do
				local tile = Tile(Position({ x = x, y = y, z = z }))
				if tile then
					local monster = tile:getTopCreature()
					if monster and monster:isMonster() then
						if monster:getName():lower == string.lower(bossName) then
							monster:remove()
						end
					end
				end
			end
		end
	end
	return true
end

local function teleportAllPlayersFromAreat(fromArea1, fromArea2, toPos)
	for x = fromArea1.x, fromArea2.x do
		for y = fromArea1.y, fromArea2.y do
			for z = fromArea1.z, fromArea2.z do
				local tile = Tile(Position({ x = x, y = y, z = z }))
				if tile then
					local player = tile:getTopCreature()
					if player and player:isPlayer() then
						player:teleportTo(toPos)
						player:getPosition():sendMagicEffect(CONST_ME_TELEPORT)
					end
				end
			end
		end
	end
	return true
end

local function PrepareEnter()
	removeBosst({ x = 33679, y = 31919, z = 9 }, { x = 33701, y = 31941, z = 9 }, "glooth fairy")
	teleportAllPlayersFromAreat({ x = 33659, y = 31935, z = 9 }, { x = 33668, y = 31939, z = 9 }, { x = 33684, y = 31935, z = 9 })
	Game.createMonster("Glooth Fairy", { x = 33688, y = 31937, z = 9 })
end

local oramondGloothLever = Action()

function oramondGloothLever.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item.itemid == 8913 then
		if Game.getStorageValue(15560) >= os.time() then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You need to wait 15 minutes to use again.")
			return true
		end

		local position = Position(33688, 31932, 9)
		local spectators = Game.getSpectators(position, false, false, 13, 13, 13, 13)
		for _, spectator in pairs(spectators) do
			if spectator:isPlayer() then
				spectator:sendTextMessage(MESSAGE_EVENT_ADVANCE, "A team is already inside the quest room.")
				return true
			end
			spectator:remove()
		end

		Game.setStorageValue(18081, os.time() + 15 * 60)

		player:say("Everyone in this place will be teleported into Glooth Fairy's hideout in one minute. No way back!!!", TALKTYPE_MONSTER_SAY)
		addEvent(PrepareEnter, 60 * 1000)
	end

	item:transform(item.itemid == 8913 and 8914 or 8913)
	return true
end

oramondGloothLever:uid(1020)
oramondGloothLever:register()
