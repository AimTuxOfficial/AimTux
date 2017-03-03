#include "interfaces.h"
#include "hooker.h"
#include "modsupport.h"
#include "Utils/netvarmanager.h"
#include "EventListener.h"

EventListener* eventListener = nullptr;

/* called when the library is loading */
int __attribute__((constructor)) AimTuxInit()
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
	Hooker::FindGetLocalClient();
	Hooker::FindLineGoesThroughSmoke();
	Hooker::FindInitKeyValues();
	Hooker::FindLoadFromBuffer();
	Hooker::FindVstdlibFunctions();
	Hooker::FindOverridePostProcessingDisable();
	Hooker::FindCrosshairWeaponTypeCheck();
	Hooker::FindCamThinkSvCheatsCheck();
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

	eventListener = new EventListener({ "cs_game_disconnected", "player_connect_full", "player_death", "player_hurt", "switch_team" });

	if (ModSupport::current_mod != ModType::CSCO && Hooker::HookRecvProp("CBaseViewModel", "m_nSequence", SkinChanger::sequenceHook))
		SkinChanger::sequenceHook->SetProxyFunction((RecvVarProxyFn) SkinChanger::SetViewModelSequence);

	NetVarManager::DumpNetvars();
	Offsets::GetOffsets();

	Fonts::SetupFonts();

	Settings::LoadSettings();

	srand(time(NULL)); // Seed random # Generator so we can call rand() later

	return 0;
}

void __attribute__((destructor)) AimTuxShutdown()
{
	cvar->FindVar("cl_mouseenable")->SetValue(1);

	SDL2::UnhookWindow();
	SDL2::UnhookPollEvent();

	NoSmoke::AimTuxShutdown();

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

	input->m_fCameraInThirdPerson = false;
	input->m_vecCameraOffset.z = 150.f;
	GetLocalClient(-1)->m_nDeltaTick = -1;

	delete eventListener;

	*bSendPacket = true;
	*s_bOverridePostProcessingDisable = false;
	*CrosshairWeaponTypeCheck = 5;
	*CamThinkSvCheatsCheck = 0x74;
	*(CamThinkSvCheatsCheck + 0x1) = 0x64;

	Util::ProtectAddr(bSendPacket, PROT_READ | PROT_EXEC);
	Util::ProtectAddr(CrosshairWeaponTypeCheck, PROT_READ | PROT_EXEC);
	for (ptrdiff_t off = 0; off < 0x2; off++)
		Util::ProtectAddr(CamThinkSvCheatsCheck + off, PROT_READ | PROT_EXEC);

	cvar->ConsoleColorPrintf(ColorRGBA(255, 150, 150), "AimTux has been unloaded successfully.\n");
}
