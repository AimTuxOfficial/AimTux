#include "atgui.h"
#include "skins.h"
#include <string>

bool UI::isVisible = false;

ImColor Settings::UI::mainColor = ImColor(54, 54, 54, 255);
ImColor Settings::UI::bodyColor = ImColor(24, 24, 24, 240);
ImColor Settings::UI::fontColor = ImColor(255, 255, 255, 255);
bool showMainWindow = true;
bool showSkinChangerWindow = false;
bool showConfigWindow = false;
bool showColorsWindow = false;
float gunWearAmount = 0.005f;
float knifeWearAmount = 0.005f;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

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

	ImVec4 mainColorHovered = ImVec4(Settings::UI::mainColor.Value.x + 0.1f, Settings::UI::mainColor.Value.y + 0.1f, Settings::UI::mainColor.Value.z + 0.1f, Settings::UI::mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.Value.x + 0.2f, Settings::UI::mainColor.Value.y + 0.2f, Settings::UI::mainColor.Value.z + 0.2f, Settings::UI::mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(Settings::UI::bodyColor.Value.x, Settings::UI::bodyColor.Value.y, Settings::UI::bodyColor.Value.z, Settings::UI::bodyColor.Value.w + .1f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 1);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 10.0f;
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
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]= frameBgColor;
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg]= Settings::UI::mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = frameBgColor;
	style.Colors[ImGuiCol_CheckMark] = Settings::UI::mainColor;
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
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void SetupMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &showMainWindow, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Skin Changer Window", &showSkinChangerWindow, 0, ImVec2(ImGui::CalcTextSize("Skin Changer Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Config Window", &showConfigWindow, 0, ImVec2(ImGui::CalcTextSize("Config Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Spectators Window", &Settings::ShowSpectators::enabled, 0, ImVec2(ImGui::CalcTextSize("Spectators Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Colors Window", &showColorsWindow, 0, ImVec2(ImGui::CalcTextSize("Colors Window", NULL, true).x, 0.0f));

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void ColorsWindow()
{
	if (!showColorsWindow)
		return;

	const char* colorSelection[] =
			{
					"UI Main",
					"UI Body",
					"UI Font",
					"FOV Circle",
					"ESP - Team",
					"ESP - Enemy",
					"ESP - Enemy Visible",
					"ESP - Bones",
					"ESP - Bomb",
					"ESP - Team Text",
					"ESP - Enemy Text",
					"ESP - Enemy Visible Text",
					"Chams - Team",
					"Chams - Team Visible",
					"Chams - Enemy",
					"Chams - Enemy Visible",
					"Glow - Team",
					"Glow - Enemy",
					"Glow - Enemy Visible",
					"Glow - Weapon",
					"Glow - Grenade",
					"Glow - Defuser",
					"Dlights - Team",
					"Dlights - Enemy",
			};
	ImColor* colors[] =
			{
					&Settings::UI::mainColor,
					&Settings::UI::bodyColor,
					&Settings::UI::fontColor,
					&Settings::ESP::FOVCrosshair::color,
					&Settings::ESP::ally_color,
					&Settings::ESP::enemy_color,
					&Settings::ESP::enemy_visible_color,
					&Settings::ESP::bones_color,
					&Settings::ESP::bomb_color,
					&Settings::ESP::Info::ally_color,
					&Settings::ESP::Info::enemy_color,
					&Settings::ESP::Info::enemy_visible_color,
					&Settings::ESP::Chams::players_ally_color,
					&Settings::ESP::Chams::players_ally_visible_color,
					&Settings::ESP::Chams::players_enemy_color,
					&Settings::ESP::Chams::players_enemy_visible_color,
					&Settings::ESP::Glow::ally_color,
					&Settings::ESP::Glow::enemy_color,
					&Settings::ESP::Glow::enemy_visible_color,
					&Settings::ESP::Glow::weapon_color,
					&Settings::ESP::Glow::grenade_color,
					&Settings::ESP::Glow::defuser_color,
					&Settings::Dlights::ally_color,
					&Settings::Dlights::enemy_color,
			};
	static int colorSelected = 0;

	ImGui::SetNextWindowSize(ImVec2(540, 265), ImGuiSetCond_Always);
	if (ImGui::Begin("Colors", &showColorsWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, NULL, true);
		{
			ImGui::PushItemWidth(-1);
				ImGui::ListBox("##COLORSELECTION", &colorSelected, colorSelection, IM_ARRAYSIZE(colorSelection), 10);
			ImGui::PopItemWidth();
		}
		ImGui::NextColumn();
		{
			UI::ColorPicker4((float *)colors[colorSelected]);
		}
		ImGui::End();
	}
}

void AimbotTab()
{
	const char* targets[] = { "PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };

	UI::ReverseCheckbox("Enabled", &Settings::Aimbot::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		if (ImGui::BeginChild("COL1", ImVec2(0, 0), true))
		{
			ImGui::Text("Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Friendly", &Settings::Aimbot::friendly);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##AIMTARGET", &Settings::Aimbot::bone, targets, IM_ARRAYSIZE(targets));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Accuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Aim", &Settings::Aimbot::AutoAim::enabled);
				ImGui::Checkbox("Recoil Control", &Settings::Aimbot::RCS::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##AA", &Settings::Aimbot::fov, 0, 180);
					ImGui::SliderFloat("##RCS", &Settings::Aimbot::RCS::value, 0, 2);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Humanizing");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Smoothing", &Settings::Aimbot::Smooth::enabled);
				ImGui::Checkbox("Smooth Salting", &Settings::Aimbot::Smooth::Salting::enabled);
				ImGui::Text("Error Margin");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##SMOOTH", &Settings::Aimbot::Smooth::value, 0, 1);
					ImGui::SliderFloat("##SALT", &Settings::Aimbot::Smooth::Salting::percentage, 0, 100);
					ImGui::SliderFloat("##ERROR", &Settings::Aimbot::errorMargin, 0, 2);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		if (ImGui::BeginChild("COL2", ImVec2(0, 0), true))
		{
			ImGui::Text("Aimkey Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Aimbot::aimkey_only);
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::Aimbot::aimkey);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Casual / DM Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Aim Step", &Settings::Aimbot::AimStep::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##STEP", &Settings::Aimbot::AimStep::value, 0, 100);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Pistol", &Settings::Aimbot::AutoPistol::enabled);
				ImGui::Checkbox("Auto Shoot", &Settings::Aimbot::AutoShoot::enabled);
				ImGui::Checkbox("Silent Aim", &Settings::Aimbot::silent);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("No Shoot", &Settings::Aimbot::no_shoot);
				ImGui::Checkbox("Auto Scope", &Settings::Aimbot::AutoShoot::autoscope);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}

void TriggerbotTab()
{
	ImGui::Columns(2, NULL, false);
	UI::ReverseCheckbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::SameLine();

	UI::KeyBindButton(&Settings::Triggerbot::key);

	ImGui::Separator();

	UI::ReverseCheckbox("Delay", &Settings::Triggerbot::Delay::enabled);
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
		ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
	ImGui::PopItemWidth();

	ImGui::Separator();
	ImGui::PushItemWidth(150);
		ImGui::ListBoxHeader("##TRIGGERFILTER", 6);
			ImGui::Selectable("Friendly", &Settings::Triggerbot::Filter::friendly);
			ImGui::Selectable("Head", &Settings::Triggerbot::Filter::head);
			ImGui::Selectable("Chest", &Settings::Triggerbot::Filter::chest);
			ImGui::Selectable("Stomach", &Settings::Triggerbot::Filter::stomach);
			ImGui::Selectable("Arms", &Settings::Triggerbot::Filter::arms);
			ImGui::Selectable("Legs", &Settings::Triggerbot::Filter::legs);
		ImGui::ListBoxFooter();
	ImGui::PopItemWidth();
}

void VisualsTab()
{
	const char* WallTypes[] = { "Flat 2D", "Box 3D" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* ChamsTypes[] = { "Normal", "Flat" };
	const char* ArmsTypes[] = { "Default", "Rainbow", "Wireframe", "None" };

	ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		if (ImGui::BeginChild("ESP", ImVec2(0, 0), true))
		{
			ImGui::Text("Player ESP");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Walls", &Settings::ESP::Walls::enabled);
				ImGui::Checkbox("Tracers", &Settings::ESP::Tracer::enabled);
				ImGui::Checkbox("Show Bones", &Settings::ESP::Bones::enabled);
				ImGui::Checkbox("Show Friendly", &Settings::ESP::friendly);
				ImGui::Checkbox("Visibility Check", &Settings::ESP::visibility_check);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##WALLTYPE", &Settings::ESP::Walls::type, WallTypes, IM_ARRAYSIZE(WallTypes));
					ImGui::Combo("##TRACERTYPE", &Settings::ESP::Tracer::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Player Information");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Name", &Settings::ESP::Info::showName);
				ImGui::Checkbox("Health", &Settings::ESP::Info::showHealth);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Weapon", &Settings::ESP::Info::showWeapon);
				ImGui::Checkbox("Colored", &Settings::ESP::Info::colorCode);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("World ESP");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Dropped Weapon Names", &Settings::ESP::Weapons::enabled);
				ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Bomb ESP", &Settings::ESP::Bomb::enabled);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		if (ImGui::BeginChild("Chams", ImVec2(0, 0), true))
		{
			ImGui::Text("Chams");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Players", &Settings::ESP::Chams::players);
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				ImGui::PushID(1);
					ImGui::Checkbox("Visibility Check", &Settings::ESP::Chams::visibility_check);
				ImGui::PopID();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##CHAMSTYPE", &Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
					ImGui::Combo("##ARMSTYPE", &Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Crosshair");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
				ImGui::Checkbox("No View Punch", &Settings::View::NoPunch::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000);
					ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255);
				ImGui::PopItemWidth();
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
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
	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Y Axis", &Settings::AntiAim::enabled_Y);
		const char* YFakeTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		const char* YActualTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		const char* XTypes[] = { "UP", "DOWN", "DANCE" };

		if (ImGui::BeginChild("YAWTYPE", ImVec2(0, 60), true))
		{
			ImGui::Columns(2, NULL, false);
			{
				ImGui::SetColumnOffset(1, 150);
				ImGui::Text("Fake");
				ImGui::Text("Actual");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(150);
					ImGui::Combo("##YFAKETYPE", &Settings::AntiAim::type_fake_Y, YFakeTypes, IM_ARRAYSIZE(YFakeTypes));
					ImGui::Combo("##YACTUALTYPE", &Settings::AntiAim::type_Y, YActualTypes, IM_ARRAYSIZE(YActualTypes));
				ImGui::PopItemWidth();
			}
			ImGui::EndChild();
		}

		UI::ReverseCheckbox("X Axis", &Settings::AntiAim::enabled_X);

		ImGui::SameLine();
		ImGui::PushItemWidth(174);
			ImGui::Combo("##XTYPE", &Settings::AntiAim::type_X, XTypes, IM_ARRAYSIZE(XTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Edge", &Settings::AntiAim::HeadEdge::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##EDGEDISTANCE", &Settings::AntiAim::HeadEdge::distance, 10, 30);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Crouch", &Settings::Aimbot::AutoCrouch::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Auto Stop", &Settings::Aimbot::AutoStop::enabled);

		UI::ReverseCheckbox("Resolver", &Settings::Resolver::enabled);
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("Auto Wall", &Settings::Aimbot::AutoWall::enabled);
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##AUTOWALLDMG", &Settings::Aimbot::AutoWall::value, 0, 100, "Min Damage %f");
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(150);
			ImGui::ListBoxHeader("##AUTOWALLBODYPART", 6);
				ImGui::Selectable("Head", &Settings::Aimbot::AutoWall::bones[HITBOX_HEAD]);
				ImGui::Selectable("Neck", &Settings::Aimbot::AutoWall::bones[HITBOX_NECK]);
				ImGui::Selectable("Pelvis", &Settings::Aimbot::AutoWall::bones[HITBOX_PELVIS]);
				ImGui::Selectable("Spine", &Settings::Aimbot::AutoWall::bones[HITBOX_SPINE]);
				ImGui::Selectable("Legs", &Settings::Aimbot::AutoWall::bones[HITBOX_LEGS]);
				ImGui::Selectable("Arms", &Settings::Aimbot::AutoWall::bones[HITBOX_ARMS]);
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	}
}

void MiscTab()
{
	const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right" };
	static char nickname[127] = "";
	const char* AnimationTypes[] = { "Static", "Marquee", "Words", "Letters" };

	ImGui::Columns(2, NULL, true);
	{
		if (ImGui::BeginChild("Child1", ImVec2(0, 0), true))
		{
			ImGui::Text("Movement");
			ImGui::Separator();
			ImGui::Checkbox("Bunny Hop", &Settings::BHop::enabled);
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
					ImGui::Checkbox("Auto Strafe", &Settings::AutoStrafe::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::Combo("##STRAFETYPE", &Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Spammer");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Position", &Settings::Spammer::PositionSpammer::enabled);
				ImGui::Checkbox("Kill", &Settings::Spammer::KillSpammer::enabled);
				ImGui::Checkbox("Chat", &Settings::Spammer::NormalSpammer::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat Only", &Settings::Spammer::PositionSpammer::say_team);
				ImGui::Checkbox("Team Chat Only", &Settings::Spammer::KillSpammer::say_team);
				ImGui::Checkbox("Team Chat Only", &Settings::Spammer::NormalSpammer::say_team);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("FOV");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("FOV", &Settings::FOVChanger::enabled);
				ImGui::Checkbox("Viewmodel FOV", &Settings::FOVChanger::viewmodel_enabled);
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
		if (ImGui::BeginChild("Child2", ImVec2(0, 0), true))
		{
			ImGui::Text("Clantag");
			ImGui::Separator();
			ImGui::Checkbox("Enabled", &Settings::ClanTagChanger::enabled);
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
					ImGui::InputText("##CLANTAGTEXT", Settings::ClanTagChanger::value, 30);
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##ANIMATIONTYPE", &Settings::ClanTagChanger::type, AnimationTypes, IM_ARRAYSIZE(AnimationTypes)))
					{
						switch (Settings::ClanTagChanger::type)
						{
							case MARQUEE:
								ClanTagChanger::animations[0] = ClanTagChanger::Marquee("CUSTOM", Settings::ClanTagChanger::value);
								break;
							case WORDS:
								ClanTagChanger::animations[0] = ClanTagChanger::Words("CUSTOM", Settings::ClanTagChanger::value);
								break;
							case LETTERS:
								ClanTagChanger::animations[0] = ClanTagChanger::Letters("CUSTOM", Settings::ClanTagChanger::value);
								break;
						}
					}
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Nickname");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
					ImGui::InputText("##NICKNAMETEXT", nickname, 127);
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Set Nickname"))
					NameChanger::SetName(nickname);
				ImGui::SameLine();
				if (ImGui::Button("No Name", ImVec2(-1, 0)))
				{
					Settings::NameChanger::enabled = true;
					Settings::NameChanger::last_blank = true;
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Fake Lag", &Settings::FakeLag::enabled);
				ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
				ImGui::Checkbox("AirStuck", &Settings::Airstuck::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16);
				ImGui::PopItemWidth();
				ImGui::Checkbox("Show Ranks", &Settings::ShowRanks::enabled);
				UI::KeyBindButton(&Settings::Airstuck::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}

void MainWindow()
{
	if (!showMainWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(1000, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("AimTux", &showMainWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] =
				{
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
			int height = 25;

			if (ImGui::Button(tabs[i], ImVec2(width, height)))
				page = i;

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

	ImGui::SetNextWindowSize(ImVec2(800, 690), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin Changer", &showSkinChangerWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		static int current_weapon = 1;
		static int current_weapon_skin = Settings::Skinchanger::skins[current_weapon].PaintKit;
		static float weaponWear = 0.00050000002374872565f;
		static int weaponSkinSeed;
		static int weaponStatTrak;
		static char weaponName[18];
		static int isCT = 1;

		if (ImGui::Checkbox("Enabled", &Settings::Skinchanger::enabled))
			SkinChanger::ForceFullUpdate = true;

		ImGui::Separator();
		if (ImGui::BeginChild("##GUNSECTION", ImVec2(0, 0), true))
		{
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Text("Guns");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Skins");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
					ImGui::ListBoxHeader("##GUNS", ImVec2(0, 300));
						for (int i = 0; i < IM_ARRAYSIZE(guns); i++)
						{
							const bool item_selected = (i == current_weapon);
							if (strlen(guns[i]) == 0)
								continue;
							ImGui::PushID(i);
								if (ImGui::Selectable(guns[i], item_selected))
								{
									current_weapon = i;

									auto keyExists = Settings::Skinchanger::skins.find(i);
									if (keyExists == Settings::Skinchanger::skins.end())
										current_weapon_skin = -1;
									else
										current_weapon_skin = Settings::Skinchanger::skins[i].PaintKit;
								}
							ImGui::PopID();
						}
				ImGui::ListBoxFooter();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
					ImGui::ListBoxHeader("##SKINS", ImVec2(0, 300));
						for (int i = 0; i < IM_ARRAYSIZE(weapon_skins); i++)
						{
							const bool item_selected = (i == current_weapon_skin);
							if (strlen(weapon_skins[i]) == 0)
									continue;
							ImGui::PushID(i);
								if (ImGui::Selectable(weapon_skins[i], item_selected))
									current_weapon_skin = i;
							ImGui::PopID();
						}
					ImGui::ListBoxFooter();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Text("Knife");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Other");
			}
			ImGui::Separator();
			ImGui::Columns(1);
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::BeginChild("##KNIFESECTION", ImVec2(0, 0), true))
				{
					ImGui::Columns(2, NULL, false);
					{
						ImGui::SetColumnOffset(1, ImGui::GetWindowWidth() - 60);
						ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
							for (int i = 0; i < IM_ARRAYSIZE(knives); i++)
							{
								const bool item_selected = ((WEAPON_KNIFE_BAYONET + i) == current_weapon);
								if (strlen(knives[i]) == 0)
										continue;
								ImGui::PushID(i);
									if (ImGui::Selectable(knives[i], item_selected))
									{
										current_weapon = (WEAPON_KNIFE_BAYONET + i);
										current_weapon_skin = Settings::Skinchanger::skins[isCT > 0 ? WEAPON_KNIFE : WEAPON_KNIFE_T].PaintKit;
									}
								ImGui::PopID();
							}
						ImGui::ListBoxFooter();
					}
					ImGui::NextColumn();
					{
						ImGui::RadioButton("CT", &isCT, 1);
						ImGui::RadioButton("T", &isCT, 0);
					}
					ImGui::Columns(1);
					ImGui::EndChild();
				}
			}
			ImGui::NextColumn();
			{
				if (ImGui::BeginChild("Other", ImVec2(-1, -1), true))
				{
					ImGui::InputInt("Skin ID", &current_weapon_skin);
					ImGui::SliderFloat("Wear", &weaponWear, 0.00050000002374872565f, 1.0f, "0%f");
					ImGui::InputInt("Seed", &weaponSkinSeed);
					ImGui::InputInt("StatTrak", &weaponStatTrak);
					ImGui::InputText("Name", weaponName, IM_ARRAYSIZE(weaponName));
					ImGui::Separator();
					ImGui::Columns(2, NULL, true);
					{
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

								current_weapon_skin = skin.PaintKit;
								weaponSkinSeed = skin.Seed;
								weaponWear = skin.Wear;
								weaponStatTrak = skin.StatTrak;
								std::fill(std::begin(weaponName), std::end(weaponName), 0);
								std::copy(std::begin(skin.CustomName), std::end(skin.CustomName), std::begin(weaponName));
							}
						}
					}
					ImGui::NextColumn();
					{
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
					}
					ImGui::EndChild();
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}
}

void ConfigWindow()
{
	if (!showConfigWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(195, 250), ImGuiSetCond_Always);
	if (ImGui::Begin("Configs", &showConfigWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		static std::vector<std::string> configItems = GetConfigs();
		static int configItemCurrent = -1;

		if (ImGui::Button("Refresh"))
			configItems = GetConfigs();

		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent] << "/config.json";

			Settings::LoadDefaultsOrSave(path);
		}

		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent];

			Settings::DeleteConfig(path);

			configItems = GetConfigs();
			configItemCurrent = -1;
		}

		static char buf[128] = "";
		ImGui::PushItemWidth(138);
			ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button("Add"))
		{
			if (strlen(buf) == 0)
				return;

			pstring path = GetConfigDirectory();
			path << buf;

			if (DoesFileExist(path.c_str()))
				return;

			mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			Settings::LoadDefaultsOrSave(path << "/config.json");

			configItems = GetConfigs();
		}

		ImGui::PushItemWidth(178);
		if (ImGui::ListBox("", &configItemCurrent, configItems, 7))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent] << "/config.json";

				Settings::LoadConfig(path);
			}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}

void SpectatorsWindow()
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

		C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
		std::list<int> observators = ShowSpectators::GetObservervators(localplayer);

		for (int entityId : observators)
		{
			C_BaseEntity* entity = entitylist->GetClientEntity(entityId);

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(entityId, &entityInformation);

			if (strcmp(entityInformation.guid, "BOT") == 0)
				continue;

			ImGui::Separator();

			ImGui::Text(entityInformation.name);
			ImGui::NextColumn();

			switch (*entity->GetObserverMode())
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
			}
			ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();

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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(960, 520));
			MainWindow();
		ImGui::PopStyleVar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(800, 690));
			SkinChangerWindow();
		ImGui::PopStyleVar();

		ConfigWindow();
		ColorsWindow();
	}

	SpectatorsWindow();
}
