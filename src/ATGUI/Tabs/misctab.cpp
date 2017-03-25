#include "misctab.h"

static char nickname[127] = "";

void Misc::RenderTab()
{
	const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right", "Rage" };
	const char* animationTypes[] = { "Static", "Marquee", "Words", "Letters" };
	const char* spammerTypes[] = { "None", "Normal", "Positions" };
	const char* teams[] = { "Allies", "Enemies", "Both" };
	const char* grenadeTypes[] = { "FLASH", "SMOKE", "MOLOTOV", "HEGRENADE" };
	const char* throwTypes[] = { "NORMAL", "RUN", "JUMP", "WALK" };

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("Child1", ImVec2(0, 0), true);
		{
			ImGui::Text("Movement");
			ImGui::Separator();

			ImGui::Checkbox("Bunny Hop", &Settings::BHop::enabled);
			SetTooltip("Auto bunny hop");
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Edge Jump", &Settings::EdgeJump::enabled);
				SetTooltip("Jumps off the edges");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::EdgeJump::key);
			}
			ImGui::Columns(1);

			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Strafe", &Settings::AutoStrafe::enabled);
				SetTooltip("Auto strafe when bunny hopping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##STRAFETYPE", (int*)& Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
				ImGui::PopItemWidth();
			}

			if (Settings::AutoStrafe::type == AutostrafeType::AS_RAGE)
			{
				ImGui::Checkbox("Silent", &Settings::AutoStrafe::silent);
				SetTooltip("Strafes won't be visible for spectators");
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Spammer");
			ImGui::Separator();

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Checkbox("Kill Messages", &Settings::Spammer::KillSpammer::enabled);
				SetTooltip("Spams a kill message when killing an enemy");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM1", &Settings::Spammer::KillSpammer::sayTeam);
				SetTooltip("Only show kill message in team chat");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Options###KILL"))
					ImGui::OpenPopup("options_kill");

				ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("options_kill"))
				{
					static int killSpammerMessageCurrent = -1;
					static char killSpammerMessageBuf[126];

					ImGui::PushItemWidth(445);
					ImGui::InputText("###SPAMMERMESSAGE", killSpammerMessageBuf, IM_ARRAYSIZE(killSpammerMessageBuf));
					ImGui::PopItemWidth();
					ImGui::SameLine();

					if (ImGui::Button("Add"))
					{
						if (strlen(killSpammerMessageBuf) > 0)
							Settings::Spammer::KillSpammer::messages.push_back(std::string(killSpammerMessageBuf));

						strcpy(killSpammerMessageBuf, "");
					}
					ImGui::SameLine();

					if (ImGui::Button("Remove"))
						if (killSpammerMessageCurrent > -1 && (int) Settings::Spammer::KillSpammer::messages.size() > killSpammerMessageCurrent)
							Settings::Spammer::KillSpammer::messages.erase(Settings::Spammer::KillSpammer::messages.begin() + killSpammerMessageCurrent);

					ImGui::PushItemWidth(550);
					ImGui::ListBox("", &killSpammerMessageCurrent, Settings::Spammer::KillSpammer::messages, 10);
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}

			ImGui::Columns(1);
			ImGui::Checkbox("Radio Commands", &Settings::Spammer::RadioSpammer::enabled);

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Combo("###SPAMMERYPE", (int*)&Settings::Spammer::type, spammerTypes, IM_ARRAYSIZE(spammerTypes));
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM2", &Settings::Spammer::say_team);
				SetTooltip("Only spam messages in team chat");
			}
			ImGui::NextColumn();
			{
				if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::Button("Options###SPAMMER"))
					ImGui::OpenPopup("options_spammer");

				if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
					ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
				else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
					ImGui::SetNextWindowSize(ImVec2(200, 240), ImGuiSetCond_Always);

				if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::BeginPopup("options_spammer"))
				{
					if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
					{
						static int spammerMessageCurrent = -1;
						static char spammerMessageBuf[126];

						ImGui::PushItemWidth(445);
						ImGui::InputText("###SPAMMERMESSAGE", spammerMessageBuf, IM_ARRAYSIZE(spammerMessageBuf));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						if (ImGui::Button("Add"))
						{
							if (strlen(spammerMessageBuf) > 0)
								Settings::Spammer::NormalSpammer::messages.push_back(std::string(spammerMessageBuf));

							strcpy(spammerMessageBuf, "");
						}
						ImGui::SameLine();

						if (ImGui::Button("Remove"))
							if (spammerMessageCurrent > -1 && (int) Settings::Spammer::NormalSpammer::messages.size() > spammerMessageCurrent)
								Settings::Spammer::NormalSpammer::messages.erase(Settings::Spammer::NormalSpammer::messages.begin() + spammerMessageCurrent);

						ImGui::PushItemWidth(550);
						ImGui::ListBox("", &spammerMessageCurrent, Settings::Spammer::NormalSpammer::messages, 10);
						ImGui::PopItemWidth();
					}
					else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
					{
						ImGui::PushItemWidth(185);
						ImGui::Combo("###POSITIONSTEAM", &Settings::Spammer::PositionSpammer::team, teams, IM_ARRAYSIZE(teams));
						ImGui::PopItemWidth();
						ImGui::Separator();
						ImGui::Checkbox("Show Name", &Settings::Spammer::PositionSpammer::showName);
						ImGui::Checkbox("Show Weapon", &Settings::Spammer::PositionSpammer::showWeapon);
						ImGui::Checkbox("Show Rank", &Settings::Spammer::PositionSpammer::showRank);
						ImGui::Checkbox("Show Wins", &Settings::Spammer::PositionSpammer::showWins);
						ImGui::Checkbox("Show Health", &Settings::Spammer::PositionSpammer::showHealth);
						ImGui::Checkbox("Show Money", &Settings::Spammer::PositionSpammer::showMoney);
						ImGui::Checkbox("Show Last Place", &Settings::Spammer::PositionSpammer::showLastplace);
					}

					ImGui::EndPopup();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("FOV");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("FOV", &Settings::FOVChanger::enabled);
				SetTooltip("Change camera FOV");
				ImGui::Checkbox("Viewmodel FOV", &Settings::FOVChanger::viewmodelEnabled);
				SetTooltip("Change viewmodel FOV");
				ImGui::Checkbox("Ignore Scope", &Settings::FOVChanger::ignoreScope);
				SetTooltip("Disable FOV Changer while scoping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
				ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodelValue, 0, 360);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Third Person");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::ThirdPerson::enabled);
				SetTooltip("Switches from first-person perspective to third-person perspective.");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##TPCAMOFFSET", &Settings::ThirdPerson::distance, 0.f, 500.f, "Camera Offset: %0.f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Grenade Helper");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled ###ghenabled", &Settings::GrenadeHelper::enabled);
				SetTooltip("Show Saved Grenade Throws, Visuals required.");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only matching ###match", &Settings::GrenadeHelper::onlyMatchingInfos);
				SetTooltip("Shows only the info's for your equipped Grenade.");
			}

			ImGui::Columns(2);
			{
				if (ImGui::Button("Aimassist", ImVec2(-1, 0)))
					ImGui::OpenPopup("optionAimAssist");
				ImGui::SetNextWindowSize(ImVec2(200, 120), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("optionAimAssist"))
				{
					ImGui::PushItemWidth(-1);
					ImGui::Checkbox("Enabled", &Settings::GrenadeHelper::aimAssist);
					SetTooltip("Whether the Aimassist will help you throw Grenades.");
					ImGui::SliderFloat("###aimstep", &Settings::GrenadeHelper::aimStep, 0, 10, "Speed: %0.3f");
					SetTooltip("The speed at which the Aimassist helps.");
					ImGui::SliderFloat("###aimfov", &Settings::GrenadeHelper::aimFov, 0, 180, "Fov: %0.2f");
					SetTooltip("The Fov at which the Aimassist starts.");
					ImGui::SliderFloat("###aimdistance", &Settings::GrenadeHelper::aimDistance, 0, 100, "Distance: %0.2f");
					SetTooltip("The distance at which the Aimassist starts.");
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Add Info", ImVec2(-1, 0)))
					ImGui::OpenPopup("addinfo_throw");

				ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("addinfo_throw"))
				{
					static int throwMessageCurrent = -1;
					static char inputName[40];
					static int tType = (int)ThrowType::NORMAL;
					static int gType = (int)GrenadeType::SMOKE;

					if (engine->IsInGame())
					{
						C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
						if (localPlayer)
						{
							C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon *) entityList->GetClientEntityFromHandle(
									localPlayer->GetActiveWeapon());
							if (activeWeapon &&
								activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_GRENADE)
								gType = (int)getGrenadeType(activeWeapon);
						}
					}
					ImGui::Columns(1);
					ImGui::PushItemWidth(500);
					ImGui::InputText("", inputName, sizeof(inputName));
					ImGui::PopItemWidth();
					ImGui::SameLine();
					if (ImGui::Button("Add") && engine->IsInGame() && Settings::GrenadeHelper::actMapName.length() > 0)
					{
						C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
						if (strlen(inputName) > 0)
						{
							GrenadeInfo n = GrenadeInfo((GrenadeType)gType, localPlayer->GetEyePosition(), *localPlayer->GetVAngles(), (ThrowType)tType, inputName);
							Settings::GrenadeHelper::grenadeInfos.push_back(n);
							pstring path = GetGhConfigDirectory() << Settings::GrenadeHelper::actMapName;
							if (!DoesFileExist(path.c_str()))
								mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
							Settings::SaveGrenadeInfo(path << "/config.json");
						}
						strcpy(inputName, "");
					}
					ImGui::Columns(2);
					ImGui::Combo("###Throwtype", &tType, throwTypes, IM_ARRAYSIZE(throwTypes));
					ImGui::NextColumn();
					ImGui::Combo("###Grenadetype", &gType, grenadeTypes, IM_ARRAYSIZE(grenadeTypes));
					ImGui::Columns(1);
					ImGui::Separator();
					ImGui::PushItemWidth(550);
					auto lambda =[](void* data, int idx, const char** out_text)
					{
						*out_text = Settings::GrenadeHelper::grenadeInfos.at(idx).name.c_str();
						return *out_text != NULL;
					};
					ImGui::ListBox("", &throwMessageCurrent, lambda, NULL, Settings::GrenadeHelper::grenadeInfos.size(), 7);
					ImGui::PopItemWidth();
					ImGui::Columns(1);
					if (ImGui::Button("Remove",  ImVec2(ImGui::GetWindowWidth(), 30)))
						if (throwMessageCurrent > -1 && (int) Settings::GrenadeHelper::grenadeInfos.size() > throwMessageCurrent)
						{
							Settings::GrenadeHelper::grenadeInfos.erase(Settings::GrenadeHelper::grenadeInfos.begin() + throwMessageCurrent);
							pstring path = GetGhConfigDirectory() << Settings::GrenadeHelper::actMapName;
							if (!DoesFileExist(path.c_str()))
								mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
							Settings::SaveGrenadeInfo(path << "/config.json");
						}
					ImGui::EndPopup();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("Child2", ImVec2(0, 0), true);
		{
			ImGui::Text("Clantag");
			ImGui::Separator();
			ImGui::Checkbox("Enabled", &Settings::ClanTagChanger::enabled);
			SetTooltip("Display a custom clantag");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::InputText("##CLANTAG", Settings::ClanTagChanger::value, 30))
					ClanTagChanger::UpdateClanTagCallback();
				ImGui::PopItemWidth();

				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Animation Speed");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##ANIMATIONTYPE", (int*)& Settings::ClanTagChanger::type, animationTypes, IM_ARRAYSIZE(animationTypes)))
					ClanTagChanger::UpdateClanTagCallback();
				if (ImGui::SliderInt("##ANIMATIONSPEED", &Settings::ClanTagChanger::animationSpeed, 0, 2000))
					ClanTagChanger::UpdateClanTagCallback();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Nickname");
			ImGui::Separator();

			ImGui::InputText("##NICKNAME", nickname, 127);

			ImGui::SameLine();
			if (ImGui::Button("Set Nickname", ImVec2(-1, 0)))
				NameChanger::SetName(std::string(nickname).c_str());

			if (ImGui::Button("Glitch Name"))
				NameChanger::SetName("\n\xAD\xAD\xAD");
			SetTooltip("Allows you to change your name an infinite amount of times and doesn't show in server message");
			ImGui::SameLine();
			if (ImGui::Button("No Name"))
			{
				NameChanger::changes = 0;
				NameChanger::type = NameChanger::NC_Type::NC_NORMAL;
			}

			ImGui::SameLine();
			if (ImGui::Button("Rainbow Name"))
				NameChanger::InitColorChange(NameChanger::NC_Type::NC_RAINBOW);

			ImGui::SameLine();
			if (ImGui::Button("Colorize Name", ImVec2(-1, 0)))
				ImGui::OpenPopup("optionColorizeName");
			ImGui::SetNextWindowSize(ImVec2(150, 300), ImGuiSetCond_Always);
			if (ImGui::BeginPopup("optionColorizeName"))
			{
				ImGui::PushItemWidth(-1);
				for (auto& it : NameChanger::colors)
				{
					if (ImGui::Button(it.second, ImVec2(-1, 0)))
						NameChanger::InitColorChange(NameChanger::NC_Type::NC_SOLID, it.first);
				}
				ImGui::PopItemWidth();

				ImGui::EndPopup();
			}
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Name Stealer", &Settings::NameStealer::enabled))
					NameStealer::entityId = -1;
			}
			ImGui::NextColumn();
			{
				ImGui::Combo("", &Settings::NameStealer::team, teams, IM_ARRAYSIZE(teams));
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Fake Lag", &Settings::FakeLag::enabled);
				SetTooltip("Chokes packets so it appears you're lagging");
				ImGui::Checkbox("Adaptive Fake Lag", &Settings::FakeLag::adaptive);
				SetTooltip("Chokes packets based on velocity (minimum choked is fakelag value)");
				ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
				SetTooltip("Auto accept games when in MM queue");
				ImGui::Checkbox("AirStuck", &Settings::Airstuck::enabled);
				SetTooltip("Stops tickrate so you freeze in place");
				ImGui::Checkbox("Autoblock", &Settings::Autoblock::enabled);
				SetTooltip("Allows you to block players from moving forwards by standing in front of them and mirroring their moves - great for griefing");
				if (ImGui::Checkbox("Teleport", &Settings::Teleport::enabled))
				{
					if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::Teleport::enabled)
					{
						Settings::Teleport::enabled = false;
						ImGui::OpenPopup("Error###UNTRUSTED_FEATURE");
					}
				}
				SetTooltip("Teleport to (0, 0) on any map");
				ImGui::Checkbox("Jump Throw", &Settings::JumpThrow::enabled);
				SetTooltip("Hold to prime grenade, release to perform perfect jump throw. Good for executing map smokes.");
				ImGui::Checkbox("Auto Defuse", &Settings::AutoDefuse::enabled);
				SetTooltip("Will automatically defuse the bomb with 0.5 seconds remaining - starts at 5.5 seconds until explosion with kit and 10.5 without");
				ImGui::Checkbox("Sniper Crosshair", &Settings::SniperCrosshair::enabled);
				SetTooltip("Enables the crosshair with sniper rifles");
				ImGui::Checkbox("Disable post-processing", &Settings::DisablePostProcessing::enabled);
				SetTooltip("Disables post-processing");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16, "Amount: %0.f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Show Ranks", &Settings::ShowRanks::enabled);
				SetTooltip("Displays competitive rank of all players in the scoreboard next to their name during a competitive match");
				ImGui::Checkbox("Screenshot Cleaner", &Settings::ScreenshotCleaner::enabled);
				SetTooltip("Prevents AimTux visuals from appearing in screenshots taken");
				UI::KeyBindButton(&Settings::Airstuck::key);
				UI::KeyBindButton(&Settings::Autoblock::key);
				UI::KeyBindButton(&Settings::Teleport::key);
				UI::KeyBindButton(&Settings::JumpThrow::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
			if (ImGui::BeginPopupModal("Error###UNTRUSTED_FEATURE"))
			{
				ImGui::Text("You cannot use this feature on a VALVE server.");

				ImGui::Checkbox("This is not a VALVE server", &ValveDSCheck::forceUT);

				if (ImGui::Button("OK"))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();

			ImGui::EndChild();
		}
	}
}
