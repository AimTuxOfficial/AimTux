//
// Created by orinion on 08.02.17.
//

#include "grenadehelper.h"
using namespace GrenadeHelper;

bool Settings::GrenadeHelper::enabled = true;
std::vector<GrenadeHelper::GrenadeInfo> /**Settings::GrenadeHelper::**/grenadeInfos = { GrenadeInfo(GrenadeType::SMOKE, Vector(1149.4f,-1183.97f,-141.51f),QAngle(-39.49f,-171.85f,0f),ThrowType::CROUCH),
                                                                                  GrenadeInfo(GrenadeType::FLASH, Vector(803f,-1418f,-44.91f),QAngle(-30.49f,-178.85f,0f),ThrowType::NORMAL)};

void GrenadeHelper::Paint()
{
    if(!Settings::GrenadeHelper::enabled)
        return;

    if (!engine->IsInGame())
        return;

    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if (!localplayer)
        return;

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());

    if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
        return;

    //draw the smokes
    for(auto grenadeInfo = grenadeInfos.begin(); grenadeInfo != grenadeInfos.end(); grenadeInfo++)
    {
        if(grenadeInfo->pos.DistTo(localplayer->GetVecOrigin()) > 1000)//TODO change dist
        {
            //Draw normal
        }
        else
        {
            //Draw showing the QAngle
        }
    }
}

void GrenadeHelper::FireGameEvent(IGameEvent* event)
{
    if (!Settings::GrenadeHelper::enabled)
        return;

    if (!engine->IsInGame())
        return;

    if (strcmp(event->GetName(), "game_newmap") != 0)
        return;

    const char* mapname = event->GetString("mapname");

    //load info for new map
}