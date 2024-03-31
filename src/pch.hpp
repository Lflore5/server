/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

// --------------------
// Internal Includes
// --------------------

// Utils
#include "utils/benchmark.hpp"
#include "utils/definitions.hpp"
#include "utils/simd.hpp"
#include "utils/vectorset.hpp"
#include "utils/arraylist.hpp"
#include "utils/vectorsort.hpp"

// --------------------
// STL Includes
// --------------------

#include <bitset>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <forward_list>
#include <list>
#include <map>
#include <unordered_set>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>
#include <regex>
#include <set>
#include <thread>
#include <vector>
#include <variant>
#include <numeric>
#include <cmath>
#include <mutex>

// --------------------
// System Includes
// --------------------

#ifdef _WIN32
	#include <io.h> // For _isatty() on Windows
	#define isatty _isatty
	#define STDIN_FILENO _fileno(stdin)
#else
	#include <unistd.h> // For isatty() on Linux and other POSIX systems
#endif

#ifdef OS_WINDOWS
	#include <conio.h>
#endif

// --------------------
// Third Party Includes
// --------------------

// ABSL
#include <absl/numeric/int128.h>

// ASIO
#include <asio.hpp>

// CURL
#include <curl/curl.h>

// FMT
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/args.h>

// FMT Custom Formatter for Enums
template <typename E>
struct fmt::formatter<E, std::enable_if_t<std::is_enum_v<E>, char>> : formatter<std::underlying_type_t<E>> {
	template <typename FormatContext>
	auto format(E e, FormatContext &ctx) {
		return formatter<std::underlying_type_t<E>>::format(
			static_cast<std::underlying_type_t<E>>(e), ctx
		);
	}
};

// GMP
#include <gmp.h>

// JSON
#include <json/json.h>

// LUA
#if __has_include("luajit/lua.hpp")
	#include <luajit/lua.hpp>
#else
	#include <lua.hpp>
#endif

#include "lua/global/shared_object.hpp"

/**
 * @brief Magic Enum is a C++ library that facilitates easy conversion between enums and strings.
 * By default, the range of supported enum values is from -128 to 128. We need extends that range.
 *
 * @def MAGIC_ENUM_RANGE_MIN
 * @note Sets the lower limit of the enum value range to -500.
 *
 * @def MAGIC_ENUM_RANGE_MAX
 * @note Sets the upper limit of the enum value range to 500.
 */
#define MAGIC_ENUM_RANGE_MIN -500
#define MAGIC_ENUM_RANGE_MAX 500
#include <magic_enum.hpp>

// Memory Mapped File
#include <mio/mmap.hpp>

// MySQL
#if __has_include("<mysql.h>")
	#include <mysql.h>
#else
	#include <mysql/mysql.h>
#endif

#include <mysql/errmsg.h>

// Parallel Hash Map
#include <parallel_hashmap/phmap.h>
#include <parallel_hashmap/btree.h>

// PugiXML
#include <pugixml.hpp>

// Zlib
#include <zlib.h>

#include <boost/di.hpp>

// -------------------------
// GIT Metadata Includes
// -------------------------

#if __has_include("gitmetadata.h")
	#include "gitmetadata.h"
#endif

// ---------------------
// Standard STL Includes
// ---------------------

#include <string>
#include <iostream>

/**
 * Static custom libraries that can be pre-compiled like DI and messaging
 */
#include "lib/messaging/message.hpp"
#include "lib/messaging/command.hpp"
#include "lib/messaging/event.hpp"
#include "lib/logging/log_with_spd_log.hpp"

#include <eventpp/utilities/scopedremover.h>
#include <eventpp/eventdispatcher.h>

#include "lua/global/shared_object.hpp"

constexpr std::string_view methodName(const char* s) {
	std::string_view prettyFunction(s);
	size_t bracket = prettyFunction.rfind('(');
	size_t space = prettyFunction.rfind(' ', bracket) + 1;
	return prettyFunction.substr(space, bracket - space);
}

#if defined(__GNUC__) || defined(__clang__)
	#define __METHOD_NAME__ methodName(__PRETTY_FUNCTION__)
#elif defined(_MSC_VER)
	#define __METHOD_NAME__ methodName(__FUNCSIG__)
#else
	#error "Compiler not supported"
#endif
