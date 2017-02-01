#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace ShowRanks
{
	void CreateMove(CUserCmd* cmd);
}

extern msgfuncServerRankRevealAllFn msgfuncServerRankRevealAll;