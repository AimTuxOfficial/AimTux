#include "grenadehelper.h"

#include "../Utils/xorstring.h"
#include "../Utils/draw.h"
#include "../Utils/math.h"
#include "../config.h"
#include "../fonts.h"
#include "../settings.h"
#include "../interfaces.h"

#include "skinchanger.h" //GetLocalClient
#include "../Hooks/hooks.h"

#include <sstream>

bool shotLastTick = false;

GrenadeType GetGrenadeType(C_BaseCombatWeapon* wpn)
{
	switch (*wpn->GetItemDefinitionIndex())
	{
		case ItemDefinitionIndex::WEAPON_HEGRENADE:
			return GrenadeType::HEGRENADE;
		case ItemDefinitionIndex::WEAPON_SMOKEGRENADE:
			return GrenadeType::SMOKE;
		case ItemDefinitionIndex::WEAPON_FLASHBANG:
		case ItemDefinitionIndex::WEAPON_DECOY:
			return GrenadeType::FLASH;
		case ItemDefinitionIndex::WEAPON_MOLOTOV:
		case ItemDefinitionIndex::WEAPON_INCGRENADE:
			return GrenadeType::MOLOTOV;
		default:
			return (GrenadeType)-1;
	}
}

static ImColor GetColor(GrenadeType type)
{
	switch (type)
	{
		case GrenadeType::HEGRENADE:
			return Settings::GrenadeHelper::infoHE.Color();
		case GrenadeType::SMOKE:
			return Settings::GrenadeHelper::infoSmoke.Color();
		case GrenadeType::FLASH:
			return Settings::GrenadeHelper::infoFlash.Color();
		case GrenadeType::MOLOTOV:
			return Settings::GrenadeHelper::infoMolotov.Color();
		default:
			return ImColor(255, 255, 255);
	}
}
static void DrawGrenadeInfo(GrenadeInfo* info)
{
	Vector pos2d;
	if( debugOverlay->ScreenPosition( Vector(info->pos.x, info->pos.y, info->pos.z), pos2d ) )
		return;

	float radius = 20;
	Draw::AddCircle( pos2d.x, pos2d.y, radius, GetColor(info->gType), 15 );
	Draw::AddText( pos2d.x + radius, pos2d.y, info->name.c_str(), GetColor(info->gType) );
}
static void DrawAimHelp(GrenadeInfo* info)
{
	Vector infoVec;
	Math::AngleVectors(info->angle, infoVec);
	infoVec *= 150 / infoVec.Length();
	infoVec += info->pos;

	Vector posVec;
	if( debugOverlay->ScreenPosition( infoVec, posVec ) )
		return;

	// Draw Point to Throw to
	Draw::AddCircleFilled(posVec.x, posVec.y, 5, Settings::GrenadeHelper::aimDot.Color(), 20 );

	// Draw Help line
	Draw::AddLine(Paint::engineWidth / 2, Paint::engineHeight / 2, posVec.x, posVec.y, Settings::GrenadeHelper::aimLine.Color());
}
static void AimAssist(CUserCmd* cmd)
{
	if (!Settings::GrenadeHelper::aimAssist || !engine->IsInGame() || !Settings::GrenadeHelper::enabled)
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer || !localPlayer->GetAlive())
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());

	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	bool shootThisTick = cmd->buttons & IN_ATTACK;
	if (!shootThisTick && !shotLastTick)
		return;

	if (Settings::GrenadeHelper::grenadeInfos.empty())
		return;
	//for storing the best result
	GrenadeInfo* grenadeInfo = nullptr;
	float distOnScreen;//Viewangle difference
	float dist;//3D distance

	for (auto act = Settings::GrenadeHelper::grenadeInfos.begin(); act != Settings::GrenadeHelper::grenadeInfos.end(); act++)
	{
		if (Settings::GrenadeHelper::onlyMatchingInfos && GetGrenadeType(activeWeapon) != act->gType)
			continue;

		float dist3D = localPlayer->GetEyePosition().DistTo(act->pos);
		if (dist3D > Settings::GrenadeHelper::aimDistance)
			continue;

		float actDistOnScreen = Math::GetFov(act->angle, *localPlayer->GetVAngles());

		if ((grenadeInfo &&  distOnScreen < actDistOnScreen) || actDistOnScreen > Settings::GrenadeHelper::aimFov)
			continue;

		grenadeInfo = act.base();
		distOnScreen = actDistOnScreen;
		dist = dist3D;
	}
	if (!grenadeInfo)
		return;

	if (!shootThisTick && shotLastTick && dist < 5)
	{
		//throw the grenade
		if (grenadeInfo->tType == ThrowType::JUMP)
			cmd->buttons |= IN_JUMP;
		if (grenadeInfo->tType == ThrowType::WALK)
			cmd->buttons |= IN_WALK;
		engine->SetViewAngles(grenadeInfo->angle);
	}
	else
	{
		if (dist > 0.5f)
		{
			//Move towards the aimpos
			QAngle movement = Math::CalcAngle(localPlayer->GetEyePosition(), grenadeInfo->pos);
			if (cmd->forwardmove < dist) cmd->forwardmove = dist * 2;
			cmd->sidemove = 0;
			cmd->buttons |= IN_WALK;
			Math::CorrectMovement(movement, cmd, cmd->forwardmove, cmd->sidemove);
		}
		if (cmd->viewangles !=  grenadeInfo->angle)
		{
			//Aim towards the aimspot
			float maxStep = Settings::GrenadeHelper::aimStep;
			QAngle old = cmd->viewangles;
			float diffX = std::max(-maxStep, std::min(grenadeInfo->angle.x - old.x, maxStep));
			float p = Math::GetFov(old + QAngle(diffX, 0.1, 0), grenadeInfo->angle);
			float q = Math::GetFov(old + QAngle(diffX, -0.1, 0), grenadeInfo->angle);
			float diffY = p < q ? std::min(p, maxStep): -std::min(q, maxStep);
			cmd->viewangles += QAngle(diffX, diffY, 0);
			Math::ClampAngles(cmd->viewangles);
			engine->SetViewAngles(cmd->viewangles);
			Math::CorrectMovement(old, cmd, cmd->forwardmove, cmd->sidemove);
		}
	}
}
static void CheckForUpdate()
{
	if (!engine->IsInGame())
		return;

	std::string levelName = std::string(GetLocalClient(-1)->m_szLevelNameShort);
	unsigned long p = levelName.find_last_of("/");
	if (p != std::string::npos)
		levelName.erase(0, p + 1);

	if (!Settings::GrenadeHelper::actMapName.compare(levelName))
		return;

	Settings::GrenadeHelper::actMapName = levelName;
	std::ostringstream path;
	path << GetGhConfigDirectory()<< levelName << XORSTR("/config.json");

	if (DoesFileExist(path.str().c_str()))
		Settings::LoadGrenadeInfo(path.str());
	else
		Settings::GrenadeHelper::grenadeInfos = {};
}






void GrenadeHelper::CreateMove(CUserCmd* cmd)
{
	CheckForUpdate();
	AimAssist(cmd);
	shotLastTick = cmd->buttons & IN_ATTACK;
}
void GrenadeHelper::Paint()
{
	if (!Settings::ESP::enabled || !engine->IsInGame() || !Settings::GrenadeHelper::enabled)
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	if (Settings::GrenadeHelper::grenadeInfos.empty())
		return;

	for (auto grenadeInfo = Settings::GrenadeHelper::grenadeInfos.begin(); grenadeInfo != Settings::GrenadeHelper::grenadeInfos.end(); grenadeInfo++)
	{
		if (Settings::GrenadeHelper::onlyMatchingInfos && GetGrenadeType(activeWeapon) != grenadeInfo->gType)
			continue;

		float dist = grenadeInfo->pos.DistTo(localPlayer->GetEyePosition());
		if (dist > 1000)
			continue;

		DrawGrenadeInfo(grenadeInfo.base());

		if (dist < Settings::GrenadeHelper::aimDistance)
			DrawAimHelp(grenadeInfo.base());
	}
}
