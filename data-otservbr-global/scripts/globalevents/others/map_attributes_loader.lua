local function loadMapAttributes()
	logger.debug("Loading map attributes")
	loadLuaMapSign(SignTable)
	loadLuaMapBookDocument(BookDocumentTable)

	loadMapActionsAndUniques()
	logger.debug("Loaded all actions and uniques in the map")
end

local function loadMapActionsAndUniques()
	loadLuaMapAction(ChestAction)
	loadLuaMapUnique(ChestUnique)
	loadLuaMapAction(CorpseAction)
	loadLuaMapUnique(CorpseUnique)
	loadLuaMapAction(KeyDoorAction)
	loadLuaMapAction(LevelDoorAction)
	loadLuaMapAction(QuestDoorAction)
	loadLuaMapUnique(QuestDoorUnique)
	loadLuaMapAction(ItemAction)
	loadLuaMapUnique(ItemUnique)
	loadLuaMapAction(ItemUnmovableAction)
	loadLuaMapAction(LeverAction)
	loadLuaMapUnique(LeverUnique)
	loadLuaMapAction(TeleportAction)
	loadLuaMapUnique(TeleportUnique)
	loadLuaMapAction(TeleportItemAction)
	loadLuaMapUnique(TeleportItemUnique)
	loadLuaMapAction(TileAction)
	loadLuaMapUnique(TileUnique)
	loadLuaMapAction(TilePickAction)
	CreateMapItem(CreateItemOnMap)
	updateKeysStorage(QuestKeysUpdate)
end

local function resetGlobalStorages()
	for i = 1, #startupGlobalStorages do
		Game.setStorageValue(startupGlobalStorages[i], 0)
	end
end

local function resetFerumbrasAscendantQuestHabitats()
	for i = 1, #GlobalStorage.FerumbrasAscendant.Habitats do
		local storage = GlobalStorage.FerumbrasAscendant.Habitats[i]
		Game.setStorageValue(storage, 0)
	end
end

local mapAttributesLoader = GlobalEvent("Map Attributes Loader")

function mapAttributesLoader.onStartup()
	loadMapAttributes()
	resetGlobalStorages()
	resetFerumbrasAscendantQuestHabitats()
end

mapAttributesLoader:register()
