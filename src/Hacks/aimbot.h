#pragma once

#include <vector>
#include <cstdint>
#include "../SDK/IInputSystem.h"
#include "../SDK/IGameEvent.h"

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
