#pragma once

#include "util.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

extern std::vector<std::pair<int, const char*>> weaponSkins;
extern std::vector<std::pair<int, const char*>> gloveSkins;

extern int filterBloodhound[4];
extern int filterSporty[4];
extern int filterSlick[4];
extern int filterWrap[4];
extern int filterMoto[4];
extern int filterSpecialist[4];

namespace Skins
{
	void Localize();
}
