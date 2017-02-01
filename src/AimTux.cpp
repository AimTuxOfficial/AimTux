#include <iostream>

#include "interfaces.h"
#include "hooker.h"
#include "modsupport.h"
#include "Utils/netvarmanager.h"
#include "EventListener.h"

EventListener* eventListener = nullptr;

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Interfaces::FindInterfaces();
	Interfaces::DumpInterfaces();

	Hooker::FindViewRender();
	Hooker::FindSDLInput();
	Hooker::InitializeVMHooks();
	Hooker::FindIClientMode();
	Hooker::FindGlobalVars();
	Hooker::FindCInput();
	Hooker::FindGlowManager();
	Hooker::FindPlayerResource();
	Hooker::FindGameRules();
	Hooker::FindRankReveal();
	Hooker::FindSendClanTag();
	Hooker::FindSendPacket();
	Hooker::FindPrediction();
	Hooker::FindIsReadyCallback();
	Hooker::FindSurfaceDrawing();
	Hooker::FindClientStateFn();
	Hooker::FindLineGoesThroughSmoke();
	Hooker::FindInitKeyValues();
	Hooker::FindLoadFromBuffer();
	Hooker::FindGetCSWpnData();
	Hooker::HookSwapWindow();
	Hooker::HookPollEvent();

	cvar->ConsoleColorPrintf(ColorRGBA(150, 255, 150), "AimTux was successfully injected.\n");

	ModSupport::OnInit();

	clientVMT->HookVM((void*) Hooks::IN_KeyEvent, 20);
	clientVMT->HookVM((void*) Hooks::FrameStageNotify, 36);
	clientVMT->ApplyVMT();

	panelVMT->HookVM((void*) Hooks::PaintTraverse, 42);
	panelVMT->ApplyVMT();

	modelRenderVMT->HookVM((void*) Hooks::DrawModelExecute, 21);
	modelRenderVMT->ApplyVMT();

	clientModeVMT->HookVM((void*) Hooks::OverrideView, 19);
	clientModeVMT->HookVM((void*) Hooks::CreateMove, 25);
	clientModeVMT->HookVM((void*) Hooks::GetViewModelFOV, 36);
	clientModeVMT->ApplyVMT();

	gameEventsVMT->HookVM((void*) Hooks::FireEvent, 9);
	gameEventsVMT->HookVM((void*) Hooks::FireEventClientSide, 10);
	gameEventsVMT->ApplyVMT();

	viewRenderVMT->HookVM((void*) Hooks::RenderSmokePostViewmodel, 41);
	viewRenderVMT->ApplyVMT();

	inputInternalVMT->HookVM((void*) Hooks::SetKeyCodeState, 92);
	inputInternalVMT->HookVM((void*) Hooks::SetMouseCodeState, 93);
	inputInternalVMT->ApplyVMT();

	materialVMT->HookVM((void*) Hooks::BeginFrame, 42);
	materialVMT->ApplyVMT();

	surfaceVMT->HookVM((void*) Hooks::PlaySound, 82);
	surfaceVMT->HookVM((void*) Hooks::OnScreenSizeChanged, 116);
	surfaceVMT->ApplyVMT();

	launcherMgrVMT->HookVM((void*) Hooks::PumpWindowsMessageLoop, 19);
	launcherMgrVMT->ApplyVMT();

	engineVGuiVMT->HookVM((void*) Hooks::Paint, 15);
	engineVGuiVMT->ApplyVMT();

	soundVMT->HookVM((void*) Hooks::EmitSound1, 5);
	soundVMT->HookVM((void*) Hooks::EmitSound2, 6);
	soundVMT->ApplyVMT();

	eventListener = new EventListener({ "cs_game_disconnected", "player_connect_full", "player_death", "player_hurt" });

	SkinChanger::HookCBaseViewModel();

	NetVarManager::DumpNetvars();
	Offsets::GetOffsets();

	Fonts::SetupFonts();

	Settings::LoadSettings();

	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	cvar->FindVar("cl_mouseenable")->SetValue(1);

	SDL2::UnhookWindow();
	SDL2::UnhookPollEvent();

	clientVMT->ReleaseVMT();
	panelVMT->ReleaseVMT();
	modelRenderVMT->ReleaseVMT();
	clientModeVMT->ReleaseVMT();
	gameEventsVMT->ReleaseVMT();
	viewRenderVMT->ReleaseVMT();
	inputInternalVMT->ReleaseVMT();
	materialVMT->ReleaseVMT();
	surfaceVMT->ReleaseVMT();
	launcherMgrVMT->ReleaseVMT();
	engineVGuiVMT->ReleaseVMT();
	soundVMT->ReleaseVMT();

	delete eventListener;

	SkinChanger::UnhookCBaseViewModel();

	*bSendPacket = true;

	cvar->ConsoleColorPrintf(ColorRGBA(255, 150, 150), "AimTux has been unloaded successfully.\n");
}
