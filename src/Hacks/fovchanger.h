#pragma once

#include "../SDK/CViewRender.h"

namespace FOVChanger
{
	//Hooks
	void OverrideView(CViewSetup* pSetup);
	void GetViewModelFOV(float& fov);
};
