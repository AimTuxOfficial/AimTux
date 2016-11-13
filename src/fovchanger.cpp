#include "fovchanger.h"

void FOVChanger::RenderView(CViewSetup & setup, CViewSetup & hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	if (!cSettings.FOVChanger.enabled && !cSettings.FOVChanger.viewmodel_enabled)
			return;

	if (!engine->IsInGame())
		return;

	C_BaseEntity* localplayer = entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return;
	}

	if (cSettings.FOVChanger.enabled && !localplayer->IsScoped())
		setup.fov = cSettings.FOVChanger.value;

	if (cSettings.FOVChanger.viewmodel_enabled)
		setup.fovViewmodel = cSettings.FOVChanger.viewmodel_value;
}
