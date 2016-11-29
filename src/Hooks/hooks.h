#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../UI/ui_container.h"
#include "../hacks.h"

typedef void (*FrameStageNotifyFn) (void*, int);
typedef void (*PaintTraverseFn) (void*, VPANEL, bool, bool);
typedef void (*DrawModelExecuteFn) (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
typedef bool (*CreateMoveFn) (void*, float, CUserCmd*);
typedef bool (*FireEventClientSideFn) (void*, IGameEvent*);
typedef int (*IN_KeyEventFn) (void*, int, int, const char*);
typedef void (*RenderViewFn) (void*, CViewSetup&, CViewSetup&, unsigned int, int);
typedef void (*SetKeyCodeStateFn) (void*, ButtonCode_t, bool);
typedef void (*OnScreenSizeChangedFn) (void*, int, int);
typedef void (*PlaySoundFn) (void*, const char*);

namespace Hooks
{
	void PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force);
	void FrameStageNotify(void* thisptr, ClientFrameStage_t stage);
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
	bool FireEventClientSide(void* thisptr, IGameEvent* event);
	int IN_KeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding);
	void RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw);
	void SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed);
	void OnScreenSizeChanged(void* thisptr, int oldwidth, int oldheight);
	void PlaySound(void* thisptr, const char* filename);
}

namespace CreateMove
{
	extern bool SendPacket;
}

namespace RenderView
{
	extern float currentFOV;
}