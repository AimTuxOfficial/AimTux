#include "fakelag.h"

bool Settings::FakeLag::enabled = false;
int Settings::FakeLag::value = 5;

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
	if (!Settings::FakeLag::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (localplayer->GetLifeState() != LIFE_ALIVE || localplayer->GetHealth() == 0)
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		*bSendPacket = true;
		return;
	}

	if (ticks >= ticksMax)
	{
		*bSendPacket = true;
		ticks = 0;
	}
	else
	{
		*bSendPacket = ticks < 16 - Settings::FakeLag::value;
	}

	ticks++;
}