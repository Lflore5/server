local upFloorIds = {435, 1948, 1968, 5542, 20474, 20475, 28656, 31129, 31130, 31262, 34243}

local teleport = Action()

function teleport.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if table.contains(upFloorIds, item.itemid) then
		fromPosition:moveUpstairs()
	else
		fromPosition.z = fromPosition.z + 1
	end
	player:teleportTo(fromPosition, false)
	return true
end

for index, value in ipairs(upFloorIds) do
    teleport:id(value)
end

teleport:register()
