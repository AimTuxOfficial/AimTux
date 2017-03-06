#pragma once

#include "../SDK/SDK.h"
#include "util.h"
#include <algorithm>
#include <map>
#include <string>

namespace Util
{
namespace Items
{
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

    std::string GetItemEntityName(ItemDefinitionIndex index);

    std::string GetItemConfigEntityName(ItemDefinitionIndex index);

    std::string GetItemDisplayName(ItemDefinitionIndex index);

    bool IsKnife(ItemDefinitionIndex index);
    bool IsUtility(ItemDefinitionIndex index);
    bool IsGlove(ItemDefinitionIndex index);
    bool IsCTWeapon(ItemDefinitionIndex index);
    bool IsTWeapon(ItemDefinitionIndex index);
}
}
