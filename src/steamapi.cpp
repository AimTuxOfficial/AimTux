#include "steamapi.h"
#include "interfaces.h"

#include "../SDK/steam/isteamclient.h"
#include "../SDK/steam/isteaminput.h"

#include "../Utils/util.h"

// Steam api sucks!
struct SteamInputInner
{
    void* vtable;
    void* blank;
    void* blank2;
    SteamInputActionEventCallbackPointer actionEventCallback;
};
struct SteamInputHack
{
    void* vtable;
    SteamInputInner* inner;
};

typedef void (*RunFrameFn)(ISteamInput*, bool);
SteamInputActionEventCallbackPointer originalActionEventCallbackPointer;
static ISteamInput* steamInput = nullptr;
void SteamInputActionEventCallback(SteamInputActionEvent_t* event)
{
    if (event->eEventType == ESteamInputActionEventType_DigitalAction)
    {
	cvar->ConsoleDPrintf("Input: (%s)\n", steamInput->GetStringForDigitalActionName(event->digitalAction.actionHandle));
    }
    // Call the original csgo controller callback
    originalActionEventCallbackPointer(event);
}


void SteamAPI::HookSteamInput() {
    void* libSteamApi = dlopen("./bin/linux64/libsteam_api.so", RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

    typedef ISteamClient* (*GetSteamClientFn)();
    GetSteamClientFn GetSteamClientFunc = (GetSteamClientFn)(dlsym(libSteamApi, "SteamClient"));
    typedef HSteamPipe (*GetSteamPipeFn)();
    GetSteamPipeFn GetSteamPipeFunc = (GetSteamPipeFn)(dlsym(libSteamApi, "GetHSteamPipe"));

    ISteamClient* steamClient = GetSteamClientFunc();
    HSteamPipe steamPipe = GetSteamPipeFunc();
    HSteamUser steamUser = steamClient->ConnectToGlobalUser(steamPipe);

    typedef void* (*SteamFindOrCreateInterfaceFn)(HSteamUser, const char*);
    SteamFindOrCreateInterfaceFn SteamFindOrCreateInterfaceFunc = (SteamFindOrCreateInterfaceFn)(dlsym(libSteamApi, "SteamInternal_FindOrCreateUserInterface"));

    steamInput = (ISteamInput*)SteamFindOrCreateInterfaceFunc(steamUser, STEAMINPUT_INTERFACE_VERSION);

    // god-tier hack, Steam doesn't expose the original Callback and CSGO uses it
    SteamInputHack* hack = (SteamInputHack*)steamInput;
    originalActionEventCallbackPointer = hack->inner->actionEventCallback;
    steamInput->EnableActionEventCallbacks(SteamInputActionEventCallback);

    dlclose(libSteamApi);
}

void SteamAPI::UnhookSteamInput() {
    if (steamInput)
    {
	steamInput->EnableActionEventCallbacks(originalActionEventCallbackPointer);
    }
}