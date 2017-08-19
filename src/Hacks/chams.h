#pragma once

#include "../Hooks/hooks.h"
#include "../interfaces.h"
#include "../settings.h"

namespace Chams
{
	//Hooks
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
}
