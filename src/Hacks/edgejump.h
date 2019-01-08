#pragma once

#include "../SDK/IInputSystem.h"

namespace EdgeJump
{
	//Hooks
	void PrePredictionCreateMove(CUserCmd* cmd);
	void PostPredictionCreateMove(CUserCmd* cmd);
}
