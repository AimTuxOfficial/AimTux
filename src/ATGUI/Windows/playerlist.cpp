#include "playerlist.h"

bool PlayerList::showWindow = false;

static char nickname[127] = "";

void PlayerList::RenderWindow()
{
	if( Settings::UI::Windows::Playerlist::reload )
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Playerlist::posX, Settings::UI::Windows::Playerlist::posY), ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Playerlist::sizeX, Settings::UI::Windows::Playerlist::sizeY), ImGuiSetCond_Always);
		Settings::UI::Windows::Playerlist::reload = false;
		PlayerList::showWindow = Settings::UI::Windows::Playerlist::open;
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Playerlist::posX, Settings::UI::Windows::Playerlist::posY), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Playerlist::sizeX, Settings::UI::Windows::Playerlist::sizeY), ImGuiSetCond_FirstUseEver);
	}
	if (!PlayerList::showWindow)
	{
		Settings::UI::Windows::Playerlist::open = false;
		return;
	}

	if (ImGui::Begin(XORSTR("Player list"), &PlayerList::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		Settings::UI::Windows::Playerlist::open = true;
		ImVec2 temp = ImGui::GetWindowSize();
		Settings::UI::Windows::Playerlist::sizeX = (int)temp.x;
		Settings::UI::Windows::Playerlist::sizeY = (int)temp.y;
		temp = ImGui::GetWindowPos();
		Settings::UI::Windows::Playerlist::posX = (int)temp.x;
		Settings::UI::Windows::Playerlist::posY = (int)temp.y;

		static int currentPlayer = -1;

		if (!engine->IsInGame() || (*csPlayerResource && !(*csPlayerResource)->GetConnected(currentPlayer)))
			currentPlayer = -1;

		ImGui::ListBoxHeader(XORSTR("##PLAYERS"), ImVec2(-1, (ImGui::GetWindowSize().y - 95)));
		if (engine->IsInGame() && *csPlayerResource)
		{
			ImGui::Columns(8);

			ImGui::Text(XORSTR("ID"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Nickname"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Team"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("SteamID"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Clan tag"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Stats"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Rank"));
			ImGui::NextColumn();

			ImGui::Text(XORSTR("Wins"));
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
						teamName = strdup(XORSTR("Unassigned"));
						break;
					case TeamID::TEAM_SPECTATOR:
						teamName = strdup(XORSTR("Spectator"));
						break;
					case TeamID::TEAM_TERRORIST:
						teamName = strdup(XORSTR("Terrorist"));
						break;
					case TeamID::TEAM_COUNTER_TERRORIST:
						teamName = strdup(XORSTR("Counter Terrorist"));
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

					ImGui::Text("%s", entityInformation.guid);
					ImGui::NextColumn();

					ImGui::Text("%s", teamName);
					ImGui::NextColumn();

					ImGui::Text("%s", (*csPlayerResource)->GetClan(it));
					ImGui::NextColumn();

					ImGui::Text("%d/%d/%d", (*csPlayerResource)->GetKills(it),(*csPlayerResource)->GetAssists(it), (*csPlayerResource)->GetDeaths(it));
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

			ImGui::Columns(3);
			{
				bool isFriendly = std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end();
				if (ImGui::Checkbox(XORSTR("Friend"), &isFriendly))
				{
					if (isFriendly)
						Aimbot::friends.push_back(entityInformation.xuid);
					else
						Aimbot::friends.erase(std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid));
				}

				bool shouldResolve = std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) != Resolver::Players.end();
				if (ImGui::Checkbox(XORSTR("Resolver"), &shouldResolve))
				{
					if (shouldResolve)
						Resolver::Players.push_back(entityInformation.xuid);
					else
						Resolver::Players.erase(std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid));
				}
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button(XORSTR("Steal name")))
				{
					std::string name(entityInformation.name);
					name = Util::PadStringRight(name, name.length() + 1);

					strcpy(nickname, name.c_str());
					NameChanger::SetName(Util::PadStringRight(name, name.length() + 1));
				}

				const char* clanTag = (*csPlayerResource)->GetClan(currentPlayer);
				if (strlen(clanTag) > 0 && ImGui::Button(XORSTR("Steal clan tag")))
				{
					Settings::ClanTagChanger::enabled = true;
					strcpy(Settings::ClanTagChanger::value, clanTag);
					Settings::ClanTagChanger::type = ClanTagType::STATIC;

					ClanTagChanger::UpdateClanTagCallback();
				}
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button(XORSTR("Print information")))
				{
					cvar->ConsoleColorPrintf(ColorRGBA(255, 255, 255), XORSTR("\n=====\nPlayer informations:\n[%s] %s \nSteamID: %s\n=====\n"),(*csPlayerResource)->GetClan(currentPlayer), entityInformation.name, entityInformation.guid);
				}
			}
		}

		ImGui::End();
	}
}
