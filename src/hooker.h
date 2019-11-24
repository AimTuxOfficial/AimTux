#pragma once

#include <memory>
#include "Utils/recvproxyhook.h"

struct dlinfo_t
{
	const char* library = nullptr;
	uintptr_t address = 0;
	size_t size = 0;
};

namespace Hooker
{
	bool GetLibraryInformation(const char* library, uintptr_t* address, size_t* size);
	bool HookRecvProp(const char* className, const char* propertyName, std::unique_ptr<RecvPropHook>& recvPropHook);
	void FindIClientMode();
	void FindGlobalVars();
	void FindCInput();
	void FindGlowManager();
	void FindPlayerResource();
	void FindGameRules();
	void FindRankReveal();
	void FindSendClanTag();
	void FindViewRender();
	void FindPrediction();
	void FindSetLocalPlayerReady();
	void FindSurfaceDrawing();
	void FindGetLocalClient();
	void FindLineGoesThroughSmoke();
	void FindInitKeyValues();
	void FindLoadFromBuffer();
	//void FindVstdlibFunctions();
	void FindOverridePostProcessingDisable();
	void HookSwapWindow();
	void HookPollEvent();
	void FindSDLInput();
	void FindSetNamedSkybox();
	void FindPanelArrayOffset();
	void FindPlayerAnimStateOffset();
    void FindPlayerAnimOverlayOffset();
	void FindSequenceActivity();
	void FindAbsFunctions();
	void FindItemSystem();
}
