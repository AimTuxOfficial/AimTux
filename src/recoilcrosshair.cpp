#include "recoilcrosshair.h"

bool Settings::Recoilcrosshair::enabled = true;

void Recoilcrosshair::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::Recoilcrosshair::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || localplayer->GetLifeState() != LIFE_ALIVE)
		return;

	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon()));
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
	Draw::DrawRect(Vector2D(crosshairX - 4, crosshairY - 1), Vector2D(crosshairX + 5, crosshairY + 2), Color(0, 0, 0, 170));
	// outline vertical
	Draw::DrawRect(Vector2D(crosshairX - 1, crosshairY - 4), Vector2D(crosshairX + 2, crosshairY + 5), Color(0, 0, 0, 170));
	// line horizontal
	Draw::DrawLine(Vector2D(crosshairX - 3, crosshairY), Vector2D(crosshairX + 4, crosshairY), Color(255, 255, 255, 255));
	// line vertical
	Draw::DrawLine(Vector2D(crosshairX, crosshairY + 3), Vector2D(crosshairX, crosshairY - 4), Color(255, 255, 255, 255));
}