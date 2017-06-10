#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace NameStealer
{
	extern int entityId;

	//Hooks
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
};
