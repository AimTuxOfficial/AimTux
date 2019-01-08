#pragma once

#include "../SDK/vector.h"
#include "../SDK/IVModelRender.h"

namespace Chams
{
	//Hooks
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
}
