local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_STUN)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_NONE)

local condition = Condition(CONDITION_INTENSEHEX)
condition:setParameter(CONDITION_PARAM_TICKS, 3000)
combat:addCondition(condition)

local spell = Spell("instant")

function spell.onCastSpell(creature, var)
	local monster = creature:getMonster()
	if monster and monster:soulPit() and table.contains(creature:getEvents(CREATURE_EVENT_THINK), "opressorSoulPit") then
		return combat:execute(creature, var)
	end

	return true
end

spell:name("soulpit intensehex")
spell:words("###940")
spell:blockWalls(true)
spell:needTarget(true)
spell:needLearn(true)
spell:register()
