#pragma once

#include "../SDK/IInputSystem.h"

namespace PredictionSystem
{
	//Hooks
	/* CreateMove */
	void StartPrediction(CUserCmd* cmd);
	void EndPrediction();
};
