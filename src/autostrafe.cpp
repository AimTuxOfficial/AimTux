#include "autostrafe.h"

bool Settings::AutoStrafe::enabled = true;

void AutoStrafe::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AutoStrafe::enabled)
		return;

	C_BaseEntity* localplayer = reinterpret_cast<C_BaseEntity*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

	// TODO: Return if localplayer's movetype is equal to MOVETYPE_NOCLIP or MOVETYPE_LADDER
	if (localplayer->GetFlags() & FL_ONGROUND)
		return;

	if (cmd->mousedx > 1 || cmd->mousedx < -1)
		cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
}
