#pragma once

#include "../ImGUI/imgui.h"
#include "../SDK/IClientEntity.h"
#include "../SDK/vector.h"
#include "../SDK/IVModelRender.h"
#include "../SDK/IInputSystem.h"


namespace ESP
{
	extern const char* ranks[];

	ImColor GetESPPlayerColor(C_BasePlayer* player, bool visible);

	//Hooks
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
	bool PrePaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void Paint();
	void EmitSound(int iEntIndex, const char *pSample);
	void CreateMove(CUserCmd* cmd);
}
