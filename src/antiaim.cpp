#include "antiaim.h"

bool Settings::AntiAim::enabled_Y = false;
bool Settings::AntiAim::enabled_X = false;
AntiAimType_Y Settings::AntiAim::type_Y = SPIN_FAST;
AntiAimType_X Settings::AntiAim::type_X = STATIC_DOWN;

void AntiAim::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AntiAim::enabled_Y && !Settings::AntiAim::enabled_X)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::AimStepInProgress)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (active_weapon && active_weapon->IsGrenade()))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	static bool bFlip;
	static float fYaw = 0.0f;

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
		else if (Settings::AntiAim::type_Y == FAKE4)
		{
			if (bFlip)
				angle.y += 140.0f;
			else
				angle.y -= 40.0f;

			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == BACKWARDS_FAKE)
		{
			angle.y -= bFlip ? 0.0f : 180.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FAKE_RIGHT)
		{
			angle.y -= bFlip ? 90.0f : -90.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FAKE_LEFT)
		{
			angle.y -= bFlip ? -90.0f : 90.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FLIP_FAKE)
		{
			static bool bFlip_0;
			
			if (bFlip)
			{
				
				bFlip_0 = !bFlip_0;
				angle.y -= bFlip_0 ? 90.0f : -90.0f;
			}
			else
				angle.y -= 180.0f;
			
			CreateMove::SendPacket = bFlip;
		}
	}

	if (Settings::AntiAim::enabled_X)
	{
		if (Settings::AntiAim::type_X == STATIC_UP)
		{
			angle.x = -89.0f;
		}
		else if (Settings::AntiAim::type_X == STATIC_DOWN)
		{
			angle.x = 89.0f;
		}
#ifdef UNTRUSTED_SETTINGS
		else if (Settings::AntiAim::type_X == STATIC_UP_FAKE)
		{
			angle.x = bFlip ? 89.0f : -89.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_X == STATIC_DOWN_FAKE)
		{
			angle.x = bFlip ? -89.0f : 89.0f;
			CreateMove::SendPacket = bFlip;
		}
#endif
	}

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
