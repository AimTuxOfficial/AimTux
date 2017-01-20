#pragma once

#include "util.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"

extern std::vector<std::pair<int, const char*>> guns;
extern std::vector<std::pair<int, const char*>> knives;
extern std::vector<std::pair<int, const char*>> weapon_skins;

namespace Skins
{
	void Localize();
}