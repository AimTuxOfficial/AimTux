#include "nofall.h"

#include "../settings.h"
#include "../interfaces.h"

int lastFlags = 0;
float heightDiff;
bool shouldDuck = false;

void NoFall::PrePredictionCreateMove( CUserCmd *cmd ) {
    Ray_t ray;
    trace_t tr;

    if ( !Settings::NoFall::enabled )
        return;

    C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
    if ( !localplayer )
        return;

    if ( localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP )
        return;

    lastFlags = localplayer->GetFlags();

    if( shouldDuck && !( lastFlags & FL_ONGROUND ) ) {
        cmd->buttons |= IN_DUCK;
    }

    Vector origin = localplayer->GetVecOrigin();
    ray.Init( origin, Vector( origin.x, origin.y, origin.z - 8192.0f ) );
    CTraceFilter traceFilter;
    traceFilter.pSkip = localplayer;
    trace->TraceRay( ray, MASK_SHOT, &traceFilter, &tr );

    heightDiff = origin.z - tr.endpos.z;
    if( heightDiff > 200.0f ){ // gonna take damage, try to nofall.
        shouldDuck = true;
    }
}


void NoFall::PostPredictionCreateMove( CUserCmd *cmd ) {
    if ( !Settings::NoFall::enabled )
        return;

    C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
    if ( !localplayer )
        return;

    if ( localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP )
        return;

    if ( !(lastFlags & FL_ONGROUND) && (localplayer->GetFlags() & FL_ONGROUND) && shouldDuck ){
        cmd->buttons &= ~IN_DUCK;
        shouldDuck = false;
    }
}