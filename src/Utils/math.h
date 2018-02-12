#pragma once

#include "../SDK/SDK.h"

namespace Math {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors(const QAngle &angles, Vector &forward);
	void NormalizeAngles(QAngle& angle);
	void ClampAngles(QAngle& angle);
	void CorrectMovement(const QAngle &vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
	float DotProduct(const Vector &v1, const float* v2);
	void VectorAngles(const Vector &forward, QAngle &angles);
	void VectorTransform (const Vector &in1, const matrix3x4_t& in2, Vector &out);
	QAngle CalcAngle(const Vector &src, const Vector &dst);
	float float_rand( float min, float max );
}