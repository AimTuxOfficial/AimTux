#include <iostream>

#include "interfaces.h"
#include "hooker.h"
#include "netvarmanager.h"

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Hooker::HookInterfaces();
	Hooker::HookViewRender();
	Hooker::HookSDLInput();
	Hooker::HookVMethods();
	Hooker::HookIClientMode();
	Hooker::HookGlobalVars();
	Hooker::HookGlowManager();
	Hooker::HookPlayerResource();
	Hooker::HookRankReveal();
	Hooker::HookSendClanTag();
	Hooker::HookSendPacket();
	Hooker::HookIsReadyCallback();
	Hooker::HookSurfaceDrawing();
	Hooker::HookPrediction();
	Hooker::HookSwapWindow();
	Hooker::HookPollEvent();

	Chams::CreateMaterials();

	cvar->ConsoleColorPrintf(ColorRGBA(150, 255, 150), "AimTux was successfully injected.\n");

	client_vmt->HookVM((void*) Hooks::IN_KeyEvent, 20);
	client_vmt->HookVM((void*) Hooks::FrameStageNotify, 36);
	client_vmt->ApplyVMT();

	panel_vmt->HookVM((void*) Hooks::PaintTraverse, 42);
	panel_vmt->ApplyVMT();

	modelRender_vmt->HookVM((void*) Hooks::DrawModelExecute, 21);
	modelRender_vmt->ApplyVMT();

	clientMode_vmt->HookVM((void*) Hooks::CreateMove, 25);
	clientMode_vmt->ApplyVMT();

	gameEvents_vmt->HookVM((void*) Hooks::FireEventClientSide, 10);
	gameEvents_vmt->ApplyVMT();

	viewRender_vmt->HookVM((void*) Hooks::RenderView, 6);
	viewRender_vmt->ApplyVMT();

	inputInternal_vmt->HookVM((void*) Hooks::SetKeyCodeState, 92);
	inputInternal_vmt->HookVM((void*) Hooks::SetMouseCodeState, 93);
	inputInternal_vmt->ApplyVMT();

	material_vmt->HookVM((void*) Hooks::BeginFrame, 42);
	material_vmt->ApplyVMT();

	surface_vmt->HookVM((void*) Hooks::PlaySound, 82);
	surface_vmt->HookVM((void*) Hooks::OnScreenSizeChanged, 116);
	surface_vmt->ApplyVMT();

	launchermgr_vmt->HookVM((void*) Hooks::PumpWindowsMessageLoop, 19);
	launchermgr_vmt->ApplyVMT();
	
	enginevgui_vmt->HookVM((void*) Hooks::Paint, 15);
	enginevgui_vmt->ApplyVMT();

	SkinChanger::HookCBaseViewModel();

	NetVarManager::dumpNetvars();
	Offsets::getOffsets();

	Fonts::SetupFonts();

	Settings::LoadSettings();

	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	cvar->FindVar("cl_mouseenable")->SetValue(1);

	SDL2::UnhookWindow();
	SDL2::UnhookPollEvent();

	client_vmt->ReleaseVMT();
	panel_vmt->ReleaseVMT();
	modelRender_vmt->ReleaseVMT();
	clientMode_vmt->ReleaseVMT();
	gameEvents_vmt->ReleaseVMT();
	viewRender_vmt->ReleaseVMT();
	inputInternal_vmt->ReleaseVMT();
	material_vmt->ReleaseVMT();
	surface_vmt->ReleaseVMT();
	launchermgr_vmt->ReleaseVMT();
	enginevgui_vmt->ReleaseVMT();

	SkinChanger::UnhookCBaseViewModel();

	*bSendPacket = true;

	cvar->ConsoleColorPrintf(ColorRGBA(255, 150, 150), "AimTux has been unloaded successfully.\n");
}
