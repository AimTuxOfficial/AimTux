#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include <list>

namespace Entity
{
bool IsVisible(C_BasePlayer* player, Bone bone, float fov = 180.f, bool smoke_check = false);
bool IsPlanting(C_BasePlayer* player);
Bone GetBoneByName(C_BasePlayer* player, const char* boneName);
}