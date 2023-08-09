/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "creatures/players/account/account.hpp"
#include "lua/creature/talkaction.h"
#include "lua/functions/events/talk_action_functions.hpp"

int TalkActionFunctions::luaCreateTalkAction(lua_State* L) {
	// TalkAction(words) or TalkAction(word1, word2, word3)
	std::vector<std::string> wordsVector;
	for (int i = 2; i <= lua_gettop(L); i++) {
		wordsVector.push_back(getString(L, i));
	}

	auto talkActionPtr = std::make_shared<TalkAction>(getScriptEnv()->getScriptInterface());
	talkActionPtr->setWords(std::move(wordsVector));
	pushUserdata<TalkAction>(L, talkActionPtr);
	setMetatable(L, -1, "TalkAction");
	return 1;
}

int TalkActionFunctions::luaTalkActionOnSay(lua_State* L) {
	// talkAction:onSay(callback)
	auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	if (!talkActionPtr->loadCallback()) {
		pushBoolean(L, false);
		return 1;
	}
	pushBoolean(L, true);
	return 1;
}

int TalkActionFunctions::luaTalkActionGroupType(lua_State* L) {
	// talkAction:groupType(GroupType = GROUP_TYPE_NORMAL)
	auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	account::GroupType groupType;

	int type = lua_type(L, 2);
	if (type == LUA_TNUMBER) {
		groupType = static_cast<account::GroupType>(getNumber<uint8_t>(L, 2));
	} else if (type == LUA_TSTRING) {
		std::string strValue = getString(L, 2);
		if (strValue == "normal") {
			groupType = account::GROUP_TYPE_NORMAL;
		} else if (strValue == "tutor") {
			groupType = account::GROUP_TYPE_TUTOR;
		} else if (strValue == "seniortutor" || strValue == "senior tutor") {
			groupType = account::GROUP_TYPE_SENIORTUTOR;
		} else if (strValue == "gamemaster" || strValue == "gm") {
			groupType = account::GROUP_TYPE_GAMEMASTER;
		} else if (strValue == "communitymanager" || strValue == "cm" || strValue == "community manager") {
			groupType = account::GROUP_TYPE_COMMUNITYMANAGER;
		} else if (strValue == "god") {
			groupType = account::GROUP_TYPE_GOD;
		} else {
			auto string = fmt::format("Invalid group type string value {} for group type for script: {}", strValue, getScriptEnv()->getScriptInterface()->getLoadingScriptName());
			reportErrorFunc(string);
			pushBoolean(L, false);
			return 1;
		}
	} else {
		auto string = fmt::format("Expected number or string value for group type for script: {}", getScriptEnv()->getScriptInterface()->getLoadingScriptName());
		reportErrorFunc(string);
		pushBoolean(L, false);
		return 1;
	}

	talkActionPtr->setGroupType(groupType);
	pushBoolean(L, true);
	return 1;
}

int TalkActionFunctions::luaTalkActionRegister(lua_State* L) {
	// talkAction:register()
	auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	if (!talkActionPtr->isLoadedCallback()) {
		pushBoolean(L, false);
		return 1;
	}

	if (talkActionPtr->getGroupType() == account::GROUP_TYPE_NONE) {
		auto string = fmt::format("TalkAction with name {} does't have groupType", talkActionPtr->getWords());
		reportErrorFunc(string);
		pushBoolean(L, false);
		return 1;
	}

	pushBoolean(L, g_talkActions().registerLuaEvent(talkActionPtr));
	return 1;
}

int TalkActionFunctions::luaTalkActionSeparator(lua_State* L) {
	// talkAction:separator(sep)
	auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	talkActionPtr->setSeparator(getString(L, 2));
	pushBoolean(L, true);
	return 1;
}

int TalkActionFunctions::luaTalkActionGetName(lua_State* L) {
	// local name = talkAction:getName()
	const auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	pushString(L, talkActionPtr->getWords());
	return 1;
}

int TalkActionFunctions::luaTalkActionGetGroupType(lua_State* L) {
	// local groupType = talkAction:getGroupType()
	const auto talkActionPtr = getUserdataShared<TalkAction>(L, 1);
	if (!talkActionPtr) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_TALK_ACTION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	lua_pushnumber(L, static_cast<lua_Number>(talkActionPtr->getGroupType()));
	return 1;
}
