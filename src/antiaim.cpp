#include "antiaim.h"

/*
 * 0 => none
 * 1 => spinbot
 * 2 => jitter
 * 3 => sideways
 */
int Settings::AntiAim::type = 1;

bool AntiAim::CreateMove (CUserCmd* cmd)
{
	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
		return false;

	if (Settings::AntiAim::type == 1)
	{
		static float fYaw = 0.0f;
		fYaw += 40.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.x = 89;
		angle.y = fYaw;
	}
	else if (Settings::AntiAim::type == 2)
	{
		static bool yFlip = false;
		yFlip = !yFlip;

		angle.y = yFlip ? 270.0f : 90.0f;
	}
	else if (Settings::AntiAim::type == 3)
	{
		static bool yFlip = false;
		yFlip = !yFlip;

		if (yFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);

	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}