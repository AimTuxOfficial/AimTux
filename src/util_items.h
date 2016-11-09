#pragma once

#include <string>
#include <map>
#include <algorithm>
#include "SDK/SDK.h"

namespace Util {
	namespace Items {
		/*
		 * Look up a ItemDefinitionIndex ordinal value by the symbolic name
		 * using an internal map
		 */
		enum ItemDefinitionIndex GetItemIndex(const std::string);

		/*
		 * Look up the symbolic name of a ItemDefinitionIndex ordinal value
		 * using an internal map
		 */
		std::string GetItemName(const enum ItemDefinitionIndex);
	}
}
