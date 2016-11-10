#include "fovchanger.h"

bool Settings::FOVChanger::enabled = false;
float Settings::FOVChanger::value = 100.f;

bool Settings::FOVChanger::viewmodel_enabled = false;
float Settings::FOVChanger::viewmodel_value = 90.f;

void FOVChanger::RenderView(CViewSetup & setup, CViewSetup & hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	if (!Settings::FOVChanger::enabled && !Settings::FOVChanger::viewmodel_enabled)
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

	if (Settings::FOVChanger::enabled && !localplayer->IsScoped())
		setup.fov = Settings::FOVChanger::value;

	if (Settings::FOVChanger::viewmodel_enabled)
		setup.fovViewmodel = Settings::FOVChanger::viewmodel_value;
}
