#include "Fuzion.h"
#include "EventListener.h"
#include "Utils/netvarmanager.h"

static EventListener* eventListener = nullptr;

const char *Util::logFileName = "/tmp/fuzion.log";

char Fuzion::buildID[NAME_MAX] = {
#include "../build_id_hex" // Made by ./build script.
};

void MainThread()
{
	Interfaces::FindInterfaces();
    //Interfaces::DumpInterfaces();
    cvar->ConsoleDPrintf("Loading...\n");
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
	Hooker::FindSetLocalPlayerReady();
	Hooker::FindSurfaceDrawing();
	Hooker::FindGetLocalClient();
	Hooker::FindLineGoesThroughSmoke();
	Hooker::FindInitKeyValues();
	Hooker::FindLoadFromBuffer();
	//Hooker::FindVstdlibFunctions();
	Hooker::FindOverridePostProcessingDisable();
	Hooker::HookSwapWindow();
	Hooker::HookPollEvent();
    Hooker::FindPanelArrayOffset();

    Offsets::GetOffsets();
    Fonts::SetupFonts();

    cvar->ConsoleDPrintf("Panorama UI Engine @ %p\n", (void*)panoramaEngine->AccessUIEngine());
    cvar->ConsoleDPrintf("Install path: %s\n", panoramaEngine->AccessUIEngine()->GetApplicationInstallPath());
    cvar->ConsoleDPrintf("UI Frametime: %f\n", panoramaEngine->AccessUIEngine()->GetCurrentFrameTime());
    cvar->ConsoleDPrintf("PanelArray is at %p\n", (void*)panorama::panelArray);

    //uiEngineVMT->HookVM((void*)Hooks::RunScript, 110);
    //uiEngineVMT->HookVM((void*)Hooks::CreatePanel, 140);
    //uiEngineVMT->HookVM((void*)Hooks::DispatchEvent, 49);
    //uiEngineVMT->ApplyVMT();

	clientVMT->HookVM(Hooks::FrameStageNotify, 37);
	clientVMT->ApplyVMT();

    clientModeVMT->HookVM(Hooks::OverrideView, 19);
    clientModeVMT->HookVM(Hooks::CreateMove, 25);
    clientModeVMT->HookVM(Hooks::GetViewModelFOV, 36);
    clientModeVMT->ApplyVMT();

    engineVGuiVMT->HookVM(Hooks::Paint, 15);
    engineVGuiVMT->ApplyVMT();

	gameEventsVMT->HookVM(Hooks::FireEvent, 9);
	gameEventsVMT->HookVM(Hooks::FireEventClientSide, 10);
	gameEventsVMT->ApplyVMT();

    inputInternalVMT->HookVM(Hooks::SetKeyCodeState, 92);
    inputInternalVMT->HookVM(Hooks::SetMouseCodeState, 93);
    inputInternalVMT->ApplyVMT();

    launcherMgrVMT->HookVM(Hooks::PumpWindowsMessageLoop, 19);
    launcherMgrVMT->ApplyVMT();

	materialVMT->HookVM(Hooks::BeginFrame, 42);
	materialVMT->ApplyVMT();

    modelRenderVMT->HookVM(Hooks::DrawModelExecute, 21);
    modelRenderVMT->ApplyVMT();

    panelVMT->HookVM(Hooks::PaintTraverse, 42);
    panelVMT->ApplyVMT();

    soundVMT->HookVM( Hooks::EmitSound2, 6);
    soundVMT->ApplyVMT();

	surfaceVMT->HookVM(Hooks::OnScreenSizeChanged, 116);
	surfaceVMT->ApplyVMT();

    viewRenderVMT->HookVM(Hooks::RenderSmokePostViewmodel, 41);
    viewRenderVMT->ApplyVMT();

	eventListener = new EventListener({ XORSTR("cs_game_disconnected"), XORSTR("player_connect_full"), XORSTR("player_death"), XORSTR("player_hurt"), XORSTR("switch_team") });

	if (Hooker::HookRecvProp(XORSTR("CBaseViewModel"), XORSTR("m_nSequence"), SkinChanger::sequenceHook))
		SkinChanger::sequenceHook->SetProxyFunction((RecvVarProxyFn) SkinChanger::SetViewModelSequence);

	//NetVarManager::DumpNetvars();


	//Settings::LoadSettings();

	srand(time(NULL)); // Seed random # Generator so we can call rand() later

	AntiAim::LuaInit();

    cvar->ConsoleColorPrintf(ColorRGBA(0, 225, 0), XORSTR("\nFuzion Successfully loaded.\n"));
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
