#pragma once

#include "CViewRender.h"
class IClientMode {
public:
	virtual ~IClientMode() {}

	virtual int ClientModeCSNormal(void *) = 0;

	virtual void InitViewport() = 0;

	virtual void Init() = 0;

	virtual void VGui_Shutdown() = 0;

	virtual void Shutdown() = 0;

	virtual void Enable() = 0;

	//virtual void EnableWithRootPanel(vgui::VPANEL pRoot) = 0;

	virtual void Disable() = 0;

	virtual void Layout(bool bForce = false) = 0;

	//virtual vgui::Panel *GetViewport() = 0;

	//virtual vgui::Panel *GetPanelFromViewport(const char *pchNamePath) = 0;

	//virtual vgui::AnimationController *GetViewportAnimationController() = 0;

	virtual void ProcessInput(bool bActive) = 0;

	virtual bool ShouldDrawDetailObjects() = 0;

	virtual bool ShouldDrawEntity(C_BaseEntity *pEnt) = 0;

	virtual bool ShouldDrawLocalPlayer(C_BasePlayer *pPlayer) = 0;

	virtual bool ShouldDrawParticles() = 0;

	virtual bool ShouldDrawFog(void) = 0;

	virtual void OverrideView(CViewSetup *pSetup) = 0; // 19

	//virtual void OverrideAudioState(AudioState_t *pAudioState) = 0;

	virtual int KeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;

	virtual void StartMessageMode(int iMessageModeType) = 0;

	//virtual vgui::Panel *GetMessagePanel() = 0;

	virtual void OverrideMouseInput(float *x, float *y) = 0;

	virtual bool CreateMove(float flInputSampleTime, CUserCmd *cmd) = 0;
};
