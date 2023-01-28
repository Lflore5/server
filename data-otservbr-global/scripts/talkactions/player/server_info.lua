local serverInfo = TalkAction("!serverinfo")

function serverInfo.onSay(player, words, param)
	local text = "Server Info: \n\n"
	.. "\nExp rate: x" .. configManager.getNumber(configKeys.RATE_EXPERIENCE)
	.. "\nExp rate stages: x" .. getRateFromTable(experienceStages, player:getLevel(), configManager.getNumber(configKeys.RATE_EXPERIENCE))
	.. "\nSword Skill rate: x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_SWORD), configRateSkill)
	.. "\nClub Skill rate: x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_CLUB), configRateSkill)
	.. "\nAxe Skill rate: x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_AXE), configRateSkill)
	.. "\nDistance Skill rate : x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_DISTANCE), configRateSkill)
	.. "\nShield Skill rate : x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_SHIELD), configRateSkill)
	.. "\nFist Skill rate : x" .. getRateFromTable(skillsStages, player:getSkillLevel(SKILL_FIST), configRateSkill)
	.. "\nMagic rate : x" .. getRateFromTable(magicLevelStages, player:getBaseMagicLevel(), configManager.getNumber(configKeys.RATE_MAGIC))
	.. "\nLoot rate: x" .. configManager.getNumber(configKeys.RATE_LOOT)
	.. "\nSpawns rate: x" .. configManager.getNumber(configKeys.RATE_SPAWN)
	.. "\nLevel to buy house " .. configManager.getNumber(configKeys.HOUSE_BUY_LEVEL)
    .. "\nProtection level: " .. configManager.getNumber(configKeys.PROTECTION_LEVEL)
	.. "\nWorldType: " .. configManager.getString(configKeys.WORLD_TYPE)
	.. "\nKills/day to red skull: " .. configManager.getNumber(configKeys.DAY_KILLS_TO_RED)
	.. "\nKills/week to red skull: " .. configManager.getNumber(configKeys.WEEK_KILLS_TO_RED)
	.. "\nKills/month to red skull: " .. configManager.getNumber(configKeys.MONTH_KILLS_TO_RED)
	.. "\nServer Save: " .. configManager.getString(configKeys.GLOBAL_SERVER_SAVE_TIME)
	player:showTextDialog(34266, text)
	return false
end

serverInfo:separator(" ")
serverInfo:register()