local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_HOLYDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_HOLYDAMAGE)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_SMALLHOLY)

function onGetFormulaValues(player, level, maglevel)
	local min = (level / 5) + (maglevel * 1.79) + 11
	local max = (level / 5) + (maglevel * 3) + 18
	return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

local spell = Spell("instant")

function spell.onCastSpell(creature, var)
	return combat:execute(creature, var)
end

spell:group("attack")
spell:id(122)
spell:name("Divine Missile")
spell:words("exori san")
spell:castSound(SOUND_EFFECT_TYPE_SPELL_OR_RUNE)
spell:impactSound(SOUND_EFFECT_TYPE_SPELL_DIVINE_MISSILE)
spell:level(40)
spell:mana(20)
spell:isPremium(true)
spell:range(4)
spell:needCasterTargetOrDirection(true)
spell:blockWalls(true)
spell:cooldown(DEFAULT_COOLDOWN.SPELL)
spell:groupCooldown(DEFAULT_COOLDOWN.SPELL_GROUP)
spell:needLearn(false)
spell:vocation("paladin;true", "royal paladin;true")
spell:register()
