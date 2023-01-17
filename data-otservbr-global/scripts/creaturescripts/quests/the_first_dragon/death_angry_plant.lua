local deathAngryPlant = CreatureEvent("AngryPlantDeath")

function deathAngryPlant.onDeath(creature, corpse, lasthitkiller, mostdamagekiller, lasthitunjustified, mostdamageunjustified)
	if corpse then
		corpse:setAttribute(UNIQUEID, 1066)
	end
	return true
end

deathAngryPlant:register()
