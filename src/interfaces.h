#pragma once

#include "SDK/SDK.h"
#include "vmt.h"

extern IBaseClientDLL* client;
extern ISurface* surface;
extern IVPanel*	panel;
extern IEngineClient* engine;
extern IClientEntityList* entitylist;
extern IVDebugOverlay* debugOverlay;
extern IVModelInfo* modelInfo;
extern IVModelRender* modelRender;
extern IClientMode* clientMode;
extern IEngineTrace* trace;
extern IInputSystem* input;
extern IInputInternal* inputInternal;
extern IMaterialSystem* material;
extern ICvar* cvar;
extern CGlobalVars* globalvars;
extern CEffects* effects;
extern IGameEventManager2* gameevents;
extern IPhysicsSurfaceProps* physics;
extern IPrediction* prediction;
extern IGameMovement* gamemovement;
extern IMoveHelper* movehelper;

extern VMT* panel_vmt;
extern VMT* client_vmt;
extern VMT* modelRender_vmt;
extern VMT* clientMode_vmt;
extern VMT* gameEvents_vmt;
extern VMT* viewRender_vmt;
extern VMT* inputInternal_vmt;

extern int* nPredictionRandomSeed;
extern bool* bSendPacket;
extern CMoveData* g_MoveData;