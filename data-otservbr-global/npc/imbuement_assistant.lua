local internalNpcName = "Imbuement Assistant"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 141,
	lookHead = 41,
	lookBody = 72,
	lookLegs = 39,
	lookFeet = 96,
	lookAddons = 3,
	lookMount = 688,
}

npcConfig.flags = {
	floorchange = false,
}

npcConfig.voices = {
	interval = 15000,
	chance = 50,
	{ text = "Hello adventurer, looking for Imbuement items? Just ask me!" },
}

local playerImbuementData = {}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)

npcType.onThink = function(npc, interval)
	npcHandler:onThink(npc, interval)
end

npcType.onAppear = function(npc, creature)
	npcHandler:onAppear(npc, creature)
end

npcType.onDisappear = function(npc, creature)
	npcHandler:onDisappear(npc, creature)
end

npcType.onMove = function(npc, creature, fromPosition, toPosition)
	npcHandler:onMove(npc, creature, fromPosition, toPosition)
end

npcType.onSay = function(npc, creature, type, message)
	npcHandler:onSay(npc, creature, type, message)
end

npcType.onCloseChannel = function(npc, creature)
	npcHandler:onCloseChannel(npc, creature)
	playerImbuementData[creature:getId()] = nil
end

function addItemsToShoppingBag(npc, player)
	local playerId = player:getId()
	local playerData = playerImbuementData[playerId]

	if playerData then
		local moneyRequired = playerData.moneyRequired
		local itemList = playerData.itemList
		if player:getMoney() + player:getBankBalance() < moneyRequired then
			npcHandler:say("Sorry, you don't have enough money", npc, player)
			npcHandler:setTopic(player:getId(), 0)
			return false, "You don't have enough money."
		end

		local totalWeight = 0
		for _, item in pairs(itemList) do
			local itemType = ItemType(item.itemId)
			totalWeight = totalWeight + (itemType:getWeight() * item.count)
		end

		if player:getFreeCapacity() < totalWeight then
			return false, "You not enough weight."
		end

		if player:getFreeBackpackSlots() == 0 then
			return false, "You not enough room."
		end

		local shoppingBag = player:addItem(2856, 1) -- present box
		for _, item in pairs(itemList) do
			shoppingBag:addItem(item.itemId, item.count)
		end

		player:removeMoneyBank(moneyRequired)

		return true
	end

	return false
end

local function purchaseItems(npc, player, message, text, moneyRequired, itemList)
	if npcHandler:getTopic(player:getId()) == 1 then
		npcHandler:say("Do you want to buy items for " .. text .. " imbuement for " .. moneyRequired .. " gold?", npc, player)
		npcHandler:setTopic(player:getId(), 2)

		playerImbuementData[player:getId()] = {
			moneyRequired = moneyRequired,
			itemList = itemList
		}
	end
end

local function creatureSayCallback(npc, creature, type, message)
	local player = Player(creature)
	local playerId = player:getId()
	if not npcHandler:checkInteraction(npc, creature) then
		return false
	end

	local imbuementPackages = "Available imbuement packages: {bash}, {blockade}, {chop}, {epiphany}, {precision}, {slash}. additional attributes: {featherweight}, {strike}, {swiftness}, {vampirism}, {vibrancy}, {void}. elemental damage: {electrify}, {frost}, {reap}, {scorch}, {venom}. elemental protection: {cloud fabric}, {demon presence}, {dragon hide}, {lich shroud}, {quara scale}, {snake skin}."
	if MsgContains(message, "imbuement packages") then
		npcHandler:setTopic(playerId, 1)
		npcHandler:say(imbuementPackages, npc, creature)
	-- Skill increase packages
	elseif MsgContains(message, "bash") then
		print("entered message: ".. message)
		purchaseItems(npc, player, message, "skill club", 6250, {
			{itemId = 9657, count = 20}, -- cyclops toe
			{itemId = 22189, count = 15}, -- ogre nose ring
			{itemId = 10405, count = 10} -- warmaster's wristguards
		})
	elseif MsgContains(message, "blockade") then
		purchaseItems(npc, player, message, "skill shield", 16150, {
			{itemId = 9641, count = 20}, -- piece of scarab shell
			{itemId = 11703, count = 25}, -- brimstone shell
			{itemId = 20199, count = 25} -- frazzle skin
		})
	elseif MsgContains(message, "chop") then
		purchaseItems(npc, player, message, "skill axe", 13050, {
			{itemId = 10196, count = 20}, -- orc tooth
			{itemId = 11447, count = 25}, -- battle stone
			{itemId = 21200, count = 20} -- moohtant horn
		})
	elseif MsgContains(message, "epiphany") then
		purchaseItems(npc, player, message, "magic level", 10650, {
			{itemId = 9635, count = 25}, -- elvish talisman
			{itemId = 11452, count = 15}, -- broken shamanic staff
			{itemId = 10309, count = 15} -- strand of medusa hair
		})
	elseif MsgContains(message, "precision") then
		purchaseItems(npc, player, message, "skill distance", 6750, {
			{itemId = 11464, count = 25}, -- elven scouting glass
			{itemId = 18994, count = 20}, -- elven hoof
			{itemId = 10298, count = 10} -- metal spike
		})
	elseif MsgContains(message, "slash") then
		purchaseItems(npc, player, message, "skill sword", 6550, {
			{itemId = 9691, count = 25}, -- lion's mane
			{itemId = 21202, count = 25}, -- mooh'tah shell
			{itemId = 9654, count = 5} -- war crystal
		})
	-- Additional attributes packages
	elseif MsgContains(message, "featherweight") then
		purchaseItems(npc, player, message, "capacity increase", 12250, {
			{itemId = 25694, count = 20}, -- fairy wings
			{itemId = 25702, count = 10}, -- little bowl of myrrh
			{itemId = 20205, count = 5} -- goosebump leather
		})
	elseif MsgContains(message, "strike") then
		purchaseItems(npc, player, message, "critical", 16700, {
			{itemId = 11444, count = 20}, -- protective charm
			{itemId = 10311, count = 25}, -- sabretooth
			{itemId = 22728, count = 5} -- vexclaw talon
		})
	elseif MsgContains(message, "swiftness") then
		purchaseItems(npc, player, message, "speed", 5225, {
			{itemId = 17458, count = 15}, -- damselfly wing
			{itemId = 10302, count = 25}, -- compass
			{itemId = 14081, count = 20} -- waspoid wing
		})
	elseif MsgContains(message, "vampirism") then
		purchaseItems(npc, player, message, "life leech", 10475, {
			{itemId = 9685, count = 25}, -- vampire teeth
			{itemId = 9633, count = 15}, -- bloody pincers
			{itemId = 9663, count = 5} -- piece of dead brain
		})
	elseif MsgContains(message, "vibrancy") then
		purchaseItems(npc, player, message, "paralysis removal", 15000, {
			{itemId = 22053, count = 20}, -- wereboar hooves
			{itemId = 23507, count = 15}, -- crystallized anger
			{itemId = 28567, count = 5} -- quill
		})
	elseif MsgContains(message, "void") then
		purchaseItems(npc, player, message, "mana leech", 17400, {
			{itemId = 11492, count = 25}, -- rope belt
			{itemId = 20200, count = 25}, -- silencer claws
			{itemId = 22730, count = 5} -- some grimeleech wings
		})
	-- Elemental damage packages
	elseif MsgContains(message, "electrify") then
		purchaseItems(npc, player, message, "energy damage", 3770, {
			{itemId = 18993, count = 25}, -- rorc feather
			{itemId = 21975, count = 5}, -- peacock feather fan
			{itemId = 23508, count = 1} -- energy vein
		})
	elseif MsgContains(message, "frost") then
		purchaseItems(npc, player, message, "ice damage", 9750, {
			{itemId = 9661, count = 25}, -- frosty heart
			{itemId = 21801, count = 10}, -- seacrest hair
			{itemId = 9650, count = 5} -- polar bear paw
		})
	elseif MsgContains(message, "reap") then
		purchaseItems(npc, player, message, "death damage", 3475, {
			{itemId = 11484, count = 25}, -- pile of grave earth
			{itemId = 9647, count = 20}, -- demonic skeletal hand
			{itemId = 10420, count = 5} -- petrified scream
		})
	elseif MsgContains(message, "scorch") then
		purchaseItems(npc, player, message, "fire damage", 15875, {
			{itemId = 9636, count = 25}, -- fiery heart
			{itemId = 5920, count = 5}, -- green dragon scale
			{itemId = 5954, count = 5} -- demon horn
		})
	elseif MsgContains(message, "venom") then
		purchaseItems(npc, player, message, "earth damage", 1820, {
			{itemId = 9686, count = 25}, -- swamp grass
			{itemId = 9640, count = 20}, -- poisonous slime
			{itemId = 21194, count = 2} -- slime heart
		})

	-- Elemental protection packages
	elseif MsgContains(message, "cloud fabric") then
		purchaseItems(npc, player, message, "energy protection", 13775, {
			{itemId = 9644, count = 20}, -- wyvern talisman
			{itemId = 14079, count = 15}, -- crawler head plating
			{itemId = 9665, count = 10} -- wyrm scale
		})
	elseif MsgContains(message, "demon presence") then
		purchaseItems(npc, player, message, "holy protection", 20250, {
			{itemId = 9639, count = 25}, -- cultish robe
			{itemId = 9638, count = 25}, -- cultish mask
			{itemId = 10304, count = 20} -- hellspawn tail
		})
	elseif MsgContains(message, "dragon hide") then
		purchaseItems(npc, player, message, "fire protection", 10850, {
			{itemId = 5877, count = 20}, -- green dragon leather
			{itemId = 16131, count = 10}, -- blazing bone
			{itemId = 11658, count = 5} -- draken sulphur
		})
	elseif MsgContains(message, "lich shroud") then
		purchaseItems(npc, player, message, "death protection", 5650, {
			{itemId = 11466, count = 25}, -- flask of embalming fluid
			{itemId = 22007, count = 20}, -- gloom wolf fur
			{itemId = 9660, count = 5} -- mystical hourglass
		})
	elseif MsgContains(message, "quara scale") then
		purchaseItems(npc, player, message, "ice protection", 3650, {
			{itemId = 10295, count = 25}, -- winter wolf fur
			{itemId = 10307, count = 15}, -- thick fur
			{itemId = 14012, count = 10} -- deepling warts
		})
	elseif MsgContains(message, "snake skin") then
		purchaseItems(npc, player, message, "earth protection", 12550, {
			{itemId = 17823, count = 25}, -- piece of swampling wood
			{itemId = 9694, count = 20}, -- snake skin
			{itemId = 11702, count = 10} -- brimstone fangs
		})
	elseif MsgContains(message, "yes") and npcHandler:getTopic(playerId) == 2 then
		local success, message = addItemsToShoppingBag(npc, player)
		if not success then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, message)
			npcHandler:setTopic(playerId, 1)
			npcHandler:say(imbuementPackages, npc, player)
			return
		end

		playerImbuementData[playerId] = nil
		npcHandler:say("You have successfully completed your purchase of the items.", npc, player)
		npcHandler:setTopic(playerId, 1)
		npcHandler:say(imbuementPackages, npc, creature)
	end
end

npcHandler:setMessage(MESSAGE_GREET, "Hello |PLAYERNAME|, say {imbuement packages} or {trade} for buy imbuement items.")
npcHandler:setMessage(MESSAGE_WALKAWAY, "See you later |PLAYERNAME| come back soon.")
npcHandler:setMessage(MESSAGE_FAREWELL, "See you later |PLAYERNAME| come back soon.")

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)

npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)

npcConfig.shop = {
	{ itemName = "battle stone", clientId = 11447, buy = 290 },
	{ itemName = "blazing bone", clientId = 16131, buy = 610 },
	{ itemName = "bloody pincers", clientId = 9633, buy = 100 },
	{ itemName = "brimstone fangs", clientId = 11702, buy = 380 },
	{ itemName = "brimstone shell", clientId = 11703, buy = 210 },
	{ itemName = "broken shamanic staff", clientId = 11452, buy = 35 },
	{ itemName = "compass", clientId = 10302, buy = 45 },
	{ itemName = "crawler head plating", clientId = 14079, buy = 210 },
	{ itemName = "crystallized anger", clientId = 23507, buy = 400 },
	{ itemName = "cultish mask", clientId = 9638, buy = 280 },
	{ itemName = "cultish robe", clientId = 9639, buy = 150 },
	{ itemName = "cyclops toe", clientId = 9657, buy = 55 },
	{ itemName = "damselfly wing", clientId = 17458, buy = 20 },
	{ itemName = "deepling warts", clientId = 14012, buy = 180 },
	{ itemName = "demon horn", clientId = 5954, buy = 1000 },
	{ itemName = "demonic skeletal hand", clientId = 9647, buy = 80 },
	{ itemName = "draken sulphur", clientId = 11658, buy = 550 },
	{ itemName = "elven hoof", clientId = 18994, buy = 115 },
	{ itemName = "elven scouting glass", clientId = 11464, buy = 50 },
	{ itemName = "elvish talisman", clientId = 9635, buy = 45 },
	{ itemName = "energy vein", clientId = 23508, buy = 270 },
	{ itemName = "fairy wings", clientId = 25694, buy = 200 },
	{ itemName = "fiery heart", clientId = 9636, buy = 375 },
	{ itemName = "flask of embalming fluid", clientId = 11466, buy = 30 },
	{ itemName = "frazzle skin", clientId = 20199, buy = 400 },
	{ itemName = "frosty heart", clientId = 9661, buy = 280 },
	{ itemName = "gloom wolf fur", clientId = 22007, buy = 70 },
	{ itemName = "goosebump leather", clientId = 20205, buy = 650 },
	{ itemName = "green dragon leather", clientId = 5877, buy = 100 },
	{ itemName = "green dragon scale", clientId = 5920, buy = 100 },
	{ itemName = "hellspawn tail", clientId = 10304, buy = 475 },
	{ itemName = "lion's mane", clientId = 9691, buy = 60 },
	{ itemName = "little bowl of myrrh", clientId = 25702, buy = 500 },
	{ itemName = "metal spike", clientId = 10298, buy = 320 },
	{ itemName = "mooh'tah shell", clientId = 21202, buy = 110 },
	{ itemName = "moohtant horn", clientId = 21200, buy = 140 },
	{ itemName = "mystical hourglass", clientId = 9660, buy = 700 },
	{ itemName = "ogre nose ring", clientId = 22189, buy = 210 },
	{ itemName = "orc tooth", clientId = 10196, buy = 150 },
	{ itemName = "peacock feather fan", clientId = 21975, buy = 350 },
	{ itemName = "petrified scream", clientId = 10420, buy = 250 },
	{ itemName = "piece of dead brain", clientId = 9663, buy = 420 },
	{ itemName = "piece of scarab shell", clientId = 9641, buy = 45 },
	{ itemName = "piece of swampling wood", clientId = 17823, buy = 30 },
	{ itemName = "pile of grave earth", clientId = 11484, buy = 25 },
	{ itemName = "poisonous slime", clientId = 9640, buy = 50 },
	{ itemName = "polar bear paw", clientId = 9650, buy = 30 },
	{ itemName = "protective charm", clientId = 11444, buy = 60 },
	{ itemName = "quill", clientId = 28567, buy = 1100 },
	{ itemName = "rope belt", clientId = 11492, buy = 66 },
	{ itemName = "rorc feather", clientId = 18993, buy = 70 },
	{ itemName = "sabretooth", clientId = 10311, buy = 400 },
	{ itemName = "seacrest hair", clientId = 21801, buy = 260 },
	{ itemName = "silencer claws", clientId = 20200, buy = 390 },
	{ itemName = "slime heart", clientId = 21194, buy = 160 },
	{ itemName = "snake skin", clientId = 9694, buy = 400 },
	{ itemName = "some grimeleech wings", clientId = 22730, buy = 1200 },
	{ itemName = "strand of medusa hair", clientId = 10309, buy = 600 },
	{ itemName = "swamp grass", clientId = 9686, buy = 20 },
	{ itemName = "thick fur", clientId = 10307, buy = 150 },
	{ itemName = "vampire teeth", clientId = 9685, buy = 275 },
	{ itemName = "vexclaw talon", clientId = 22728, buy = 1100 },
	{ itemName = "war crystal", clientId = 9654, buy = 460 },
	{ itemName = "warmaster's wristguards", clientId = 10405, buy = 200 },
	{ itemName = "waspoid wing", clientId = 14081, buy = 190 },
	{ itemName = "wereboar hooves", clientId = 22053, buy = 175 },
	{ itemName = "winter wolf fur", clientId = 10295, buy = 20 },
	{ itemName = "wyrm scale", clientId = 9665, buy = 400 },
	{ itemName = "wyvern talisman", clientId = 9644, buy = 265 },
}
-- On buy npc shop message
npcType.onBuyItem = function(npc, player, itemId, subType, amount, ignore, inBackpacks, totalCost)
	npc:sellItem(player, itemId, amount, subType, 0, ignore, inBackpacks)
end
-- On sell npc shop message
npcType.onSellItem = function(npc, player, itemId, subtype, amount, ignore, name, totalCost)
	player:sendTextMessage(MESSAGE_INFO_DESCR, string.format("Sold %ix %s for %i gold.", amount, name, totalCost))
end
-- On check npc shop message (look item)
npcType.onCheckItem = function(npc, player, clientId, subType) end

npcType:register(npcConfig)
