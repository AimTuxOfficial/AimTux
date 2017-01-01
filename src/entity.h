#pragma once

#include <list>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Entity
{
	bool IsVisible(C_BasePlayer* player, int bone);
	bool IsPlanting(C_BasePlayer* player);
	int GetBoneByName(C_BasePlayer* player, const char* boneName);
}