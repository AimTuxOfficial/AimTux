#include "antiaim.h"

bool Settings::AntiAim::enabled_Y = false;
bool Settings::AntiAim::enabled_X = false;
AntiAimType_Y Settings::AntiAim::type_Y = SPIN_FAST;
AntiAimType_X Settings::AntiAim::type_X = STATIC_DOWN;

void AntiAim::CreateMove (CUserCmd* cmd)
{
	if (!Settings::AntiAim::enabled_Y && !Settings::AntiAim::enabled_X)
		return;

	if (Aimbot::AimStepInProgress)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon()));

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (active_weapon && active_weapon->isGrenade()))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	static bool bFlip;
	static float fYaw = 0.0f;
	static float fPitch = 0.0f;

	bFlip = !bFlip;

	if (Settings::AntiAim::enabled_Y)
	{
		if (Settings::AntiAim::type_Y == SPIN_FAST || Settings::AntiAim::type_Y == SPIN_SLOW)
		{
			fYaw += Settings::AntiAim::type_Y == SPIN_FAST ? 40.0f : 5.0f;

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
		else if (Settings::AntiAim::type_X == JITTER_UP_DOWN_FAST || Settings::AntiAim::type_X == JITTER_UP_DOWN_SLOW)
		{
			fPitch += Settings::AntiAim::type_X == JITTER_UP_DOWN_FAST ? 40.0f : 5.0f;

			if (fPitch > 80.0f)
				fPitch -= 160.0f;

			angle.x = fPitch;
		}
		else if (Settings::AntiAim::type_X == ZERO)
		{
			angle.x = 0.f;
		}
	}

	Math::NormalizeAngles(angle);

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
