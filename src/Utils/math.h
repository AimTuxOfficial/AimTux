#pragma once

#include "../SDK/SDK.h"

namespace Math {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors(const QAngle &angles, Vector &forward);
	void NormalizeAngles(QAngle& angle);
	void ClampAngles(QAngle& angle);
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
	float DotProduct(Vector &v1, const float* v2);
	void VectorAngles(const Vector &forward, QAngle &angles);
	void VectorTransform (Vector &in1, const matrix3x4_t& in2, Vector &out);
	QAngle CalcAngle(Vector src, Vector dst);
	float float_rand( float min, float max );
}