#include "edgejump.h"

bool Settings::EdgeJump::enabled = false;
ButtonCode_t Settings::EdgeJump::key = ButtonCode_t::KEY_C;

int flags_backup = 0;

void EdgeJump::PrePredictionCreateMove(CUserCmd* cmd)
{
	if (!Settings::EdgeJump::enabled)
		return;

	if (!input->IsButtonDown(Settings::EdgeJump::key))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	flags_backup = localplayer->GetFlags();
}

void EdgeJump::PostPredictionCreateMove(CUserCmd* cmd)
{
	if (!Settings::EdgeJump::enabled)
		return;

	if (!input->IsButtonDown(Settings::EdgeJump::key))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (flags_backup & FL_ONGROUND && !(localplayer->GetFlags() & FL_ONGROUND))
		cmd->buttons |= IN_JUMP;
}
