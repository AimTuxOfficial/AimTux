#include "esp.h"

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

			Draw::DrawLine(LOC(vBonePos1.x, vBonePos1.y), LOC(vBonePos2.x, vBonePos2.y), cSettings.ESP.bones_color);
		}
	}
}

void ESP::DrawTracer(C_BaseEntity* entity)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	int playerTeam = localplayer->GetTeam();
	int entityTeam = entity->GetTeam();
	Color color = playerTeam == entityTeam ? cSettings.ESP.ally_color : cSettings.ESP.enemy_color;

	int width;
	int height;
	engine->GetScreenSize(width, height);

	Vector2D tracerLocation;

	switch (cSettings.ESP.Tracer.type)
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
		color = isVisible ? cSettings.ESP.enemy_visible_color : cSettings.ESP.enemy_color;
	else
		color = cSettings.ESP.ally_color;

	if (cSettings.ESP.Walls.type == FLAT_2D)
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
	else if (cSettings.ESP.Walls.type == BOX_3D)
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
	bool isVisible = Entity::IsVisible(entity, BONE_HEAD);
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	Color color;

	if (localplayer->GetTeam() != entity->GetTeam())
		color = isVisible ? cSettings.ESP.Info.enemy_visible_color : cSettings.ESP.Info.enemy_color;
	else
		color = cSettings.ESP.Info.ally_color;

	IEngineClient::player_info_t entityInformation;
	engine->GetPlayerInfo(entityIndex, &entityInformation);

	// Name string
	pstring name;
	name << entityInformation.name;

	// Health string
	pstring health;
	health + entity->GetHealth();
	health << "hp";

	Vector2D size_name = Draw::GetTextSize(name.c_str(), esp_font);
	Vector2D size_health = Draw::GetTextSize(health.c_str(), esp_font);

	Vector max = entity->GetCollideable()->OBBMaxs();

	Vector pos, pos3D;
	Vector top, top3D;

	pos3D = entity->GetVecOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (WorldToScreen(pos3D, pos) || WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);

	if (cSettings.ESP.Info.showHealth)
		Draw::DrawCenteredString(health.c_str(), LOC (top.x, top.y + height + (size_health.y / 2)), color, esp_font);

	if (cSettings.ESP.Info.showName)
		Draw::DrawCenteredString(name.c_str(), LOC (top.x, top.y - (size_name.y / 2)), color, esp_font);
}

void ESP::DrawFOVCrosshair()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer->GetAlive())
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	Draw::DrawCircle(LOC(width / 2, height / 2), 20, cSettings.Aimbot.fov / 90 * width / 2, Color(255, 100, 100, 255));
}

void ESP::DrawBombBox(C_BasePlantedC4* entity)
{
	Color color = cSettings.ESP.bomb_color;
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
					color = cSettings.ESP.Glow.enemy_visible_color;
				else
					color = cSettings.ESP.Glow.enemy_color;
			}
			else
			{
				color = cSettings.ESP.Glow.ally_color;
			}
		}
		else if (client->m_ClassID != CBaseWeaponWorldModel &&
			(strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == CDEagle || client->m_ClassID == CAK47))
		{
				color = cSettings.ESP.Glow.weapon_color;
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
	if (!cSettings.ESP.enabled)
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

			if (cSettings.ESP.visibility_check && !Entity::IsVisible(entity, BONE_HEAD))
				continue;

			if (!cSettings.ESP.friendly && localplayer->GetTeam() == entity->GetTeam())
				continue;

			if (!localplayer->GetAlive() && entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget()) == entity)
				continue;

			if (cSettings.ESP.Bones.enabled)
				ESP::DrawBones(entity);

			if (cSettings.ESP.Walls.enabled)
				ESP::DrawPlayerBox(entity);

			if (cSettings.ESP.Tracer.enabled)
				ESP::DrawTracer(entity);

			if (cSettings.ESP.Info.showHealth || cSettings.ESP.Info.showName)
				ESP::DrawPlayerInfo(entity, i);
		}
		else if (client->m_ClassID == CPlantedC4)
		{
			C_BasePlantedC4* bomb = (C_BasePlantedC4*) entitylist->GetClientEntity(i);

			if (cSettings.ESP.Bomb.enabled && bomb->IsBombTicking() && !bomb->IsBombDefused())
				ESP::DrawBombBox(bomb);
		}
		else if (client->m_ClassID != CBaseWeaponWorldModel &&
				(strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == CDEagle || client->m_ClassID == CAK47))
		{
			if (cSettings.ESP.Weapons.enabled)
				ESP::DrawWeaponText(entity, client);
		}
	}

	if (cSettings.ESP.FOVCrosshair.enabled)
		ESP::DrawFOVCrosshair();

	if (cSettings.ESP.Glow.enabled)
		ESP::DrawGlow();
}
