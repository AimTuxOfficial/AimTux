//
// Created by orinion on 08.02.17.
//

#include "grenadehelper.h"

using namespace GrenadeHelper;

bool Settings::GrenadeHelper::enabled = true;
std::vector<GrenadeInfo> /**Settings::GrenadeHelper::**/grenadeInfos = { GrenadeInfo(GrenadeType::SMOKE, Vector(1149.4f,-1183.97f,-141.51f),QAngle(-42.f,-165.f,0.f),ThrowType::NORMAL),
                                                                                  GrenadeInfo(GrenadeType::FLASH, Vector(803,-1418,-44.91f),QAngle(-30.49f,-178.85f,0.f),ThrowType::NORMAL)};
void GrenadeHelper::DrawGrenadeInfo(GrenadeInfo* info)
{
    Vector pos2d;
    if (debugOverlay->ScreenPosition(Vector(info->pos.x,info->pos.y,info->pos.z), pos2d))
        return;
    Draw::Circle(Vector2D(pos2d.x,pos2d.y),15,20,Color(255,10,10));
}

void GrenadeHelper::DrawAimHelp(GrenadeInfo* info)
{
    Vector infoVec;
    Math::AngleVectors(info->angle, infoVec);
    infoVec *= 150/infoVec.Length();
    Vector aim = info->pos + infoVec;
    Vector posVec;
    if (debugOverlay->ScreenPosition(aim, posVec))
        return;
    Vector2D pos2d(posVec.x,posVec.y);
    Draw::FilledCircle(pos2d,20,5,Color(10,10,255));//Draw Point to Throw to

    int w,h;
    engine->GetScreenSize(w,h);
    Draw::Line(Vector2D(w/2,h/2),pos2d,Color(255,255,255));//Draw Help line
}

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

    //draw the info
    for(auto grenadeInfo = grenadeInfos.begin(); grenadeInfo != grenadeInfos.end(); grenadeInfo++)
    {
        float dist = grenadeInfo->pos.DistTo(localplayer->GetVecOrigin());
        if(dist > 10000)
            continue;
        DrawGrenadeInfo(grenadeInfo.base());

        if(dist < 75)//TODO change dist
        {
            DrawAimHelp(grenadeInfo.base());
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

    //  const char* mapname = event->GetString("mapname");

    //load info for new map
}