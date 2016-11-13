#include "fakelag.h"

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
	if (!cSettings.FakeLag.enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		CreateMove::SendPacket = true;
		return;
	}

	if (ticks >= ticksMax)
	{
		CreateMove::SendPacket = true;
		ticks = 0;
	}
	else
	{
		CreateMove::SendPacket = ticks < 16 - cSettings.FakeLag.value;
	}

	ticks++;
}