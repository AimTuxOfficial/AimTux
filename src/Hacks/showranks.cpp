#include "showranks.h"

#include "../settings.h"

struct RankReveal
{
    char _pad[0x10];
    void *ptr;
    int ebx;
    char _pad2[0x300];
};

void ShowRanks::CreateMove(CUserCmd* cmd)
{
	if (!Settings::ShowRanks::enabled)
		return;

	if (!(cmd->buttons & IN_SCORE))
		return;

	RankReveal input;
	input.ptr = nullptr;
	input.ebx = 3;

	if( MsgFunc_ServerRankRevealAll ){
		MsgFunc_ServerRankRevealAll((void*)&input);
	}
}
