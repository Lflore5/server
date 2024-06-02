-- Reward = bag -> sandals, 5 small stones, 50 gold coins
local goblintemple1Quest = Action()

function goblintemple1Quest.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local bagId = 2853
	local rewardIds = {
		{3551, 1},
		{1781, 5},
		{3031, 50}
	}

	for _, reward in ipairs(rewardIds) do
		local rewardId, rewardCount = reward[1], reward[2]
		if not player:canGetReward(rewardId, "goblintemple") then
			return true
		end
	end

	local bag = player:addItem(bagId, 1)
	if bag then
		for _, reward in ipairs(rewardIds) do
			local rewardId, rewardCount = reward[1], reward[2]
			bag:addItem(rewardId, rewardCount)
		end
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You have found a bag.")
		player:questKV("goblintemple"):set("completed", true)
	end

	return true
end

goblintemple1Quest:uid(14049)
goblintemple1Quest:register()
