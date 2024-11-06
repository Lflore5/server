/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

struct Aura {
	Aura(uint16_t initId, const std::string &name) :
		id(initId), name(name) { }
	uint8_t id;
	std::string name;
};

struct Shader {
	Shader(uint8_t initId, const std::string &name) :
		id(initId), name(name) { }
	uint8_t id;
	std::string name;
};

struct Effect {
	Effect(uint16_t initId, const std::string &name) :
		id(initId), name(name) { }
	uint8_t id;
	std::string name;
};

struct Wing {
	Wing(uint16_t initId, const std::string &name) :
		id(initId), name(name) { }
	uint8_t id;
	std::string name;
};

class Attachedeffects {
public:
	bool reload();
	bool loadFromXml();

	std::shared_ptr<Aura> getAuraByID(uint8_t id);
	std::shared_ptr<Effect> getEffectByID(uint8_t id);
	std::shared_ptr<Wing> getWingByID(uint8_t id);
	std::shared_ptr<Shader> getShaderByID(uint8_t id);

	std::shared_ptr<Aura> getAuraByName(const std::string &name);
	std::shared_ptr<Shader> getShaderByName(const std::string &name);
	std::shared_ptr<Effect> getEffectByName(const std::string &name);
	std::shared_ptr<Wing> getWingByName(const std::string &name);

	[[nodiscard]] const phmap::parallel_flat_hash_set<std::shared_ptr<Aura>> &getAuras() const {
		return auras;
	}
	[[nodiscard]] const phmap::parallel_flat_hash_set<std::shared_ptr<Shader>> &getShaders() const {
		return shaders;
	}
	[[nodiscard]] const phmap::parallel_flat_hash_set<std::shared_ptr<Effect>> &getEffects() const {
		return effects;
	}
	[[nodiscard]] const phmap::parallel_flat_hash_set<std::shared_ptr<Wing>> &getWings() const {
		return wings;
	}

private:
	phmap::parallel_flat_hash_set<std::shared_ptr<Aura>> auras;
	phmap::parallel_flat_hash_set<std::shared_ptr<Shader>> shaders;
	phmap::parallel_flat_hash_set<std::shared_ptr<Effect>> effects;
	phmap::parallel_flat_hash_set<std::shared_ptr<Wing>> wings;
};
