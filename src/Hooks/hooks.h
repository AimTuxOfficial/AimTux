#pragma once

#include "../SDK/SDK.h"

#include <queue>

namespace Hooks
{
	/* Client */
	void FrameStageNotify(void* thisptr, ClientFrameStage_t stage);
	void LevelInitPostEntity();

	/* ClientMode */
	void OverrideView(void* thisptr, CViewSetup* pSetup);
	bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
	bool ShouldDrawCrosshair(void* thisptr);
	float GetViewModelFOV(void* thisptr);

	/* GameEvents */
	bool FireEventClientSide(void* thisptr, IGameEvent* event);

	/* Input Internal */
	void SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed);
	void SetMouseCodeState(void* thisptr, ButtonCode_t code, MouseCodeState_t state);

	/* Material */
	void OverrideConfig( void* thisptr, MaterialSystem_Config_t* config, bool forceUpdate );
	void BeginFrame(void* thisptr, float frameTime);

	/* ModelRender */
	void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);

	/* Panel */
	void PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force);

	/* Sound */
	void EmitSound2(void* thisptr, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, int nSeed, soundlevel_t iSoundLevel, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, StartSoundParams_t& params);

	/* Surface */
	void OnScreenSizeChanged(void* thisptr, int oldwidth, int oldheight);

	/* ViewRender */
	void RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw);
	void RenderSmokePostViewmodel(void* thisptr);




	/* OpenGL Hooks */
	int PumpWindowsMessageLoop(void* thisptr, void* unknown);

	/* Painting */
	void Paint(void* thisptr, PaintMode_t mode); // Draw with Surface
	void PaintImGui(); // Draw with ImGui.
}

namespace CreateMove
{
	extern bool sendPacket;
	extern QAngle lastTickViewAngles;
}

namespace OverrideView
{
	extern float currentFOV;
}

namespace Paint
{
    extern int engineWidth; // updated in paint.
    extern int engineHeight;
}

namespace SetKeyCodeState
{
	extern bool shouldListen;
	extern ButtonCode_t* keyOutput;
}

namespace RenderView
{
	struct RenderRequest
	{
		int destX, destY;
		int width, height;
		ITexture* tex;
		IMaterial* mat;
	};

	extern std::queue<RenderView::RenderRequest> renderQueue;
}
typedef void (*RenderViewFn) (void*, CViewSetup&, CViewSetup&, unsigned int, int);