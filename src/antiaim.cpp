#include "antiaim.h"

bool Settings::Aimbot::SpinBot::enabled = true;

bool AntiAim::CreateMove (CUserCmd* cmd)
{
	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
		return false;

	if (Settings::Aimbot::SpinBot::enabled)
	{
		static float fYaw = 0.0f;

		fYaw += 40.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.y = fYaw;
		angle.x = 89;
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);

	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}