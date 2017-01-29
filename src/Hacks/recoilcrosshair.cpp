#include "recoilcrosshair.h"

bool Settings::Recoilcrosshair::enabled = false;
bool Settings::Recoilcrosshair::showOnlyWhenShooting = false;

void Recoilcrosshair::Paint()
{
	if (!Settings::ESP::enabled)
		return;

	if (!Settings::Recoilcrosshair::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (localplayer->GetShotsFired() < 1 && Settings::Recoilcrosshair::showOnlyWhenShooting)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	CSWeaponType weaponType = active_weapon->GetCSWpnData()->GetWeaponType();
	if (weaponType != CSWeaponType::WEAPONTYPE_RIFLE && weaponType != CSWeaponType::WEAPONTYPE_SUBMACHINEGUN && weaponType != CSWeaponType::WEAPONTYPE_MACHINEGUN)
		return;

	QAngle punchAngle = *localplayer->GetAimPunchAngle();

	int ScreenWidth, ScreenHeight;
	engine->GetScreenSize(ScreenWidth, ScreenHeight);

	int x = (int) (ScreenWidth * 0.5f);
	int y = (int) (ScreenHeight * 0.5f);
	int dx = ScreenWidth / OverrideView::currentFOV;
	int dy = ScreenHeight / OverrideView::currentFOV;

	int crosshairX = (int) (x - (dx * punchAngle.y));
	int crosshairY = (int) (y + (dy * punchAngle.x));

	// outline horizontal
	Draw::FilledRectangle(Vector2D(crosshairX - 4, crosshairY - 1), Vector2D(crosshairX + 5, crosshairY + 2), Color(0, 0, 0, 170));
	// outline vertical
	Draw::FilledRectangle(Vector2D(crosshairX - 1, crosshairY - 4), Vector2D(crosshairX + 2, crosshairY + 5), Color(0, 0, 0, 170));
	// line horizontal
	Draw::Line(Vector2D(crosshairX - 3, crosshairY), Vector2D(crosshairX + 4, crosshairY), Color(255, 255, 255, 255));
	// line vertical
	Draw::Line(Vector2D(crosshairX, crosshairY + 3), Vector2D(crosshairX, crosshairY - 4), Color(255, 255, 255, 255));
}
