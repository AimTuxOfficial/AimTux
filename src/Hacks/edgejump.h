#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace EdgeJump
{
	void PrePredictionCreateMove(CUserCmd* cmd);
	void PostPredictionCreateMove(CUserCmd* cmd);
}
