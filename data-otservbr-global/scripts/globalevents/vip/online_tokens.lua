local config = {
	enabled = false,
	storage = Storage.VipSystem.OnlineTokensGain,
	checkDuplicateIps = false,

	tokenItemId = 14112, -- bar of gold (if you don't use custom item, you need to verify all drops in monsters)

	interval = 60 * 1000, -- 1 hora

	-- per hour | system will calculate how many tokens will be given and when
	-- put 0 in tokensPerHour.free to disable free from receiving tokens
	tokensPerHour = {
		free = 5,
		vip = 10,
	},

	awardOn = 5,
}

local onlineTokensEvent = GlobalEvent("GainTokenInterval")
local runsPerHour = 3600 / (config.interval / 1000)

local function tokensPerRun(tokensPerHour)
	return tokensPerHour / runsPerHour
end

function onlineTokensEvent.onThink(interval)
	local players = Game.getPlayers()
	if #players == 0 then
		return true
	end

	local tournamentCoinName = configManager.getString(configKeys.TOURNAMENT_COINS_NAME)
	local checkIp = {}
	for _, player in pairs(players) do
		if player:getGroup():getId() > GROUP_TYPE_SENIORTUTOR then
			goto continue
		end

		local ip = player:getIp()
		if ip ~= 0 and (not config.checkDuplicateIps or not checkIp[ip]) then
			checkIp[ip] = true
			local remainder = math.max(0, player:getStorageValue(config.storage)) / 10000000
			local tokens = tokensPerRun(player:isVip() and config.tokensPerHour.vip or config.tokensPerHour.free) + remainder
			player:setStorageValue(config.storage, tokens * 10000000)
			if tokens >= config.awardOn then
				local tokensMath = math.floor(tokens)
				local item = player:addItem(config.tokenItemId, tokensMath)
				if item then
					player:sendTextMessage(MESSAGE_STATUS_SMALL, string.format("Congratulations %s!\z You have received %d %s for being online.", player:getName(), tokensMath, tournamentCoinName))
				end
				player:setStorageValue(config.storage, (tokens - tokensMath) * 10000000)
			end
		end

		::continue::
	end
	return true
end

if config.enabled then
	onlineTokensEvent:interval(config.interval)
	onlineTokensEvent:register()
end
