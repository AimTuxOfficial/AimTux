#pragma once

#include "../SDK/SDK.h"

#include "../interfaces.h"

#include "../UI/ui_container.h"

#include "../aimbot.h"
#include "../airstuck.h"
#include "../antiaim.h"
#include "../autostrafe.h"
#include "../bhop.h"
#include "../chams.h"
#include "../clantagchanger.h"
#include "../dlights.h"
#include "../esp.h"
#include "../fakelag.h"
#include "../fovchanger.h"
#include "../namechanger.h"
#include "../noflash.h"
#include "../radar.h"
#include "../recoilcrosshair.h"
#include "../showranks.h"
#include "../showspectators.h"
#include "../skinchanger.h"
#include "../spammer.h"
#include "../teleport.h"
#include "../triggerbot.h"

namespace Hooks
{
	void PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void FrameStageNotify(void* thisptr, ClientFrameStage_t stage);
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
	bool FireEventClientSide(void* thisptr, IGameEvent* event);
	int IN_KeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding);
	void RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw);
}
