#pragma once

#include <unordered_map>
#include <sys/mman.h>
#include <link.h>
#include <fstream>
#include "Utils/patternfinder.h"
#include "SDK/SDK.h"
#include "Utils/vmt.h"
#include "Utils/util.h"

extern IBaseClientDLL* client;
extern ISurface* surface;
extern IVPanel* panel;
extern IEngineClient* engine;
extern IClientEntityList* entityList;
extern IVDebugOverlay* debugOverlay;
extern IVModelInfo* modelInfo;
extern IVModelRender* modelRender;
extern IClientMode* clientMode;
extern IEngineTrace* trace;
extern IInputSystem* inputSystem;
extern IInputInternal* inputInternal;
extern IMaterialSystem* material;
extern ICvar* cvar;
extern CGlobalVars* globalVars;
extern CEffects* effects;
extern IGameEventManager2* gameEvents;
extern IPhysicsSurfaceProps* physics;
extern CViewRender* viewRender;
extern IPrediction* prediction;
extern IGameMovement* gameMovement;
extern IMoveHelper* moveHelper;
extern CGlowObjectManager* glowManager;
extern ILauncherMgr* launcherMgr;
extern C_CSPlayerResource** csPlayerResource;
extern C_CSGameRules** csGameRules;
extern IEngineVGui* engineVGui;
extern IEngineSound* sound;
extern ILocalize* localize;
extern ICommandLine* commandline;
extern CInput* input;

extern VMT* panelVMT;
extern VMT* clientVMT;
extern VMT* modelRenderVMT;
extern VMT* clientModeVMT;
extern VMT* gameEventsVMT;
extern VMT* viewRenderVMT;
extern VMT* inputInternalVMT;
extern VMT* materialVMT;
extern VMT* surfaceVMT;
extern VMT* launcherMgrVMT;
extern VMT* engineVGuiVMT;
extern VMT* soundVMT;

extern LineGoesThroughSmokeFn LineGoesThroughSmoke;
extern InitKeyValuesFn InitKeyValues;
extern LoadFromBufferFn LoadFromBuffer;

extern int* nPredictionRandomSeed;
extern bool* bSendPacket;
extern CMoveData* g_MoveData;

extern uintptr_t original_swap_window;
extern uintptr_t* swap_window_jump_address;

extern uintptr_t original_pollevent;
extern uintptr_t* pollevent_jump_address;

namespace Interfaces
{
	void FindInterfaces();
	void DumpInterfaces();
}