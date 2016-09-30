#ifndef __AIMBOT_H_
#define __AIMBOT_H_

#include "settings.h"
#include "SDK.h"
#include "interfaces.h"
#include "bone.h"
#include "entity.h"

namespace Aimbot
{
	void CheckAngles (QAngle& angle);
	void CorrectMovement (QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);

	bool CreateMove (CUserCmd* cmd);
	void RCS (QAngle& angle);
}

#endif