#include "bhop.h"

bool Settings::BHop::enabled = false;

void BHop::CreateMove(CUserCmd* cmd)
{
	if (!Settings::BHop::enabled)
		return;

	static bool bLastJumped = false;
	static bool bShouldFake = false;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	if (!localplayer)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
		cmd->buttons |= IN_JUMP;
	}
	else if (cmd->buttons & IN_JUMP)
	{
		if (localplayer->GetFlags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}
