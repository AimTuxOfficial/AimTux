#pragma once

#include "../SDK/IInputSystem.h"
#include "../SDK/IClientEntity.h"

namespace AntiAim
{
    extern float lastRealYaw;
    extern float lastFakeYaw;


    float GetMaxDelta( CCSGOAnimState *animState );

    //Hooks
    void CreateMove(CUserCmd* cmd);
}