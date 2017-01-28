#include "modsupport.h"

ModType ModSupport::current_mod = ModType::NO_MOD;

void ModSupport::OnInit()
{
    const char* output;
    commandline->CheckParm("-game", &output);

    if (strstr(output, "csco"))
    {
        current_mod = ModType::CSCO;
        cvar->ConsoleColorPrintf(ColorRGBA(150, 150, 255), "Counter-Strike: Classic Offensive detected!\n");
    }
}