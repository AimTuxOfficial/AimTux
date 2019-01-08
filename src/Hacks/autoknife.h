#pragma once

#include "../SDK/IClientEntity.h"
#include "../SDK/IInputSystem.h"

namespace AutoKnife
{
	bool IsPlayerBehind(C_BasePlayer* localplayer, C_BasePlayer* player);
	int GetKnifeDamageDone(C_BasePlayer* localplayer, C_BasePlayer* player);
	int GetKnife2DamageDone(C_BasePlayer* localplayer, C_BasePlayer* player);
	void CreateMove(CUserCmd* cmd);
};
