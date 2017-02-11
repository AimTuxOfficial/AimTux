#include "grenadehelper.h"

bool shotLastTick = false;
pstring actMapName = pstring();
bool Settings::GrenadeHelper::enabled = true;
bool Settings::GrenadeHelper::onlyMatchingInfos = true;
bool Settings::GrenadeHelper::aimAssist = false;

ImColor Settings::GrenadeHelper::aimLine = ImColor(200, 200, 200, 255);
ImColor Settings::GrenadeHelper::aimDot = ImColor(10, 10, 200, 255);
ImColor Settings::GrenadeHelper::infoHE = ImColor(30, 100, 30, 255);
ImColor Settings::GrenadeHelper::infoMolotov = ImColor(100, 20, 20, 255);
ImColor Settings::GrenadeHelper::infoSmoke = ImColor(30, 30, 30, 255);
ImColor Settings::GrenadeHelper::infoFlash = ImColor(255, 255, 0, 255);

std::vector<GrenadeInfo> Settings::GrenadeHelper::grenadeInfos = {
		GrenadeInfo(GrenadeType::SMOKE, Vector(1149.4f, -1183.97f, -141.51f), QAngle(-42.f, -165.f, 0.f), ThrowType::NORMAL, pstring("Smoke A Stairs")),
		GrenadeInfo(GrenadeType::FLASH, Vector(803, -1418, -44.91f), QAngle(-30.49f, -178.85f, 0.f), ThrowType::NORMAL, pstring("Popflash A"))
};

bool GrenadeHelper::matches(C_BaseCombatWeapon* wpn, GrenadeType type)
{
	switch (type)
	{
		case GrenadeType::HEGRENADE:
			return strcmp(wpn->GetCSWpnData()->szClassName, "weapon_hegrenade") == 0;
		case GrenadeType::SMOKE:
			return strcmp(wpn->GetCSWpnData()->szClassName, "weapon_smokegrenade") == 0;
		case GrenadeType::FLASH:
			return strcmp(wpn->GetCSWpnData()->szClassName, "weapon_flashbang") == 0;
		case GrenadeType::MOLOTOV:
			return strcmp(wpn->GetCSWpnData()->szClassName, "weapon_molotov") == 0
				   || strcmp(wpn->GetCSWpnData()->szClassName, "weapon_incgrenade") == 0;
		default:
			return false;
	}
}

ImColor GrenadeHelper::getColor(GrenadeType type)
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
		default:
			return ImColor(255, 255, 255);
	}
}

void GrenadeHelper::DrawGrenadeInfo(GrenadeInfo* info)
{
	Vector pos2d;
	if (debugOverlay->ScreenPosition(Vector(info->pos.x, info->pos.y, info->pos.z), pos2d))
		return;

	Color clr = Color::FromImColor(getColor(info->gType));
	float radius = 20;
	Draw::Circle(Vector2D(pos2d.x, pos2d.y), 15, radius, clr);
	Draw::Text(pos2d.x + radius, pos2d.y, info->name.c_str(), esp_font, clr);
}

void GrenadeHelper::DrawAimHelp(GrenadeInfo* info)
{
	Vector infoVec;
	Math::AngleVectors(info->angle, infoVec);
	infoVec *= 150 / infoVec.Length();
	Vector aim = info->pos + infoVec;

	Vector posVec;
	if (debugOverlay->ScreenPosition(aim, posVec))
		return;

	int w, h;
	engine->GetScreenSize(w, h);

	Vector2D pos2d(posVec.x, posVec.y);

	// Draw Point to Throw to
	Draw::FilledCircle(pos2d, 20, 5, Color::FromImColor(Settings::GrenadeHelper::aimDot));

	// Draw Help line
	Draw::Line(Vector2D(w / 2, h / 2), pos2d, Color::FromImColor(Settings::GrenadeHelper::aimLine));
}

void GrenadeHelper::Paint()
{
	if (!Settings::ESP::enabled || !Settings::GrenadeHelper::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	for (auto grenadeInfo = Settings::GrenadeHelper::grenadeInfos.begin(); grenadeInfo != Settings::GrenadeHelper::grenadeInfos.end(); grenadeInfo++)
	{
		if (Settings::GrenadeHelper::onlyMatchingInfos && !matches(activeWeapon,grenadeInfo->gType))
			continue;

		float dist = grenadeInfo->pos.DistTo(localPlayer->GetVecOrigin());
		if (dist > 10000)
			continue;

		GrenadeHelper::DrawGrenadeInfo(grenadeInfo.base());

		if (dist < 75)
			GrenadeHelper::DrawAimHelp(grenadeInfo.base());
	}
}

void GrenadeHelper::AimAssist(CUserCmd* cmd)
{
	if (!Settings::GrenadeHelper::aimAssist || !engine->IsInGame())
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());

	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	// If he is shooting, he will not throw the Grenade
	bool shootThisTick = cmd->buttons & IN_ATTACK;
	if (!shootThisTick && !shotLastTick)
		return;

	for (auto grenadeInfo = Settings::GrenadeHelper::grenadeInfos.begin(); grenadeInfo != Settings::GrenadeHelper::grenadeInfos.end(); grenadeInfo++)
	{
		if (Settings::GrenadeHelper::onlyMatchingInfos && !matches(activeWeapon,grenadeInfo->gType))
			continue;

		float dist = Math::GetDistance(localPlayer->GetEyePosition(), grenadeInfo->pos);
		if (dist > 75.f)
			continue;

		if (dist > 3.f)
		{
			QAngle n = Math::CalcAngle(localPlayer->GetEyePosition(),grenadeInfo->pos);
			n.x = cmd->viewangles.x;
			cmd->viewangles = n;
			cmd->forwardmove = dist;
			// Todo make it not change the viewangles. Pretty Ghetto atm
		}
		else if (!shootThisTick && shotLastTick)
		{
			engine->SetViewAngles(grenadeInfo->angle);
			// cmd->viewangles = grenadeInfo->angle;
			// TODO Not working ;( maybe safe the value and Do it later or dont do it silent.
		}
		break;
	}
}

void GrenadeHelper::CheckForUpdate()
{
	if (!engine->IsInGame())
		return;
	if (!actMapName.compare(GetLocalClient(-1)->m_szLevelNameShort))
		return;
	actMapName = pstring(GetLocalClient(-1)->m_szLevelNameShort);
	cvar->ConsoleDPrintf(actMapName.c_str());
	//Update
	std::vector<Config> gconfigs = GetConfigs(GetGhConfigDirectory().c_str());
	for (auto config = gconfigs.begin(); config != gconfigs.end(); config++)
	{
		if (config->name.compare(actMapName))
			continue;
		//Settings::LoadGrenadeInfo(config->path);
		return;
	}
	Settings::GrenadeHelper::grenadeInfos = {};
	cvar->ConsoleDPrintf("No Smokes for this map found.\n");
}

void GrenadeHelper::CreateMove(CUserCmd* cmd)
{
	GrenadeHelper::CheckForUpdate();
	GrenadeHelper::AimAssist(cmd);
	shotLastTick = cmd->buttons & IN_ATTACK;
}