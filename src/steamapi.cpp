#include "steamapi.h"
#include "interfaces.h"
#include "ATGUI/atgui.h"
#include "sdlhook.h"

#include "../SDK/steam/isteamclient.h"
#include "../SDK/steam/isteaminput.h"

#include "../Utils/util.h"

#include <SDL2/SDL.h>

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
    static InputDigitalActionHandle_t inGameMenuTrigger = 0;
    static InputDigitalActionHandle_t inMenuMenuTrigger = 0;
    static InputDigitalActionHandle_t inGameSelectTrigger = 0;
    static InputDigitalActionHandle_t inMenuSelectTrigger = 0;
    static bool inGameMenuKeyPressedLastFrame = false;
    static bool inMenuMenuKeyPressedLastFrame = false;
    static bool inGameSelectPressedLastFrame = false;
    static bool inMenuSelectPressedLastFrame = false;

    //TODO: could probably do this with engine->IsInGame(), but i dont really feel like finding out if it's safe to call from here(it's most likely not)
    if (event->eEventType == ESteamInputActionEventType_AnalogAction)
    {
        int mode = event->analogAction.analogActionData.eMode;
        float x = event->analogAction.analogActionData.x;
        float y = event->analogAction.analogActionData.y;
	// mini-touchpads(Despite the enum saying absolute, this is relative)
	// Removed: goblins at valve have the same Enum value for the gyro?? Maybe i'm doing it wrong?
	//if (mode == 4)
	//{
	//    SDL2::mouseX += (int)x;
	//    SDL2::mouseY += (int)y;
	//}
	
	// joysticks
	if (mode == 6)
	{
	    SDL2::mouseX += (int)(x * 8.0f);
	    SDL2::mouseY -= (int)(y * 8.0f);
	}
    }
    if (event->eEventType == ESteamInputActionEventType_DigitalAction)
    {
        if (!inGameMenuTrigger || !inMenuMenuTrigger || !inGameSelectPressedLastFrame || !inMenuSelectPressedLastFrame)
        {
            const char* eventName = steamInput->GetStringForDigitalActionName(event->digitalAction.actionHandle);
	    // Currently we're using the "Sprint/Melee Latch" action to open the menu. This is bound to Left-stick-click by default.
	    // I guess someone at Valve thought that csgo had sprinting and made sure to put to enable this by default
	    // Action Layers don't work, and this whole input system is horrible(can't add any via API either, or even just get buttons pressed via ISteamInput)
	    // I would use SDL gamepad events instead, but they are not present.
	    if (!strcmp(eventName, "Sprint/Melee Latch"))
	    {
	        inGameMenuTrigger = event->digitalAction.actionHandle;
	    }
	    // And for Opening the Menu while not In-Game, we are using the "Options" event. This event does nothing.
	    // Make sure to bind it in your steam controller settings, there are plenty of open slots(In Menu!)
	    else if (!strcmp(eventName, "Options"))
	    {
   	        inGameMenuTrigger = event->digitalAction.actionHandle;
	    }
	    // Why yes this is the mouse-down button, in-menu of course
	    else if (!strcmp(eventName, "Select"))
	    {
	        inMenuSelectTrigger = event->digitalAction.actionHandle;
	    }
	    // bing bing wahoo
	    else if (!strcmp(eventName, "Jump"))
	    {
	        inGameSelectTrigger = event->digitalAction.actionHandle;
	    }
        }

	bool keydown = event->digitalAction.digitalActionData.bState;
	if (event->digitalAction.actionHandle == inGameMenuTrigger)
	{
	    if (!inGameMenuKeyPressedLastFrame && keydown)
	    {
	        UI::SetVisible(!UI::isVisible);
	    }
	    inGameMenuKeyPressedLastFrame = keydown;
	}
	else if (event->digitalAction.actionHandle == inMenuMenuTrigger)
	{	
	    if (!inMenuMenuKeyPressedLastFrame && keydown)
	    {
	        UI::SetVisible(!UI::isVisible);
	    }
	    inMenuMenuKeyPressedLastFrame = keydown;
	}
	else if (event->digitalAction.actionHandle == inGameSelectTrigger)
	{
	    SDL2::isMouseDown = keydown;
	}
	else if (event->digitalAction.actionHandle == inMenuSelectTrigger)
	{
	    SDL2::isMouseDown = keydown;
	}

	cvar->ConsoleDPrintf("Input: (%s)\n", steamInput->GetStringForDigitalActionName(event->digitalAction.actionHandle));
    }
      
    // Call the original csgo controller callback(if no hack menu of course)
    if (!UI::isVisible)
    {
        originalActionEventCallbackPointer(event);
    }
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
