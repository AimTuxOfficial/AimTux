#include "antiaim.h"

bool Settings::AntiAim::enabled = true;
AntiAimType Settings::AntiAim::type = JITTER;

bool AntiAim::CreateMove (CUserCmd* cmd)
{
	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
		return false;

	if (Settings::AntiAim::type == SPIN)
	{
		static float fYaw = 0.0f;
		fYaw += 40.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.x = 89;
		angle.y = fYaw;
	}
	else if (Settings::AntiAim::type == JITTER)
	{
		static bool yFlip;
		yFlip = !yFlip;

		angle.y = yFlip ? 270.0f : 90.0f;
	}
	else if (Settings::AntiAim::type == SIDE)
	{
		static bool yFlip;
		yFlip = !yFlip;

		if (yFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	}
	else if (Settings::AntiAim::type == STATIC)
	{
		static bool yFlip;
		static bool yFlip2;
		yFlip = !yFlip;
		yFlip2 = !yFlip2;

		if (yFlip)
		{
			if (yFlip2)
			{
				angle.y += 90.0f;
			}
			else
			{
				angle.y -= 90.0f;
			}
		}
		else
		{
			angle.y += 180.0f;
		}
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);

	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}