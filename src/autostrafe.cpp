#include "autostrafe.h"

bool Settings::AutoStrafe::enabled = true;
AutostrafeType Settings::AutoStrafe::type = AS_FORWARDS;

void AutoStrafe::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AutoStrafe::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
		return;

	if (localplayer->GetFlags() & FL_ONGROUND)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (cmd->mousedx > 1 || cmd->mousedx < -1){
		switch(Settings::AutoStrafe::type)
		{
			case 0: cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f; break;
			case 1: cmd->sidemove = cmd->mousedx < 0.f ? 450.f : -450.f;	break;
			case 2: cmd->forwardmove = cmd->mousedx < 0.f ? -450.f : 450.f; break;
			case 3: cmd->forwardmove = cmd->mousedx < 0.f ? 450.f : -450.f; break;
		}
	}
}
