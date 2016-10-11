#ifndef __SHOWRANK_H_
#define __SHOWRANK_H_

#include "SDK/SDK.h"
#include "interfaces.h"
#include "settings.h"

namespace ShowRank
{
	void CreateMove(CUserCmd* cmd);
}

extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;

#endif