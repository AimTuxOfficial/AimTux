#pragma once

#include "SDK/SDK.h"
#include "Utils/vmt.h"

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
extern IPanoramaUIEngine* panoramaEngine;
extern IFileSystem* fileSystem;
extern IGameTypes* gameTypes;
extern CItemSystem* itemSystem;

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
extern VMT* uiEngineVMT;

extern LineGoesThroughSmokeFn LineGoesThroughSmoke;
extern InitKeyValuesFn InitKeyValues;
extern LoadFromBufferFn LoadFromBuffer;

extern GetLocalClientFn GetLocalClient;

//extern RandomSeedFn RandomSeed;
//extern RandomFloatFn RandomFloat;
//extern RandomFloatExpFn RandomFloatExp;
//extern RandomIntFn RandomInt;
//extern RandomGaussianFloatFn RandomGaussianFloat;

extern SetNamedSkyBoxFn SetNamedSkyBox;

extern int* nPredictionRandomSeed;
extern CMoveData* g_MoveData;
extern bool* s_bOverridePostProcessingDisable;
extern ConVar *cl_csm_enabled;
extern int32_t *g_nagleTime;

namespace Interfaces
{
	void FindInterfaces();
	void DumpInterfaces();
}
