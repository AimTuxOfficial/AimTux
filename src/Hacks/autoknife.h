#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../Utils/entity.h"
#include "../Utils/math.h"

namespace AutoKnife
{
	bool IsPlayerBehind(C_BasePlayer* localplayer, C_BasePlayer* player);
	int GetKnifeDamageDone(C_BasePlayer* localplayer, C_BasePlayer* player);
	int GetKnife2DamageDone(C_BasePlayer* localplayer, C_BasePlayer* player);
	void CreateMove(CUserCmd* cmd);
};
