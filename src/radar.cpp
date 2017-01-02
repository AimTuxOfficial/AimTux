#include "radar.h"

bool Settings::Radar::enabled = false;
float Settings::Radar::zoom = 16.f;
bool Settings::Radar::enemies = false;
bool Settings::Radar::allies = false;
bool Settings::Radar::bomb = false;
bool Settings::Radar::defuser = false;
bool Settings::Radar::legit = false;
bool Settings::Radar::visibility_check = false;

Vector2D WorldToRadar( const Vector location, const Vector origin, const QAngle angles, int width, int scale = 16)
{
	float x_diff = location.x - origin.x;
	float y_diff = location.y - origin.y;

	int iRadarRadius = width;
	float fRange = scale * iRadarRadius;

	float flOffset = atan(y_diff / x_diff);
	flOffset *= 180;
	flOffset /= M_PI;

	if ((x_diff < 0) && (y_diff >= 0))
		flOffset = 180 + flOffset;
	else if ((x_diff < 0) && (y_diff < 0))
		flOffset = 180 + flOffset;
	else if ((x_diff >= 0) && (y_diff < 0))
		flOffset = 360 + flOffset;

	y_diff = -1 * (sqrt((x_diff * x_diff) + (y_diff * y_diff)));
	x_diff = 0;

	flOffset = angles.y - flOffset;

	flOffset *= M_PI;
	flOffset /= 180;

	float xnew_diff = x_diff * cos(flOffset) - y_diff * sin(flOffset);
	float ynew_diff = x_diff * sin(flOffset) + y_diff * cos(flOffset);

	if (-1 * y_diff > fRange)
	{
		float flScale;

		flScale = (-1 * y_diff) / fRange;

		xnew_diff /= flScale;
		ynew_diff /= flScale;
	}

	xnew_diff /= scale * 2;
	ynew_diff /= scale * 2;

	return Vector2D((iRadarRadius / 2) + (int) xnew_diff, (iRadarRadius / 2) + (int) ynew_diff);
}

static void SquareConstraint(ImGuiSizeConstraintCallbackData *data)
{
	data->DesiredSize = ImVec2(std::max(data->DesiredSize.x, data->DesiredSize.y), std::max(data->DesiredSize.x, data->DesiredSize.y));
}

void Radar::DrawWindow()
{
	if (!Settings::Radar::enabled)
		return;

	if (!UI::isVisible && !engine->IsInGame())
		return;

	ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);

	if (ImGui::Begin("Radar", &Settings::Radar::enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoTitleBar))
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		ImVec2 winpos = ImGui::GetWindowPos();
		ImVec2 winsize = ImGui::GetWindowSize();

		draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5, winpos.y), ImVec2(winpos.x + winsize.x * 0.5, winpos.y + winsize.y), ImColor(70,70,70, 255), 1.f);
		draw_list->AddLine(ImVec2(winpos.x, winpos.y + winsize.y * 0.5 ), ImVec2(winpos.x + winsize.x, winpos.y + winsize.y * 0.5), ImColor(70,70,70, 255), 1.f);

		draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5, winpos.y + winsize.y * 0.5 ), ImVec2(winpos.x, winpos.y), ImColor(90,90,90, 255), 1.f);
		draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5, winpos.y + winsize.y * 0.5 ), ImVec2(winpos.x + winsize.x, winpos.y), ImColor(90,90,90, 255), 1.f);

		C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
		{
			ImGui::End();
			return;
		}

		QAngle localplayer_angles;
		engine->GetViewAngles(localplayer_angles);

		// draw localplayer
		if (localplayer->GetAlive() || (!localplayer->GetAlive() && (!localplayer->GetObserverTarget() || *localplayer->GetObserverMode() == OBS_MODE_ROAMING)))
			draw_list->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5, winpos.y + winsize.y * 0.5), 4.5f, ImColor(255, 255, 255, 255));

		for (int i = 1; i < entitylist->GetHighestEntityIndex(); i++)
		{
			C_BaseEntity* entity = entitylist->GetClientEntity(i);
			if (!entity)
				continue;

			Vector2D screenpos = WorldToRadar(entity->GetVecOrigin(), localplayer->GetVecOrigin(), localplayer_angles, winsize.x, Settings::Radar::zoom);
			int classId = entity->GetClientClass()->m_ClassID;

			ImColor color;
			int shape = -1;

			if (classId == CCSPlayer)
			{
				C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(i);

				if (player == localplayer)
					continue;

				if (player->GetDormant() || !player->GetAlive())
					continue;

				if (player->GetTeam() == localplayer->GetTeam() && !Settings::Radar::allies)
					continue;

				if (player->GetTeam() != localplayer->GetTeam() && !Settings::Radar::enemies)
					continue;

				bool bIsVisible = player->GetTeam() == localplayer->GetTeam() || (Settings::Radar::visibility_check && (*player->GetSpotted() || Entity::IsVisible(player, BONE_HEAD)));
				if (!bIsVisible && Settings::Radar::legit)
					continue;

				color = ESP::GetESPPlayerColor(player, bIsVisible);

				Vector localPos = localplayer->GetVecOrigin();
				Vector playerPos = player->GetVecOrigin();

				if (playerPos.z + 64.0f < localPos.z)
					shape = EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN;
				else if (playerPos.z - 64.0f > localPos.z)
					shape = EntityShape_t::SHAPE_TRIANGLE;
				else
					shape = EntityShape_t::SHAPE_CIRCLE;
			}
			else if (classId == CC4)
			{
				if (!Settings::Radar::bomb)
					continue;

				C_BaseCombatWeapon* bomb = (C_BaseCombatWeapon*) entity;
				Vector vOrig = bomb->GetVecOrigin();

				int owner = bomb->GetOwner();
				if (owner != -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
					continue;

				color = Settings::ESP::bomb_color;
				shape = EntityShape_t::SHAPE_SQUARE;
			}
			else if (classId == CPlantedC4)
			{
				if (!Settings::Radar::bomb)
					continue;

				C_PlantedC4* bomb = (C_PlantedC4*) entity;

				color = bomb->GetBombDefuser() != -1 || bomb->IsBombDefused() ? Settings::ESP::bomb_defusing_color : Settings::ESP::bomb_color;
				shape = EntityShape_t::SHAPE_SQUARE;
			}
			else if (classId == CBaseAnimating)
			{
				if (localplayer->HasDefuser() || localplayer->GetTeam() != TEAM_COUNTER_TERRORIST)
					continue;

				color = Settings::ESP::defuser_color;
				shape = EntityShape_t::SHAPE_SQUARE;
			}

			switch (shape)
			{
				case EntityShape_t::SHAPE_CIRCLE:
					draw_list->AddCircleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), 4.5f, color);
					break;
				case EntityShape_t::SHAPE_SQUARE:
					draw_list->AddRectFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y),
											 ImVec2(winpos.x + screenpos.x + 9.0f, winpos.y + screenpos.y + 9.0f),
											 color, 0.0f, 0);
					break;
				case EntityShape_t::SHAPE_TRIANGLE:
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y + 5.0f),
												 ImVec2(winpos.x + screenpos.x + 5.0f, winpos.y + screenpos.y + 5.0f),
												 ImVec2(winpos.x + screenpos.x + 2.5f, winpos.y + screenpos.y),
												 color);
					break;
				case EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN:
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y),
					                             ImVec2(winpos.x + screenpos.x + 5.0f, winpos.y + screenpos.y),
					                             ImVec2(winpos.x + screenpos.x + 2.5f, winpos.y + screenpos.y + 5.0f),
					                             color);
					break;
			}

		}

		ImGui::End();
	}
}