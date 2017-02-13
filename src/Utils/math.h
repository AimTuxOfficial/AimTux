#pragma once

#include "../SDK/SDK.h"

namespace Math {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors(const QAngle &angles, Vector &forward);
	void NormalizeAngles(QAngle& angle);
	void ClampAngles(QAngle& angle);
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
	void VectorAngles(const Vector &forward, QAngle &angles);
	QAngle CalcAngle(Vector src, Vector dst);
}