#include "colors.h"

bool Colors::showWindow = false;

void Colors::RenderWindow()
{
	if (!Colors::showWindow)
		return;

	struct ColorProperty
	{
		const char* name;
		ImColor* ptr;
		bool* hpPtr;
	};

	ColorProperty colors[] = {
			{ "UI Main", &Settings::UI::mainColor, nullptr },
			{ "UI Body", &Settings::UI::bodyColor, nullptr },
			{ "UI Font", &Settings::UI::fontColor, nullptr },
			{ "FOV Circle", &Settings::ESP::FOVCrosshair::color, nullptr },
			{ "Hitmarker", &Settings::ESP::Hitmarker::color, nullptr },
			{ "ESP - Enemy", &Settings::ESP::enemyColor, &Settings::ESP::hpEnemyColor },
			{ "ESP - Team", &Settings::ESP::allyColor, &Settings::ESP::hpAllyColor },
			{ "ESP - Enemy Visible", &Settings::ESP::enemyVisibleColor, &Settings::ESP::hpEnemyVisibleColor },
			{ "ESP - Team Visible", &Settings::ESP::allyVisibleColor, &Settings::ESP::hpAllyVisibleColor },
			{ "ESP - CT", &Settings::ESP::ctColor, &Settings::ESP::hpCtColor },
			{ "ESP - T", &Settings::ESP::tColor, &Settings::ESP::hpTColor },
			{ "ESP - CT Visible", &Settings::ESP::ctVisibleColor, &Settings::ESP::hpCtVisibleColor },
			{ "ESP - T Visible", &Settings::ESP::tVisibleColor, &Settings::ESP::hpTVisibleColor },
			{ "ESP - LocalPlayer", &Settings::ESP::localplayerColor, &Settings::ESP::hpLocalplayerColor },
			{ "ESP - Bomb", &Settings::ESP::bombColor, nullptr },
			{ "ESP - Bomb Defusing", &Settings::ESP::bombDefusingColor, nullptr },
			{ "ESP - Hostage", &Settings::ESP::hostageColor, nullptr },
			{ "ESP - Defuser", &Settings::ESP::defuserColor, nullptr },
			{ "ESP - Weapon", &Settings::ESP::weaponColor, nullptr },
			{ "ESP - Chicken", &Settings::ESP::chickenColor, nullptr },
			{ "ESP - Fish", &Settings::ESP::fishColor, nullptr },
			{ "ESP - Smoke", &Settings::ESP::smokeColor, nullptr },
			{ "ESP - Decoy", &Settings::ESP::decoyColor, nullptr },
			{ "ESP - Flashbang", &Settings::ESP::flashbangColor, nullptr },
			{ "ESP - Grenade", &Settings::ESP::grenadeColor, nullptr },
			{ "ESP - Molotov", &Settings::ESP::molotovColor, nullptr },
			{ "ESP - Skeleton", &Settings::ESP::Skeleton::color, nullptr },
			{ "Chams - Team", &Settings::ESP::Chams::allyColor, &Settings::ESP::Chams::hpAllyColor },
			{ "Chams - Team Visible", &Settings::ESP::Chams::allyVisibleColor, &Settings::ESP::Chams::hpAllyVisibleColor },
			{ "Chams - Enemy", &Settings::ESP::Chams::enemyColor, &Settings::ESP::Chams::hpEnemyColor },
			{ "Chams - Enemy Visible", &Settings::ESP::Chams::enemyVisibleColor, &Settings::ESP::Chams::hpEnemyVisibleColor },
			{ "Chams - LocalPlayer", &Settings::ESP::Chams::localplayerColor, &Settings::ESP::Chams::hpLocalplayerColor },
			{ "Chams - Arms", &Settings::ESP::Chams::Arms::color, nullptr },
			{ "Chams - Weapon", &Settings::ESP::Chams::Weapon::color, nullptr },
			{ "Grenade Helper - Aim Line", &Settings::GrenadeHelper::aimLine, nullptr},
			{ "Grenade Helper - Aim Dot", &Settings::GrenadeHelper::aimDot, nullptr},
			{ "Grenade Helper - HE info", &Settings::GrenadeHelper::infoHE, nullptr},
			{ "Grenade Helper - Smoke info", &Settings::GrenadeHelper::infoSmoke, nullptr},
			{ "Grenade Helper - Molotov info", &Settings::GrenadeHelper::infoMolotov, nullptr},
			{ "Grenade Helper - Flash info", &Settings::GrenadeHelper::infoFlash, nullptr},
			{ "Radar - Enemy", &Settings::Radar::enemyColor, &Settings::Radar::hpEnemyColor },
			{ "Radar - Team", &Settings::Radar::allyColor, &Settings::Radar::hpAllyColor },
			{ "Radar - Enemy Visible", &Settings::Radar::enemyVisibleColor, &Settings::Radar::hpEnemyVisibleColor },
			{ "Radar - Team Visible", &Settings::Radar::allyVisibleColor, &Settings::Radar::hpAllyVisibleColor },
			{ "Radar - CT", &Settings::Radar::ctColor, &Settings::Radar::hpCtColor },
			{ "Radar - T", &Settings::Radar::tColor, &Settings::Radar::hpTColor },
			{ "Radar - CT Visible", &Settings::Radar::ctVisibleColor, &Settings::Radar::hpCtVisibleColor },
			{ "Radar - T Visible", &Settings::Radar::tVisibleColor, &Settings::Radar::hpTVisibleColor },
			{ "Radar - Bomb", &Settings::Radar::bombColor, nullptr },
			{ "Radar - Bomb Defusing", &Settings::Radar::bombDefusingColor, nullptr },
			{ "Glow - Team", &Settings::ESP::Glow::allyColor, &Settings::ESP::Glow::hpAllyColor },
			{ "Glow - Enemy", &Settings::ESP::Glow::enemyColor, &Settings::ESP::Glow::hpEnemyColor },
			{ "Glow - Enemy Visible", &Settings::ESP::Glow::enemyVisibleColor, &Settings::ESP::Glow::hpEnemyVisibleColor },
			{ "Glow - LocalPlayer", &Settings::ESP::Glow::localplayerColor, &Settings::ESP::Glow::hpLocalplayerColor },
			{ "Glow - Weapon", &Settings::ESP::Glow::weaponColor, nullptr },
			{ "Glow - Grenade", &Settings::ESP::Glow::grenadeColor, nullptr },
			{ "Glow - Defuser", &Settings::ESP::Glow::defuserColor, nullptr },
			{ "Glow - Chicken", &Settings::ESP::Glow::chickenColor, nullptr },
			{ "Sky", &Settings::NoSky::color, nullptr },
			{ "Walls", &Settings::ASUSWalls::color, nullptr },
	};

	const char* colorNames[IM_ARRAYSIZE(colors)];
	for (int i = 0; i < IM_ARRAYSIZE(colors); i++)
		colorNames[i] = colors[i].name;

	static int colorSelected = 0;

	ImGui::SetNextWindowSize(ImVec2(540, 295), ImGuiSetCond_Always);
	if (ImGui::Begin("Colors", &Colors::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, NULL, true);
		{
			ImGui::PushItemWidth(-1);
			ImGui::ListBox("##COLORSELECTION", &colorSelected, colorNames, IM_ARRAYSIZE(colorNames), 11);
			ImGui::PopItemWidth();
		}
		ImGui::NextColumn();
		{
			UI::ColorPicker4((float *)colors[colorSelected].ptr);
			if (colors[colorSelected].hpPtr)
			{
				ImGui::Checkbox("Health-Based Color", colors[colorSelected].hpPtr);
				SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow");
			}
		}
		ImGui::End();
	}
}