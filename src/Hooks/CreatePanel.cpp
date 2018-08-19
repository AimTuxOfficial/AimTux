#include "hooks.h"

panorama::PanelWrapper *Hooks::CreatePanel( panorama::UIEngine *thisptr, panorama::CPanoramaSymbol* symbol, const char *str, panorama::IUIPanel *panel ) {
    cvar->ConsoleDPrintf("Panel Created: %s\n", panel->GetID());
    return uiEngineVMT->GetOriginalMethod<CreatePanelFn>(139)( thisptr, symbol, str, panel );
}