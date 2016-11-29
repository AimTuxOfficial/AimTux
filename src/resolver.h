#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "draw.h"
#include "interfaces.h"
#include "pstring.h"
#include "entity.h"

struct PlayerAA
{
	C_BasePlayer* player;
	QAngle angle;
	
	PlayerAA(C_BasePlayer* player, QAngle angle)
	{
		this->player = player;
		this->angle = angle;
	}
};

namespace Resolver
{
	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
}