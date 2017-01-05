#include "showranks.h"

bool Settings::ShowRanks::enabled = true;

void ShowRanks::CreateMove(CUserCmd* cmd)
{
	if (!Settings::ShowRanks::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (cmd->buttons & IN_SCORE)
	{
		float input[3] = { 0.f };
		MsgFunc_ServerRankRevealAll(input);
	}
}