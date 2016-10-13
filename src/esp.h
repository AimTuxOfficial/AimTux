#ifndef __ESP_H_
#define __ESP_H_

#include "settings.h"
#include "SDK/SDK.h"
#include "draw.h"
#include "interfaces.h"
#include "pstring.h"
#include "entity.h"

namespace ESP
{
	void DrawTracer(C_BasePlayer* localPlayer, C_BaseEntity* entity);
	void DrawPlayerBox(C_BasePlayer* localPlayer, C_BaseEntity* entity);
	void DrawPlayerInfo(C_BasePlayer* localPlayer, C_BaseEntity* entity, int entityIndex);
	void DrawBombBox(C_BasePlantedC4* entity);
	void DrawWeaponText(C_BaseEntity* entity, ClientClass* client);
	void DrawBones(C_BaseEntity* entity);
	void PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void DrawFOVCrosshair();
}

#endif