#include "snipercrosshair.h"

bool Settings::SniperCrosshair::enabled = false;

void SniperCrosshair::BeginFrame()
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		C_BasePlayer* observerTarget = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());
		if (!observerTarget)
			return;

		localplayer = observerTarget;
	}

	*CrosshairWeaponTypeCheck = Settings::SniperCrosshair::enabled && !localplayer->IsScoped() ? 255 : 5;
}
