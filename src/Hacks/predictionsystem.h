#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"

namespace PredictionSystem
{
	//Hooks
	/* CreateMove */
	void StartPrediction(CUserCmd* cmd);
	void EndPrediction();
};
