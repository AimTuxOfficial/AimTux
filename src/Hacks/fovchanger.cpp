#include "fovchanger.h"

bool Settings::FOVChanger::enabled = false;
bool Settings::FOVChanger::ignoreScope = true;
float Settings::FOVChanger::value = 100.f;

bool Settings::FOVChanger::viewmodelEnabled = false;
float Settings::FOVChanger::viewmodelValue = 90.f;

void FOVChanger::OverrideView(CViewSetup* pSetup)
{
	if (!Settings::FOVChanger::enabled && !Settings::FOVChanger::viewmodelEnabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return;
	}

	if (Settings::FOVChanger::enabled && (Settings::FOVChanger::ignoreScope ? !localplayer->IsScoped() : true))
		pSetup->fov = Settings::FOVChanger::value;
}

void FOVChanger::GetViewModelFOV(float& fov)
{
	if (!Settings::FOVChanger::enabled && !Settings::FOVChanger::viewmodelEnabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return;
	}

	if (Settings::FOVChanger::viewmodelEnabled && (Settings::FOVChanger::ignoreScope ? !localplayer->IsScoped() : true))
		fov = Settings::FOVChanger::viewmodelValue;
}
