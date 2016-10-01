#include "antiaim.h"

bool Settings::AntiAim::enabled = true;
AntiAimType Settings::AntiAim::type = BACKWARDS;

void AntiAim::CreateMove (CUserCmd* cmd)
{
	if (!Settings::AntiAim::enabled)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
		return;

	C_BaseEntity* localplayer = reinterpret_cast<C_BaseEntity*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	static bool yFlip;
	static float fYaw = 0.0f;

	yFlip = !yFlip;

	if (Settings::AntiAim::type == SPIN)
	{
		fYaw += 40.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.x = 89;
		angle.y = fYaw;
	}
	else if (Settings::AntiAim::type == JITTER)
	{
		angle.y = yFlip ? 270.0f : 90.0f;
	}
	else if (Settings::AntiAim::type == SIDE)
	{
		if (yFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	}
	else if (Settings::AntiAim::type == BACKWARDS)
	{
		angle.y -= 180.0f;
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);

	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}