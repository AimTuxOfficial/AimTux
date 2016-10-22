#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "draw.h"
#include "interfaces.h"
#include "pstring.h"
#include "entity.h"

namespace ESP
{
	void DrawTracer(C_BaseEntity* entity);
	void DrawPlayerBox(C_BaseEntity* entity);
	void DrawPlayerInfo(C_BaseEntity* entity, int entityIndex);
	void DrawBombBox(C_BasePlantedC4* entity);
	void DrawWeaponText(C_BaseEntity* entity, ClientClass* client);
	void DrawBones(C_BaseEntity* entity);
	void DrawFOVCrosshair();
	void DrawGlow();
	void PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force);
}

extern GlowObjectManagerFn GlowObjectManager;