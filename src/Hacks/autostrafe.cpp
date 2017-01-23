#include "autostrafe.h"

bool Settings::AutoStrafe::enabled = false;
int Settings::AutoStrafe::type = AS_FORWARDS;
bool Settings::AutoStrafe::silent = true;

void LegitStrafe(C_BasePlayer* localplayer, CUserCmd* cmd)
{
	if (localplayer->GetFlags() & FL_ONGROUND)
		return;

	if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
		return;

	if (cmd->mousedx > 1 || cmd->mousedx < -1)
	{
		switch (Settings::AutoStrafe::type)
		{
			case AS_FORWARDS:
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
				break;
			case AS_BACKWARDS:
				cmd->sidemove = cmd->mousedx < 0.f ? 450.f : -450.f;
				break;
			case AS_LEFTSIDEWAYS:
				cmd->forwardmove = cmd->mousedx < 0.f ? -450.f : 450.f;
				break;
			case AS_RIGHTSIDEWAYS:
				cmd->forwardmove = cmd->mousedx < 0.f ? 450.f : -450.f;
				break;
		}
	}
}

void RageStrafe(C_BasePlayer* localplayer, CUserCmd* cmd)
{
	bool bWASD = true;

	if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
		bWASD = false;

	static bool left_right;
	bool forward_move = false;

	if (localplayer->GetFlags() & FL_ONGROUND)
	{
		if (input->IsButtonDown(KEY_SPACE) && bWASD)
			forward_move = true;
	}
	else
	{
		if (localplayer->GetFlags() & IN_JUMP)
		{
			cmd->buttons &= ~IN_JUMP;
			forward_move = true;
		}
	}

	if (forward_move && localplayer->GetVelocity().Length() <= 50.0f)
		cmd->forwardmove = 800.0f;

	float yaw_change = 0.0f;
	if (localplayer->GetVelocity().Length() > 50.f)
		yaw_change = 30.0f * fabsf(30.0f / localplayer->GetVelocity().Length());

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (active_weapon && !active_weapon->GetAmmo() == 0 && cmd->buttons & IN_ATTACK)
		yaw_change = 0.0f;

	QAngle angle = cmd->viewangles;

	if (!(localplayer->GetFlags() & FL_ONGROUND) && bWASD)
	{
		if (left_right || cmd->mousedx > 1)
		{
			angle.y += yaw_change;
			cmd->sidemove = 450.0f;
		}
		else if (!left_right || cmd->mousedx < 1)
		{
			angle.y -= yaw_change;
			cmd->sidemove = -450.0f;
		}

		left_right = !left_right;
	}

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);

	Vector moveold(cmd->forwardmove, cmd->sidemove, 0.0f);
	Math::CorrectMovement(angle, cmd, moveold.x, moveold.y);

	if (!Settings::AutoStrafe::silent)
		cmd->viewangles = angle;
}

void AutoStrafe::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AutoStrafe::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	switch (Settings::AutoStrafe::type)
	{
		case AS_FORWARDS:
		case AS_BACKWARDS:
		case AS_LEFTSIDEWAYS:
		case AS_RIGHTSIDEWAYS:
			LegitStrafe(localplayer, cmd);
			break;
		case AS_RAGE:
			RageStrafe(localplayer, cmd);
			break;
	}
}
