#pragma once

#include <list>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Entity
{
	bool IsVisible(C_BaseEntity *pEntity, int bone);
	int GetBoneByName(C_BaseEntity *pEntity, const char* boneName);
}