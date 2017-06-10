#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace FOVChanger
{
	//Hooks
	void OverrideView(CViewSetup* pSetup);
	void GetViewModelFOV(float& fov);
};
