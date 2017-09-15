#include "Fuzion.h"
#include "EventListener.h"
#include "preload.h"
#include "Utils/netvarmanager.h"

static EventListener* eventListener = nullptr;
// The below line is defined by the build script. Keep this on line 8.
char buildID[] = "vjNEFLyq80ZCLlEBvqYWbsGPIeysy864"; // Line defined by the build script.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

static bool preload = false;
static bool isShuttingDown = false;
void *Fuzion::prev = NULL,*Fuzion::curr = NULL,*Fuzion::next = NULL;
char Fuzion::buildPath[PATH_MAX] = {0};

void MainThread()
{
	if( preload )
	{
		while( client == nullptr )
		{
			client = GetInterface<IBaseClientDLL>(XORSTR("./csgo/bin/linux64/client_client.so"), XORSTR("VClient"));
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}
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
	Hooker::FindSendPacket();
	Hooker::FindPrediction();
	Hooker::FindIsReadyCallback();
	Hooker::FindSurfaceDrawing();
	Hooker::FindGetLocalClient();
	Hooker::FindLineGoesThroughSmoke();
	Hooker::FindInitKeyValues();
	Hooker::FindLoadFromBuffer();
	//Hooker::FindVstdlibFunctions();
	Hooker::FindOverridePostProcessingDisable();
	Hooker::FindCrosshairWeaponTypeCheck();
	Hooker::HookSwapWindow();
	Hooker::HookPollEvent();


	if( preload )
	{
		cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 200), XORSTR("LD_PRELOAD method Detected...\n"));
		bool found = false;
		for (int i = 0; environ[i]; i++)
		{
			if (strstr(environ[i], buildID) != NULL)
			{
				found = true;
			}
		}
		if (found)
		{
			cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 0), XORSTR("Environ has our buildID!\n"));
		}
		else
		{
			cvar->ConsoleColorPrintf(ColorRGBA(0, 150, 0), XORSTR("Environ Memory Purged Sucessfully.\n"));
		}
		cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 200), XORSTR("-- Hooks --\n"));

		/* The program will force exit before this point, if these are not found, so this is more of an informational read of what is hooked */
		cvar->ConsoleColorPrintf(ColorRGBA(0, 0, 200), XORSTR("fopen(): Hooked\n"));
		cvar->ConsoleColorPrintf(ColorRGBA(0, 0, 200), XORSTR("getenv(): Hooked\n"));
		cvar->ConsoleColorPrintf(ColorRGBA(0, 0, 200), XORSTR("open(): Hooked\n"));
		cvar->ConsoleColorPrintf(ColorRGBA(0, 0, 200), XORSTR("execve(): Hooked\n"));

		cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 200), XORSTR("-- Tests --\n"));
		if (getenv(XORSTR("LD_PRELOAD")) == NULL)
		{
			cvar->ConsoleColorPrintf(ColorRGBA(0, 150, 0), XORSTR("getenv(\"LD_PRELOAD\") Clean.\n"));
		}
		else
		{
			cvar->ConsoleColorPrintf(ColorRGBA(255, 255, 0), XORSTR("getenv(\"LD_PRELOAD\") = %s\n"), getenv(XORSTR("LD_PRELOAD")));
		}

		if (strcmp(XORSTR("/dev/null"), getenv(XORSTR("TMPDIR"))) == 0)
		{
			cvar->ConsoleColorPrintf(ColorRGBA(0, 150, 0), XORSTR("getenv(\"TMPDIR\") -> /dev/null.\n"));
		}
		else
		{
			cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 0), XORSTR("getenv(\"TMPDIR\") ->%s\n"), getenv(XORSTR("TMPDIR")));
		}

		char buffer[PATH_MAX];
		found = false;
		FILE *maps = fopen(XORSTR("/proc/self/maps"), "r");
		while (fgets(buffer, PATH_MAX, maps)) {
			if (strstr(buffer, buildID) != NULL)
				found = true;
		}
		fclose(maps);
		if (found)
		{
			cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 0), XORSTR("fopen(\"/proc/self/maps\") contains our shared object!\n"));
		}
		else
		{
			cvar->ConsoleColorPrintf(ColorRGBA(0, 150, 0), XORSTR("fopen(\"/proc/self/maps\") file Clean.\n"));
		}
	}
	else
	{
		cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 200), XORSTR("GDB Injection method Detected...\n"));
	}


	cvar->ConsoleColorPrintf(ColorRGBA(0, 225, 0), XORSTR("\nFuzion Successfully loaded.\n"));

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

	if (ModSupport::current_mod != ModType::CSCO && Hooker::HookRecvProp(XORSTR("CBaseViewModel"), XORSTR("m_nSequence"), SkinChanger::sequenceHook))
		SkinChanger::sequenceHook->SetProxyFunction((RecvVarProxyFn) SkinChanger::SetViewModelSequence);

	//NetVarManager::DumpNetvars();
	Offsets::GetOffsets();

	Fonts::SetupFonts();

	//Settings::LoadSettings();

	srand(time(NULL)); // Seed random # Generator so we can call rand() later

	AntiAim::LuaInit();


    snprintf(Fuzion::buildPath, PATH_MAX, "/%s", buildID);
    Util::RemoveLinkMapEntry(Fuzion::buildPath, &Fuzion::prev, &Fuzion::curr, &Fuzion::next); // This Breaks uload. Need to restore linked list first.
    if( Util::SearchLinkMap(Fuzion::buildPath) ) {
        cvar->ConsoleColorPrintf(ColorRGBA(200, 0, 0), XORSTR( "Warning! .so file did not get removed in link_map\n" ) );
    }
	if( preload )
	{
		while( !isShuttingDown )
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if( Util::IsDebuggerPresent() != 0 )
			{
				cvar->ConsoleColorPrintf(ColorRGBA(225, 0, 0), XORSTR("DEBUGGER DETECTED! EXITING FUZION\n"));
				Fuzion::SelfShutdown();
			}
		}
	}

    /*
    while( !isShuttingDown )
    {
        static bool bFirst = true;
        if( inputSystem->IsButtonDown(ButtonCode_t::KEY_P) && bFirst )
        {
            Util::RestoreLinkMapEntry(prev, curr, next);
            if( Util::SearchLinkMap(buildPath) )
            {
                cvar->ConsoleColorPrintf(ColorRGBA(0, 200, 0), XORSTR( "Found buildpath again.\n" ) );
            }
            bFirst = false;
        }
    }
    */
}
/* Entrypoint to the Library. Called when loading */
int __attribute__((constructor)) Startup()
{
	// Search in Environment Memory for our buildID before purging environ memory
	for(int i = 0; environ[i]; i++)
	{
		if(strstr(environ[i], buildID) != NULL)
		{
			preload = true;
			if( !Preload::Startup(buildID) )
			{
				char fd[PATH_MAX];
				snprintf(fd, sizeof(fd), XORSTR("/tmp/%s.log"), buildID);
				FILE *log = fopen(fd, "w");
				fprintf(log, XORSTR("Could not find functions to hook in Preload::Startup(). Exiting.\n"));
				fclose(log);
				exit(-1);
			}
			Preload::CleanEnvironment();
		}
	}

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
	isShuttingDown = true;
	cvar->FindVar(XORSTR("cl_mouseenable"))->SetValue(1);

	SDL2::UnhookWindow();
	SDL2::UnhookPollEvent();

	Preload::Cleanup();
	AntiAim::LuaCleanup();

	Aimbot::XDOCleanup();
	NoSmoke::Cleanup();
	TracerEffect::RestoreTracers();

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

	Util::ProtectAddr(bSendPacket, PROT_READ | PROT_EXEC);
	Util::ProtectAddr(CrosshairWeaponTypeCheck, PROT_READ | PROT_EXEC);

	cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), XORSTR("Fuzion Unloaded successfully.\n"));
}
void Fuzion::SelfShutdown()
{
    Util::RestoreLinkMapEntry(prev, curr, next);
    // Beta Feature.
	// Does not Correctly/Fully Unload yet.
    
	Shutdown();
    //void *self = dlopen()
	/*
	dlclose(self);
	dlclose(self);
	*/
}
