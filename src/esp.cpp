#include "esp.h"
#include "settings.h"

bool Settings::ESP::enabled	= true;
Color Settings::ESP::ally_color = Color(0, 50, 200);
Color Settings::ESP::enemy_color = Color(200, 0, 50);
Color Settings::ESP::enemy_visible_color = Color(200, 200, 50);
Color Settings::ESP::bones_color = Color(255, 255, 255);
Color Settings::ESP::bomb_color = Color(200, 0, 50);
bool Settings::ESP::Glow::enabled = false;
bool Settings::ESP::friendly = true;
Color Settings::ESP::Glow::ally_color = Color(0, 50, 200, 0);
Color Settings::ESP::Glow::enemy_color = Color(200, 0, 50, 0);
Color Settings::ESP::Glow::enemy_visible_color = Color(200, 200, 50, 0);
Color Settings::ESP::Glow::weapon_color = Color(200, 0, 50, 200);
bool Settings::ESP::visibility_check = false;
bool Settings::ESP::Walls::enabled = false;
WallBoxType Settings::ESP::Walls::type = FLAT_2D;
bool Settings::ESP::Info::showName = true;
bool Settings::ESP::Info::showHealth = false;
bool Settings::ESP::Info::showWeapon = false;
bool Settings::ESP::Info::colorCode = false;
Color Settings::ESP::Info::ally_color = Color(0, 50, 200);
Color Settings::ESP::Info::enemy_color = Color(200, 0, 50);
Color Settings::ESP::Info::enemy_visible_color = Color(200, 200, 50);
bool Settings::ESP::Bones::enabled = false;
bool Settings::ESP::Bomb::enabled = true;
bool Settings::ESP::Weapons::enabled = false;
bool Settings::ESP::Tracer::enabled = false;
bool Settings::ESP::FOVCrosshair::enabled = false;
TracerType Settings::ESP::Tracer::type = BOTTOM;

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

static wchar_t* cwConvert(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
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

			Draw::DrawLine(LOC(vBonePos1.x, vBonePos1.y), LOC(vBonePos2.x, vBonePos2.y), Settings::ESP::bones_color);
		}
	}
}

void ESP::DrawTracer(C_BaseEntity* entity)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	int playerTeam = localplayer->GetTeam();
	int entityTeam = entity->GetTeam();
	Color color = playerTeam == entityTeam ? Settings::ESP::ally_color : Settings::ESP::enemy_color;

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
		color = isVisible ? Settings::ESP::enemy_visible_color : Settings::ESP::enemy_color;
	else
		color = Settings::ESP::ally_color;

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

void ESP::DrawPlayerInfo(C_BaseEntity* entity, int entityIndex)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(entity->GetActiveWeapon());
	if (!active_weapon)
		return;

	bool isVisible = Entity::IsVisible(entity, BONE_HEAD);
	Color color = color = Color(255, 255, 255, 255);

	if (Settings::ESP::Info::colorCode)
	{
		if (localplayer->GetTeam() != entity->GetTeam())
			color = isVisible ? Settings::ESP::Info::enemy_visible_color : Settings::ESP::Info::enemy_color;
		else
			color = Settings::ESP::Info::ally_color;
	}

	IEngineClient::player_info_t entityInformation;
	engine->GetPlayerInfo(entityIndex, &entityInformation);

	std::string modelName = std::string(active_weapon->GetClientClass()->m_pNetworkName);
	if (strstr(modelName.c_str(), "Weapon"))
		modelName = modelName.substr(7, modelName.length() - 7);
	else
		modelName = modelName.substr(1, modelName.length() - 1);

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

	Draw::DrawCenteredString(topText.c_str(), LOC (top.x, top.y - (size_top.y / 2)), color, esp_font);
	Draw::DrawCenteredString(bottomText.c_str(), LOC (top.x, top.y + height + (size_bottom.y / 2)), color, esp_font);
}

void ESP::DrawFOVCrosshair()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer->GetAlive())
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	Draw::DrawCircle(LOC(width / 2, height / 2), 20, Settings::Aimbot::fov / 90 * width / 2, Color(255, 100, 100, 255));
}

void ESP::DrawBombBox(C_BasePlantedC4* entity)
{
	Color color = Settings::ESP::bomb_color;
	Color colorText = entity->GetBombDefuser() != -1 ? Color(0, 50, 200) : Color(255, 255, 255);

	int width = 7;
	int additionalHeight = 4;
	float bombTime = entity->GetBombTime() - globalvars->curtime;

	Vector vecOrigin = entity->GetVecOrigin();
	Vector vecViewOffset = Vector(vecOrigin.x, vecOrigin.y, vecOrigin.z - 4);

	pstring str = "C4";

	if (bombTime > 0)
		str << " (" << bombTime << ")";

	Vector s_veclocalplayer_s;
	if (!WorldToScreen(vecOrigin, s_veclocalplayer_s))
	{
		DrawESPBox(vecOrigin, vecViewOffset, color, width, additionalHeight);
		Draw::DrawCenteredString(str.c_str(), LOC(s_veclocalplayer_s.x, s_veclocalplayer_s.y), colorText, esp_font);
	}
}

void ESP::DrawWeaponText(C_BaseEntity* entity, ClientClass* client)
{
	std::string modelName = std::string(client->m_pNetworkName);
	if (strstr(modelName.c_str(), "Weapon"))
		modelName = modelName.substr(7, modelName.length() - 7);
	else
		modelName = modelName.substr(1, modelName.length() - 1);

	Vector vecOrigin = entity->GetVecOrigin();
	if (vecOrigin == Vector(0, 0, 0))
		return;

	Vector s_veclocalplayer_s;
	if (!WorldToScreen(vecOrigin, s_veclocalplayer_s))
		Draw::DrawCenteredString(modelName.c_str(), LOC(s_veclocalplayer_s.x, s_veclocalplayer_s.y), Color(255, 255, 255, 255), esp_font);
}

void ESP::DrawGlow()
{
	static CGlowObjectManager* glow_object_mgr = GlowObjectManager();

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 0; i < glow_object_mgr->max_size; i++) {
		auto glow_object = &glow_object_mgr->m_GlowObjectDefinitions[i];

		if (!glow_object || glow_object->m_nNextFreeSlot != ENTRY_IN_USE || !glow_object->m_pEntity)
			continue;

		Color color;
		ClientClass* client = glow_object->m_pEntity->GetClientClass();

		if (client->m_ClassID == CCSPlayer)
		{
			if (glow_object->m_pEntity == (C_BaseEntity*)localplayer
				|| glow_object->m_pEntity->GetDormant()
				|| !glow_object->m_pEntity->GetAlive())
				continue;

			if (glow_object->m_pEntity->GetTeam() != localplayer->GetTeam())
			{
				if (Entity::IsVisible(glow_object->m_pEntity, BONE_HEAD))
					color = Settings::ESP::Glow::enemy_visible_color;
				else
					color = Settings::ESP::Glow::enemy_color;
			}
			else
			{
				color = Settings::ESP::Glow::ally_color;
			}
		}
		else if (client->m_ClassID != CBaseWeaponWorldModel &&
			(strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == CDEagle || client->m_ClassID == CAK47))
		{
				color = Settings::ESP::Glow::weapon_color;
		}

		glow_object->m_flGlowColor[0] = color.r / 255.0f;
		glow_object->m_flGlowColor[1] = color.g / 255.0f;
		glow_object->m_flGlowColor[2] = color.b / 255.0f;
		glow_object->m_flGlowAlpha = color.a / 255.0f;
		glow_object->m_flBloomAmount = 1.0f;
		glow_object->m_bRenderWhenOccluded = true;
		glow_object->m_bRenderWhenUnoccluded = false;
	}
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

	if (Settings::ESP::Glow::enabled)
		ESP::DrawGlow();
}
