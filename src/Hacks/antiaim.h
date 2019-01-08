#pragma once

#include "../SDK/IInputSystem.h"

namespace AntiAim
{
	void LuaInit();
	void LuaCleanup();

	//Hooks
	void CreateMove(CUserCmd* cmd);
}
