#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace GrenadeHelper
{
    enum GrenadeType : int
    {
        FLASH,
        SMOKE,
        MOLOTOV,
        HEGRENADE
    };
    enum ThrowType : int
    {
        NORMAL,
        CROUCH,
        JUMP,
        CROUCH_JUMP
    };
    struct GrenadeInfo
    {
        GrenadeType gType;
        Vector pos;
        QAngle angle;
        ThrowType tType;
        GrenadeInfo(GrenadeType gType, Vector pos, QAngle angle,ThrowType tType){
            this->gType = gType;
            this->pos = pos;
            this->angle = angle;
            this->tType = tType;
        }
    };

    void DrawGrenadeInfo(GrenadeInfo* info);
    void DrawAimHelp(GrenadeInfo* info);

    void FireGameEvent(IGameEvent* event);//for loading new data for new Map
    //void CreateMove(CUserCmd* cmd);//Activly Help to perfect grenade?
    void Paint();//Draw the Grenade Esp
};
