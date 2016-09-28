#include "bhop.h"

bool Settings::BHop::enabled = true;

void BHop::CreateMove(CUserCmd* cmd)
{
    if (Settings::BHop::enabled) {
        static bool bLastJumped = false;
        static bool bShouldFake = false;

        C_BaseEntity* localplayer = reinterpret_cast<C_BaseEntity*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

        if (!bLastJumped && bShouldFake) {
            bShouldFake = false;
            cmd->buttons |= IN_JUMP;
        } else if (cmd->buttons & IN_JUMP) {
            if (localplayer->GetFlags() & FL_ONGROUND) {
                bLastJumped = true;
                bShouldFake = true;
            } else {
                cmd->buttons &= ~IN_JUMP;
                bLastJumped = false;
            }
        } else {
            bLastJumped = false;
            bShouldFake = false;
        }
    }
}