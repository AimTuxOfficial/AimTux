#include "snipercrosshair.h"

#include "../settings.h"
#include "../interfaces.h"

#include "../Utils/xorstring.h"
#include "../Utils/draw.h"
#include "../Hooks/hooks.h"

bool Settings::SniperCrosshair::enabled = false;

bool SniperCrosshair::DrawCrosshair()
{
	if ( !Settings::ESP::enabled || !Settings::SniperCrosshair::enabled )
		return false;

	if ( !engine->IsInGame() )
		return false;

	C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if ( !localPlayer || !localPlayer->GetAlive() )
        return false;

    C_BaseCombatWeapon *activeWeapon = ( C_BaseCombatWeapon* ) entityList->GetClientEntityFromHandle( localPlayer->GetActiveWeapon() );
    if ( !activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_SNIPER_RIFLE )
        return false;
	
	if ( localPlayer->IsScoped() )
		return false;

	activeWeapon->GetCSWpnData()->SetWeaponType( CSWeaponType::WEAPONTYPE_RIFLE ); // this doesn't matter too much, as long as it's not 5 (WEAPONTYPE_SNIPER_RIFLE)
	activeWeapon->DrawCrosshair();
	activeWeapon->GetCSWpnData()->SetWeaponType( CSWeaponType::WEAPONTYPE_SNIPER_RIFLE ); // restore after drawing
	return true;
}
