#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

#include "../Hacks/snipercrosshair.h"

typedef bool (*ShouldDrawCrosshairFn) (void*);

bool Hooks::ShouldDrawCrosshair(void* thisptr)
{
	C_BasePlayer* localPlayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
	
	if( Settings::SniperCrosshair::enabled && localPlayer && localPlayer->GetAlive() )
	{
		if( SniperCrosshair::DrawCrosshair() )
			return false;
	}

	clientModeVMT->GetOriginalMethod<ShouldDrawCrosshairFn>(29)(thisptr);
}
