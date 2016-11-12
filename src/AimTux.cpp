#include <iostream>

#include "interfaces.h"
#include "hooker.h"
#include "netvarmanager.h"

#include "atgui.h"
#include "Hooks/hooks.h"

UI_Container* gui;

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Hooker::HookInterfaces();
	Hooker::HookViewRender();
	Hooker::HookVMethods();
	Hooker::HookIClientMode();
	Hooker::HookGlobalVars();
	Hooker::HookGlowManager();
	Hooker::HookRankReveal();
	Hooker::HookSendClanTag();
	Hooker::HookSendPacket();
	Hooker::HookPrediction();

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
	inputInternal_vmt->ApplyVMT();

	SkinChanger::HookCBaseViewModel();

	NetVarManager::dumpNetvars();
	Offsets::getOffsets();

	gui = new UI_Container;

	Fonts::SetupFonts();
	SetupUI();

	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	cvar->FindVar("cl_mouseenable")->SetValue(1);

	client_vmt->ReleaseVMT();
	panel_vmt->ReleaseVMT();
	modelRender_vmt->ReleaseVMT();
	clientMode_vmt->ReleaseVMT();
	gameEvents_vmt->ReleaseVMT();
	viewRender_vmt->ReleaseVMT();
	inputInternal_vmt->ReleaseVMT();

	SkinChanger::UnhookCBaseViewModel();

	*bSendPacket = true;

	cvar->ConsoleColorPrintf(ColorRGBA(255, 150, 150), "AimTux has been unloaded successfully.\n");
}
