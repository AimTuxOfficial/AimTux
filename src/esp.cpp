#include <math.h>
#include "esp.h"
#include "settings.h"
#include "skins.h"

bool Settings::ESP::enabled	= true;
ImColor Settings::ESP::ally_color = ImColor(0, 50, 200, 255);
ImColor Settings::ESP::enemy_color = ImColor(200, 0, 50, 255);
ImColor Settings::ESP::enemy_visible_color = ImColor(200, 200, 50, 255);
ImColor Settings::ESP::bones_color = ImColor(255, 255, 255, 255);
ImColor Settings::ESP::bomb_color = ImColor(200, 0, 50, 255);
bool Settings::ESP::Glow::enabled = false;
bool Settings::ESP::friendly = true;
ImColor Settings::ESP::Glow::ally_color = ImColor(0, 50, 200, 0);
ImColor Settings::ESP::Glow::enemy_color = ImColor(200, 0, 50, 0);
ImColor Settings::ESP::Glow::enemy_visible_color = ImColor(200, 200, 50, 0);
ImColor Settings::ESP::Glow::weapon_color = ImColor(200, 0, 50, 200);
ImColor Settings::ESP::Glow::grenade_color = ImColor(200, 0, 50, 200);
ImColor Settings::ESP::Glow::defuser_color = ImColor(100, 100, 200, 200);
bool Settings::ESP::visibility_check = false;
bool Settings::ESP::show_scope_border = true;
bool Settings::ESP::Walls::enabled = false;
int Settings::ESP::Walls::type = FLAT_2D;
bool Settings::ESP::HealthBar::enabled = false;
bool Settings::ESP::Info::showName = true;
bool Settings::ESP::Info::showHealth = false;
bool Settings::ESP::Info::showWeapon = false;
bool Settings::ESP::Info::colorCode = false;
ImColor Settings::ESP::Info::ally_color = ImColor(0, 50, 200, 255);
ImColor Settings::ESP::Info::enemy_color = ImColor(200, 0, 50, 255);
ImColor Settings::ESP::Info::enemy_visible_color = ImColor(200, 200, 50, 255);
bool Settings::ESP::Bones::enabled = false;
bool Settings::ESP::Bomb::enabled = true;
bool Settings::ESP::Weapons::enabled = false;
bool Settings::ESP::Tracer::enabled = false;
bool Settings::ESP::FOVCrosshair::enabled = false;
int Settings::ESP::Tracer::type = BOTTOM;
ImColor Settings::ESP::FOVCrosshair::color = ImColor(180, 50, 50, 255);

bool WorldToScreen(const Vector &vOrigin, Vector &vScreen)
{
	return debugOverlay->ScreenPosition(vOrigin, vScreen);
}

Vector2D WorldToScreen(const Vector &vOrigin)
{
	Vector vec;
	debugOverlay->ScreenPosition(vOrigin, vec);
	return LOC(vec.x, vec.y);
}

//credits to Casual_Hacker from UC for this method (I modified it a lil bit)
float GetArmourHealth(float flDamage, int ArmorValue)
{
	float flCurDamage = flDamage;

	if (flCurDamage == 0.0f || ArmorValue == 0)
		return flCurDamage;

	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	float flNew = flCurDamage * flArmorRatio;
	float flArmor = (flCurDamage - flNew) * flArmorBonus;

	if (flArmor > ArmorValue)
	{
		flArmor = ArmorValue * (1.0f / flArmorBonus);
		flNew = flCurDamage - flArmor;
	}

	return flNew;
}

void DrawESPBox(Vector vecOrigin, Vector vecViewOffset, Color color, int width, int additionalHeight)
{
	//SIDES
	Vector2D a = WorldToScreen(vecOrigin + Vector(width, width, additionalHeight));
	Vector2D b = WorldToScreen(vecViewOffset + Vector(width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(-width, width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(-width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(-width, -width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(-width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(width, -width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);

	// TOP
	a = WorldToScreen(vecViewOffset + Vector(width, width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecViewOffset + Vector(width, width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(-width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecViewOffset + Vector(-width, -width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(-width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecViewOffset + Vector(width, -width, additionalHeight));
	b = WorldToScreen(vecViewOffset + Vector(-width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);

	// BOTTOM
	a = WorldToScreen(vecOrigin + Vector(width, width, additionalHeight));
	b = WorldToScreen(vecOrigin + Vector(width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(width, width, additionalHeight));
	b = WorldToScreen(vecOrigin + Vector(-width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(-width, -width, additionalHeight));
	b = WorldToScreen(vecOrigin + Vector(-width, width, additionalHeight));
	Draw::DrawLine(a, b, color);

	a = WorldToScreen(vecOrigin + Vector(width, -width, additionalHeight));
	b = WorldToScreen(vecOrigin + Vector(-width, -width, additionalHeight));
	Draw::DrawLine(a, b, color);
}

void ESP::DrawBones(C_BaseEntity* entity)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(entity->GetModel());
	if (!pStudioModel)
		return;

	static matrix3x4_t pBoneToWorldOut[128];
	if (entity->SetupBones(pBoneToWorldOut, 128, 256, 0))
	{
		for (int i = 0; i < pStudioModel->numbones; i++)
		{
			mstudiobone_t* pBone = pStudioModel->pBone(i);
			if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
				continue;

			Vector vBonePos1;
			if (WorldToScreen(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
				continue;

			Vector vBonePos2;
			if (WorldToScreen(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
				continue;

			Draw::DrawLine(LOC(vBonePos1.x, vBonePos1.y), LOC(vBonePos2.x, vBonePos2.y), Color().FromImColor(Settings::ESP::bones_color));
		}
	}
}

void ESP::DrawTracer(C_BaseEntity* entity)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	int playerTeam = localplayer->GetTeam();
	int entityTeam = entity->GetTeam();
	Color color = Color().FromImColor(playerTeam == entityTeam ? Settings::ESP::ally_color : Settings::ESP::enemy_color);

	int width;
	int height;
	engine->GetScreenSize(width, height);

	Vector2D tracerLocation;

	switch (Settings::ESP::Tracer::type)
	{
		case BOTTOM:
			tracerLocation = LOC(width / 2, height);
			break;
		case CURSOR:
			tracerLocation = LOC(width / 2, height / 2);
			break;
	}

	Vector s_vecEntity_s;
	if (!WorldToScreen(entity->GetVecOrigin(), s_vecEntity_s) && localplayer->GetHealth() > 0)
		Draw::DrawLine(tracerLocation, LOC(s_vecEntity_s.x, s_vecEntity_s.y), color);
}

void ESP::DrawPlayerBox(C_BaseEntity* entity)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	int playerTeam = localplayer->GetTeam();
	int entityTeam = entity->GetTeam();
	bool isVisible = Entity::IsVisible(entity, BONE_HEAD);

	Color color;

	if (playerTeam != entityTeam)
		color = Color().FromImColor(isVisible ? Settings::ESP::enemy_visible_color : Settings::ESP::enemy_color);
	else
		color = Color().FromImColor(Settings::ESP::ally_color);

	if (Settings::ESP::Walls::type == FLAT_2D)
	{
		Vector max = entity->GetCollideable()->OBBMaxs();

		Vector pos, pos3D;
		Vector top, top3D;

		pos3D = entity->GetVecOrigin();
		top3D = pos3D + Vector(0, 0, max.z);

		if (WorldToScreen(pos3D, pos) || WorldToScreen(top3D, top))
			return;

		float height = (pos.y - top.y);
		float width = height / 4.f;

		Draw::DrawOutlinedBox(top.x, top.y, width, height, color);
	}
	else if (Settings::ESP::Walls::type == BOX_3D)
	{
		int width = 14;
		int additionalHeight = 6;

		Vector vecOrigin = entity->GetVecOrigin();

		Vector vecHeadBone = entity->GetBonePosition(Bone::BONE_HEAD);
		Vector vecViewOffset = Vector(vecOrigin.x, vecOrigin.y, vecHeadBone.z);

		Vector s_veclocalplayer_s;
		if (!WorldToScreen(vecOrigin, s_veclocalplayer_s))
			DrawESPBox(vecOrigin, vecViewOffset, color, width, additionalHeight);
	}
}

Color GetHealthColor(int hp)
{
	float hpHue = hp * 1.2f / 360.0f;
	Color color = Color().FromHSB(hpHue, 1.0f, 1.0f);
	color.b = 48; // Just for looks
	return color;
}

void ESP::DrawPlayerHealthBar(C_BaseEntity* entity)
{
	int yOffset = 2;
	int frameWidth = 1;
	int minH = 4;
	int maxH = 8;
	Color outline = Color(8, 8, 8, 92);

	int hp = entity->GetHealth();
	Color color = GetHealthColor(hp);

	Vector max = entity->GetCollideable()->OBBMaxs();

	Vector pos, pos3D;
	Vector top, top3D;

	pos3D = entity->GetVecOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (WorldToScreen(pos3D, pos) || WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);
	float width = height / 4.0f;

	int leftSide = (int)(top.x - width);
	int rightSideFull = (int)(top.x + width);
	int rightSide = (int)(leftSide + width * 2.0f * hp / 100.0f);

	// Always show at least 1 pixel
	if (rightSide - leftSide < 1)
		rightSide += 1;

	int barHeight = (int)(height / 32);

	if (barHeight < minH)
		barHeight = minH;
	if (barHeight > maxH)
		barHeight = maxH;

	Vector2D left = Vector2D(leftSide, pos.y + yOffset);
	Vector2D right = Vector2D(rightSide, pos.y + yOffset + barHeight);

	Vector2D frameLeft = Vector2D(left.x - frameWidth, left.y - frameWidth);
	Vector2D frameRight = Vector2D(rightSideFull + frameWidth, right.y + frameWidth);

	Draw::DrawRect(left, right, color);
	Draw::DrawRect(frameLeft, frameRight, outline);
}

void ESP::DrawPlayerInfo(C_BaseEntity* entity, int entityIndex)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(entity->GetActiveWeapon());
	if (!active_weapon)
		return;

	bool isVisible = Entity::IsVisible(entity, BONE_HEAD);
	Color color = Color(255, 255, 255, 255);

	if (Settings::ESP::Info::colorCode)
	{
		if (localplayer->GetTeam() != entity->GetTeam())
			color = Color().FromImColor(isVisible ? Settings::ESP::Info::enemy_visible_color : Settings::ESP::Info::enemy_color);
		else
			color = Color().FromImColor(Settings::ESP::Info::ally_color);
	}

	IEngineClient::player_info_t entityInformation;
	engine->GetPlayerInfo(entityIndex, &entityInformation);

	std::string modelName = std::string(Util::GetValueByKey(guns, *active_weapon->GetItemDefinitionIndex()));
	if (modelName == "")
	{
		modelName = std::string(active_weapon->GetClientClass()->m_pNetworkName);
		if (strstr(modelName.c_str(), "Weapon"))
			modelName = modelName.substr(7, modelName.length() - 7);
		else
			modelName = modelName.substr(1, modelName.length() - 1);
	}

	pstring topText;
	pstring bottomText;

	if (Settings::ESP::Info::showName)
		topText << entityInformation.name;

	if (Settings::ESP::Info::showHealth)
		bottomText << entity->GetHealth() << "hp";

	if (Settings::ESP::Info::showWeapon)
		bottomText << (bottomText.length() > 0 ? " | " : "") << modelName;

	Vector2D size_top = Draw::GetTextSize(topText.c_str(), esp_font);
	Vector2D size_bottom = Draw::GetTextSize(bottomText.c_str(), esp_font);

	Vector max = entity->GetCollideable()->OBBMaxs();

	Vector pos, pos3D;
	Vector top, top3D;

	pos3D = entity->GetVecOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (WorldToScreen(pos3D, pos) || WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);

	// So the text doesn't cover up the health bar
	float yOffset = Settings::ESP::HealthBar::enabled ? 6.0f : 0.0f;

	Draw::DrawCenteredString(topText.c_str(), LOC (top.x, top.y - (size_top.y / 2)), color, esp_font);
	Draw::DrawCenteredString(bottomText.c_str(), LOC (top.x, top.y + height + (size_bottom.y / 2) + yOffset), color, esp_font);
}

void ESP::DrawBombBox(C_BasePlantedC4* entity)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	Color color = Color().FromImColor(Settings::ESP::bomb_color);

	int width = 7;
	int additionalHeight = 4;

	float bombTime = entity->GetBombTime() - globalvars->curtime;
	if (bombTime <= 0.0f)
		return;

	Vector vecOrigin = entity->GetVecOrigin();
	Vector vecViewOffset = Vector(vecOrigin.x, vecOrigin.y, vecOrigin.z - 4);

	pstring str = "C4";

	float flDistance = sqrt(localplayer->GetEyePosition().DistToSqr(vecOrigin));

	float a = 450.7f;
	float b = 75.68f;
	float c = 789.2f;
	float d = ((flDistance - b) / c);
	float flDamage = a*exp(-d * d);

	float damage = std::max((int)ceilf(GetArmourHealth(flDamage, localplayer->GetArmor())), 0);

	bool surviveBlast = localplayer->GetHealth() > damage;

	if (surviveBlast && damage == 1.f)
		damage = 0.0f;

	if (bombTime > 0)
	{
		if (localplayer->GetAlive())
			str << " (" << bombTime << ", " << damage << " damage)";
		else
			str << " (" << bombTime << ")";
	}

	Vector s_veclocalplayer_s;
	if (!WorldToScreen(vecOrigin, s_veclocalplayer_s))
	{
		Color colorText = entity->GetBombDefuser() != -1 ? Color(0, 50, 200) : surviveBlast ? Color(0, 255, 0) : Color(255, 0, 0);
		DrawESPBox(vecOrigin, vecViewOffset, color, width, additionalHeight);
		Draw::DrawCenteredString(str.c_str(), LOC(s_veclocalplayer_s.x, s_veclocalplayer_s.y), colorText, esp_font);
	}
}

void ESP::DrawWeaponText(C_BaseEntity* entity, ClientClass* client)
{
	int modelId = *((C_BaseAttributableItem*)entity)->GetItemDefinitionIndex();

	std::string modelName = Util::GetValueByKey(guns, modelId);
	if (modelName == "")
	{
		modelName = std::string(client->m_pNetworkName);
		if (strstr(modelName.c_str(), "Weapon"))
			modelName = modelName.substr(7, modelName.length() - 7);
		else
			modelName = modelName.substr(1, modelName.length() - 1);
	}

	Vector vecOrigin = entity->GetVecOrigin();
	if (vecOrigin == Vector(0, 0, 0))
		return;

	Vector s_veclocalplayer_s;
	if (!WorldToScreen(vecOrigin, s_veclocalplayer_s))
		Draw::DrawCenteredString(modelName.c_str(), LOC(s_veclocalplayer_s.x, s_veclocalplayer_s.y), Color(255, 255, 255, 255), esp_font);
}

void ESP::DrawGlow()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 0; i < glowmanager->m_GlowObjectDefinitions.Count(); i++) {
		GlowObjectDefinition_t& glow_object = glowmanager->m_GlowObjectDefinitions[i];

		if (glow_object.IsUnused() || !glow_object.m_pEntity)
			continue;

		Color color;
		ClientClass* client = glow_object.m_pEntity->GetClientClass();
		bool should_glow = true;

		if (client->m_ClassID == CCSPlayer)
		{
			if (glow_object.m_pEntity == (C_BaseEntity*)localplayer
				|| glow_object.m_pEntity->GetDormant()
				|| !glow_object.m_pEntity->GetAlive())
				continue;

			if (glow_object.m_pEntity->GetTeam() != localplayer->GetTeam())
			{
				if (Entity::IsVisible(glow_object.m_pEntity, BONE_HEAD))
					color = Color().FromImColor(Settings::ESP::Glow::enemy_visible_color);
				else
					color = Color().FromImColor(Settings::ESP::Glow::enemy_color);
			}
			else
			{
				color = Color().FromImColor(Settings::ESP::Glow::ally_color);
			}
		}
		else if (client->m_ClassID != CBaseWeaponWorldModel &&
			(strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == CDEagle || client->m_ClassID == CAK47))
		{
				color = Color().FromImColor(Settings::ESP::Glow::weapon_color);
		}
		else if (client->m_ClassID == CBaseCSGrenadeProjectile || client->m_ClassID == CDecoyProjectile ||
				client->m_ClassID == CMolotovProjectile || client->m_ClassID == CSmokeGrenadeProjectile)
		{
			color = Color().FromImColor(Settings::ESP::Glow::grenade_color);
		}
		else if (client->m_ClassID == CBaseAnimating)
		{
			color = Color().FromImColor(Settings::ESP::Glow::defuser_color);

			if (localplayer->HasDefuser() || localplayer->GetTeam() == TEAM_TERRORIST)
				should_glow = false;
		}

		should_glow = should_glow && color.a > 0;

		glow_object.m_flGlowColor[0] = color.r / 255.0f;
		glow_object.m_flGlowColor[1] = color.g / 255.0f;
		glow_object.m_flGlowColor[2] = color.b / 255.0f;
		glow_object.m_flGlowAlpha = should_glow ? color.a / 255.0f : 255.0f;
		glow_object.m_flBloomAmount = 1.0f;
		glow_object.m_bRenderWhenOccluded = should_glow;
		glow_object.m_bRenderWhenUnoccluded = false;
	}
}

bool ESP::PrePaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
#ifdef EXPERIMENTAL_SETTINGS
	if (strcmp("HudZoom", panel->GetName(vgui_panel)) == 0)
		return Settings::ESP::show_scope_border;
#endif

	return true;
}

void ESP::DrawFOVCrosshair()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer->GetAlive())
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	float radAimbotFov = Settings::Aimbot::AutoAim::fov * M_PI / 180;
	float radViewFov = RenderView::currentFOV * M_PI / 180;

	float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * width;

	Draw::DrawCircle(LOC(width / 2, height / 2), 20, circleRadius, Color().FromImColor(Settings::ESP::FOVCrosshair::color));
}

void ESP::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::ESP::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 1; i < entitylist->GetHighestEntityIndex(); ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		ClientClass* client = entity->GetClientClass();
		if (client->m_ClassID == CCSPlayer)
		{
			if (entity == (C_BaseEntity*)localplayer
				|| entity->GetDormant()
				|| !entity->GetAlive())
				continue;

			if (Settings::ESP::visibility_check && !Entity::IsVisible(entity, BONE_HEAD))
				continue;

			if (!Settings::ESP::friendly && localplayer->GetTeam() == entity->GetTeam())
				continue;

			if (!localplayer->GetAlive() && entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget()) == entity)
				continue;

			if (Settings::ESP::Bones::enabled)
				ESP::DrawBones(entity);

			if (Settings::ESP::Walls::enabled)
				ESP::DrawPlayerBox(entity);

			if (Settings::ESP::HealthBar::enabled)
				ESP::DrawPlayerHealthBar(entity);

			if (Settings::ESP::Tracer::enabled)
				ESP::DrawTracer(entity);

			if (Settings::ESP::Info::showName || Settings::ESP::Info::showHealth || Settings::ESP::Info::showWeapon)
				ESP::DrawPlayerInfo(entity, i);
		}
		else if (client->m_ClassID == CPlantedC4)
		{
			C_BasePlantedC4* bomb = (C_BasePlantedC4*) entitylist->GetClientEntity(i);

			if (Settings::ESP::Bomb::enabled && bomb->IsBombTicking() && !bomb->IsBombDefused())
				ESP::DrawBombBox(bomb);
		}
		else if (client->m_ClassID != CBaseWeaponWorldModel &&
				(strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == CDEagle || client->m_ClassID == CAK47))
		{
			if (Settings::ESP::Weapons::enabled)
				ESP::DrawWeaponText(entity, client);
		}
	}

	if (Settings::ESP::FOVCrosshair::enabled)
		ESP::DrawFOVCrosshair();
}

void ESP::BeginFrame(float frameTime)
{
	if (!engine->IsInGame())
		return;

	if (Settings::ESP::Glow::enabled)
		ESP::DrawGlow();
}