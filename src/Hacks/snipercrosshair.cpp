#include "snipercrosshair.h"

bool Settings::SniperCrosshair::enabled = false;

void SniperCrosshair::BeginFrame()
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	*CrosshairWeaponTypeCheck = Settings::SniperCrosshair::enabled && !localplayer->IsScoped() ? 255 : 5;
}
