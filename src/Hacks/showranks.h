#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace ShowRanks
{
	//Hooks
	void CreateMove(CUserCmd* cmd);
}

extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
