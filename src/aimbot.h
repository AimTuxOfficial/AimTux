#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"
#include "entity.h"
#include "math.h"

namespace Aimbot
{
	extern bool AimStepInProgress;

	void RCS(QAngle& angle, bool hasTarget);
	void Smooth(QAngle& angle, CUserCmd* cmd);

	void CreateMove(CUserCmd* cmd);
}