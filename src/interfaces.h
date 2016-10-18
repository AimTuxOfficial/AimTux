#ifndef __INTERFACES_H_
#define __INTERFACES_H_

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
extern IMaterialSystem* material;
extern ICvar* cvar;
extern CGlobalVars* globalvars;
extern CEffects* effects;
extern IGameEventManager2* gameevents;
extern IPhysicsSurfaceProps* physics;

extern VMT* panel_vmt;
extern VMT* client_vmt;
extern VMT* modelRender_vmt;
extern VMT* clientMode_vmt;
extern VMT* gameEvents_vmt;

#endif
