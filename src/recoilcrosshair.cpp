#include "recoilcrosshair.h"

bool Settings::Recoilcrosshair::enabled = true;

void Recoilcrosshair::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::Recoilcrosshair::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || localplayer->GetLifeState() != LIFE_ALIVE)
		return;

	C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntity(localplayer->GetViewModel() & 0xFFF));
	if (!viewmodel)
		return;

	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntity(viewmodel->GetWeapon() & 0xFFF));
	if (!active_weapon)
		return;

	if (!active_weapon->isAutomatic())
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
	Draw::DrawRect(LOC(crosshairX - 4, crosshairY - 1), LOC(crosshairX + 5, crosshairY + 2), Color(0, 0, 0, 170));
	// outline vertical
	Draw::DrawRect(LOC(crosshairX - 1, crosshairY - 4), LOC(crosshairX + 2, crosshairY + 5), Color(0, 0, 0, 170));
	// line horizontal
	Draw::DrawLine(LOC(crosshairX - 3, crosshairY), LOC(crosshairX + 4, crosshairY), Color(255, 255, 255, 255));
	// line vertical
	Draw::DrawLine(LOC(crosshairX, crosshairY + 3), LOC(crosshairX, crosshairY - 4), Color(255, 255, 255, 255));
}