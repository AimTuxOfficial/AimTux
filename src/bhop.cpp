#include "bhop.h"

bool Settings::BHop::enabled = true;

void BHop::CreateMove (CUserCmd* cmd)
{
	if (Settings::BHop::enabled)
	{
		C_BaseEntity* localplayer = reinterpret_cast<C_BaseEntity*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
		
		if (localplayer && cmd->buttons & IN_JUMP && !(localplayer->GetFlags() & FL_ONGROUND))
			cmd->buttons &= ~IN_JUMP;
	}
}