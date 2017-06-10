#pragma once

#include "../settings.h"
#include "../interfaces.h"
#include "../Utils/entity.h"
#include "../Utils/math.h"

extern "C"
{
	#include <xdo.h>
}

namespace Aimbot
{
	extern bool aimStepInProgress;
	extern std::vector<int64_t> friends;
    extern int targetAimbot;

	void XDOCleanup();

	//Hooks
	void CreateMove(CUserCmd* cmd);
	void FireGameEvent(IGameEvent* event);
	void UpdateValues();


}
