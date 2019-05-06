#include "hooks.h"

#include "../interfaces.h"
#include "../shortcuts.h"
#include "../ATGUI/atgui.h"
#include "../GUI/gui.h"

bool SetKeyCodeState::shouldListen = false;
ButtonCode_t* SetKeyCodeState::keyOutput = nullptr;

typedef void (*SetKeyCodeStateFn) (void*, ButtonCode_t, bool);

void Hooks::SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed)
{
	if (SetKeyCodeState::shouldListen && bPressed)
	{
		SetKeyCodeState::shouldListen = false;
		*SetKeyCodeState::keyOutput = code;
		UI::UpdateWeaponSettings();
	}

	if (!SetKeyCodeState::shouldListen)
		Shortcuts::SetKeyCodeState(code, bPressed);


	if( code == ButtonCode_t::KEY_DELETE && bPressed ){
        for( int i = 0; i < 1024; i++ ){
            panorama::IUIPanel *panel = panorama::panelArray->slots[i].panel;
            if( panoramaEngine->AccessUIEngine()->IsValidPanelPointer(panel) ){
                cvar->ConsoleDPrintf("Panel %d: (%s)\n", i, panel->GetID());
            }
        }
	}

    if( code == ButtonCode_t::KEY_HOME && bPressed ){
        GUI::ToggleUI();
	}
	inputInternalVMT->GetOriginalMethod<SetKeyCodeStateFn>(92)(thisptr, code, bPressed);
}
