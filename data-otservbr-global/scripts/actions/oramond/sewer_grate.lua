local upFloorIds = { 21298 }

local sewerGrate = Action()

function sewerGrate.onUse(cid, item, fromPosition, itemEx, toPosition)
	if isInArray(upFloorIds, item.itemid) == TRUE then
		fromPosition.x = fromPosition.x + 1
		fromPosition.z = fromPosition.z + 2
	end
	doTeleportThing(cid, fromPosition, FALSE)
	return TRUE
end

sewerGrate:id(21298)
sewerGrate:register()
