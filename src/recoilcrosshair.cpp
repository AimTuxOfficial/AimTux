#include "recoilcrosshair.h"

bool Settings::Recoilcrosshair::enabled = true;
bool Settings::Recoilcrosshair::showOnlyWhenShooting = false;

void Recoilcrosshair::Paint()
{
	if (!Settings::Recoilcrosshair::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if(localplayer->GetShotsFired() < 1 && Settings::Recoilcrosshair::showOnlyWhenShooting)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon || !active_weapon->IsAutomatic())
		return;

	QAngle punchAngle = localplayer->GetAimPunchAngle();

	int ScreenWidth, ScreenHeight;
	engine->GetScreenSize(ScreenWidth, ScreenHeight);

	int x = (int) (ScreenWidth * 0.5f);
	int y = (int) (ScreenHeight * 0.5f);
	int dx = ScreenWidth / 90;
	int dy = ScreenHeight / 90;

	int crosshairX = (int) (x - (dx * punchAngle.y));
	int crosshairY = (int) (y + (dy * punchAngle.x));

	// outline horizontal
	Draw::FilledRectangle(LOC(crosshairX - 4, crosshairY - 1), LOC(crosshairX + 5, crosshairY + 2), Color(0, 0, 0, 170));
	// outline vertical
	Draw::FilledRectangle(LOC(crosshairX - 1, crosshairY - 4), LOC(crosshairX + 2, crosshairY + 5), Color(0, 0, 0, 170));
	// line horizontal
	Draw::Line(LOC(crosshairX - 3, crosshairY), LOC(crosshairX + 4, crosshairY), Color(255, 255, 255, 255));
	// line vertical
	Draw::Line(LOC(crosshairX, crosshairY + 3), LOC(crosshairX, crosshairY - 4), Color(255, 255, 255, 255));
}
