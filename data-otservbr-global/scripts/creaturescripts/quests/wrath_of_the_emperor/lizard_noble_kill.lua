local lizardNobleKill = CreatureEvent("LizardNobleDeath")
function lizardNobleKill.onDeath(creature, _corpse, _lastHitKiller, mostDamageKiller)
	onDeathForParty(creature, mostDamageKiller, function(creature, player)
		local storage = player:getStorageValue(Storage.WrathoftheEmperor.Mission07)
		if storage >= 0 and storage < 6 then
			player:setStorageValue(Storage.WrathoftheEmperor.Mission07, math.max(1, storage) + 1)
		end
	end)
	return true
end

lizardNobleKill:register()
