#include "fovchanger.h"

bool Settings::FOVChanger::enabled = false;
float Settings::FOVChanger::value = 100.f;

bool Settings::FOVChanger::viewmodel_enabled = false;
float Settings::FOVChanger::viewmodel_value = 90.f;

void FOVChanger::RenderView(CViewSetup & setup, CViewSetup & hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	if (!Settings::FOVChanger::enabled)
			return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->IsScoped())
		setup.fov = Settings::FOVChanger::value;

	setup.fovViewmodel = Settings::FOVChanger::viewmodel_value;
}