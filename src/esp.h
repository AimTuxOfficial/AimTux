#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "Hooks/hooks.h"
#include "draw.h"
#include "interfaces.h"
#include "pstring.h"
#include "entity.h"

namespace ESP
{
	extern const char* Ranks[];

	bool GetBox(C_BaseEntity* entity, int& x, int& y, int& w, int& h);
	ImColor GetESPPlayerColor(C_BaseEntity* entity, bool visible);
	void DrawBox(Color color, int x, int y, int w, int h);
	void DrawEntity(C_BaseEntity* entity, const char* string, Color color);
	void DrawPlayer(int index, C_BaseEntity* player, IEngineClient::player_info_t player_info);
	void DrawBomb(C_BaseCombatWeapon* bomb);
	void DrawPlantedBomb(C_BasePlantedC4* bomb);
	void DrawDefuseKit(C_BaseEntity* defuser);
	void DrawDroppedWeapons(C_BaseCombatWeapon* weapon);
	void DrawHostage(C_BaseEntity* hostage);
	void DrawChicken(C_BaseEntity* chicken);
	void DrawFish(C_BaseEntity* fish);
	void DrawThrowable(C_BaseEntity* throwable, ClientClass* cClass);
	void DrawSkeleton(C_BaseEntity* player);
	void DrawBulletTrace(C_BaseEntity* player);
	void DrawTracer(C_BaseEntity *entity);
	void CollectFootstep(int iEntIndex, const char *pSample);
	void DrawSounds();
	void DrawFOVCrosshair();
	void DrawGlow();

	void BeginFrame(float frameTime);
	bool PrePaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void Paint();
	void EmitSound(int iEntIndex, const char *pSample);
}
