#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace EdgeJump
{
	//Hooks
	void PrePredictionCreateMove(CUserCmd* cmd);
	void PostPredictionCreateMove(CUserCmd* cmd);
}
