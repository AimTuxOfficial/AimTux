#ifndef __INTERFACES_H_
#define __INTERFACES_H_

#include "SDK.h"
#include "vmt.h"

extern HLClient*			client;
extern ISurface*			surface;
extern IPanel*				panel;
extern CEngineClient*		engine;
extern IClientEntityList*	entitylist;
extern CDebugOverlay*		debugOverlay;
extern IVModelInfo*			modelInfo;
extern IClientMode*			clientMode;
extern IEngineTrace*		trace;

extern VMT* panel_vmt;
extern VMT* client_vmt;
extern VMT* clientMode_vmt;

#endif