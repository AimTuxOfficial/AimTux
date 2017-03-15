#include "colors.h"

bool Colors::showWindow = false;

void Colors::RenderWindow()
{
	if (!Colors::showWindow)
		return;

	struct ColorListVar
	{
		const char* name;
		union
		{
			ColorVar* colorVarPtr;
			HealthColorVar* healthColorVarPtr;
		};
		enum
		{
			COLORVAR_TYPE,
			HEALTHCOLORVAR_TYPE
		} type;

		ColorListVar(const char* name, ColorVar* ptr)
		{
			this->name = name;
			this->colorVarPtr = ptr;
			this->type = COLORVAR_TYPE;
		}

		ColorListVar(const char* name, HealthColorVar* ptr)
		{
			this->name = name;
			this->healthColorVarPtr = ptr;
			this->type = HEALTHCOLORVAR_TYPE;
		}
	};

	ColorListVar colors[] = {
			{ "UI Main", &Settings::UI::mainColor },
			{ "UI Body", &Settings::UI::bodyColor },
			{ "UI Font", &Settings::UI::fontColor },
			{ "FOV Circle", &Settings::ESP::FOVCrosshair::color },
			{ "Hitmarker", &Settings::ESP::Hitmarker::color },
			{ "ESP - Enemy", &Settings::ESP::enemyColor },
			{ "ESP - Team", &Settings::ESP::allyColor },
			{ "ESP - Enemy Visible", &Settings::ESP::enemyVisibleColor },
			{ "ESP - Team Visible", &Settings::ESP::allyVisibleColor },
			{ "ESP - CT", &Settings::ESP::ctColor },
			{ "ESP - T", &Settings::ESP::tColor },
			{ "ESP - CT Visible", &Settings::ESP::ctVisibleColor },
			{ "ESP - T Visible", &Settings::ESP::tVisibleColor },
			{ "ESP - LocalPlayer", &Settings::ESP::localplayerColor },
			{ "ESP - Bomb", &Settings::ESP::bombColor },
			{ "ESP - Bomb Defusing", &Settings::ESP::bombDefusingColor },
			{ "ESP - Hostage", &Settings::ESP::hostageColor },
			{ "ESP - Defuser", &Settings::ESP::defuserColor },
			{ "ESP - Weapon", &Settings::ESP::weaponColor },
			{ "ESP - Chicken", &Settings::ESP::chickenColor },
			{ "ESP - Fish", &Settings::ESP::fishColor },
			{ "ESP - Smoke", &Settings::ESP::smokeColor },
			{ "ESP - Decoy", &Settings::ESP::decoyColor },
			{ "ESP - Flashbang", &Settings::ESP::flashbangColor },
			{ "ESP - Grenade", &Settings::ESP::grenadeColor },
			{ "ESP - Molotov", &Settings::ESP::molotovColor },
			{ "ESP - Skeleton", &Settings::ESP::Skeleton::color },
			{ "Chams - Team", &Settings::ESP::Chams::allyColor },
			{ "Chams - Team Visible", &Settings::ESP::Chams::allyVisibleColor },
			{ "Chams - Enemy", &Settings::ESP::Chams::enemyColor },
			{ "Chams - Enemy Visible", &Settings::ESP::Chams::enemyVisibleColor },
			{ "Chams - LocalPlayer", &Settings::ESP::Chams::localplayerColor },
			{ "Chams - Arms", &Settings::ESP::Chams::Arms::color },
			{ "Chams - Weapon", &Settings::ESP::Chams::Weapon::color },
			{ "Grenade Helper - Aim Line", &Settings::GrenadeHelper::aimLine },
			{ "Grenade Helper - Aim Dot", &Settings::GrenadeHelper::aimDot },
			{ "Grenade Helper - HE Info", &Settings::GrenadeHelper::infoHE },
			{ "Grenade Helper - Smoke Info", &Settings::GrenadeHelper::infoSmoke },
			{ "Grenade Helper - Molotov Info", &Settings::GrenadeHelper::infoMolotov },
			{ "Grenade Helper - Flash Info", &Settings::GrenadeHelper::infoFlash },
			{ "Radar - Enemy", &Settings::Radar::enemyColor },
			{ "Radar - Team", &Settings::Radar::allyColor },
			{ "Radar - Enemy Visible", &Settings::Radar::enemyVisibleColor },
			{ "Radar - Team Visible", &Settings::Radar::allyVisibleColor },
			{ "Radar - CT", &Settings::Radar::ctColor },
			{ "Radar - T", &Settings::Radar::tColor },
			{ "Radar - CT Visible", &Settings::Radar::ctVisibleColor },
			{ "Radar - T Visible", &Settings::Radar::tVisibleColor },
			{ "Radar - Bomb", &Settings::Radar::bombColor },
			{ "Radar - Bomb Defusing", &Settings::Radar::bombDefusingColor },
			{ "Glow - Team", &Settings::ESP::Glow::allyColor },
			{ "Glow - Enemy", &Settings::ESP::Glow::enemyColor },
			{ "Glow - Enemy Visible", &Settings::ESP::Glow::enemyVisibleColor },
			{ "Glow - LocalPlayer", &Settings::ESP::Glow::localplayerColor },
			{ "Glow - Weapon", &Settings::ESP::Glow::weaponColor },
			{ "Glow - Grenade", &Settings::ESP::Glow::grenadeColor },
			{ "Glow - Defuser", &Settings::ESP::Glow::defuserColor },
			{ "Glow - Chicken", &Settings::ESP::Glow::chickenColor },
			{ "Sky", &Settings::NoSky::color },
			{ "Walls", &Settings::ASUSWalls::color },
	};

	const char* colorNames[IM_ARRAYSIZE(colors)];
	for (int i = 0; i < IM_ARRAYSIZE(colors); i++)
		colorNames[i] = colors[i].name;

	static int colorSelected = 0;

	ImGui::SetNextWindowSize(ImVec2(540, 325), ImGuiSetCond_Always);
	if (ImGui::Begin("Colors", &Colors::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, NULL, true);
		{
			ImGui::PushItemWidth(-1);
			ImGui::ListBox("##COLORSELECTION", &colorSelected, colorNames, IM_ARRAYSIZE(colorNames), 12);
			ImGui::PopItemWidth();
		}
		ImGui::NextColumn();
		{
			if (colors[colorSelected].type == ColorListVar::HEALTHCOLORVAR_TYPE)
			{
				UI::ColorPicker4((float*)colors[colorSelected].healthColorVarPtr);
				ImGui::Checkbox("Rainbow", &colors[colorSelected].healthColorVarPtr->rainbow);
				SetTooltip("Makes the color an animated rainbow.");
				ImGui::SameLine();
				ImGui::Checkbox("Health-Based", &colors[colorSelected].healthColorVarPtr->hp);
				SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow.");
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].healthColorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
				ImGui::PopItemWidth();
			}
			else
			{
				UI::ColorPicker4((float*)colors[colorSelected].colorVarPtr);
				ImGui::Checkbox("Rainbow", &colors[colorSelected].colorVarPtr->rainbow);
				SetTooltip("Makes the color an animated rainbow.");
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].colorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
				ImGui::PopItemWidth();
			}
		}
		ImGui::End();
	}
}