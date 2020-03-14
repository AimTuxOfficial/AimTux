#include "recoilcrosshair.h"

#include "../Hooks/hooks.h"

#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/draw.h"

void Recoilcrosshair::Paint( ) {
	if( !Settings::Recoilcrosshair::enabled )
		return;
	C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
	if ( !localplayer || !localplayer->GetAlive() )
		return;

	if ( localplayer->GetShotsFired() < 1 && Settings::Recoilcrosshair::showOnlyWhenShooting )
		return;

	C_BaseCombatWeapon* activeWeapon = ( C_BaseCombatWeapon* ) entityList->GetClientEntityFromHandle(
			localplayer->GetActiveWeapon() );
	if ( !activeWeapon )
		return;

	CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
	if ( weaponType != CSWeaponType::WEAPONTYPE_RIFLE && weaponType != CSWeaponType::WEAPONTYPE_SUBMACHINEGUN &&
		 weaponType != CSWeaponType::WEAPONTYPE_MACHINEGUN )
		return;

	QAngle punchAngle = *localplayer->GetAimPunchAngle();

	int x = Paint::engineWidth / 2;
	int y = Paint::engineHeight / 2;
	int dx = Paint::engineWidth / OverrideView::currentFOV;
	int dy = Paint::engineHeight / OverrideView::currentFOV;

	int crosshairX = ( int ) ( x - ( dx * punchAngle.y ) );
	int crosshairY = ( int ) ( y + ( dy * punchAngle.x ) );

	// outline horizontal
	Draw::AddRectFilled( crosshairX - 4, crosshairY - 1, crosshairX + 5, crosshairY + 2, ImColor( 0, 0, 0, 225 ) );
	// outline vertical
	Draw::AddRectFilled( crosshairX - 1, crosshairY - 4, crosshairX + 2, crosshairY + 5, ImColor( 0, 0, 0, 225 ) );
	// line horizontal
	Draw::AddLine( crosshairX - 3, crosshairY, crosshairX + 4, crosshairY, ImColor( 255, 255, 255, 255 ) );
	// line vertical
	Draw::AddLine( crosshairX, crosshairY + 3, crosshairX, crosshairY - 4, ImColor( 255, 255, 255, 255 ) );
}

