#pragma once

#include "../SDK/IInputSystem.h"
#include "../SDK/definitions.h"

namespace ShowRanks
{
	//Hooks
	void CreateMove(CUserCmd* cmd);
}

extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
