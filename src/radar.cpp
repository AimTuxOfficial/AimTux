#include "radar.h"

bool Settings::Radar::enabled = false;
float Settings::Radar::zoom = 16.f;
bool Settings::Radar::enemies = false;
bool Settings::Radar::allies = false;
bool Settings::Radar::bomb = false;
bool Settings::Radar::defuser = false;
bool Settings::Radar::legit = false;
bool Settings::Radar::visibility_check = false;
bool Settings::Radar::InGame::enabled = false;

std::set<int> visible_players;

Vector2D WorldToRadar(const Vector location, const Vector origin, const QAngle angles, int width, float scale = 16.f)
{
	float x_diff = location.x - origin.x;
	float y_diff = location.y - origin.y;

	int iRadarRadius = width;

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

	xnew_diff /= scale;
	ynew_diff /= scale;

	xnew_diff = (iRadarRadius / 2) + (int) xnew_diff;
	ynew_diff = (iRadarRadius / 2) + (int) ynew_diff;

	// clamp x & y
	// FIXME: instead of using hardcoded "4" we should fix cliprect of the radar window
	if (xnew_diff > iRadarRadius)
		xnew_diff = iRadarRadius - 4;
	else if (xnew_diff < 4)
		xnew_diff = 4;

	if (ynew_diff> iRadarRadius)
		ynew_diff = iRadarRadius;
	else if (ynew_diff < 4)
		ynew_diff = 0;

	return Vector2D(xnew_diff, ynew_diff);
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
				C_BasePlayer* player = (C_BasePlayer*) entity;

				if (player == localplayer)
					continue;

				if (player->GetDormant() || !player->GetAlive())
					continue;

				if (player->GetTeam() == localplayer->GetTeam() && !Settings::Radar::allies)
					continue;

				if (player->GetTeam() != localplayer->GetTeam() && !Settings::Radar::enemies)
					continue;

				bool bIsVisible = player->GetTeam() == localplayer->GetTeam() || (Settings::Radar::visibility_check && (*player->GetSpotted() || std::find(visible_players.begin(), visible_players.end(), i) != visible_players.end()));
				if (!bIsVisible && Settings::Radar::legit)
					continue;

				C_BasePlayer* observer_target = (C_BasePlayer*) entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget());
				if (observer_target && player == observer_target && *localplayer->GetObserverMode() == OBS_MODE_IN_EYE)
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

				if (!(*csGameRules) || !(*csGameRules)->IsBombDropped())
					continue;

				color = Settings::ESP::bomb_color;
				shape = EntityShape_t::SHAPE_SQUARE;
			}
			else if (classId == CPlantedC4)
			{
				if (!Settings::Radar::bomb)
					continue;

				if (!(*csGameRules) || !(*csGameRules)->IsBombPlanted())
					continue;

				C_PlantedC4* bomb = (C_PlantedC4*) entity;

				color = bomb->GetBombDefuser() != -1 || bomb->IsBombDefused() ? Settings::ESP::bomb_defusing_color : Settings::ESP::bomb_color;
				shape = EntityShape_t::SHAPE_SQUARE;
			}
			else if (classId == CBaseAnimating)
			{
				if (!Settings::Radar::defuser)
					continue;

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
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y + 9.0f),
												 ImVec2(winpos.x + screenpos.x + 9.0f, winpos.y + screenpos.y + 9.0f),
												 ImVec2(winpos.x + screenpos.x + 5.f, winpos.y + screenpos.y),
												 color);
					break;
				case EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN:
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y),
					                             ImVec2(winpos.x + screenpos.x + 9.0f, winpos.y + screenpos.y),
					                             ImVec2(winpos.x + screenpos.x + 5.f, winpos.y + screenpos.y + 9.0f),
					                             color);
					break;
			}

		}

		ImGui::End();
	}
}

void Radar::InGameRadar(C_BasePlayer* player)
{
	if (!player->GetAlive() || player->GetDormant())
		return;

	*player->GetSpotted() = true;
}

void Radar::BeginFrame()
{
	if (!Settings::Radar::enabled && !Settings::Radar::InGame::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 1; i < engine->GetMaxClients(); i++)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		C_BasePlayer* player = (C_BasePlayer*) entity;

		if (Settings::Radar::InGame::enabled)
			Radar::InGameRadar(player);

		if (Settings::Radar::enabled)
		{
			// we shouldn't see people behind us
			if (Entity::IsVisible(player, BONE_HEAD, 55.f))
				visible_players.insert(i);
			else
				visible_players.erase(i);
		}
	}
}
