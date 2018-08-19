#include "hooks.h"


static unsigned char savedEvent[0x300];
void Hooks::DispatchEvent( panorama::UIEngine *thisptr, panorama::IUIEvent *event ) {
    static bool bFirst = true;
    if( bFirst ){
        cvar->ConsoleDPrintf("Event dispatched: %p\n", (void*)event);
        memcpy(savedEvent, event, 0x300);
        cvar->ConsoleDPrintf("Saved @ %p\n", (void*)savedEvent);
        bFirst = false;
    } else {
        cvar->ConsoleDPrintf("Event dispatched: %p (not saving)\n", (void*)event);
    }

    uiEngineVMT->GetOriginalMethod<DispatchEventFn>(48)( thisptr, event );
}