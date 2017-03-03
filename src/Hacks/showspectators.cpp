#include "showspectators.h"

bool Settings::ShowSpectators::enabled = false;

std::list<int> ShowSpectators::GetObservervators(int playerId)
{
	std::list<int> list;

	if (!engine->IsInGame())
		return list;

	C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(playerId);
	if (!player)
		return list;

	if (!player->GetAlive())
	{
		C_BasePlayer* observerTarget = (C_BasePlayer*) entityList->GetClientEntityFromHandle(player->GetObserverTarget());
		if (!observerTarget)
			return list;

		player = observerTarget;
	}

	for (int i = 1; i < engine->GetMaxClients(); i++)
	{
		C_BasePlayer* pPlayer = (C_BasePlayer*) entityList->GetClientEntity(i);
		if (!pPlayer)
			continue;

		if (pPlayer->GetDormant() || pPlayer->GetAlive())
			continue;

		C_BasePlayer* target = (C_BasePlayer*) entityList->GetClientEntityFromHandle(pPlayer->GetObserverTarget());
		if (player != target)
			continue;

		list.push_back(i);
	}

	return list;
}

void ShowSpectators::RenderWindow()
{
	if (!Settings::ShowSpectators::enabled)
		return;

	if (!UI::isVisible && !engine->IsInGame())
		return;

	ImGui::SetNextWindowSize(ImVec2(50, 100), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Spectators", &Settings::ShowSpectators::enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		ImGui::Columns(2);
		ImGui::Separator();

		ImGui::Text("Name");
		ImGui::NextColumn();

		ImGui::Text("Mode");
		ImGui::NextColumn();

		for (int playerId : ShowSpectators::GetObservervators(engine->GetLocalPlayer()))
		{
			if (playerId == engine->GetLocalPlayer())
				continue;

			C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(playerId);

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(playerId, &entityInformation);

			if (entityInformation.fakeplayer)
				continue;

			ImGui::Separator();

			ImGui::Text("%s", entityInformation.name);
			ImGui::NextColumn();

			switch (*player->GetObserverMode())
			{
				case ObserverMode_t::OBS_MODE_IN_EYE:
					ImGui::Text("Perspective");
					break;
				case ObserverMode_t::OBS_MODE_CHASE:
					ImGui::Text("3rd person");
					break;
				case ObserverMode_t::OBS_MODE_ROAMING:
					ImGui::Text("Free look");
					break;
				case ObserverMode_t::OBS_MODE_DEATHCAM:
					ImGui::Text("Deathcam");
					break;
				case ObserverMode_t::OBS_MODE_FREEZECAM:
					ImGui::Text("Freezecam");
					break;
				case ObserverMode_t::OBS_MODE_FIXED:
					ImGui::Text("Fixed");
					break;
				default:
					break;
			}
			ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::End();
	}
}
