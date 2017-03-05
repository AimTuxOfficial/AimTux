#pragma once

#include "../Hooks/hooks.h"
#include "../SDK/SDK.h"
#include "../Utils/entity.h"
#include "../interfaces.h"
#include "../settings.h"
#include <fstream>
#include <pwd.h>
#include <sstream>
#include <zconf.h>

namespace Chams
{
void DrawModelExecute(void* thisptr, void* context, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
void CreateMove(CUserCmd* cmd);
}
