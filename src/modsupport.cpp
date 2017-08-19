#include "modsupport.h"

ModType ModSupport::current_mod = ModType::NO_MOD;

void ModSupport::OnInit()
{
    const char* output;
    commandline->CheckParm(XORSTR("-game"), &output);

    if (strstr(output, XORSTR("csco")))
    {
        current_mod = ModType::CSCO;
        cvar->ConsoleColorPrintf(ColorRGBA(0, 255, 255), XORSTR("Counter-Strike: Classic Offensive detected!\n"));
    }
}
