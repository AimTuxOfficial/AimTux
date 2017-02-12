#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace FOVChanger
{
	void OverrideView(CViewSetup* pSetup);
	void GetViewModelFOV(float& fov);
};
