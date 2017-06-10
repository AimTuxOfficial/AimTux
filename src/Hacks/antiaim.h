#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../Hooks/hooks.h"
#include "../interfaces.h"
#include "aimbot.h"
#include <lua.hpp>

namespace AntiAim
{
	void LuaInit();
	void LuaCleanup();

	//Hooks
	void CreateMove(CUserCmd* cmd);
}
