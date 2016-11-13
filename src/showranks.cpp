#include "showranks.h"

void ShowRanks::CreateMove(CUserCmd* cmd)
{
	if (!cSettings.ShowRanks.enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (cmd->buttons & IN_SCORE)
	{
		float input[3] = { 0.f };
		MsgFunc_ServerRankRevealAll(input);
	}
}