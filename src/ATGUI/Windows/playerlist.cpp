#include "playerlist.h"

bool PlayerList::showWindow = false;

static char nickname[127] = "";

void PlayerList::RenderWindow()
{
	if (!PlayerList::showWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Player list", &PlayerList::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		static int currentPlayer = -1;

		if (!engine->IsInGame() || (*csPlayerResource && !(*csPlayerResource)->GetConnected(currentPlayer)))
			currentPlayer = -1;

		ImGui::ListBoxHeader("##PLAYERS", ImVec2(-1, (ImGui::GetWindowSize().y - 95)));
		if (engine->IsInGame() && *csPlayerResource)
		{
			ImGui::Columns(6);

			ImGui::Text("ID");
			ImGui::NextColumn();

			ImGui::Text("Nickname");
			ImGui::NextColumn();

			ImGui::Text("Team");
			ImGui::NextColumn();

			ImGui::Text("Clan tag");
			ImGui::NextColumn();

			ImGui::Text("Rank");
			ImGui::NextColumn();

			ImGui::Text("Wins");
			ImGui::NextColumn();

			std::unordered_map<TeamID, std::vector<int>, Util::IntHash<TeamID>> players = {
					{ TeamID::TEAM_UNASSIGNED, { } },
					{ TeamID::TEAM_SPECTATOR, { } },
					{ TeamID::TEAM_TERRORIST, { } },
					{ TeamID::TEAM_COUNTER_TERRORIST, { } },
			};

			for (int i = 1; i < engine->GetMaxClients(); i++)
			{
				if (i == engine->GetLocalPlayer())
					continue;

				if (!(*csPlayerResource)->GetConnected(i))
					continue;

				players[(*csPlayerResource)->GetTeam(i)].push_back(i);
			}

			for (int team = (int) TeamID::TEAM_UNASSIGNED; team <= (int) TeamID::TEAM_COUNTER_TERRORIST ; team++)
			{
				char* teamName = strdup("");
				switch ((TeamID) team)
				{
					case TeamID::TEAM_UNASSIGNED:
						teamName = strdup("Unassigned");
						break;
					case TeamID::TEAM_SPECTATOR:
						teamName = strdup("Spectator");
						break;
					case TeamID::TEAM_TERRORIST:
						teamName = strdup("Terrorist");
						break;
					case TeamID::TEAM_COUNTER_TERRORIST:
						teamName = strdup("Counter Terrorist");
						break;
				}

				for (auto it : players[(TeamID) team])
				{
					std::string id = std::to_string(it);

					IEngineClient::player_info_t entityInformation;
					engine->GetPlayerInfo(it, &entityInformation);

					if (entityInformation.ishltv)
						continue;

					ImGui::Separator();

					if (ImGui::Selectable(id.c_str(), it == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
						currentPlayer = it;
					ImGui::NextColumn();

					ImGui::Text("%s", entityInformation.name);
					ImGui::NextColumn();

					ImGui::Text("%s", teamName);
					ImGui::NextColumn();

					ImGui::Text("%s", (*csPlayerResource)->GetClan(it));
					ImGui::NextColumn();

					ImGui::Text("%s", ESP::ranks[*(*csPlayerResource)->GetCompetitiveRanking(it)]);
					ImGui::NextColumn();

					ImGui::Text("%d", *(*csPlayerResource)->GetCompetitiveWins(it));
					ImGui::NextColumn();
				}
			}
		}
		ImGui::ListBoxFooter();

		if (currentPlayer != -1)
		{
			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(currentPlayer, &entityInformation);

			ImGui::Columns(2);
			{
				bool isFriendly = std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end();
				if (ImGui::Checkbox("Friend", &isFriendly))
				{
					if (isFriendly)
						Aimbot::friends.push_back(entityInformation.xuid);
					else
						Aimbot::friends.erase(std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid));
				}

				bool shouldResolve = std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) != Resolver::Players.end();
				if (ImGui::Checkbox("Resolver", &shouldResolve))
				{
					if (shouldResolve)
						Resolver::Players.push_back(entityInformation.xuid);
					else
						Resolver::Players.erase(std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid));
				}
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Steal name"))
				{
					std::string name(entityInformation.name);
					name = Util::PadStringRight(name, name.length() + 1);

					strcpy(nickname, name.c_str());
					NameChanger::SetName(Util::PadStringRight(name, name.length() + 1));
				}

				const char* clanTag = (*csPlayerResource)->GetClan(currentPlayer);
				if (strlen(clanTag) > 0 && ImGui::Button("Steal clan tag"))
				{
					Settings::ClanTagChanger::enabled = true;
					strcpy(Settings::ClanTagChanger::value, clanTag);
					Settings::ClanTagChanger::type = ClanTagType::STATIC;

					ClanTagChanger::UpdateClanTagCallback();
				}
			}
		}

		ImGui::End();
	}
}