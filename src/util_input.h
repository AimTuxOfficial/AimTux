#pragma once

#include <string>
#include <map>
#include <algorithm>
#include "SDK/SDK.h"

namespace Util {
	namespace Input {
		/*
		 * Look up a ButtonCode_t ordinal value by the symbolic name
		 * using an internal map
		 */
		const enum ButtonCode_t GetButtonCode(const std::string);

		/*
		 * Look up the symbolic name of a ButtonCode_t ordinal value
		 * using an internal map
		 */
		const std::string GetButtonName(const enum ButtonCode_t);
	}
}
