#include "radar.h"

bool Settings::Radar::enabled = false;
int Settings::Radar::zoom = 16;
bool Settings::Radar::enemies = false;
bool Settings::Radar::allies = false;
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
		draw_list->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5, winpos.y + winsize.y * 0.5), 3.f, ImColor(255, 255, 255, 255));

		for (int i = 1; i < engine->GetMaxClients(); ++i)
		{
			C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(i);
			if (!player)
				continue;

			if (player == localplayer)
				continue;

			if (player->GetDormant() || !player->GetAlive())
				continue;

			if (player->GetTeam() == localplayer->GetTeam() && !Settings::Radar::allies)
				continue;

			if (player->GetTeam() != localplayer->GetTeam() && !Settings::Radar::enemies)
				continue;

			Vector2D screenpos = WorldToRadar(player->GetVecOrigin(), localplayer->GetVecOrigin(), localplayer_angles, winsize.x, Settings::Radar::zoom);
			bool bIsVisible = player->GetTeam() == localplayer->GetTeam() || (Settings::Radar::visibility_check && (*player->GetSpotted() || Entity::IsVisible(player, BONE_HEAD)));

			if (!bIsVisible && Settings::Radar::legit)
				continue;

			ImColor color = ESP::GetESPPlayerColor(player, bIsVisible);

			draw_list->AddCircleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), 3.f, color);
		}

		ImGui::End();
	}
}