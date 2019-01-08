#include "gui.h"

#include "../interfaces.h"

/* CSGO Panels */
panorama::IUIPanel* GUI::menuRoot = NULL;
panorama::IUIPanel* GUI::hudRoot = NULL;
/* Custom Panels */
panorama::IUIPanel* GUI::fuzionMain = NULL;

// Javascript to force root panel to have our child and raise it.
const char *cuckProtocol =
        "var parentPanel = $.GetContextPanel();\n"
                "var fuzion = parentPanel.FindChild(\"FuzionMain\");\n"
                "$.Msg(\"Loading Panel: \" + fuzion.id);"
                "fuzion.BLoadLayoutFromString( \"%s\", false, false);\n";

static constexpr unsigned int JS_MAX = 65535;
char jsCode[JS_MAX];
std::string mainXML =
#include "main.xml"
;

static panorama::IUIPanel* GetRoot( bool inGame ){
    panorama::IUIPanel *panel = panoramaEngine->AccessUIEngine()->GetLastDispatchedEventTargetPanel();

    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(panel) ){
        cvar->ConsoleDPrintf("[GUI::GetRoot]Failed to grab Last Event Target Panel!\n");
        return NULL;
    }
    panorama::IUIPanel *itr = panel;
    panorama::IUIPanel *ret = nullptr;
    while( itr && panoramaEngine->AccessUIEngine()->IsValidPanelPointer(itr) ){
        if( inGame ){
            if( !strcmp(itr->GetID(), "CSGOHud") ){
                ret = itr;
                break;
            }
        } else {
            if( !strcmp(itr->GetID(), "CSGOMainMenu") ){
                ret = itr;
                break;
            }
        }
        itr = itr->GetParent();
    }
    return ret;
}
static void SetupAndCheckPanels()
{
    /* Grab the CSGO root panels if we don't have them */
    if( engine->IsInGame() && !GUI::hudRoot ){
        panorama::IUIPanel* panel = GetRoot( engine->IsInGame() );
        if( !panel ){
            cvar->ConsoleDPrintf("Could not get InGame HUD Root Panel!\n");
            return;
        }
        GUI::hudRoot = panel;
    } else if( !GUI::menuRoot ){
        panorama::IUIPanel* panel = GetRoot( engine->IsInGame() );
        if( !panel ){
            cvar->ConsoleDPrintf("Could not get MainMenu Root Panel!\n");
            return;
        }
        GUI::menuRoot = panel;
    }
    /* Are we in-game? The root panel is different */
    panorama::IUIPanel *root = (engine->IsInGame() ? GUI::hudRoot : GUI::menuRoot);
    cvar->ConsoleDPrintf("Root panel is: (%s)\n", root->GetID());

    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(root) ){
        cvar->ConsoleDPrintf("[GUI::SetupAndCheckPanels] - Root panel pointer Invalid(%p)\n", (void*)root);
        return;
    }
    if( !root->HasBeenLayedOut() ){
        cvar->ConsoleDPrintf("[GUI::SetupAndCheckPanels] - Root panel has not been layed out yet!\n");
        return;
    }
    /* Setup our Custom Panel */
    if( !GUI::fuzionMain ){
        cvar->ConsoleDPrintf("Creating Fuzion panel...\n");
        // Get rid of newlines, they mess up the javascript syntax
        std::replace(mainXML.begin(), mainXML.end(), '\n', ' ');
        snprintf(jsCode, JS_MAX, cuckProtocol, mainXML.c_str());

        panorama::CPanoramaSymbol type = panoramaEngine->AccessUIEngine()->MakeSymbol("Panel");
        cvar->ConsoleDPrintf("Panel symbol: (%s)\n", panoramaEngine->AccessUIEngine()->ResolveSymbol(type));
        GUI::fuzionMain = panoramaEngine->AccessUIEngine()->CreatePanel(&type, "FuzionMain", root)->panel;
        panoramaEngine->AccessUIEngine()->RunScript(root, jsCode, "panorama/layout/base.xml", 8, 10, false);
        cvar->ConsoleDPrintf("Root ID: %s\n", root->GetID());
    }
    /* Afterwards, Set parent based on if we're in-game */
    GUI::fuzionMain->SetParent( root );
}

void GUI::ToggleUI()
{
    SetupAndCheckPanels();
    if( !panoramaEngine->AccessUIEngine()->IsValidPanelPointer(GUI::fuzionMain) ){
        cvar->ConsoleDPrintf("[GUI::ToggleUI] - Something is wrong with our Fuzion Panel Pointer(%p)\n", (void*)GUI::fuzionMain);
        return;
    }
    if( !GUI::fuzionMain->HasBeenLayedOut() ){
        cvar->ConsoleDPrintf("[GUI::ToggleUI] - Fuzion Panel not layed out yet. Try again.\n");
        return;
    }

    GUI::fuzionMain->SetVisible(!GUI::fuzionMain->IsVisible());
}