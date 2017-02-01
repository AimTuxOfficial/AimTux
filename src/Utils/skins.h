#pragma once

#include "util.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

extern std::vector<std::pair<int, const char*>> guns;
extern std::vector<std::pair<int, const char*>> weaponSkins;
extern std::vector<std::pair<int, const char*>> gloveSkins;

namespace Skins
{
	void Localize();

	AttribItem_t& GetSkinConfig(ItemDefinitionIndex itemDefinitionIndex);
}
