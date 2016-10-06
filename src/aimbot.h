#ifndef __AIMBOT_H_
#define __AIMBOT_H_

#include "settings.h"
#include "SDK.h"
#include "interfaces.h"
#include "entity.h"
#include "math.h"

namespace Aimbot
{
	extern bool AimStepInProgress;

	void CheckAngles(QAngle& angle);
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);

	void CreateMove(CUserCmd* cmd);
	void RCS(QAngle& angle);
}

#endif