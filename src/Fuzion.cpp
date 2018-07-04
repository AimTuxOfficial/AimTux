#include "Fuzion.h"
#include "EventListener.h"
#include "Utils/netvarmanager.h"

static EventListener* eventListener = nullptr;

char Fuzion::buildID[NAME_MAX] = {
#include "../build_id_hex" // Made by ./build script.
};

void MainThread()
{
	Interfaces::FindInterfaces();
	//Interfaces::DumpInterfaces();

	Hooker::FindSetNamedSkybox();
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
	Hooker::FindPrediction();
	Hooker::FindIsReadyCallback();
	Hooker::FindSurfaceDrawing();
	Hooker::FindGetLocalClient();
	Hooker::FindLineGoesThroughSmoke();
	Hooker::FindInitKeyValues();
	Hooker::FindLoadFromBuffer();
	//Hooker::FindVstdlibFunctions();
	Hooker::FindOverridePostProcessingDisable();
	Hooker::HookSwapWindow();
	Hooker::HookPollEvent();

	clientVMT->HookVM((void*) Hooks::IN_KeyEvent, 20);
	clientVMT->HookVM((void*) Hooks::FrameStageNotify, 36);
	clientVMT->ApplyVMT();

    clientModeVMT->HookVM((void*) Hooks::OverrideView, 19);
    clientModeVMT->HookVM((void*) Hooks::CreateMove, 25);
    clientModeVMT->HookVM((void*) Hooks::GetViewModelFOV, 36);
    clientModeVMT->ApplyVMT();

    engineVGuiVMT->HookVM((void*) Hooks::Paint, 15);
    engineVGuiVMT->ApplyVMT();

	gameEventsVMT->HookVM((void*) Hooks::FireEvent, 9);
	gameEventsVMT->HookVM((void*) Hooks::FireEventClientSide, 10);
	gameEventsVMT->ApplyVMT();

    inputInternalVMT->HookVM((void*) Hooks::SetKeyCodeState, 92);
    inputInternalVMT->HookVM((void*) Hooks::SetMouseCodeState, 93);
    inputInternalVMT->ApplyVMT();

    launcherMgrVMT->HookVM((void*) Hooks::PumpWindowsMessageLoop, 19);
    launcherMgrVMT->ApplyVMT();

	materialVMT->HookVM((void*) Hooks::BeginFrame, 42);
	materialVMT->ApplyVMT();

    modelRenderVMT->HookVM((void*) Hooks::DrawModelExecute, 21);
    modelRenderVMT->ApplyVMT();

    panelVMT->HookVM((void*) Hooks::PaintTraverse, 42);
    panelVMT->ApplyVMT();

    soundVMT->HookVM((void*) Hooks::EmitSound1, 5);
    soundVMT->HookVM((void*) Hooks::EmitSound2, 6);
    soundVMT->ApplyVMT();

	surfaceVMT->HookVM((void*) Hooks::PlaySound, 82);
	surfaceVMT->HookVM((void*) Hooks::OnScreenSizeChanged, 116);
	surfaceVMT->ApplyVMT();

    viewRenderVMT->HookVM((void*) Hooks::RenderSmokePostViewmodel, 41);
    viewRenderVMT->ApplyVMT();

	eventListener = new EventListener({ XORSTR("cs_game_disconnected"), XORSTR("player_connect_full"), XORSTR("player_death"), XORSTR("player_hurt"), XORSTR("switch_team") });

	if (Hooker::HookRecvProp(XORSTR("CBaseViewModel"), XORSTR("m_nSequence"), SkinChanger::sequenceHook))
		SkinChanger::sequenceHook->SetProxyFunction((RecvVarProxyFn) SkinChanger::SetViewModelSequence);

	//NetVarManager::DumpNetvars();
	Offsets::GetOffsets();

	Fonts::SetupFonts();

	//Settings::LoadSettings();

	srand(time(NULL)); // Seed random # Generator so we can call rand() later

	AntiAim::LuaInit();
}
/* Entrypoint to the Library. Called when loading */
int __attribute__((constructor)) Startup()
{
	std::thread mainThread(MainThread);
	// The root of all suffering is attachment
	// Therefore our little buddy must detach from this realm.
	// Farewell my thread, may we join again some day..
	mainThread.detach();

	return 0;
}
/* Called when un-injecting the library */
void __attribute__((destructor)) Shutdown()
{
	cvar->FindVar(XORSTR("cl_mouseenable"))->SetValue(1);

	SDL2::UnhookWindow();
	SDL2::UnhookPollEvent();

	AntiAim::LuaCleanup();

	Aimbot::XDOCleanup();
	NoSmoke::Cleanup();
	TracerEffect::RestoreTracers();

	clientVMT->ReleaseVMT();
    clientModeVMT->ReleaseVMT();
    engineVGuiVMT->ReleaseVMT();
    gameEventsVMT->ReleaseVMT();
    inputInternalVMT->ReleaseVMT();
    launcherMgrVMT->ReleaseVMT();
    materialVMT->ReleaseVMT();
    modelRenderVMT->ReleaseVMT();
    panelVMT->ReleaseVMT();
	soundVMT->ReleaseVMT();
    surfaceVMT->ReleaseVMT();
    viewRenderVMT->ReleaseVMT();

    input->m_fCameraInThirdPerson = false;
	input->m_vecCameraOffset.z = 150.f;
	GetLocalClient(-1)->m_nDeltaTick = -1;

	delete eventListener;

	*s_bOverridePostProcessingDisable = false;

	cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), XORSTR("Fuzion Unloaded successfully.\n"));
}
void Fuzion::SelfShutdown()
{
    // Beta Feature.
	// Does not Correctly/Fully Unload yet.
    
	Shutdown();
    //void *self = dlopen()
	/*
	dlclose(self);
	dlclose(self);
	*/
}
