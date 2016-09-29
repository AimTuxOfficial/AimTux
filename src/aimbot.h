#ifndef __AIMBOT_H_
#define __AIMBOT_H_

#include "settings.h"
#include "SDK.h"
#include "interfaces.h"
#include "bone.h"

namespace Aimbot
{
	void CheckAngle (QAngle& angle);
	bool CreateMove (CUserCmd* cmd);
	void RCS (QAngle& angle);
}

#endif