#ifndef __MATH_H
#define __MATH_H

#include "SDK.h"

namespace Math {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors(const QAngle &angles, Vector &forward);
	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
	void VectorAngles(const Vector &forward, QAngle &angles);
	QAngle CalcAngle(Vector src, Vector dst);
}

#endif