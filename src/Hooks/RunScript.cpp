#include "hooks.h"

int Hooks::RunScript( panorama::UIEngine *thisptr, panorama::IUIPanel *panel, const char *entireJSCode, const char *pathToXMLContext, int int1, int int2, bool alreadyCompiled ) {
    cvar->ConsoleDPrintf( "--RunScript--\n Panel: %s Str1: %s, Str2: (%s), int1: %d, int2: %d, bool1(%s)\n", panel->GetID(), entireJSCode, pathToXMLContext, int1, int2, alreadyCompiled? "yes" : "no" );


    int code = uiEngineVMT->GetOriginalMethod<RunScriptFn>(109)( thisptr, panel, entireJSCode, pathToXMLContext, int1, int2, alreadyCompiled );
    cvar->ConsoleDPrintf("RETURN CODE: %d\n", code);
    return code;
}