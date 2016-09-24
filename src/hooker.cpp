#include "hooker.h"

HLClient* client = nullptr;
ISurface* surface = nullptr;
IPanel* panel = nullptr;
CEngineClient* engine = nullptr;
IClientEntityList* entitylist = nullptr;
CDebugOverlay* debugOverlay = nullptr;
IVModelInfo* modelInfo = nullptr;

VMT* panel_vmt = nullptr;
VMT* client_vmt = nullptr;

void Hooker::HookInterfaces ()
{
	client = GetInterface<HLClient>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
	engine = GetInterface<CEngineClient>("./bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);
	surface = GetInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", SURFACE_INTERFACE_VERSION);
	panel = GetInterface<IPanel>("./bin/linux64/vgui2_client.so", PANEL_INTERFACE_VERSION);
	debugOverlay = GetInterface<CDebugOverlay>("./bin/linux64/engine_client.so", DEBUG_OVERLAY_VERSION);
	modelInfo = GetInterface<IVModelInfo>("./bin/linux64/engine_client.so", VMODELINFO_CLIENT_INTERFACE_VERSION);
}

void Hooker::HookVMethods ()
{
	panel_vmt = new VMT (panel);
	client_vmt = new VMT (client);
}