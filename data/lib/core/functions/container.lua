function Container.isContainer(self)
	return true
end

function Container.createLootItem(self, item, charm, prey)
	if self:getEmptySlots() == 0 then
		return true
	end

	local itemCount = 0
	local randvalue = getLootRandom()
	local lootBlockType = ItemType(item.itemId)
	local chanceTo = item.chance

	if not lootBlockType then
		return
	end

	-- Bestiary charm bonus
	if charm and lootBlockType:getType() == ITEM_TYPE_CREATUREPRODUCT then
		chanceTo = math.ceil((chanceTo * GLOBAL_CHARM_GUT) / 100)
	end

	-- Active prey loot bonus
	if prey ~= 100 then
		chanceTo = math.ceil((chanceTo * prey) / 100)
	end

	if randvalue < chanceTo then
		if lootBlockType:isStackable() then
			local maxc, minc = item.maxCount or 1, item.minCount or 1
			itemCount = math.max(0, randvalue % (maxc - minc + 1)) + minc			
		else
			itemCount = 1
		end
	end
	
	while (itemCount > 0) do
		local n = math.min(itemCount, 100)
		itemCount = itemCount - n
		
		local tmpItem = self:addItem(item.itemId, n)
		if not tmpItem then
			return false
		end

		if tmpItem:isContainer() then
			for i = 1, #item.childLoot do
				if not tmpItem:createLootItem(item.childLoot[i], charm, prey) then
					tmpItem:remove()
					return false
				end
			end
		end

		if item.subType ~= -1 then
			tmpItem:transform(item.itemId, item.subType)
		elseif lootBlockType:isFluidContainer() then
			tmpItem:transform(item.itemId, 0)
		end

		if item.actionId ~= -1 then
			tmpItem:setActionId(item.actionId)
		end

		if item.text and item.text ~= "" then
			tmpItem:setText(item.text)
		end
	end
	return true
end

function Container.isDepot(self)
	return (self:getId() == ITEM_DEPOT_I
	or self:getId() == ITEM_DEPOT_II
	or self:getId() == ITEM_DEPOT_III
	or self:getId() == ITEM_DEPOT_IV
	or self:getId() == ITEM_DEPOT_V
	or self:getId() == ITEM_DEPOT_VI
	or self:getId() == ITEM_DEPOT_VII
	or self:getId() == ITEM_DEPOT_VIII
	or self:getId() == ITEM_DEPOT_IX
	or self:getId() == ITEM_DEPOT_X
	or self:getId() == ITEM_DEPOT_XI
	or self:getId() == ITEM_DEPOT_XII
	or self:getId() == ITEM_DEPOT_XIII
	or self:getId() == ITEM_DEPOT_XIV
	or self:getId() == ITEM_DEPOT_XV
	or self:getId() == ITEM_DEPOT_XVI
	or self:getId() == ITEM_DEPOT_XVII
	or self:getId() == ITEM_DEPOT_XVIII)
end
