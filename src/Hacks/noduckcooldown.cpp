#include "noduckcooldown.h"

#include "../settings.h"
#include "../interfaces.h"

void NoDuckCooldown::CreateMove(CUserCmd* cmd)
{
	if (!Settings::NoDuckCooldown::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	if (!localplayer || !localplayer->GetAlive())
		return;

	cmd->buttons |= IN_BULLRUSH;
}
