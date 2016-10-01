#include "antiaim.h"

bool Settings::AntiAim::enabled_Y = true;
bool Settings::AntiAim::enabled_X = true;
AntiAimType_Y Settings::AntiAim::type_Y = SPIN;
AntiAimType_X Settings::AntiAim::type_X = STATIC_DOWN;

void AntiAim::CreateMove (CUserCmd* cmd)
{
	if (!Settings::AntiAim::enabled_Y && !Settings::AntiAim::enabled_X)
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

	static bool bFlip;
	static float fYaw = 0.0f;

	bFlip = !bFlip;

	if (Settings::AntiAim::enabled_Y)
	{
		if (Settings::AntiAim::type_Y == SPIN)
		{
			fYaw += 40.0f;

			if (fYaw > 180.0f)
				fYaw -= 360.0f;

			angle.y = fYaw;
		}
		else if (Settings::AntiAim::type_Y == JITTER)
		{
			angle.y = bFlip ? 270.0f : 90.0f;
		}
		else if (Settings::AntiAim::type_Y == SIDE)
		{
			if (bFlip)
				angle.y += 90.0f;
			else
				angle.y -= 90.0f;
		}
		else if (Settings::AntiAim::type_Y == BACKWARDS)
		{
			angle.y -= 180.0f;
		}
	}

	if (Settings::AntiAim::enabled_X)
	{
		if (Settings::AntiAim::type_X == STATIC_UP)
		{
			angle.x = -271.f;
		}
		else if (Settings::AntiAim::type_X == STATIC_DOWN)
		{
			angle.x = 271.f;
		}
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);

	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}