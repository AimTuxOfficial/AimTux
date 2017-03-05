#pragma once

#include "../Hooks/hooks.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"
#include "aimbot.h"

namespace AntiAim
{
bool GetBestHeadAngle(QAngle& angle);
void CreateMove(CUserCmd* cmd);
}
