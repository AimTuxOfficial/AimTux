#include <iostream>

#include "interfaces.h"
#include "hooker.h"
#include "netvarmanager.h"

#include "atgui.h"
#include "Hooks/hooks.h"

UI_Container* gui;

pthread_t thread;
pthread_mutex_t mtx_quit;

int needQuit(pthread_mutex_t *mtx)
{
	switch (pthread_mutex_trylock(mtx))
	{
		case 0:
			pthread_mutex_unlock(mtx);
			return 1;
		case EBUSY:
			return 0;
	}

	return 1;
}

void *thread_do(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t *) arg;

	while (!needQuit(mutex))
	{
		ClanTagChanger::Run();
		NameChanger::Run();
		Spammer::Run();

		// We need to delay it otherwise we will be
		// causing buffer overflow using the clantag changer.
		usleep(100000);
	}

	return NULL;
}

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Hooker::HookInterfaces();
	Hooker::HookVMethods();
	Hooker::HookIClientMode();
	Hooker::HookGlobalVars();
	Hooker::HookGlowManager();
	Hooker::HookRankReveal();
	Hooker::HookSendClanTag();
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

	NetVarManager::dumpNetvars();
	Offsets::getOffsets();

	gui = new UI_Container;

	Fonts::SetupFonts();
	SetupUI();

	pthread_mutex_init(&mtx_quit, NULL);
	pthread_mutex_lock(&mtx_quit);
	pthread_create(&thread, NULL, thread_do, &mtx_quit);

	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	pthread_mutex_unlock(&mtx_quit);
	pthread_join(thread, NULL);

	engine->ExecuteClientCmd("cl_mouseenable 1");
	
	client_vmt->ReleaseVMT();
	panel_vmt->ReleaseVMT();
	modelRender_vmt->ReleaseVMT();
	clientMode_vmt->ReleaseVMT();
	gameEvents_vmt->ReleaseVMT();

	cvar->ConsoleColorPrintf(ColorRGBA(255, 150, 150), "AimTux has been unloaded successfully.\n");
}
