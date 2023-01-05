/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
*/

#include "pch.hpp"

#include "lua/functions/events/global_event_functions.hpp"
#include "game/game.h"
#include "lua/global/globalevent.h"
#include "lua/scripts/scripts.h"
#include "utils/tools.h"

int GlobalEventFunctions::luaCreateGlobalEvent(lua_State* L) {
	GlobalEvent* global = new GlobalEvent(getScriptEnv()->getScriptInterface());
	if (global) {
		global->setName(getString(L, 2));
		global->setEventType(GLOBALEVENT_NONE);
		pushUserdata<GlobalEvent>(L, global);
		setMetatable(L, -1, "GlobalEvent");
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GlobalEventFunctions::luaGlobalEventType(lua_State* L) {
	// globalevent:type(callback)
	GlobalEvent* global = getUserdata<GlobalEvent>(L, 1);
	if (global) {
		std::string typeName = getString(L, 2);
		std::string tmpStr = asLowerCaseString(typeName);
		if (tmpStr == "startup") {
			global->setEventType(GLOBALEVENT_STARTUP);
		} else if (tmpStr == "shutdown") {
			global->setEventType(GLOBALEVENT_SHUTDOWN);
		} else if (tmpStr == "record") {
			global->setEventType(GLOBALEVENT_RECORD);
		} else if (tmpStr == "periodchange") {
			global->setEventType(GLOBALEVENT_PERIODCHANGE);
		} else if (tmpStr == "onthink") {
			global->setEventType(GLOBALEVENT_ON_THINK);
		} else {
			SPDLOG_ERROR("[GlobalEventFunctions::luaGlobalEventType] - "
                         "Invalid type for global event: {}");
			pushBoolean(L, false);
		}
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GlobalEventFunctions::luaGlobalEventRegister(lua_State* L) {
	// globalevent:register()
	GlobalEvent* globalevent = getUserdata<GlobalEvent>(L, 1);
	if (globalevent) {
		if (!globalevent->isLoadedCallback()) {
			pushBoolean(L, false);
			return 1;
		}
		pushBoolean(L, g_globalEvents().registerLuaEvent(globalevent));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GlobalEventFunctions::luaGlobalEventOnCallback(lua_State* L) {
	// globalevent:onThink / record / etc. (callback)
	GlobalEvent* globalevent = getUserdata<GlobalEvent>(L, 1);
	if (globalevent) {
		if (!globalevent->loadCallback()) {
			pushBoolean(L, false);
			return 1;
		}
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GlobalEventFunctions::luaGlobalEventTime(lua_State* L) {
	// globalevent:time(time)
	GlobalEvent* globalevent = getUserdata<GlobalEvent>(L, 1);
	if (globalevent) {
		std::string timer = getString(L, 2);
		std::vector<int32_t> params = vectorAtoi(explodeString(timer, ":"));

		int32_t hour = params.front();
		if (hour < 0 || hour > 23) {
			SPDLOG_ERROR("[GlobalEventFunctions::luaGlobalEventTime] - "
                         "Invalid hour {} for globalevent with name: {}",
                         timer, globalevent->getName());
			pushBoolean(L, false);
			return 1;
		}

		globalevent->setInterval(hour << 16);

		int32_t min = 0;
		int32_t sec = 0;
		if (params.size() > 1) {
			min = params[1];
			if (min < 0 || min > 59) {
				SPDLOG_ERROR("[GlobalEventFunctions::luaGlobalEventTime] - "
                              "Invalid minute: {} for globalevent with name: {}",
                              timer, globalevent->getName());
				pushBoolean(L, false);
				return 1;
			}

			if (params.size() > 2) {
				sec = params[2];
				if (sec < 0 || sec > 59) {
					SPDLOG_ERROR("[GlobalEventFunctions::luaGlobalEventTime] - "
                              "Invalid minute: {} for globalevent with name: {}",
                              timer, globalevent->getName());
					pushBoolean(L, false);
					return 1;
				}
			}
		}

		// Create an alias for the std::chrono::system_clock type so it can be referred to as "chronoclock"
		using chronoclock = std::chrono::system_clock;
		// Get the current time as a time_point object using std::chrono::system_clock
		chronoclock::time_point chrono_current_time = chronoclock::now();
		// Convert hours, minutes and seconds to total seconds and create a time_point object for the target time
		chronoclock::time_point chrono_target_time(chronoclock::time_point::duration(hour * 3600 + min * 60 + sec));

		// Calculate the difference between the current time and the target time in seconds using std::chrono::duration_cast
		auto difference = std::chrono::duration_cast<std::chrono::seconds>(chrono_target_time - chrono_current_time).count();
		// If the difference is negative, add 86400 seconds (1 day) to it
		if (difference < 0) {
			difference += 86400;
		}

		globalevent->setNextExecution(getTimeNow() + difference);
		globalevent->setEventType(GLOBALEVENT_TIMER);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GlobalEventFunctions::luaGlobalEventInterval(lua_State* L) {
	// globalevent:interval(interval)
	GlobalEvent* globalevent = getUserdata<GlobalEvent>(L, 1);
	if (globalevent) {
		globalevent->setInterval(getNumber<uint32_t>(L, 2));
		globalevent->setNextExecution(OTSYS_TIME() + getNumber<uint32_t>(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
