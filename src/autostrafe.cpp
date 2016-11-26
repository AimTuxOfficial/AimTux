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
        if(Settings::AutoStrafe::type == AS_FORWARDS){
            cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
        } else if(Settings::AutoStrafe::type == AS_BACKWARDS){
            cmd->sidemove = cmd->mousedx < 0.f ? 450.f : -450.f;
        } else if(Settings::AutoStrafe::type == AS_LEFTSIDEWAYS){
            cmd->forwardmove = cmd->mousedx < 0.f ? -450.f : 450.f;
        }else if(Settings::AutoStrafe::type == AS_RIGHTSIDEWAYS){
            cmd->forwardmove = cmd->mousedx < 0.f ? 450.f : -450.f;
        }
    }
}
