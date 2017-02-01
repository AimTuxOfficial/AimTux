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

static char nickname[127] = "";

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

inline void SetTooltip(const char* text)
{
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", text);
}

static ItemDefinitionIndex currentWeapon = ItemDefinitionIndex::INVALID;
static bool enabled = false;
static bool silent = false;
static bool friendly = false;
static Bone bone = Bone::BONE_HEAD;
static ButtonCode_t aimkey = ButtonCode_t::MOUSE_MIDDLE;
static bool aimkeyOnly = false;
static bool smoothEnabled = false;
static float smoothValue = 0.5f;
static SmoothType smoothType = SmoothType::SLOW_END;
static bool smoothSaltEnabled = false;
static float smoothSaltMultiplier = 0.0f;
static bool errorMarginEnabled = false;
static float errorMarginValue = 0.0f;
static bool autoAimEnabled = false;
static float autoAimValue = 180.0f;
static bool aimStepEnabled = false;
static float aimStepValue = 25.0f;
static bool rcsEnabled = false;
static bool rcsAlwaysOn = false;
static float rcsAmountX = 2.0f;
static float rcsAmountY = 2.0f;
static bool autoPistolEnabled = false;
static bool autoShootEnabled = false;
static bool autoScopeEnabled = false;
static bool noShootEnabled = false;
static bool ignoreJumpEnabled = false;
static bool smokeCheck = false;
static bool autoWallEnabled = false;
static float autoWallValue = 10.0f;
static bool autoWallBones[] = { true, false, false, false, false, false };
static bool autoAimRealDistance = false;

void UI::UpdateWeaponSettings()
{
	if (Settings::Aimbot::weapons.find(currentWeapon) == Settings::Aimbot::weapons.end())
		Settings::Aimbot::weapons[currentWeapon] = AimbotWeapon_t();

	AimbotWeapon_t settings = {enabled, silent, friendly, bone, aimkey, aimkeyOnly,
							   smoothEnabled, smoothValue, smoothType, smoothSaltEnabled, smoothSaltMultiplier,
							   errorMarginEnabled, errorMarginValue,
							   autoAimEnabled, autoAimValue, aimStepEnabled, aimStepValue,
							   rcsEnabled, rcsAlwaysOn, rcsAmountX, rcsAmountY,
							   autoPistolEnabled, autoShootEnabled, autoScopeEnabled,
							   noShootEnabled, ignoreJumpEnabled, smokeCheck, autoWallEnabled, autoWallValue, autoAimRealDistance
	};

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		settings.autoWallBones[bone] = autoWallBones[bone];

	Settings::Aimbot::weapons.at(currentWeapon) = settings;
}

void ReloadWeaponSettings()
{
	ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
	if (Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
		index = currentWeapon;

	enabled = Settings::Aimbot::weapons.at(index).enabled;
	silent = Settings::Aimbot::weapons.at(index).silent;
	friendly = Settings::Aimbot::weapons.at(index).friendly;
	bone = Settings::Aimbot::weapons.at(index).bone;
	aimkey = Settings::Aimbot::weapons.at(index).aimkey;
	aimkeyOnly = Settings::Aimbot::weapons.at(index).aimkeyOnly;
	smoothEnabled = Settings::Aimbot::weapons.at(index).smoothEnabled;
	smoothValue = Settings::Aimbot::weapons.at(index).smoothAmount;
	smoothType = Settings::Aimbot::weapons.at(index).smoothType;
	smoothSaltEnabled = Settings::Aimbot::weapons.at(index).smoothSaltEnabled;
	smoothSaltMultiplier = Settings::Aimbot::weapons.at(index).smoothSaltMultiplier;
	errorMarginEnabled = Settings::Aimbot::weapons.at(index).errorMarginEnabled;
	errorMarginValue = Settings::Aimbot::weapons.at(index).errorMarginValue;
	autoAimEnabled = Settings::Aimbot::weapons.at(index).autoAimEnabled;
	autoAimValue = Settings::Aimbot::weapons.at(index).autoAimFov;
	aimStepEnabled = Settings::Aimbot::weapons.at(index).aimStepEnabled;
	aimStepValue = Settings::Aimbot::weapons.at(index).aimStepValue;
	rcsEnabled = Settings::Aimbot::weapons.at(index).rcsEnabled;
	rcsAlwaysOn = Settings::Aimbot::weapons.at(index).rcsAlwaysOn;
	rcsAmountX = Settings::Aimbot::weapons.at(index).rcsAmountX;
	rcsAmountY = Settings::Aimbot::weapons.at(index).rcsAmountY;
	autoPistolEnabled = Settings::Aimbot::weapons.at(index).autoPistolEnabled;
	autoShootEnabled = Settings::Aimbot::weapons.at(index).autoShootEnabled;
	autoScopeEnabled = Settings::Aimbot::weapons.at(index).autoScopeEnabled;
	noShootEnabled = Settings::Aimbot::weapons.at(index).noShootEnabled;
	ignoreJumpEnabled = Settings::Aimbot::weapons.at(index).ignoreJumpEnabled;
	smokeCheck = Settings::Aimbot::weapons.at(index).smokeCheck;
	autoWallEnabled = Settings::Aimbot::weapons.at(index).autoWallEnabled;
	autoWallValue = Settings::Aimbot::weapons.at(index).autoWallValue;
	autoAimRealDistance = Settings::Aimbot::weapons.at(index).autoAimRealDistance;

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		autoWallBones[bone] = Settings::Aimbot::weapons.at(index).autoWallBones[bone];
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
			&Settings::ESP::enemyColor,
			&Settings::ESP::allyColor,
			&Settings::ESP::enemyVisibleColor,
			&Settings::ESP::allyVisibleColor,
			&Settings::ESP::ctColor,
			&Settings::ESP::tColor,
			&Settings::ESP::ctVisibleColor,
			&Settings::ESP::tVisibleColor,
			&Settings::ESP::bombColor,
			&Settings::ESP::bombDefusingColor,
			&Settings::ESP::hostageColor,
			&Settings::ESP::defuserColor,
			&Settings::ESP::weaponColor,
			&Settings::ESP::chickenColor,
			&Settings::ESP::fishColor,
			&Settings::ESP::smokeColor,
			&Settings::ESP::decoyColor,
			&Settings::ESP::flashbangColor,
			&Settings::ESP::grenadeColor,
			&Settings::ESP::molotovColor,
			&Settings::ESP::Skeleton::color,
			&Settings::ESP::Chams::allyColor,
			&Settings::ESP::Chams::allyVisibleColor,
			&Settings::ESP::Chams::enemyColor,
			&Settings::ESP::Chams::enemyVisibleColor,
			&Settings::ESP::Chams::Arms::color,
			&Settings::Radar::enemyColor,
			&Settings::Radar::allyColor,
			&Settings::Radar::enemyVisibleColor,
			&Settings::Radar::allyVisibleColor,
			&Settings::Radar::ctColor,
			&Settings::Radar::tColor,
			&Settings::Radar::ctVisibleColor,
			&Settings::Radar::tVisibleColor,
			&Settings::Radar::bombColor,
			&Settings::Radar::bombDefusingColor,
			&Settings::ESP::Glow::allyColor,
			&Settings::ESP::Glow::enemyColor,
			&Settings::ESP::Glow::enemyVisibleColor,
			&Settings::ESP::Glow::weaponColor,
			&Settings::ESP::Glow::grenadeColor,
			&Settings::ESP::Glow::defuserColor,
			&Settings::ESP::Glow::chickenColor,
			&Settings::NoSky::color,
			&Settings::ASUSWalls::color,
	};

	bool* healthColor[] = {
			nullptr, // UI Main
			nullptr, // UI Body
			nullptr, // UI Font
			nullptr, // FOV Circle
			nullptr, // Hitmarker
			&Settings::ESP::hpEnemyColor, // ESP - Enemy
			&Settings::ESP::hpAllyColor, // ESP - Team
			&Settings::ESP::hpEnemyVisibleColor, // ESP - Enemy Visible
			&Settings::ESP::hpAllyVisibleColor, // ESP - Team Visible
			&Settings::ESP::hpCtColor, // ESP - CT
			&Settings::ESP::hpTColor, // ESP - T
			&Settings::ESP::hpCtVisibleColor, // ESP - CT Visible
			&Settings::ESP::hpTVisibleColor, // ESP - T Visible
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
			&Settings::ESP::Chams::hpAllyColor, // Chams - Team
			&Settings::ESP::Chams::hpAllyVisibleColor, // Chams - Team Visible
			&Settings::ESP::Chams::hpEnemyColor, // Chams - Enemy
			&Settings::ESP::Chams::hpEnemyVisibleColor, // Chams - Enemy Visible
			nullptr, // Chams - Arms
			&Settings::Radar::hpEnemyColor, // Radar - Enemy
			&Settings::Radar::hpAllyColor, // Radar - Team
			&Settings::Radar::hpEnemyVisibleColor, // Radar - Enemy Visible
			&Settings::Radar::hpAllyVisibleColor, // Radar - Team Visible
			&Settings::Radar::hpCtColor, // Radar - CT
			&Settings::Radar::hpTColor, // Radar - T
			&Settings::Radar::hpCtVisibleColor, // Radar - CT Visible
			&Settings::Radar::hpTVisibleColor, // Radar - T Visible
			nullptr, // Radar - Bomb
			nullptr, // Radar - Bomb Defusing
			&Settings::ESP::Glow::hpAllyColor, // Glow - Team
			&Settings::ESP::Glow::hpEnemyColor, // Glow - Enemy
			&Settings::ESP::Glow::hpEnemyVisibleColor, // Glow - Enemy Visible
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
				SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow");
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
		UI::UpdateWeaponSettings();
	ImGui::Separator();

	ImGui::Columns(3, NULL, true);
	{
		ImGui::SetColumnOffset(1, 200);
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##FILTERWEAPONS", filterWeapons, IM_ARRAYSIZE(filterWeapons));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##GUNS", ImVec2(-1, -1));
			for (auto it : ItemDefinitionIndexMap)
			{
				bool isDefault = (int) it.first < 0;
				if (!isDefault && !Util::Contains(Util::ToLower(std::string(filterWeapons)), Util::ToLower(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(it.first).c_str())))))
					continue;

				if (it.first >= ItemDefinitionIndex::WEAPON_KNIFE_BAYONET ||
					it.first == ItemDefinitionIndex::WEAPON_KNIFE ||
					it.first == ItemDefinitionIndex::WEAPON_KNIFE_T ||
					(it.first >= ItemDefinitionIndex::WEAPON_FLASHBANG && it.first <= ItemDefinitionIndex::WEAPON_C4))
					continue;

				const bool item_selected = ((int)it.first == (int) currentWeapon);
				ImGui::PushID((int)it.first);
					std::string formattedName;
					char changeIndicator = ' ';
					bool isChanged = Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end();
					if (!isDefault && isChanged)
						changeIndicator = '*';
					formattedName = changeIndicator + (isDefault ? Util::Items::GetItemDisplayName(it.first).c_str() : std::string(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(it.first).c_str()))));

					if (ImGui::Selectable(formattedName.c_str(), item_selected))
					{
						currentWeapon = it.first;
						ReloadWeaponSettings();
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
					UI::UpdateWeaponSettings();
				SetTooltip("Whether to target friendlies");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##AIMTARGET", (int*)& bone, targets, IM_ARRAYSIZE(targets)))
						UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Accuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Auto Aim", &autoAimEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Locks onto enemies within a certain FOV amount");
				if (ImGui::Checkbox("Recoil Control", &rcsEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically controls recoil");
				if (ImGui::Checkbox("RCS Always on", &rcsAlwaysOn))
					UI::UpdateWeaponSettings();
				SetTooltip("Whether Recoil Control always controls recoil (even when not aimbotting)");
				if (ImGui::Checkbox("Distance-Based FOV", &autoAimRealDistance))
					UI::UpdateWeaponSettings();
				SetTooltip("Takes perspective into account when calculating FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##AA", &autoAimValue, 0, 180))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##RCSX", &rcsAmountX, 0, 2, "X: %0.3f"))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##RCSY", &rcsAmountY, 0, 2, "Y: %0.3f"))
						UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Humanizing");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Smoothing", &smoothEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Smoothing reduces the aimbot \"snap\". 0 for full snap. 1 for full smoothing");
				if (ImGui::Checkbox("Smooth Salting", &smoothSaltEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Breaks the smoothing into smaller steps, high smooth + low salt is slightly stuttery");
				if (ImGui::Checkbox("Error Margin", &errorMarginEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Adds a margin of error to the aim, it will be obvious what it does when using it");
				ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##SMOOTHTYPE", (int*)& smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
						UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##SMOOTH", &smoothValue, 0, 1))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##SALT", &smoothSaltMultiplier, 0, smoothValue))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##ERROR", &errorMarginValue, 0, 2))
						UI::UpdateWeaponSettings();
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
				if (ImGui::Checkbox("Enabled", &aimkeyOnly))
					UI::UpdateWeaponSettings();
				SetTooltip("Enabling this means it you need to press a specific key to aimlock");
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
					UI::UpdateWeaponSettings();
				SetTooltip("Stops you getting VAC auth kicked in Casual / DM");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##STEP", &aimStepValue, 0, 45))
						UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				switch (currentWeapon)
				{
					case ItemDefinitionIndex::INVALID:
					case ItemDefinitionIndex::WEAPON_DEAGLE:
					case ItemDefinitionIndex::WEAPON_ELITE:
					case ItemDefinitionIndex::WEAPON_FIVESEVEN:
					case ItemDefinitionIndex::WEAPON_GLOCK:
					case ItemDefinitionIndex::WEAPON_TEC9:
					case ItemDefinitionIndex::WEAPON_HKP2000:
					case ItemDefinitionIndex::WEAPON_USP_SILENCER:
					case ItemDefinitionIndex::WEAPON_P250:
					case ItemDefinitionIndex::WEAPON_CZ75A:
					case ItemDefinitionIndex::WEAPON_REVOLVER:
						if (ImGui::Checkbox("Auto Pistol", &autoPistolEnabled))
							UI::UpdateWeaponSettings();
						SetTooltip("Automatically shoots the pistol when holding fire");
						break;
					default:
						break;
				}

				if (ImGui::Checkbox("Auto Shoot", &autoShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically shoots when locking to an enemy");
				if (ImGui::Checkbox("Silent Aim", &silent))
					UI::UpdateWeaponSettings();
				SetTooltip("Prevents the camera from locking to an enemy, doesn't work for demos");
				if (ImGui::Checkbox("Smoke Check", &smokeCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("Ignore players that are in smoke");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("No Shoot", &noShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Stops you shooting when locking to an enemy");
				if (ImGui::Checkbox("Auto Scope", &autoScopeEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically scopes weapons that have them");
				if (ImGui::Checkbox("Ignore Jump", &ignoreJumpEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Prevents you from aimbotting while jumping");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled##AUTOWALL", &autoWallEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Shoots enemy through a wall if it does X amount of damage");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##AUTOWALLDMG", &autoWallValue, 0, 100, "Min Damage: %f"))
						UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Head", &autoWallBones[(int) Hitbox::HITBOX_HEAD]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on head");
				if (ImGui::Checkbox("Neck", &autoWallBones[(int) Hitbox::HITBOX_NECK]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on neck");
				if (ImGui::Checkbox("Pelvis", &autoWallBones[(int) Hitbox::HITBOX_PELVIS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on pelvis");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("Spine", &autoWallBones[(int) Hitbox::HITBOX_SPINE]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on spine");
				if (ImGui::Checkbox("Legs", &autoWallBones[(int) Hitbox::HITBOX_LEGS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on legs");
				if (ImGui::Checkbox("Arms", &autoWallBones[(int) Hitbox::HITBOX_ARMS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on arms");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			if (currentWeapon > ItemDefinitionIndex::INVALID && Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
				if (ImGui::Button("Clear Weapon Settings", ImVec2(-1, 0)))
				{
					Settings::Aimbot::weapons.erase(currentWeapon);
					ReloadWeaponSettings();
				}
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
				SetTooltip("Adds a delay to the Triggerbot");
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
				SetTooltip("Trigger on enemies");
				ImGui::Checkbox("Walls", &Settings::Triggerbot::Filters::walls);
				SetTooltip("Trigger through walls");
				ImGui::Checkbox("Head", &Settings::Triggerbot::Filters::head);
				SetTooltip("Trigger on head");
				ImGui::Checkbox("Chest", &Settings::Triggerbot::Filters::chest);
				SetTooltip("Trigger on chest");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::Triggerbot::Filters::allies);
				SetTooltip("Trigger on allies");
				ImGui::Checkbox("Smoke check", &Settings::Triggerbot::Filters::smokeCheck);
				SetTooltip("Don't shoot through smokes");
				ImGui::Checkbox("Stomach", &Settings::Triggerbot::Filters::stomach);
				SetTooltip("Trigger on stomach");
				ImGui::Checkbox("Arms", &Settings::Triggerbot::Filters::arms);
				SetTooltip("Trigger on arms");
				ImGui::Checkbox("Legs", &Settings::Triggerbot::Filters::legs);
				SetTooltip("Trigger on legs");
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
					SetTooltip("Outline players with a box");
					ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
					SetTooltip("Change players' model texture");
					ImGui::Checkbox("Health", &Settings::ESP::Bars::enabled);
					SetTooltip("Show a players health with a bar");
					ImGui::Checkbox("Tracers", &Settings::ESP::Tracers::enabled);
					SetTooltip("Draws a line to each player");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Bar Color");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Team Color");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Checkbox("Bullet Tracers", &Settings::ESP::BulletTracers::enabled);
					SetTooltip("Adds a line showing where a player is aiming");
					ImGui::Checkbox("Headdot", &Settings::ESP::Headdot::enabled);
					SetTooltip("Adds a Dot on the Head of a player");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						ImGui::Combo("##BOXTYPE", (int*)& Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
						ImGui::Combo("##CHAMSTYPE", (int*)& Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
						ImGui::Combo("##BARTYPE", (int*)& Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
						ImGui::Combo("##TRACERTYPE", (int*)& Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
						ImGui::Combo("##BARCOLTYPE", (int*)& Settings::ESP::Bars::colorType, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
						ImGui::Combo("##TEAMCOLTYPE", (int*)& Settings::ESP::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
					ImGui::PopItemWidth();
					ImGui::Checkbox("Skeleton", &Settings::ESP::Skeleton::enabled);
					SetTooltip("Show a players skeleton");
					ImGui::PushItemWidth(-1);
						ImGui::SliderFloat("##HDOTSIZE", &Settings::ESP::Headdot::size, 1.f, 5.f, "Size: %0.f");
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Filter");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies);
					SetTooltip("Show enemies");
					ImGui::Checkbox("Chickens", &Settings::ESP::Filters::chickens);
					SetTooltip("Show chickens");
					ImGui::Checkbox("Legit Mode", &Settings::ESP::Filters::legit);
					SetTooltip("Hide enemies behind walls");
					ImGui::Checkbox("Smoke Check", &Settings::ESP::Filters::smokeCheck);
					SetTooltip("Mark players behind smokes as invisible");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
					SetTooltip("Show team mates");
					ImGui::Checkbox("Fish", &Settings::ESP::Filters::fishes);
					SetTooltip("Show fish");
					ImGui::Checkbox("Visiblity Check", &Settings::ESP::Filters::visibilityCheck);
					SetTooltip("Change color of outlined box based on whether you see them");
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Player Information");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Clan", &Settings::ESP::Info::clan);
					SetTooltip("Show clan");
					ImGui::Checkbox("Rank", &Settings::ESP::Info::rank);
					SetTooltip("Show rank");
					ImGui::PushID(1);
						ImGui::Checkbox("Health", &Settings::ESP::Info::health);
						SetTooltip("Show health");
					ImGui::PopID();
					ImGui::Checkbox("Scoped", &Settings::ESP::Info::scoped);
					SetTooltip("Show whether they are scoped");
					ImGui::Checkbox("Flashed", &Settings::ESP::Info::flashed);
					SetTooltip("Show whether they are flashed");
					ImGui::Checkbox("Defuse Kit", &Settings::ESP::Info::hasDefuser);
					SetTooltip("Show whether they have a defuse kit");
					ImGui::Checkbox("Grabbing Hostage", &Settings::ESP::Info::grabbingHostage);
					SetTooltip("Show whether they are grabbing a hostage");
					ImGui::Checkbox("Location", &Settings::ESP::Info::location);
					SetTooltip("Show location");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Name", &Settings::ESP::Info::name);
					SetTooltip("Show name");
					ImGui::Checkbox("Steam ID", &Settings::ESP::Info::steamId);
					SetTooltip("Show Steam ID");
					ImGui::Checkbox("Weapon", &Settings::ESP::Info::weapon);
					SetTooltip("Show held weapon");
					ImGui::Checkbox("Reloading", &Settings::ESP::Info::reloading);
					SetTooltip("Show whether they are reloading");
					ImGui::Checkbox("Planting", &Settings::ESP::Info::planting);
					SetTooltip("Show whether they are planting");
					ImGui::Checkbox("Defusing", &Settings::ESP::Info::defusing);
					SetTooltip("Show whether they are defusing");
					ImGui::Checkbox("Rescuing Hostage", &Settings::ESP::Info::rescuing);
					SetTooltip("Show whether they are rescuing a hostage");
				}

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("World");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Weapons", &Settings::ESP::Filters::weapons);
					SetTooltip("Show weapons on floor");
					ImGui::Checkbox("Throwables", &Settings::ESP::Filters::throwables);
					SetTooltip("Show throwables");
					ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
					SetTooltip("Show a glow around entities");
				}
				ImGui::NextColumn();
				{
					ImGui::Checkbox("Bomb", &Settings::ESP::Filters::bomb);
					SetTooltip("Show bomb when planted");
					ImGui::Checkbox("Defuse Kits", &Settings::ESP::Filters::defusers);
					SetTooltip("Show defuse kits on floor");
					ImGui::Checkbox("Hostages", &Settings::ESP::Filters::hostages);
					SetTooltip("Show hostages");
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
				SetTooltip("Show a crosshair based on recoil");
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
				SetTooltip("Show circle around aimbot FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
				SetTooltip("Only show recoil crosshair when shooting");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				SetTooltip("Apply chams to arms");
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				SetTooltip("Adds a light source to players");
				ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
				SetTooltip("Hide flashbang effect");
				ImGui::Checkbox("Show Footsteps", &Settings::ESP::Sounds::enabled);
				SetTooltip("Shows you footsteps in 3D space");
				ImGui::Checkbox("No View Punch", &Settings::View::NoViewPunch::enabled);
				SetTooltip("Disables view punch when shooting");
				ImGui::Checkbox("No Sky", &Settings::NoSky::enabled);
				SetTooltip("Allows for the skybox to be colored or disabled");
				ImGui::Checkbox("No Smoke", &Settings::NoSmoke::enabled);
				SetTooltip("Disables smoke rendering");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##ARMSTYPE", (int*)& Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
					ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000, "Radius: %0.f");
					ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255, "Amount: %0.f");
					ImGui::SliderInt("##SOUNDSTIME", &Settings::ESP::Sounds::time, 250, 5000), "Timeout: %0.f";
				ImGui::PopItemWidth();
				ImGui::Checkbox("No Aim Punch", &Settings::View::NoAimPunch::enabled);
				SetTooltip("Disables aim punch when shooting");
				ImGui::Checkbox("No Scope Border", &Settings::NoScopeBorder::enabled);
				SetTooltip("Disables black scope silhouette");
				ImGui::Checkbox("ASUS Walls", &Settings::ASUSWalls::enabled);
				SetTooltip("Makes wall textures transparent");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Radar");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
				SetTooltip("Shows players on the custom radar");
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##RADARTEAMCOLTYPE", (int*)& Settings::Radar::team_color_type, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Enemies", &Settings::Radar::enemies);
				ImGui::Checkbox("Bomb", &Settings::Radar::bomb);
				ImGui::Checkbox("Legit", &Settings::Radar::legit);
				ImGui::Checkbox("In-game Radar", &Settings::Radar::InGame::enabled);
				SetTooltip("Shows players on the in-game radar");

			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##RADARZOOM", &Settings::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
					ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Radar::iconsScale, 2, 16, "Icons Scale: %0.1f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Allies", &Settings::Radar::allies);
				ImGui::Checkbox("Defuser", &Settings::Radar::defuser);
				ImGui::Checkbox("Visibility Check", &Settings::Radar::visibilityCheck);
				ImGui::Checkbox("Smoke Check", &Settings::Radar::smokeCheck);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text("Hitmarkers");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Hitmarkers", &Settings::ESP::Hitmarker::enabled);
				SetTooltip("Notify when you hit another player");

				ImGui::Checkbox("Enemies##HITMARKERS", &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox("Allies##HITMARKERS", &Settings::ESP::Hitmarker::allies);
				ImGui::Checkbox("Damage##HITMARKERS", &Settings::ESP::Hitmarker::Damage::enabled);
				SetTooltip("Show dealt damage next to the hitmarker");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##HITMARKERDUR", &Settings::ESP::Hitmarker::duration, 250, 3000, "Timeout: %0.f");
					ImGui::SliderInt("##HITMARKERSIZE", &Settings::ESP::Hitmarker::size, 1, 32, "Size: %0.f");
					ImGui::SliderInt("##HITMARKERGAP", &Settings::ESP::Hitmarker::innerGap, 1, 16, "Gap: %0.f");
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
	const char* yTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", // safe
			"LISP", "LISP SIDE", "LISP JITTER", "ANGEL BACKWARDS", "ANGEL INVERSE", "ANGEL SPIN" // untrusted
	};

	const char* xTypes[] = {
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
				SetTooltip("Enables Yaw AntiAim");
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
						if (ImGui::Combo("##YFAKETYPE", (int*)& Settings::AntiAim::Yaw::typeFake, yTypes, IM_ARRAYSIZE(yTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::typeFake >= AntiAimType_Y::LISP)
							{
								Settings::AntiAim::Yaw::typeFake = AntiAimType_Y::SPIN_SLOW;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}

						if (ImGui::Combo("##YACTUALTYPE", (int*)& Settings::AntiAim::Yaw::type, yTypes, IM_ARRAYSIZE(yTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
							{
								Settings::AntiAim::Yaw::type = AntiAimType_Y::SPIN_SLOW;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Checkbox("Pitch", &Settings::AntiAim::Pitch::enabled);
				SetTooltip("Enables Pitch AntiAim");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Pitch Actual");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
						if (ImGui::Combo("##XTYPE", (int*)& Settings::AntiAim::Pitch::type, xTypes, IM_ARRAYSIZE(xTypes)))
						{
							if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
							{
								Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
								ImGui::OpenPopup("Error###UNTRUSTED_AA");
							}
						}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Disable");
				ImGui::Separator();
				ImGui::Checkbox("Knife", &Settings::AntiAim::AutoDisable::knifeHeld);
				SetTooltip("Stops your antiaim while you have your knife out.");
				ImGui::NextColumn();

				ImGui::Checkbox("No Enemy", &Settings::AntiAim::AutoDisable::noEnemy);
				SetTooltip("Stops your antiaim when there are no enemies visible.");

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Edging");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enabled", &Settings::AntiAim::HeadEdge::enabled);
					SetTooltip("Aims your head into the closest wall");
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
			ImGui::Checkbox("Resolve All", &Settings::Resolver::resolveAll);
			SetTooltip("Resolves all players on the server");
			ImGui::Separator();
			ImGui::Text("Movement");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Crouch", &Settings::Aimbot::AutoCrouch::enabled);
				SetTooltip("Auto crouch when an enemy is in sight");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Auto Stop", &Settings::Aimbot::AutoStop::enabled);
				SetTooltip("Auto stop when an enemy is in sight");
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
				SetTooltip("Chokes packets so it appears you're lagging");
				ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
				SetTooltip("Auto accept games when in MM queue");
				ImGui::Checkbox("Auto Defuse", &Settings::AutoDefuse::enabled);
				SetTooltip("Will automatically defuse the bomb with 0.5 seconds remaining - starts at 5.5 seconds until explosion with kit and 10.5 without");
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

void WeaponSkinChanger()
{
	static int currentWeapon = 7;
	static int currentWeaponSkin = Settings::Skinchanger::skins.find((ItemDefinitionIndex) currentWeapon) != Settings::Skinchanger::skins.end() ? Settings::Skinchanger::skins.at((ItemDefinitionIndex) currentWeapon).fallbackPaintKit : -1;
	static float weaponWear = 0.005f;
	static int weaponSkinSeed = -1;
	static int weaponStatTrak = -1;
	static char weaponName[18];
	static char filterSkins[32];
	static char filterGuns[32];
	static int isCT = 1;

	if (ImGui::Checkbox("Enabled##WeaponSkins", &Settings::Skinchanger::enabled))
		SkinChanger::forceFullUpdate = true;

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
				for (auto it : ItemDefinitionIndexMap)
				{
					if (!Util::Contains(Util::ToLower(std::string(filterGuns)), Util::ToLower(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(it.first).c_str())))))
						continue;
					if (it.first == ItemDefinitionIndex ::INVALID ||
						it.first >= ItemDefinitionIndex::WEAPON_KNIFE_BAYONET ||
						it.first == ItemDefinitionIndex::WEAPON_KNIFE ||
						it.first == ItemDefinitionIndex::WEAPON_KNIFE_T ||
						(it.first >= ItemDefinitionIndex::WEAPON_FLASHBANG && it.first <= ItemDefinitionIndex::WEAPON_C4))
						continue;

					const bool item_selected = ((int)it.first == currentWeapon);
					ImGui::PushID((int)it.first);
						if (ImGui::Selectable(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(it.first).c_str())).c_str(), item_selected))
						{
							currentWeapon = (int)it.first;

							auto keyExists = Settings::Skinchanger::skins.find(it.first);
							if (keyExists == Settings::Skinchanger::skins.end())
								currentWeaponSkin = -1;
							else
								currentWeaponSkin = Settings::Skinchanger::skins.at(it.first).fallbackPaintKit;
						}
					ImGui::PopID();
				}
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);
		ImGui::InputText("##FilterSkins", filterSkins, IM_ARRAYSIZE(filterSkins));
		ImGui::ListBoxHeader("##SKINS", ImVec2(0, 300));
			for (auto it : weaponSkins)
			{
				if (!Util::Contains(Util::ToLower(std::string(filterSkins)), Util::ToLower(std::string(it.second))))
					continue;
				const bool item_selected = (it.first == currentWeaponSkin);
				ImGui::PushID(it.first);
					if (ImGui::Selectable(it.second, item_selected))
						currentWeaponSkin = it.first;
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
			for (auto knife : ItemDefinitionIndexMap)
			{
				if (knife.first < ItemDefinitionIndex::WEAPON_KNIFE_BAYONET || knife.first > ItemDefinitionIndex::WEAPON_KNIFE_PUSH)
					continue;
				const bool item_selected = ((int) knife.first == currentWeapon);
				ImGui::PushID((int)knife.first);
				if (ImGui::Selectable(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(knife.first).c_str())).c_str(), item_selected))
				{
					currentWeapon = (int)knife.first;
					currentWeaponSkin = Settings::Skinchanger::skins.at(isCT == 1 ? ItemDefinitionIndex::WEAPON_KNIFE : ItemDefinitionIndex::WEAPON_KNIFE_T).fallbackPaintKit;
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
		ImGui::InputInt("Skin ID", &currentWeaponSkin);
		ImGui::SliderFloat("Wear", &weaponWear, 0.005f, 1.0f);
		ImGui::InputInt("Seed", &weaponSkinSeed);
		ImGui::InputInt("StatTrak", &weaponStatTrak);
		ImGui::InputText("Name", weaponName, IM_ARRAYSIZE(weaponName));
		ImGui::Separator();
		if (ImGui::Button("Load", ImVec2(-1, 0)))
		{
			AttribItem_t skin = { ItemDefinitionIndex::INVALID, -1, -1, -1, -1, -1, ""};
			if (currentWeapon >= (int) ItemDefinitionIndex::WEAPON_KNIFE_BAYONET)
			{
				if (Settings::Skinchanger::skins.find((ItemDefinitionIndex) currentWeapon) == Settings::Skinchanger::skins.end())
					Settings::Skinchanger::skins[isCT == 1 ? ItemDefinitionIndex::WEAPON_KNIFE : ItemDefinitionIndex::WEAPON_KNIFE_T] = AttribItem_t();

				skin = Settings::Skinchanger::skins.at(isCT == 1 ? ItemDefinitionIndex::WEAPON_KNIFE : ItemDefinitionIndex::WEAPON_KNIFE_T);
				currentWeapon = (int) skin.itemDefinitionIndex;
			}
			else
			{
				if (Settings::Skinchanger::skins.find((ItemDefinitionIndex) currentWeapon) == Settings::Skinchanger::skins.end())
					skin = { (ItemDefinitionIndex) currentWeapon, -1, -1, -1, -1, -1, "" };
				else
					skin = Settings::Skinchanger::skins.at((ItemDefinitionIndex) currentWeapon);
			}

			currentWeaponSkin = skin.fallbackPaintKit;
			weaponSkinSeed = skin.fallbackSeed;
			weaponWear = skin.fallbackWear;
			weaponStatTrak = skin.fallbackStatTrak;
			std::fill(std::begin(weaponName), std::end(weaponName), 0);
			std::copy(std::begin(skin.customName), std::end(skin.customName), std::begin(weaponName));
		}
		if (ImGui::Button("Apply##Weapons", ImVec2(-1, 0)))
		{
			if (currentWeapon >= (int) ItemDefinitionIndex::WEAPON_KNIFE_BAYONET)
			{
				if (Settings::Skinchanger::skins.find((ItemDefinitionIndex) currentWeapon) == Settings::Skinchanger::skins.end())
					Settings::Skinchanger::skins[(ItemDefinitionIndex) currentWeapon] = AttribItem_t();

				Settings::Skinchanger::skins.at(isCT == 1 ? ItemDefinitionIndex::WEAPON_KNIFE : ItemDefinitionIndex::WEAPON_KNIFE_T) = {
						(ItemDefinitionIndex) currentWeapon,
						currentWeaponSkin == 0 ? -1 : currentWeaponSkin,
						weaponWear,
						weaponSkinSeed,
						weaponStatTrak,
						-1,
						weaponName
				};
			}
			else
			{
				if (Settings::Skinchanger::skins.find((ItemDefinitionIndex) currentWeapon) == Settings::Skinchanger::skins.end())
					Settings::Skinchanger::skins[(ItemDefinitionIndex) currentWeapon] = AttribItem_t();

				Settings::Skinchanger::skins.at((ItemDefinitionIndex) currentWeapon) = {
						(ItemDefinitionIndex) currentWeapon,
						currentWeaponSkin == 0 ? -1 : currentWeaponSkin,
						weaponWear,
						weaponSkinSeed,
						weaponStatTrak,
						-1,
						weaponName
				};
			}

			SkinChanger::forceFullUpdate = true;
		}
		ImGui::Separator();
		ImGui::EndChild();
	}
}

void GloveSkinChanger()
{
	static int currentGlove = (int) ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND;
	static int currentGloveSkin = Settings::Skinchanger::skins.find(ItemDefinitionIndex::GLOVE_T_SIDE) != Settings::Skinchanger::skins.end() ? Settings::Skinchanger::skins.at(ItemDefinitionIndex::GLOVE_T_SIDE).fallbackPaintKit : 10006;
	static float gloveWear = 0.005f;
	static char filterGloves[32];
	static char filterGloveSkins[32];

	if (ImGui::Checkbox("Enabled##GloveSkins", &Settings::Skinchanger::Gloves::enabled))
		SkinChanger::forceFullUpdate = true;

	ImGui::Separator();

	ImGui::Columns(2);
	ImGui::Text("Glove Model");
	ImGui::NextColumn();
	ImGui::Text("Glove Skin");
	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(2, NULL, false);
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##FilterGloves", filterGloves, IM_ARRAYSIZE(filterGloves));
			ImGui::ListBoxHeader("##GLOVES", ImVec2(-1, 300));
				for (auto glove : ItemDefinitionIndexMap)
				{
					if (!Util::Contains(Util::ToLower(std::string(filterGloves)), Util::ToLower(std::string(glove.second.displayName))) || glove.first < ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND)
						continue;
					if (glove.first == ItemDefinitionIndex::GLOVE_CT_SIDE || glove.first == ItemDefinitionIndex::GLOVE_T_SIDE)
						continue;
					const bool item_selected = ((int)glove.first == currentGlove);
					ImGui::PushID((int)glove.first);
					if (ImGui::Selectable(Util::WstringToString(localize->FindSafe(Util::Items::GetItemDisplayName(glove.first).c_str())).c_str(), item_selected))
					{
						currentGlove = (int)glove.first;
						currentGloveSkin = Settings::Skinchanger::skins.at(ItemDefinitionIndex::GLOVE_T_SIDE).fallbackPaintKit;
					}
					ImGui::PopID();
				}
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##FilterGloveSkins", filterGloveSkins, IM_ARRAYSIZE(filterGloveSkins));
			ImGui::ListBoxHeader("##GLOVESKINS", ImVec2(-1, 300));
				for (auto it : gloveSkins)
				{
					if (!Util::Contains(Util::ToLower(std::string(filterGloveSkins)), Util::ToLower(std::string(it.second))))
						continue;

					switch (currentGlove)
					{
						case (int) ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND:
							if (it.first != filterBloodhound[0] &&
							   it.first != filterBloodhound[1] &&
							   it.first != filterBloodhound[2] &&
							   it.first != filterBloodhound[3])
								continue;
							break;
						case (int) ItemDefinitionIndex::GLOVE_SPORTY:
							if (it.first != filterSporty[0] &&
							   it.first != filterSporty[1] &&
							   it.first != filterSporty[2] &&
							   it.first != filterSporty[3])
								continue;
							break;
						case (int) ItemDefinitionIndex::GLOVE_SLICK:
							if (it.first != filterSlick[0] &&
							   it.first != filterSlick[1] &&
							   it.first != filterSlick[2] &&
							   it.first != filterSlick[3])
								continue;
							break;
						case (int) ItemDefinitionIndex::GLOVE_LEATHER_WRAP:
							if (it.first != filterWrap[0] &&
							   it.first != filterWrap[1] &&
							   it.first != filterWrap[2] &&
							   it.first != filterWrap[3])
								continue;
							break;
						case (int) ItemDefinitionIndex::GLOVE_MOTORCYCLE:
							if (it.first != filterMoto[0] &&
							   it.first != filterMoto[1] &&
							   it.first != filterMoto[2] &&
							   it.first != filterMoto[3])
								continue;
							break;
						case (int) ItemDefinitionIndex::GLOVE_SPECIALIST:
							if (it.first != filterSpecialist[0] &&
							   it.first != filterSpecialist[1] &&
							   it.first != filterSpecialist[2] &&
							   it.first != filterSpecialist[3])
								continue;
							break;
						default:
							break;
					}
					const bool itemSelected = (it.first == currentGloveSkin);
					ImGui::PushID(it.first);
						if (ImGui::Selectable(it.second, itemSelected))
							currentGloveSkin = it.first;
					ImGui::PopID();
				}
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::Columns(2);
		ImGui::SliderFloat("Wear", &gloveWear, 0.005f, 1.0f);
	ImGui::NextColumn();
		if (ImGui::Button("Apply##Gloves", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skins.find(ItemDefinitionIndex::GLOVE_T_SIDE) == Settings::Skinchanger::skins.end())
				Settings::Skinchanger::skins[ItemDefinitionIndex::GLOVE_T_SIDE] = AttribItem_t();

			Settings::Skinchanger::skins.at(ItemDefinitionIndex::GLOVE_T_SIDE) = {
					(ItemDefinitionIndex) currentGlove,
					currentGloveSkin,
					gloveWear,
					-1,
					-1,
					-1,
					""
			};

			SkinChanger::forceFullUpdate = true;
		}
	ImGui::Columns(1);
	ImGui::Separator();
}

void SkinChangerWindow()
{
	if (!showSkinChangerWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(640, 725), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin Changer", &showSkinChangerWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] = {
				"Weapons",
				"Gloves",
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
					Settings::UI::mainColor.Value.x - (distance * 0.06f),
					Settings::UI::mainColor.Value.y - (distance * 0.06f),
					Settings::UI::mainColor.Value.z - (distance * 0.06f),
					Settings::UI::mainColor.Value.w
			);

			if (ImGui::Button(tabs[i], ImVec2(width, 0)))
				page = i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor;

			if (i < tabs_size - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch(page)
		{
			case 0:
				WeaponSkinChanger();
				break;
			case 1:
				GloveSkinChanger();
				break;
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
				ReloadWeaponSettings();
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

			std::unordered_map<TeamID, std::vector<int>> players = {
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
