#include "math.h"

void inline Math::SinCos(float radians, float *sine, float *cosine)
{
	register double __cosr, __sinr;
	__asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));

	*sine = __sinr;
	*cosine = __cosr;
}

void Math::AngleVectors (const QAngle &angles, Vector& forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	Math::SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	Math::SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

float Math::GetFov (const QAngle& viewAngle, const QAngle& aimAngle) {
	Vector ang, aim;

	Math::AngleVectors(viewAngle, aim);
	Math::AngleVectors(aimAngle, ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

void Math::VectorAngles(const Vector& forward, QAngle &angles) {
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}

	angles[2] = 0.0f;
}

QAngle Math::CalcAngle(Vector src, Vector dst)
{
	QAngle angles;
	Vector delta = src - dst;
	Math::VectorAngles(delta, angles);
	VectorNormalize(delta);
	return angles;
}