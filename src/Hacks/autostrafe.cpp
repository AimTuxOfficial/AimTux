#include "autostrafe.h"

bool Settings::AutoStrafe::enabled = false;
AutostrafeType Settings::AutoStrafe::type = AutostrafeType::AS_FORWARDS;
bool Settings::AutoStrafe::silent = true;

void LegitStrafe(C_BasePlayer* localplayer, CUserCmd* cmd)
{
	if (localplayer->GetFlags() & FL_ONGROUND)
		return;

	if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
		return;

	if (cmd->mousedx <= 1 && cmd->mousedx >= -1)
		return;

	switch (Settings::AutoStrafe::type)
	{
		case AutostrafeType::AS_FORWARDS:
			cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			break;
		case AutostrafeType::AS_BACKWARDS:
			cmd->sidemove = cmd->mousedx < 0.f ? 450.f : -450.f;
			break;
		case AutostrafeType::AS_LEFTSIDEWAYS:
			cmd->forwardmove = cmd->mousedx < 0.f ? -450.f : 450.f;
			break;
		case AutostrafeType::AS_RIGHTSIDEWAYS:
			cmd->forwardmove = cmd->mousedx < 0.f ? 450.f : -450.f;
			break;
		default:
			break;
	}
}

void RageStrafe(C_BasePlayer* localplayer, CUserCmd* cmd)
{
	static bool leftRight;
	bool inMove = cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT;

	if (cmd->buttons & IN_FORWARD && localplayer->GetVelocity().Length() <= 50.0f)
		cmd->forwardmove = 450.0f;

	float yaw_change = 0.0f;
	if (localplayer->GetVelocity().Length() > 50.f)
		yaw_change = 30.0f * fabsf(30.0f / localplayer->GetVelocity().Length());

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (activeWeapon && !activeWeapon->GetAmmo() == 0 && cmd->buttons & IN_ATTACK)
		yaw_change = 0.0f;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	if (!(localplayer->GetFlags() & FL_ONGROUND) && !inMove)
	{
		if (leftRight || cmd->mousedx > 1)
		{
			viewAngles.y += yaw_change;
			cmd->sidemove = 450.0f;
		}
		else if (!leftRight || cmd->mousedx < 1)
		{
			viewAngles.y -= yaw_change;
			cmd->sidemove = -450.0f;
		}

		leftRight = !leftRight;
	}

	Math::NormalizeAngles(viewAngles);
	Math::ClampAngles(viewAngles);

	Math::CorrectMovement(viewAngles, cmd, cmd->forwardmove, cmd->sidemove);

	if (!Settings::AutoStrafe::silent)
		cmd->viewangles = viewAngles;
}

void AutoStrafe::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AutoStrafe::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	switch (Settings::AutoStrafe::type)
	{
		case AutostrafeType::AS_FORWARDS:
		case AutostrafeType::AS_BACKWARDS:
		case AutostrafeType::AS_LEFTSIDEWAYS:
		case AutostrafeType::AS_RIGHTSIDEWAYS:
			LegitStrafe(localplayer, cmd);
			break;
		case AutostrafeType::AS_RAGE:
			RageStrafe(localplayer, cmd);
			break;
	}
}
