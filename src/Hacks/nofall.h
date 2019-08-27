#pragma once

#include "../SDK/IInputSystem.h"

namespace NoFall
{
    //Hooks
    void PrePredictionCreateMove( CUserCmd* cmd );
    void PostPredictionCreateMove( CUserCmd* cmd );
}