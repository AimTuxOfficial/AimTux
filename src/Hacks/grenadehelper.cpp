//
// Created by orinion on 08.02.17.
//

#include "grenadehelper.h"

using namespace GrenadeHelper;
bool shotLastTick = false;
bool Settings::GrenadeHelper::enabled = true;
bool Settings::GrenadeHelper::onlyMatchingInfos = true;
bool Settings::GrenadeHelper::aimAssist = false;

ImColor Settings::GrenadeHelper::aimLine = ImColor(200,200,200,255);
ImColor Settings::GrenadeHelper::aimDot = ImColor(10,10,200,255);
ImColor Settings::GrenadeHelper::infoHE = ImColor(30,100,30,255);
ImColor Settings::GrenadeHelper::infoMolotov = ImColor(100,20,20,255);
ImColor Settings::GrenadeHelper::infoSmoke = ImColor(30,30,30,255);
ImColor Settings::GrenadeHelper::infoFlash = ImColor(255,255,0,255);


std::vector<GrenadeInfo> /**Settings::GrenadeHelper::**/grenadeInfos = { GrenadeInfo(GrenadeType::SMOKE, Vector(1149.4f,-1183.97f,-141.51f),QAngle(-42.f,-165.f,0.f),ThrowType::NORMAL),
																				  GrenadeInfo(GrenadeType::FLASH, Vector(803,-1418,-44.91f),QAngle(-30.49f,-178.85f,0.f),ThrowType::NORMAL)};
bool GrenadeHelper::matches(C_BaseCombatWeapon* wpn, GrenadeType type)
{

	switch (type)
	{
		case GrenadeType::HEGRENADE:
			return strcmp(wpn->GetCSWpnData()->szClassName,"weapon_hegrenade")==0;
		case GrenadeType::SMOKE:
			return strcmp(wpn->GetCSWpnData()->szClassName,"weapon_smokegrenade")==0;
		case GrenadeType::FLASH:
			return strcmp(wpn->GetCSWpnData()->szClassName,"weapon_flashbang")==0;
		case GrenadeType::MOLOTOV:
			return strcmp(wpn->GetCSWpnData()->szClassName,"weapon_molotov")==0
					|| strcmp(wpn->GetCSWpnData()->szClassName,"weapon_incgrenade")==0;
		default:
			return false;
	}
}

ImColor getColor(GrenadeType type)
{
	switch (type)
	{
		case GrenadeType::HEGRENADE:
			return Settings::GrenadeHelper::infoHE;
		case GrenadeType::SMOKE:
			return Settings::GrenadeHelper::infoSmoke;
		case GrenadeType::FLASH:
			return Settings::GrenadeHelper::infoFlash;
		case GrenadeType::MOLOTOV:
			return Settings::GrenadeHelper::infoMolotov;

	}
}

void GrenadeHelper::DrawGrenadeInfo(GrenadeInfo* info)
{
	Vector pos2d;
	if (debugOverlay->ScreenPosition(Vector(info->pos.x,info->pos.y,info->pos.z), pos2d))
		return;
	Draw::Circle(Vector2D(pos2d.x,pos2d.y),15,20,Color::FromImColor(getColor(info->gType)));
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
	Draw::FilledCircle(pos2d,20,5,Color::FromImColor(Settings::GrenadeHelper::aimDot));//Draw Point to Throw to

	int w,h;
	engine->GetScreenSize(w,h);
	Draw::Line(Vector2D(w/2,h/2),pos2d,Color::FromImColor(Settings::GrenadeHelper::aimLine));//Draw Help line
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
		if(Settings::GrenadeHelper::onlyMatchingInfos && !matches(activeWeapon,grenadeInfo->gType))
			continue;

		float dist = grenadeInfo->pos.DistTo(localplayer->GetVecOrigin());
		if(dist > 10000)
			continue;
		DrawGrenadeInfo(grenadeInfo.base());

		if(dist < 75)
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

void GrenadeHelper::AimAssist(CUserCmd* cmd)
{
	if (!Settings::GrenadeHelper::aimAssist || !engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());

	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	bool shootThisTick = cmd->buttons & IN_ATTACK;//If he is shooting, he will not throw the Grenade
	if(!shootThisTick && !shotLastTick)
		return;

	for(auto grenadeInfo = grenadeInfos.begin(); grenadeInfo != grenadeInfos.end(); grenadeInfo++)
	{
		if(onlyMatchingInfos && !matches(activeWeapon,grenadeInfo->gType))
			continue;
		float dist = Math::GetDistance(localplayer->GetEyePosition(), grenadeInfo->pos);
		if(dist > 75.f)
			continue;

		if(dist> 3.f)
		{
			QAngle n = Math::CalcAngle(localplayer->GetEyePosition(),grenadeInfo->pos);
			n.x = cmd->viewangles.x;
			cmd->viewangles = n;
			cmd->forwardmove = dist;
			//Todo make it not change the viewangles. Pretty Ghetto atm
		}
		else
		{
			if(!shootThisTick && shotLastTick)
			{
				engine->SetViewAngles(grenadeInfo->angle);
				//cmd->viewangles = grenadeInfo->angle;
				//TODO Not working ;( maybe safe the value and Do it later or dont do it silent.
			}
		}
		break;
	}
}

void GrenadeHelper::CreateMove(CUserCmd* cmd)
{
	AimAssist(cmd);
	shotLastTick = cmd->buttons & IN_ATTACK;
}