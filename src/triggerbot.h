#ifndef __TRIGGERBOT_H
#define __TRIGGERBOT_H

#include "settings.h"
#include "SDK.h"
#include "interfaces.h"
#include "entity.h"

namespace Triggerbot {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors (const QAngle &angles, Vector& forward);

	void CreateMove (CUserCmd* cmd);
};

#endif