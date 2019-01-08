#pragma once

#include "../SDK/IInputSystem.h"

namespace TracerEffect
{
    void RestoreTracers();

    //Hooks
    void CreateMove(CUserCmd* cmd);
}