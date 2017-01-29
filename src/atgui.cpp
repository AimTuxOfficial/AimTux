#include "atgui.h"

bool UI::isVisible = false;

bool Settings::ScreenshotCleaner::enabled = false;

ImColor Settings::UI::mainColor = ImColor(54, 54, 54, 255);
ImColor Settings::UI::bodyColor = ImColor(24, 24, 24, 240);
ImColor Settings::UI::fontColor = ImColor(255, 255, 255, 255);
bool showMainWindow = true;
bool showSkinChangerWindow = false;
bool showConfigWindow = false;
bool showColorsWindow = false;
bool showPlayerListWindow = false;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

static char* nickname = strdup("");

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
					 static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
					   static_cast<void*>(&values), values.size(), height_in_items);
	}
}

void UI::SetVisible(bool visible)
{
	UI::isVisible = visible;
	cvar->FindVar("cl_mouseenable")->SetValue(!UI::isVisible);
}

void UI::SetupColors()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered	= ImVec4(Settings::UI::mainColor.Value.x + 0.1f, Settings::UI::mainColor.Value.y + 0.1f, Settings::UI::mainColor.Value.z + 0.1f, Settings::UI::mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.Value.x + 0.2f, Settings::UI::mainColor.Value.y + 0.2f, Settings::UI::mainColor.Value.z + 0.2f, Settings::UI::mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w + .05f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	style.Colors[ImGuiCol_Text] = Settings::UI::fontColor;
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = Settings::UI::bodyColor;
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
	style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
	style.Colors[ImGuiCol_Border] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = frameBgColor;
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
	style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = frameBgColor;
	style.Colors[ImGuiCol_CheckMark]  = Settings::UI::mainColor;
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_Header] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
	style.Colors[ImGuiCol_Column] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGrip] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_PlotHistogramHovered] =  mainColorHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
}

void SetupMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &showMainWindow, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

        if (ModSupport::current_mod != ModType::CSCO)
        {
            ImGui::Selectable("Skin Changer Window", &showSkinChangerWindow, 0, ImVec2(ImGui::CalcTextSize("Skin Changer Window", NULL, true).x, 0.0f));
            ImGui::SameLine();
        }

		ImGui::Selectable("Config Window", &showConfigWindow, 0, ImVec2(ImGui::CalcTextSize("Config Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Spectators Window", &Settings::ShowSpectators::enabled, 0, ImVec2(ImGui::CalcTextSize("Spectators Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Colors Window", &showColorsWindow, 0, ImVec2(ImGui::CalcTextSize("Colors Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Player List Window", &showPlayerListWindow, 0, ImVec2(ImGui::CalcTextSize("Player List Window", NULL, true).x, 0.0f));

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

static int current_weapon = -1;
static bool enabled = false;
static bool silent = false;
static bool friendly = false;
static int bone = BONE_HEAD;
static ButtonCode_t aimkey = ButtonCode_t::MOUSE_MIDDLE;
static bool aimkey_only = false;
static bool smoothEnabled = false;
static float smoothValue = 0.5f;
static int smoothType = SmoothType::SLOW_END;
static bool smoothSaltEnabled = false;
static float smoothSaltMultiplier = 0.0f;
static bool errorMarginEnabled = false;
static float errorMarginValue = 0.0f;
static bool autoAimEnabled = false;
static float autoAimValue = 180.0f;
static bool aimStepEnabled = false;
static float aimStepValue = 25.0f;
static bool rcsEnabled = false;
static bool rcsAlways_on = false;
static float rcsFloat = false;
static bool autoPistolEnabled = false;
static bool autoShootEnabled = false;
static bool autoScopeEnabled = false;
static bool noShootEnabled = false;
static bool ignoreJumpEnabled = false;
static bool smoke_check = false;
static bool autoWallEnabled = false;
static float autoWallValue = 10.0f;
static bool autoWallBones[] = { true, false, false, false, false, false };
static bool autoAimRealDistance;

void UI::updateWeaponSettings()
{
	Settings::Aimbot::Weapon settings =
			Settings::Aimbot::Weapon(enabled, silent, friendly, bone, aimkey, aimkey_only,
									 smoothEnabled, smoothValue, smoothType, smoothSaltEnabled, smoothSaltMultiplier,
									 errorMarginEnabled, errorMarginValue,
									 autoAimEnabled, autoAimValue, aimStepEnabled, aimStepValue,
									 rcsEnabled, rcsAlways_on, rcsFloat,
									 autoPistolEnabled, autoShootEnabled, autoScopeEnabled,
									 noShootEnabled, ignoreJumpEnabled, smoke_check, autoWallEnabled, autoWallValue, autoWallBones, autoAimRealDistance);

	Settings::Aimbot::weapons[current_weapon] = settings;
}

void reloadWeaponSettings()
{
	int index = -1;
	if (Settings::Aimbot::weapons.find(current_weapon) != Settings::Aimbot::weapons.end())
		index = current_weapon;

	enabled = Settings::Aimbot::weapons[index].enabled;
	silent = Settings::Aimbot::weapons[index].silent;
	friendly = Settings::Aimbot::weapons[index].friendly;
	bone = Settings::Aimbot::weapons[index].bone;
	aimkey = Settings::Aimbot::weapons[index].aimkey;
	aimkey_only = Settings::Aimbot::weapons[index].aimkey_only;
	smoothEnabled = Settings::Aimbot::weapons[index].smoothEnabled;
	smoothValue = Settings::Aimbot::weapons[index].smoothAmount;
	smoothType = Settings::Aimbot::weapons[index].smoothType;
	smoothSaltEnabled = Settings::Aimbot::weapons[index].smoothSaltEnabled;
	smoothSaltMultiplier = Settings::Aimbot::weapons[index].smoothSaltMultiplier;
	errorMarginEnabled = Settings::Aimbot::weapons[index].errorMarginEnabled;
	errorMarginValue = Settings::Aimbot::weapons[index].errorMarginValue;
	autoAimEnabled = Settings::Aimbot::weapons[index].autoAimEnabled;
	autoAimValue = Settings::Aimbot::weapons[index].autoAimFov;
	aimStepEnabled = Settings::Aimbot::weapons[index].aimStepEnabled;
	aimStepValue = Settings::Aimbot::weapons[index].aimStepValue;
	rcsEnabled = Settings::Aimbot::weapons[index].rcsEnabled;
	rcsAlways_on = Settings::Aimbot::weapons[index].rcsAlways_on;
	rcsFloat = Settings::Aimbot::weapons[index].rcsAmount;
	autoPistolEnabled = Settings::Aimbot::weapons[index].autoPistolEnabled;
	autoShootEnabled = Settings::Aimbot::weapons[index].autoShootEnabled;
	autoScopeEnabled = Settings::Aimbot::weapons[index].autoScopeEnabled;
	noShootEnabled = Settings::Aimbot::weapons[index].noShootEnabled;
	ignoreJumpEnabled = Settings::Aimbot::weapons[index].ignoreJumpEnabled;
	smoke_check = Settings::Aimbot::weapons[index].smoke_check;
	autoWallEnabled = Settings::Aimbot::weapons[index].autoWallEnabled;
	autoWallValue = Settings::Aimbot::weapons[index].autoWallValue;

	for (int bone = HITBOX_HEAD; bone <= HITBOX_ARMS; bone++)
		autoWallBones[bone] = Settings::Aimbot::weapons[index].autoWallBones[bone];

	autoAimRealDistance = Settings::Aimbot::weapons[index].autoAimRealDistance;
}

void ColorsWindow()
{
	if (!showColorsWindow)
		return;

	const char* colorSelection[] = {
			"UI Main",
			"UI Body",
			"UI Font",
			"FOV Circle",
			"Hitmarker",
			"ESP - Enemy",
			"ESP - Team",
			"ESP - Enemy Visible",
			"ESP - Team Visible",
			"ESP - CT",
			"ESP - T",
			"ESP - CT Visible",
			"ESP - T Visible",
			"ESP - Bomb",
			"ESP - Bomb Defusing",
			"ESP - Hostage",
			"ESP - Defuser",
			"ESP - Weapon",
			"ESP - Chicken",
			"ESP - Fish",
			"ESP - Smoke",
			"ESP - Decoy",
			"ESP - Flashbang",
			"ESP - Grenade",
			"ESP - Molotov",
			"ESP - Skeleton",
			"Chams - Team",
			"Chams - Team Visible",
			"Chams - Enemy",
			"Chams - Enemy Visible",
			"Chams - Arms",
			"Radar - Enemy",
			"Radar - Team",
			"Radar - Enemy Visible",
			"Radar - Team Visible",
			"Radar - CT",
			"Radar - T",
			"Radar - CT Visible",
			"Radar - T Visible",
			"Radar - Bomb",
			"Radar - Bomb Defusing",
			"Glow - Team",
			"Glow - Enemy",
			"Glow - Enemy Visible",
			"Glow - Weapon",
			"Glow - Grenade",
			"Glow - Defuser",
			"Glow - Chicken",
			"Sky",
			"Walls",
	};

	ImColor* colors[] = {
			&Settings::UI::mainColor,
			&Settings::UI::bodyColor,
			&Settings::UI::fontColor,
			&Settings::ESP::FOVCrosshair::color,
			&Settings::ESP::Hitmarker::color,
			&Settings::ESP::enemy_color,
			&Settings::ESP::ally_color,
			&Settings::ESP::enemy_visible_color,
			&Settings::ESP::ally_visible_color,
			&Settings::ESP::ct_color,
			&Settings::ESP::t_color,
			&Settings::ESP::ct_visible_color,
			&Settings::ESP::t_visible_color,
			&Settings::ESP::bomb_color,
			&Settings::ESP::bomb_defusing_color,
			&Settings::ESP::hostage_color,
			&Settings::ESP::defuser_color,
			&Settings::ESP::weapon_color,
			&Settings::ESP::chicken_color,
			&Settings::ESP::fish_color,
			&Settings::ESP::smoke_color,
			&Settings::ESP::decoy_color,
			&Settings::ESP::flashbang_color,
			&Settings::ESP::grenade_color,
			&Settings::ESP::molotov_color,
			&Settings::ESP::Skeleton::color,
			&Settings::ESP::Chams::ally_color,
			&Settings::ESP::Chams::ally_visible_color,
			&Settings::ESP::Chams::enemy_color,
			&Settings::ESP::Chams::enemy_visible_color,
			&Settings::ESP::Chams::Arms::color,
			&Settings::Radar::enemy_color,
			&Settings::Radar::ally_color,
			&Settings::Radar::enemy_visible_color,
			&Settings::Radar::ally_visible_color,
			&Settings::Radar::ct_color,
			&Settings::Radar::t_color,
			&Settings::Radar::ct_visible_color,
			&Settings::Radar::t_visible_color,
			&Settings::Radar::bomb_color,
			&Settings::Radar::bomb_defusing_color,
			&Settings::ESP::Glow::ally_color,
			&Settings::ESP::Glow::enemy_color,
			&Settings::ESP::Glow::enemy_visible_color,
			&Settings::ESP::Glow::weapon_color,
			&Settings::ESP::Glow::grenade_color,
			&Settings::ESP::Glow::defuser_color,
			&Settings::ESP::Glow::chicken_color,
			&Settings::NoSky::color,
			&Settings::ASUSWalls::color,
	};

	bool* healthColor[] = {
			nullptr, // UI Main
			nullptr, // UI Body
			nullptr, // UI Font
			nullptr, // FOV Circle
			nullptr, // Hitmarker
			&Settings::ESP::hp_enemy_color, // ESP - Enemy
			&Settings::ESP::hp_ally_color, // ESP - Team
			&Settings::ESP::hp_enemy_visible_color, // ESP - Enemy Visible
			&Settings::ESP::hp_ally_visible_color, // ESP - Team Visible
			&Settings::ESP::hp_ct_color, // ESP - CT
			&Settings::ESP::hp_t_color, // ESP - T
			&Settings::ESP::hp_ct_visible_color, // ESP - CT Visible
			&Settings::ESP::hp_t_visible_color, // ESP - T Visible
			nullptr, // ESP - Bomb
			nullptr, // ESP - Bomb Defusing
			nullptr, // ESP - Hostage
			nullptr, // ESP - Defuser
			nullptr, // ESP - Weapon
			nullptr, // ESP - Chicken
			nullptr, // ESP - Fish
			nullptr, // ESP - Smoke
			nullptr, // ESP - Decoy
			nullptr, // ESP - Flashbang
			nullptr, // ESP - Grenade
			nullptr, // ESP - Molotov
			nullptr, // ESP - Skeleton
			&Settings::ESP::Chams::hp_ally_color, // Chams - Team
			&Settings::ESP::Chams::hp_ally_visible_color, // Chams - Team Visible
			&Settings::ESP::Chams::hp_enemy_color, // Chams - Enemy
			&Settings::ESP::Chams::hp_enemy_visible_color, // Chams - Enemy Visible
			nullptr, // Chams - Arms
			&Settings::Radar::hp_enemy_color, // Radar - Enemy
			&Settings::Radar::hp_ally_color, // Radar - Team
			&Settings::Radar::hp_enemy_visible_color, // Radar - Enemy Visible
			&Settings::Radar::hp_ally_visible_color, // Radar - Team Visible
			&Settings::Radar::hp_ct_color, // Radar - CT
			&Settings::Radar::hp_t_color, // Radar - T
			&Settings::Radar::hp_ct_visible_color, // Radar - CT Visible
			&Settings::Radar::hp_t_visible_color, // Radar - T Visible
			nullptr, // Radar - Bomb
			nullptr, // Radar - Bomb Defusing
			&Settings::ESP::Glow::hp_ally_color, // Glow - Team
			&Settings::ESP::Glow::hp_enemy_color, // Glow - Enemy
			&Settings::ESP::Glow::hp_enemy_visible_color, // Glow - Enemy Visible
			nullptr, // Glow - Weapon
			nullptr, // Glow - Grenade
			nullptr, // Glow - Defuser
			nullptr, // Glow - Chicken
			nullptr, // Sky
			nullptr, // Walls
	};

	static int colorSelected = 0;

	ImGui::SetNextWindowSize(ImVec2(540, 295), ImGuiSetCond_Always);
	if (ImGui::Begin("Colors", &showColorsWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, NULL, true);
		{
			ImGui::PushItemWidth(-1);
				ImGui::ListBox("##COLORSELECTION", &colorSelected, colorSelection, IM_ARRAYSIZE(colorSelection), 11);
			ImGui::PopItemWidth();
		}
		ImGui::NextColumn();
		{
			UI::ColorPicker4((float *)colors[colorSelected]);
			if (healthColor[colorSelected])
			{
				ImGui::Checkbox("Health-Based Color", healthColor[colorSelected]);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow");
			}
		}
		ImGui::End();
	}
}

void AimbotTab()
{
	const char* targets[] = { "PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };
	const char* smoothTypes[] = { "Slow Near End", "Constant Speed" };
	static char filterWeapons[32];

	if (ImGui::Checkbox("Enabled", &enabled))
		UI::updateWeaponSettings();
	ImGui::Separator();

	ImGui::Columns(3, NULL, true);
	{
		ImGui::SetColumnOffset(1, 200);
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##FILTERWEAPONS", filterWeapons, IM_ARRAYSIZE(filterWeapons));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##GUNS", ImVec2(-1, -1));
			for (auto it : guns)
			{
				bool isDefault = it.first < 0;
				if (!isDefault && !Util::Contains(Util::ToLower(std::string(filterWeapons)), Util::ToLower(std::string(it.second))))
					continue;

				const bool item_selected = (it.first == current_weapon);
				ImGui::PushID(it.first);

					char* formattedName;
					char changeIndicator = ' ';
					bool isChanged = Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end();
					if (!isDefault && isChanged)
						changeIndicator = '*';
					asprintf(&formattedName, "%c %s", changeIndicator, it.second);

					if (ImGui::Selectable(formattedName, item_selected))
					{
						current_weapon = it.first;

						int index = -1;
						if (Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end())
							index = it.first;

						enabled = Settings::Aimbot::weapons[index].enabled;
						silent = Settings::Aimbot::weapons[index].silent;
						friendly = Settings::Aimbot::weapons[index].friendly;
						bone = Settings::Aimbot::weapons[index].bone;
						aimkey = Settings::Aimbot::weapons[index].aimkey;
						aimkey_only = Settings::Aimbot::weapons[index].aimkey_only;
						smoothEnabled = Settings::Aimbot::weapons[index].smoothEnabled;
						smoothValue = Settings::Aimbot::weapons[index].smoothAmount;
						smoothType = Settings::Aimbot::weapons[index].smoothType;
						smoothSaltEnabled = Settings::Aimbot::weapons[index].smoothSaltEnabled;
						smoothSaltMultiplier = Settings::Aimbot::weapons[index].smoothSaltMultiplier;
						errorMarginEnabled = Settings::Aimbot::weapons[index].errorMarginEnabled;
						errorMarginValue = Settings::Aimbot::weapons[index].errorMarginValue;
						autoAimEnabled = Settings::Aimbot::weapons[index].autoAimEnabled;
						autoAimValue = Settings::Aimbot::weapons[index].autoAimFov;
						aimStepEnabled = Settings::Aimbot::weapons[index].aimStepEnabled;
						aimStepValue = Settings::Aimbot::weapons[index].aimStepValue;
						rcsEnabled = Settings::Aimbot::weapons[index].rcsEnabled;
						rcsAlways_on = Settings::Aimbot::weapons[index].rcsAlways_on;
						rcsFloat = Settings::Aimbot::weapons[index].rcsAmount;
						autoPistolEnabled = Settings::Aimbot::weapons[index].autoPistolEnabled;
						autoShootEnabled = Settings::Aimbot::weapons[index].autoShootEnabled;
						autoScopeEnabled = Settings::Aimbot::weapons[index].autoScopeEnabled;
						noShootEnabled = Settings::Aimbot::weapons[index].noShootEnabled;
						ignoreJumpEnabled = Settings::Aimbot::weapons[index].ignoreJumpEnabled;
						smoke_check = Settings::Aimbot::weapons[index].smoke_check;
						autoWallEnabled = Settings::Aimbot::weapons[index].autoWallEnabled;
						autoWallValue = Settings::Aimbot::weapons[index].autoWallValue;

						for (int bone = HITBOX_HEAD; bone <= HITBOX_ARMS; bone++)
							autoWallBones[bone] = Settings::Aimbot::weapons[index].autoWallBones[bone];

						autoAimRealDistance = Settings::Aimbot::weapons[index].autoAimRealDistance;
					}
				ImGui::PopID();
			}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::SetColumnOffset(2, ImGui::GetWindowWidth() / 2 + 75);
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Friendly", &friendly))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Whether to target friendlies");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##AIMTARGET", &bone, targets, IM_ARRAYSIZE(targets)))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Accuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Auto Aim", &autoAimEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Locks onto enemies within a certain FOV amount");
				if (ImGui::Checkbox("Recoil Control", &rcsEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Automatically controls recoil");
				if (ImGui::Checkbox("RCS Always on", &rcsAlways_on))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Whether Recoil Control always controls recoil (even when not aimbotting)");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##AA", &autoAimValue, 0, 180))
						UI::updateWeaponSettings();
					if (ImGui::SliderFloat("##RCS", &rcsFloat, 0, 2))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
				if (ImGui::Checkbox("Distance-Based FOV", &autoAimRealDistance))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Takes perspective into account when calculating FOV");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Humanizing");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Smoothing", &smoothEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Smoothing reduces the aimbot \"snap\". 0 for full snap. 1 for full smoothing");
				if (ImGui::Checkbox("Smooth Salting", &smoothSaltEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Breaks the smoothing into smaller steps, high smooth + low salt is slightly stuttery");
				if (ImGui::Checkbox("Error Margin", &errorMarginEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Adds a margin of error to the aim, it will be obvious what it does when using it");
				ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##SMOOTHTYPE", &smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##SMOOTH", &smoothValue, 0, 1))
						UI::updateWeaponSettings();
					if (ImGui::SliderFloat("##SALT", &smoothSaltMultiplier, 0, smoothValue))
						UI::updateWeaponSettings();
					if (ImGui::SliderFloat("##ERROR", &errorMarginValue, 0, 2))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL2", ImVec2(0, 0), true);
		{
			ImGui::Text("Aimkey Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled", &aimkey_only))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Enabling this means it you need to press a specific key to aimlock");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&aimkey);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Casual / DM Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Aim Step", &aimStepEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Stops you getting VAC auth kicked in Casual / DM");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##STEP", &aimStepValue, 0, 100))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				switch (current_weapon)
				{
					case -1:
					case WEAPON_DEAGLE:
					case WEAPON_ELITE:
					case WEAPON_FIVESEVEN:
					case WEAPON_GLOCK:
					case WEAPON_TEC9:
					case WEAPON_HKP2000:
					case WEAPON_USP_SILENCER:
					case WEAPON_P250:
					case WEAPON_CZ75A:
					case WEAPON_REVOLVER:
						if (ImGui::Checkbox("Auto Pistol", &autoPistolEnabled))
							UI::updateWeaponSettings();
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Automatically shoots the pistol when holding fire");
						break;
				}

				if (ImGui::Checkbox("Auto Shoot", &autoShootEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Automatically shoots when locking to an enemy");
				if (ImGui::Checkbox("Silent Aim", &silent))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Prevents the camera from locking to an enemy, doesn't work for demos");
				if (ImGui::Checkbox("Smoke Check", &smoke_check))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Ignore players that are in smoke");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("No Shoot", &noShootEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Stops you shooting when locking to an enemy");
				if (ImGui::Checkbox("Auto Scope", &autoScopeEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Automatically scopes weapons that have them");
				if (ImGui::Checkbox("Ignore Jump", &ignoreJumpEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Prevents you from aimbotting while jumping");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled##AUTOWALL", &autoWallEnabled))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shoots enemy through a wall if it does X amount of damage");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##AUTOWALLDMG", &autoWallValue, 0, 100, "Min Damage: %f"))
						UI::updateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Head", &autoWallBones[HITBOX_HEAD]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on head");
				if (ImGui::Checkbox("Neck", &autoWallBones[HITBOX_NECK]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on neck");
				if (ImGui::Checkbox("Pelvis", &autoWallBones[HITBOX_PELVIS]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on pelvis");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("Spine", &autoWallBones[HITBOX_SPINE]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on spine");
				if (ImGui::Checkbox("Legs", &autoWallBones[HITBOX_LEGS]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on legs");
				if (ImGui::Checkbox("Arms", &autoWallBones[HITBOX_ARMS]))
					UI::updateWeaponSettings();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on arms");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			if (current_weapon > -1 && Settings::Aimbot::weapons.find(current_weapon) != Settings::Aimbot::weapons.end())
				if (ImGui::Button("Clear Weapon Settings", ImVec2(-1, 0)))
					Settings::Aimbot::weapons.erase(current_weapon);
			ImGui::EndChild();
		}
	}
}

void TriggerbotTab()
{
	ImGui::Checkbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("TRIG1", ImVec2(0, 0), true);
		{
			ImGui::Text("Keybind");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Trigger Key");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::Triggerbot::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Delay");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Triggerbot::Delay::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Adds a delay to the Triggerbot");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("TRIG2", ImVec2(0, 0), true);
		{
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::Triggerbot::Filters::enemies);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on enemies");
				ImGui::Checkbox("Walls", &Settings::Triggerbot::Filters::walls);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger through walls");
				ImGui::Checkbox("Head", &Settings::Triggerbot::Filters::head);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on head");
				ImGui::Checkbox("Chest", &Settings::Triggerbot::Filters::chest);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on chest");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::Triggerbot::Filters::allies);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on allies");
				ImGui::Checkbox("Smoke check", &Settings::Triggerbot::Filters::smoke_check);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Don't shoot through smokes");
				ImGui::Checkbox("Stomach", &Settings::Triggerbot::Filters::stomach);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on stomach");
				ImGui::Checkbox("Arms", &Settings::Triggerbot::Filters::arms);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on arms");
				ImGui::Checkbox("Legs", &Settings::Triggerbot::Filters::legs);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Trigger on legs");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}

void VisualsTab()
{
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Rainbow", "Wireframe", "None" };

	ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("ESP");
			ImGui::BeginChild("ESP", ImVec2(0, 0), true);
				ImGui::Text("Type");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Outline Box", &Settings::ESP::Boxes::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Outline players with a box");
					ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Change players' model texture");
					ImGui::Checkbox("Health", &Settings::ESP::Bars::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show a players health with a bar");
					ImGui::Checkbox("Tracers", &Settings::ESP::Tracers::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Draws a line to each player");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Bar Color");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Team Color");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Checkbox("Bullet Tracers", &Settings::ESP::BulletTracers::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Adds a line showing where a player is aiming");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						ImGui::Combo("##BOXTYPE", &Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
						ImGui::Combo("##CHAMSTYPE", &Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
						ImGui::Combo("##BARTYPE", &Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
						ImGui::Combo("##TRACERTYPE", &Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
						ImGui::Combo("##BARCOLTYPE", &Settings::ESP::Bars::color_type, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
						ImGui::Combo("##TEAMCOLTYPE", &Settings::ESP::team_color_type, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
					ImGui::PopItemWidth();
					ImGui::Checkbox("Skeleton", &Settings::ESP::Skeleton::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show a players skeleton");
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Filter");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show enemies");
					ImGui::Checkbox("Chickens", &Settings::ESP::Filters::chickens);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show chickens");
					ImGui::Checkbox("Legit Mode", &Settings::ESP::Filters::legit);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Hide enemies behind walls");
					ImGui::Checkbox("Smoke Check", &Settings::ESP::Filters::smoke_check);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Mark players behind smokes as invisible");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show team mates");
					ImGui::Checkbox("Fish", &Settings::ESP::Filters::fishes);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show fish");
					ImGui::Checkbox("Visiblity Check", &Settings::ESP::Filters::visibility_check);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Change color of outlined box based on whether you see them");
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Player Information");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Clan", &Settings::ESP::Info::clan);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show clan");
					ImGui::Checkbox("Rank", &Settings::ESP::Info::rank);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show rank");
					ImGui::PushID(1);
						ImGui::Checkbox("Health", &Settings::ESP::Info::health);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Show health");
					ImGui::PopID();
					ImGui::Checkbox("Scoped", &Settings::ESP::Info::scoped);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are scoped");
					ImGui::Checkbox("Flashed", &Settings::ESP::Info::flashed);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are flashed");
					ImGui::Checkbox("Defuse Kit", &Settings::ESP::Info::has_defuser);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they have a defuse kit");
					ImGui::Checkbox("Grabbing Hostage", &Settings::ESP::Info::grabbing_hostage);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are grabbing a hostage");
					ImGui::Checkbox("Location", &Settings::ESP::Info::location);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show location");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Name", &Settings::ESP::Info::name);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show name");
					ImGui::Checkbox("Steam ID", &Settings::ESP::Info::steam_id);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show Steam ID");
					ImGui::Checkbox("Weapon", &Settings::ESP::Info::weapon);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show held weapon");
					ImGui::Checkbox("Reloading", &Settings::ESP::Info::reloading);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are reloading");
					ImGui::Checkbox("Planting", &Settings::ESP::Info::planting);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are planting");
					ImGui::Checkbox("Defusing", &Settings::ESP::Info::defusing);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are defusing");
					ImGui::Checkbox("Rescuing Hostage", &Settings::ESP::Info::rescuing);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show whether they are rescuing a hostage");
				}

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("World");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Weapons", &Settings::ESP::Filters::weapons);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show weapons on floor");
					ImGui::Checkbox("Throwables", &Settings::ESP::Filters::throwables);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show throwables");
					ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show a glow around entities");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Bomb", &Settings::ESP::Filters::bomb);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show bomb when planted");
					ImGui::Checkbox("Defuse Kits", &Settings::ESP::Filters::defusers);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show defuse kits on floor");
					ImGui::Checkbox("Hostages", &Settings::ESP::Filters::hostages);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Show hostages");
				}
				ImGui::Columns(1);
				ImGui::EndChild();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		ImGui::BeginChild("Chams", ImVec2(0, 0), true);
		{
			ImGui::Text("Crosshair");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Show a crosshair based on recoil");
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Show circle around aimbot FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only show recoil crosshair when shooting");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Apply chams to arms");
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Adds a light source to players");
				ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Hide flashbang effect");
				ImGui::Checkbox("Show Footsteps", &Settings::ESP::Sounds::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shows you footsteps in 3D space");
				ImGui::Checkbox("No View Punch", &Settings::View::NoViewPunch::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Disables view punch when shooting");
				ImGui::Checkbox("No Sky", &Settings::NoSky::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Allows for the skybox to be colored or disabled");
				ImGui::Checkbox("No Smoke", &Settings::NoSmoke::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Disables smoke rendering");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##ARMSTYPE", &Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
					ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000, "Radius: %0.f");
					ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255, "Amount: %0.f");
					ImGui::SliderInt("##SOUNDSTIME", &Settings::ESP::Sounds::time, 250, 5000), "Timeout: %0.f";
				ImGui::PopItemWidth();
				ImGui::Checkbox("No Aim Punch", &Settings::View::NoAimPunch::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Disables aim punch when shooting");
				ImGui::Checkbox("No Scope Border", &Settings::NoScopeBorder::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Disables black scope silhouette");
				ImGui::Checkbox("ASUS Walls", &Settings::ASUSWalls::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Makes wall textures transparent");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Radar");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shows players on the custom radar");
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##RADARTEAMCOLTYPE", &Settings::Radar::team_color_type, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Enemies", &Settings::Radar::enemies);
				ImGui::Checkbox("Bomb", &Settings::Radar::bomb);
				ImGui::Checkbox("Legit", &Settings::Radar::legit);
				ImGui::Checkbox("In-game Radar", &Settings::Radar::InGame::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shows players on the in-game radar");

			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##RADARZOOM", &Settings::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
					ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Radar::icons_scale, 2, 16, "Icons Scale: %0.1f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Allies", &Settings::Radar::allies);
				ImGui::Checkbox("Defuser", &Settings::Radar::defuser);
				ImGui::Checkbox("Visibility Check", &Settings::Radar::visibility_check);
				ImGui::Checkbox("Smoke Check", &Settings::Radar::smoke_check);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text("Hitmarkers");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Hitmarkers", &Settings::ESP::Hitmarker::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Notify when you hit another player");

				ImGui::Checkbox("Enemies##HITMARKERS", &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox("Allies##HITMARKERS", &Settings::ESP::Hitmarker::allies);
				ImGui::Checkbox("Damage##HITMARKERS", &Settings::ESP::Hitmarker::Damage::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Show dealt damage next to the hitmarker");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##HITMARKERDUR", &Settings::ESP::Hitmarker::duration, 250, 3000, "Timeout: %0.f");
					ImGui::SliderInt("##HITMARKERSIZE", &Settings::ESP::Hitmarker::size, 1, 32, "Size: %0.f");
					ImGui::SliderInt("##HITMARKERGAP", &Settings::ESP::Hitmarker::inner_gap, 1, 16, "Gap: %0.f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}

void HvHTab()
{
	const char* YTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", // safe
			"LISP", "LISP SIDE", "LISP JITTER", "ANGEL BACKWARDS", "ANGEL INVERSE", "ANGEL SPIN" // untrusted
	};

	const char* XTypes[] = {
			"UP", "DOWN", "DANCE", "FRONT", // safe
			"FAKE UP", "FAKE DOWN", "LISP DOWN", "ANGEL DOWN", "ANGEL UP" // untrusted
	};

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("HVH1", ImVec2(0, 0), true);
		{
			ImGui::Text("AntiAim");
			ImGui::BeginChild("##ANTIAIM", ImVec2(0, ImGui::GetWindowSize().y / 2 + 32), true);
			{
				ImGui::Checkbox("Yaw", &Settings::AntiAim::Yaw::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Enables Yaw AntiAim");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Yaw Fake");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Yaw Actual");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						if (ImGui::Combo("##YFAKETYPE", &Settings::AntiAim::Yaw::type_fake, YTypes, IM_ARRAYSIZE(YTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::type_fake >= AntiAimType_Y::LISP)
							{
								Settings::AntiAim::Yaw::type_fake = SPIN_SLOW;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}

						if (ImGui::Combo("##YACTUALTYPE", &Settings::AntiAim::Yaw::type, YTypes, IM_ARRAYSIZE(YTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
							{
								Settings::AntiAim::Yaw::type = SPIN_SLOW;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Checkbox("Pitch", &Settings::AntiAim::Pitch::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Enables Pitch AntiAim");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Pitch Actual");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						if (ImGui::Combo("##XTYPE", &Settings::AntiAim::Pitch::type, XTypes, IM_ARRAYSIZE(XTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
							{
								Settings::AntiAim::Pitch::type = STATIC_UP;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Disable");
				ImGui::Separator();
				ImGui::Checkbox("Knife", &Settings::AntiAim::AutoDisable::knife_held);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Stops your antiaim while you have your knife out.");
				ImGui::NextColumn();

				ImGui::Checkbox("No Enemy", &Settings::AntiAim::AutoDisable::no_enemy);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Stops your antiaim when there are no enemies visible.");

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Edging");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enabled", &Settings::AntiAim::HeadEdge::enabled);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Aims your head into the closest wall");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						ImGui::SliderFloat("##EDGEDISTANCE", &Settings::AntiAim::HeadEdge::distance, 10, 30, "Distance: %0.f");
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
					if (ImGui::BeginPopupModal("Error###UNTRUSTED_AA"))
					{
						ImGui::Text("You cannot use this antiaim type on a VALVE server.");

						ImGui::Checkbox("This is not a VALVE server", &ValveDSCheck::forceUT);

						if (ImGui::Button("OK"))
							ImGui::CloseCurrentPopup();

						ImGui::EndPopup();
					}
				ImGui::PopStyleVar();

				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("HVH2", ImVec2(0, 0), true);
		{
			ImGui::Text("Resolver");
			ImGui::Separator();
			ImGui::Checkbox("Resolve All", &Settings::Resolver::resolve_all);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Resolves all players on the server");
			ImGui::Separator();
			ImGui::Text("Movement");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Crouch", &Settings::Aimbot::AutoCrouch::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Auto crouch when an enemy is in sight");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Auto Stop", &Settings::Aimbot::AutoStop::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Auto stop when an enemy is in sight");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}

void MiscTab()
{
	const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right", "Rage" };
	const char* animationTypes[] = { "Static", "Marquee", "Words", "Letters" };
	const char* spammerTypes[] = { "None", "Normal", "Positions" };
	const char* teams[] = { "Allies", "Enemies", "Both" };

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("Child1", ImVec2(0, 0), true);
		{
			ImGui::Text("Movement");
			ImGui::Separator();

			ImGui::Checkbox("Bunny Hop", &Settings::BHop::enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Auto bunny hop");
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Edge Jump", &Settings::EdgeJump::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Jumps off the edges");
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
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Auto strafe when bunny hopping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##STRAFETYPE", &Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
				ImGui::PopItemWidth();
			}

			if (Settings::AutoStrafe::type == AS_RAGE)
			{
				ImGui::Checkbox("Silent", &Settings::AutoStrafe::silent);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Strafes won't be visible for spectators");
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Spammer");
			ImGui::Separator();

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Checkbox("Kill Messages", &Settings::Spammer::KillSpammer::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Spams a kill message when killing an enemy");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM1", &Settings::Spammer::KillSpammer::say_team);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only show kill message in team chat");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Options###KILL"))
					ImGui::OpenPopup("options_kill");

				ImGui::SetNextWindowSize(ImVec2(565, 40), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("options_kill"))
				{
					ImGui::PushItemWidth(550);
						ImGui::InputText("", Settings::Spammer::KillSpammer::message, 127);
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}

			ImGui::Columns(1);
			ImGui::Checkbox("Radio Commands", &Settings::Spammer::RadioSpammer::enabled);

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Combo("###SPAMMERYPE", &Settings::Spammer::type, spammerTypes, IM_ARRAYSIZE(spammerTypes));
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM2", &Settings::Spammer::say_team);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only spam messages in team chat");
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
						ImGui::Checkbox("Show Name", &Settings::Spammer::PositionSpammer::show_name);
						ImGui::Checkbox("Show Weapon", &Settings::Spammer::PositionSpammer::show_weapon);
						ImGui::Checkbox("Show Rank", &Settings::Spammer::PositionSpammer::show_rank);
						ImGui::Checkbox("Show Wins", &Settings::Spammer::PositionSpammer::show_wins);
						ImGui::Checkbox("Show Health", &Settings::Spammer::PositionSpammer::show_health);
						ImGui::Checkbox("Show Money", &Settings::Spammer::PositionSpammer::show_money);
						ImGui::Checkbox("Show Last Place", &Settings::Spammer::PositionSpammer::show_lastplace);
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
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Change camera FOV");
				ImGui::Checkbox("Viewmodel FOV", &Settings::FOVChanger::viewmodel_enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Change viewmodel FOV");
				ImGui::Checkbox("Ignore Scope", &Settings::FOVChanger::ignore_scope);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Disable FOV Changer while scoping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
					ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodel_value, 0, 360);
				ImGui::PopItemWidth();
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
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Display a custom clantag");
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
					if (ImGui::Combo("##ANIMATIONTYPE", &Settings::ClanTagChanger::type, animationTypes, IM_ARRAYSIZE(animationTypes)))
						ClanTagChanger::UpdateClanTagCallback();
					if (ImGui::SliderInt("##ANIMATIONSPEED", &Settings::ClanTagChanger::animation_speed, 0, 2000))
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
				NameChanger::SetName(strdup(nickname));

			if (ImGui::Button("Glitch Name"))
				NameChanger::SetName("\n\xAD\xAD\xAD");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Allows you to change your name an infinite amount of times and doesn't show in server message");
			ImGui::SameLine();
			if (ImGui::Button("No Name"))
			{
				NameChanger::changes = 0;
				NameChanger::type = NC_NORMAL;
			}

			ImGui::SameLine();
			if (ImGui::Button("Rainbow Name"))
			{
				NameChanger::changes = 0;
				NameChanger::origName = NameChanger::GetName();
				NameChanger::type = NC_RAINBOW;
			}

			ImGui::SameLine();
			if (ImGui::Button("Solid Red Name"))
			{
				NameChanger::changes = 0;
				NameChanger::origName = NameChanger::GetName();
				NameChanger::type = NC_SOLID;
			}

			ImGui::Checkbox("Name Stealer", &Settings::NameStealer::enabled);
			ImGui::SameLine();
			ImGui::Combo("", &Settings::NameStealer::team, teams, IM_ARRAYSIZE(teams));

			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Fake Lag", &Settings::FakeLag::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Chokes packets so it appears you're lagging");
				ImGui::Checkbox("Adaptive Fake Lag", &Settings::FakeLag::adaptive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Uses dynamic choke value based on your velocity");
				ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Auto accept games when in MM queue");
				ImGui::Checkbox("AirStuck", &Settings::Airstuck::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Stops tickrate so you freeze in place");
				ImGui::Checkbox("Autoblock", &Settings::Autoblock::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Allows you to block players from moving forwards by standing in front of them and mirroring their moves - great for griefing");
				if (ImGui::Checkbox("Teleport", &Settings::Teleport::enabled))
				{
					if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::Teleport::enabled)
					{
						Settings::Teleport::enabled = false;
						ImGui::OpenPopup("Error###UNTRUSTED_FEATURE");
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Teleport to (0, 0) on any map");
				ImGui::Checkbox("Auto Defuse", &Settings::AutoDefuse::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Will automatically defuse the bomb with 0.5 seconds remaining - starts at 5.5 seconds until explosion with kit and 10.5 without");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16, "Amount: %0.f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Show Ranks", &Settings::ShowRanks::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Displays competitive rank of all players in the scoreboard next to their name during a competitive match");
				ImGui::Checkbox("Screenshot Cleaner", &Settings::ScreenshotCleaner::enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Prevents AimTux visuals from appearing in screenshots taken");
				UI::KeyBindButton(&Settings::Airstuck::key);
				UI::KeyBindButton(&Settings::Autoblock::key);
				UI::KeyBindButton(&Settings::Teleport::key);
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

void MainWindow()
{
	if (!showMainWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("AimTux", &showMainWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] = {
				"Aimbot",
				"Triggerbot",
				"Visuals",
				"HvH",
				"Misc",
		};
		int tabs_size = sizeof(tabs) / sizeof(tabs[0]);

		for (int i = 0; i < tabs_size; i++)
		{
			ImVec2 windowSize = ImGui::GetWindowSize();
			int width = windowSize.x / tabs_size - 9;

			int distance;
			if (i == page)
				distance = 0;
			else
				distance = i > page ? i - page : page - i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					Settings::UI::mainColor.Value.x - (distance * 0.035f),
					Settings::UI::mainColor.Value.y - (distance * 0.035f),
					Settings::UI::mainColor.Value.z - (distance * 0.035f),
					Settings::UI::mainColor.Value.w
			);

			if (ImGui::Button(tabs[i], ImVec2(width, 0)))
				page = i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor;

			if (i < tabs_size - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch (page)
		{
			case 0:
				AimbotTab();
				break;
			case 1:
				TriggerbotTab();
				break;
			case 2:
				VisualsTab();
				break;
			case 3:
				HvHTab();
				break;
			case 4:
				MiscTab();
				break;
		}

		ImGui::End();
	}
}

void SkinChangerWindow()
{
	if (!showSkinChangerWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(640, 695), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin Changer", &showSkinChangerWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		static int current_weapon = 7;
		static int current_weapon_skin = Settings::Skinchanger::skins[current_weapon].PaintKit;
		static float weaponWear = 0.005f;
		static int weaponSkinSeed = -1;
		static int weaponStatTrak = -1;
		static char weaponName[18];
		static char filterSkins[32];
		static char filterGuns[32];
		static int isCT = 1;

		if (ImGui::Checkbox("Enabled", &Settings::Skinchanger::enabled))
			SkinChanger::ForceFullUpdate = true;

		ImGui::Separator();

		ImGui::Columns(2);
		ImGui::Text("Guns"); ImGui::NextColumn();
		ImGui::Text("Skins");
		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::Columns(2, NULL, false);
			ImGui::PushItemWidth(-1);
				ImGui::InputText("##FilterGuns", filterGuns, IM_ARRAYSIZE(filterGuns));
				ImGui::ListBoxHeader("##GUNS", ImVec2(0, 300));
					for (auto it : guns)
					{
						if (strcmp(it.second, "<-Default->") == 0)
							continue;
						if (!Util::Contains(Util::ToLower(std::string(filterGuns)), Util::ToLower(std::string(it.second))))
							continue;
						const bool item_selected = (it.first == current_weapon);
						ImGui::PushID(it.first);
							if (ImGui::Selectable(it.second, item_selected))
							{
								current_weapon = it.first;

								auto keyExists = Settings::Skinchanger::skins.find(it.first);
								if (keyExists == Settings::Skinchanger::skins.end())
									current_weapon_skin = -1;
								else
									current_weapon_skin = Settings::Skinchanger::skins[it.first].PaintKit;
							}
						ImGui::PopID();
					}
				ImGui::ListBoxFooter();
			ImGui::PopItemWidth();
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##FilterSkins", filterSkins, IM_ARRAYSIZE(filterSkins));
			ImGui::ListBoxHeader("##SKINS", ImVec2(0, 300));
				for (auto it : weapon_skins)
				{
					if (!Util::Contains(Util::ToLower(std::string(filterSkins)), Util::ToLower(std::string(it.second))))
						continue;
					const bool item_selected = (it.first == current_weapon_skin);
					ImGui::PushID(it.first);
						if (ImGui::Selectable(it.second, item_selected))
							current_weapon_skin = it.first;
					ImGui::PopID();
				}
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::Columns(2, NULL, true);
		ImGui::Text("Knife"); ImGui::NextColumn();
		ImGui::Text("Other");
		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::Columns(3, NULL, false);
		ImGui::SetColumnOffset(1, ImGui::GetWindowWidth() / 2 - 60);
			ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
				for (auto knife : knives)
				{
					const bool item_selected = ((WEAPON_KNIFE_BAYONET + knife.first) == current_weapon);
					ImGui::PushID(knife.first);
					if (ImGui::Selectable(knife.second, item_selected))
					{
						current_weapon = (WEAPON_KNIFE_BAYONET + knife.first);
						current_weapon_skin = Settings::Skinchanger::skins[isCT > 0 ? WEAPON_KNIFE : WEAPON_KNIFE_T].PaintKit;
					}
					ImGui::PopID();
				}
			ImGui::ListBoxFooter();
		ImGui::NextColumn();
		ImGui::SetColumnOffset(2, ImGui::GetWindowWidth() / 2 - 4);
			ImGui::RadioButton("CT", &isCT, 1);
			ImGui::RadioButton("T", &isCT, 0);
		ImGui::NextColumn();
		ImGui::BeginChild("Other", ImVec2(-1, -1), true);
		{
			ImGui::InputInt("Skin ID", &current_weapon_skin);
			ImGui::SliderFloat("Wear", &weaponWear, 0.005f, 1.0f);
			ImGui::InputInt("Seed", &weaponSkinSeed);
			ImGui::InputInt("StatTrak", &weaponStatTrak);
			ImGui::InputText("Name", weaponName, IM_ARRAYSIZE(weaponName));
			ImGui::Separator();
			if (ImGui::Button("Load", ImVec2(-1, 0)))
			{
				Settings::Skinchanger::Skin skin;
				if (current_weapon >= WEAPON_KNIFE_BAYONET)
				{
					skin = Settings::Skinchanger::skins[isCT == 1 ? WEAPON_KNIFE : WEAPON_KNIFE_T];
					current_weapon = skin.ItemDefinitionIndex;
				}
				else
				{
					auto keyExists = Settings::Skinchanger::skins.find(current_weapon);
					if (keyExists == Settings::Skinchanger::skins.end())
						skin = Settings::Skinchanger::Skin(current_weapon, -1, -1, -1, -1, "", "");
					else
						skin = Settings::Skinchanger::skins[current_weapon];
				}

				current_weapon_skin = skin.PaintKit;
				weaponSkinSeed = skin.Seed;
				weaponWear = skin.Wear;
				weaponStatTrak = skin.StatTrak;
				std::fill(std::begin(weaponName), std::end(weaponName), 0);
				std::copy(std::begin(skin.CustomName), std::end(skin.CustomName), std::begin(weaponName));
			}
			if (ImGui::Button("Apply", ImVec2(-1, 0)))
			{
				if (current_weapon >= WEAPON_KNIFE_BAYONET)
				{
					Settings::Skinchanger::skins[WEAPON_KNIFE_FLIP] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_flip.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_GUT] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_gut.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_BAYONET] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_bayonet.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_M9_BAYONET] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_m9_bay.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_KARAMBIT] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_karam.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_TACTICAL] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_tactical.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_BUTTERFLY] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_butterfly.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_SURVIVAL_BOWIE] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_survival_bowie.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_FALCHION] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_falchion_advanced.mdl");
					Settings::Skinchanger::skins[WEAPON_KNIFE_PUSH] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_push.mdl");

					Settings::Skinchanger::skins[isCT > 0 ? WEAPON_KNIFE : WEAPON_KNIFE_T] = Settings::Skinchanger::Skin(
							current_weapon_skin == 0 ? -1 : current_weapon_skin,
							current_weapon,
							weaponSkinSeed,
							weaponWear,
							weaponStatTrak,
							weaponName,
							""
					);
				}
				else
				{
					Settings::Skinchanger::skins[current_weapon] = Settings::Skinchanger::Skin(
							current_weapon_skin == 0 ? -1 : current_weapon_skin,
							current_weapon,
							weaponSkinSeed,
							weaponWear,
							weaponStatTrak,
							weaponName,
							""
					);
				}

				SkinChanger::ForceFullUpdate = true;
			}
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::End();
	}
}

void ConfigWindow()
{
	if (!showConfigWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(195, 260), ImGuiSetCond_Always);
	if (ImGui::Begin("Configs", &showConfigWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		static std::vector<std::string> configItems = GetConfigs();
		static int configItemCurrent = -1;

		if (ImGui::Button("Refresh"))
			configItems = GetConfigs();

		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			if (configItems.size() > 0 && (configItemCurrent >= 0 && configItemCurrent < (int) configItems.size()))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent] << "/config.json";

				Settings::LoadDefaultsOrSave(path);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			if (configItems.size() > 0 && (configItemCurrent >= 0 && configItemCurrent < (int) configItems.size()))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent];

				Settings::DeleteConfig(path);

				configItems = GetConfigs();
				configItemCurrent = -1;
			}
		}

		static char buf[128] = "";
		ImGui::PushItemWidth(138);
			ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button("Add") && strlen(buf) > 0)
		{
			pstring path = GetConfigDirectory();
			path << buf;

			if (!DoesFileExist(path.c_str()))
			{
				mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				Settings::LoadDefaultsOrSave(path << "/config.json");

				configItems = GetConfigs();
				configItemCurrent = -1;
			}
		}

		ImGui::PushItemWidth(178);
			if (ImGui::ListBox("", &configItemCurrent, configItems, 7))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent] << "/config.json";

				Settings::LoadConfig(path);
				reloadWeaponSettings();
			}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}

void PlayerListWindow()
{
	if (!showPlayerListWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Player list", &showPlayerListWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
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

			std::unordered_map<int, std::vector<int>> players = {
					{ TEAM_UNASSIGNED, { } },
					{ TEAM_SPECTATOR, { } },
					{ TEAM_TERRORIST, { } },
					{ TEAM_COUNTER_TERRORIST, { } },
			};

			for (int i = 1; i < engine->GetMaxClients(); i++)
			{
				if (i == engine->GetLocalPlayer())
					continue;

				if (!(*csPlayerResource)->GetConnected(i))
					continue;

				players[(*csPlayerResource)->GetTeam(i)].push_back(i);
			}

			for (int team = TEAM_UNASSIGNED; team <= TEAM_COUNTER_TERRORIST ; team++)
			{
				char* teamName = strdup("");
				switch (team)
				{
					case TEAM_UNASSIGNED:
						teamName = strdup("Unassigned");
						break;
					case TEAM_SPECTATOR:
						teamName = strdup("Spectator");
						break;
					case TEAM_TERRORIST:
						teamName = strdup("Terrorist");
						break;
					case TEAM_COUNTER_TERRORIST:
						teamName = strdup("Counter Terrorist");
						break;
				}

				for (auto it : players[team])
				{
					char* id;
					asprintf(&id, "%d", it);

					IEngineClient::player_info_t entityInformation;
					engine->GetPlayerInfo(it, &entityInformation);

					if (entityInformation.ishltv)
						continue;

					ImGui::Separator();

					if (ImGui::Selectable(id, it == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
						currentPlayer = it;
					ImGui::NextColumn();

					ImGui::Text("%s", entityInformation.name);
					ImGui::NextColumn();

					ImGui::Text("%s", teamName);
					ImGui::NextColumn();

					ImGui::Text("%s", (*csPlayerResource)->GetClan(it));
					ImGui::NextColumn();

					ImGui::Text("%s", ESP::Ranks[*(*csPlayerResource)->GetCompetitiveRanking(it)]);
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
				bool isFriendly = std::find(Aimbot::Friends.begin(), Aimbot::Friends.end(), entityInformation.xuid) != Aimbot::Friends.end();
				if (ImGui::Checkbox("Friend", &isFriendly))
				{
					if (isFriendly)
						Aimbot::Friends.push_back(entityInformation.xuid);
					else
						Aimbot::Friends.erase(std::find(Aimbot::Friends.begin(), Aimbot::Friends.end(), entityInformation.xuid));
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

					nickname = strdup(name.c_str());
					NameChanger::SetName(Util::PadStringRight(name, name.length() + 1));
				}

				const char* clanTag = (*csPlayerResource)->GetClan(currentPlayer);
				if (strlen(clanTag) > 0 && ImGui::Button("Steal clan tag"))
				{
					Settings::ClanTagChanger::enabled = true;
					Settings::ClanTagChanger::value = strdup(clanTag);
					Settings::ClanTagChanger::type = STATIC;

					ClanTagChanger::UpdateClanTagCallback();
				}
			}
		}

		ImGui::End();
	}
}

void UI::SwapWindow()
{
	if (UI::isVisible)
		return;

	if (engine->IsInGame())
		return;

	Draw::ImDrawText(ImVec2(4.f, 4.f), ImColor(255, 255, 255, 255), "AimTux", NULL, 0.0f, NULL, ImFontFlags_Shadow);
}

void UI::SetupWindows()
{
	if (UI::isVisible)
	{
		SetupMainMenuBar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(960, 645));
			MainWindow();
		ImGui::PopStyleVar();

		if (ModSupport::current_mod != ModType::CSCO)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(640, 695));
			SkinChangerWindow();
			ImGui::PopStyleVar();
		}

		ConfigWindow();
		ColorsWindow();
		PlayerListWindow();
	}

	ShowSpectators::DrawWindow();
	Radar::DrawWindow();
}
