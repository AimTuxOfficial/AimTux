#ifndef __HOOKS_H
#define __HOOKS_H

#include "../SDK/SDK.h"

#include "../interfaces.h"

#include "../UI/ui_container.h"

#include "../aimbot.h"
#include "../airstuck.h"
#include "../antiaim.h"
#include "../autostrafe.h"
#include "../bhop.h"
#include "../chams.h"
#include "../chantagchanger.h"
#include "../dlights.h"
#include "../esp.h"
#include "../noflash.h"
#include "../recoilcrosshair.h"
#include "../skinchanger.h"
#include "../spammer.h"
#include "../triggerbot.h"
#include "../showranks.h"
#include "../showspectators.h"

namespace Hooks
{
	void PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void FrameStageNotify(void* thisptr, ClientFrameStage_t stage);
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
	bool FireEventClientSide(void* thisptr, IGameEvent* event);
}

#endif
