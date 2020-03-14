#include "showranks.h"

#include "../settings.h"

void ShowRanks::CreateMove(CUserCmd* cmd)
{
	if (!Settings::ShowRanks::enabled)
		return;

	if (!(cmd->buttons & IN_SCORE))
		return;

	float input[3] = { 0.f };
	if( MsgFunc_ServerRankRevealAll ){
		MsgFunc_ServerRankRevealAll(input);
	}
}
