#include "fakelag.h"

bool Settings::FakeLag::enabled = false;
float Settings::FakeLag::value = 5;

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
#ifdef EXPERIMENTAL_SETTINGS
	if (!Settings::FakeLag::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (localplayer->GetLifeState() != LIFE_ALIVE || localplayer->GetHealth() == 0)
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		Util::WriteSendPacket(true);
		return;
	}

	if (ticks >= ticksMax)
	{
		Util::WriteSendPacket(true);
		ticks = 0;
	}
	else
	{
		Util::WriteSendPacket(ticks < 16 - (int)Settings::FakeLag::value);
	}

	ticks++;
#endif
}