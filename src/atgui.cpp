#include "atgui.h"

bool UI::isVisible = false;

ImVec4 Settings::UI::mainColor = ImVec4(0.5f, 0.25f, 0.75f, 1.00f);
ImVec4 Settings::UI::bodyColor = ImVec4(0.06f, 0.05f, 0.07f, 0.85f);
bool showMainWindow = true;
bool showSkinChangerWindow = false;
bool showConfigWindow = false;
bool showSpectatorsWindow = false;
bool showMainColorPopupWindow = false;
bool test = false;

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

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
					   static_cast<void*>(&values), values.size());
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

	ImVec4 mainColorHovered = ImVec4(Settings::UI::mainColor.x + 0.1f, Settings::UI::mainColor.y + 0.1f, Settings::UI::mainColor.z + 0.1f, Settings::UI::mainColor.w);
	ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.x + 0.2f, Settings::UI::mainColor.y + 0.2f, Settings::UI::mainColor.z + 0.2f, Settings::UI::mainColor.w);

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
	style.ColumnsMinSpacing = 6.0f;
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

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = Settings::UI::bodyColor;
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]= ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg]= Settings::UI::mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarBg] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
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
		if (ImGui::Button("Main Window")) showMainWindow = !showMainWindow;
		ImGui::SameLine();

		if (ImGui::Button("Skin Changer Window")) showSkinChangerWindow = !showSkinChangerWindow;
		ImGui::SameLine();

		if (ImGui::Button("Config Window")) showConfigWindow = !showConfigWindow;
		ImGui::SameLine();

		if (ImGui::Button("Spectators")) showSpectatorsWindow = !showSpectatorsWindow;
		ImGui::SameLine();

		ImGui::EndMainMenuBar();
	}
}

void PopupWindows()
{
	if (showMainColorPopupWindow)
	{
		ImGui::SetNextWindowSize(ImVec2(240, 265), ImGuiSetCond_Always);

		if (ImGui::Begin("Color", &showMainColorPopupWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
		{
			UI::ColorPicker3((float *)&Settings::UI::mainColor);
			if (ImGui::Button("Close")) showMainColorPopupWindow = false;

			ImGui::End();
		}
	}
}

void AimbotTab()
{
	UI::ReverseCheckbox("Enabled", &Settings::Aimbot::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Silent Aim", &Settings::Aimbot::silent);

		UI::ReverseCheckbox("Aimkey Only", &Settings::Aimbot::aimkey_only);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			static char buf[128] = "TODO: hotkeys";
			ImGui::InputText("##AIMKEY", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Recoil Control", &Settings::Aimbot::RCS::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##RCS", &Settings::Aimbot::RCS::value, 0, 2);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Aim", &Settings::Aimbot::AutoAim::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##AA", &Settings::Aimbot::fov, 0, 180);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Smoothing", &Settings::Aimbot::Smooth::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##SMOOTH", &Settings::Aimbot::Smooth::value, 0, 1);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Smooth Salting", &Settings::Aimbot::Smooth::Salting::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##SALT", &Settings::Aimbot::Smooth::Salting::percentage, 0, 100);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Aim Step", &Settings::Aimbot::AimStep::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##STEP", &Settings::Aimbot::AimStep::value, 0, 100);
			ImGui::SliderFloat("##ERROR", &Settings::Aimbot::errorMargin, 0, 2, "Error Margin 0%f");
		ImGui::PopItemWidth();
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("Friendly          ", &Settings::Aimbot::friendly);
		ImGui::SameLine();
		const char* targets[] = { "PELVIS", "LEAN_ROOT", "CAM_DRIVER", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };
		ImGui::PushItemWidth(148);
			ImGui::Combo("##AIMTARGET", &Settings::Aimbot::bone, targets, IM_ARRAYSIZE(targets));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Auto Pistol", &Settings::Aimbot::AutoPistol::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("No Shoot", &Settings::Aimbot::no_shoot);

		UI::ReverseCheckbox("Auto Shoot", &Settings::Aimbot::AutoShoot::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Auto Scope", &Settings::Aimbot::AutoShoot::autoscope);
	}

}

void TriggerbotTab()
{
	UI::ReverseCheckbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::SameLine();
	ImGui::PushItemWidth(200);
		static char buf[128] = "TODO: hotkeys";
		ImGui::InputText("##TRIGGERKEY", buf, IM_ARRAYSIZE(buf));
	ImGui::PopItemWidth();

	ImGui::Separator();

	UI::ReverseCheckbox("Delay", &Settings::Triggerbot::Delay::enabled);
	ImGui::SameLine();
	ImGui::PushItemWidth(200);
		ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
	ImGui::PopItemWidth();

	ImGui::Separator();
	ImGui::PushItemWidth(148);
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
	UI::ReverseCheckbox("Enabled", &Settings::ESP::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Walls", &Settings::ESP::Walls::enabled);
		ImGui::SameLine();
		const char* WallTypes[] = { "2D", "3D" };
		ImGui::PushItemWidth(148);
			ImGui::Combo("##WALLTYPE", &Settings::ESP::Walls::type, WallTypes, IM_ARRAYSIZE(WallTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Tracers", &Settings::ESP::Tracer::enabled);
		ImGui::SameLine();
		const char* TracerTypes[] = { "Bottom", "Cursor" };
		ImGui::PushItemWidth(148);
			ImGui::Combo("##TRACERTYPE", &Settings::ESP::Tracer::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Show Name", &Settings::ESP::Info::showName);

		UI::ReverseCheckbox("Show Health", &Settings::ESP::Info::showHealth);

		UI::ReverseCheckbox("Show Weapon", &Settings::ESP::Info::showWeapon);

		UI::ReverseCheckbox("Color Code", &Settings::ESP::Info::colorCode);

		UI::ReverseCheckbox("Show Bones", &Settings::ESP::Bones::enabled);

		UI::ReverseCheckbox("Show Friendly", &Settings::ESP::friendly);

		UI::ReverseCheckbox("Visibility Check", &Settings::ESP::visibility_check);

	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("Players", &Settings::ESP::Chams::players);
		ImGui::SameLine();
		const char* ChamsTypes[] = { "Normal", "Flat" };
		ImGui::PushItemWidth(148);
			ImGui::Combo("##CHAMSTYPE", &Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Arms", &Settings::ESP::Chams::Arms::enabled);
		ImGui::SameLine();
		const char* ArmsTypes[] = { "Default", "Rainbow", "Wireframe", "None"  };
		ImGui::PushItemWidth(148);
			ImGui::Combo("##ARMSTYPE", &Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
		ImGui::PopItemWidth();

		ImGui::PushID(1);
			UI::ReverseCheckbox("Visibility Check", &Settings::ESP::Chams::visibility_check);
		ImGui::PopID();

		UI::ReverseCheckbox("Bomb ESP", &Settings::ESP::Bomb::enabled);

		UI::ReverseCheckbox("Weapon Names", &Settings::ESP::Weapons::enabled);

		UI::ReverseCheckbox("Glow", &Settings::ESP::Glow::enabled);

		UI::ReverseCheckbox("Dlights", &Settings::Dlights::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("No View Punch", &Settings::View::NoPunch::enabled);
	}

	ImGui::Columns(1);

	ImGui::Separator();

	UI::ReverseCheckbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
	ImGui::SameLine();
	UI::ReverseCheckbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);

	UI::ReverseCheckbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);

}

void HvHTab()
{
	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Y Axis", &Settings::AntiAim::enabled_Y);

		const char* YFakeTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		static int YFakeType = 0;

		ImGui::Text(""); ImGui::SameLine(); ImGui::Text(""); ImGui::SameLine(); ImGui::Text("Fake               ");
		ImGui::SameLine();

		ImGui::PushItemWidth(148);
			ImGui::Combo("##YFAKETYPE", &YFakeType, YFakeTypes, IM_ARRAYSIZE(YFakeTypes));
			ImGui::PopItemWidth();

		const char* YActualTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		static int YActualType = 0;

		ImGui::Text(""); ImGui::SameLine(); ImGui::Text(""); ImGui::SameLine(); ImGui::Text("Actual             ");
		ImGui::SameLine();

		ImGui::PushItemWidth(148);
			ImGui::Combo("##YACTUALTYPE", &YActualType, YActualTypes, IM_ARRAYSIZE(YActualTypes));
		ImGui::PopItemWidth();

		const char* XTypes[] = { "UP", "DOWN", "DANCE" };
		static int XType = 0;

		UI::ReverseCheckbox("X Axis", &Settings::AntiAim::enabled_X);
		ImGui::SameLine();
		ImGui::PushItemWidth(148);
			ImGui::Combo("##XTYPE", &XType, XTypes, IM_ARRAYSIZE(XTypes));
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

		ImGui::PushItemWidth(148);
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
	ImGui::Columns(2, NULL, false);
	{
		UI::ReverseCheckbox("Bunny Hop", &Settings::BHop::enabled);
		ImGui::SameLine();

		UI::ReverseCheckbox("Auto Strafe", &Settings::AutoStrafe::enabled);
		ImGui::SameLine();

		const char* StrafeTypes[] = { "Forwards", "Backwards", "Left", "Right" };
		static int StrafeType = 0;
		ImGui::PushItemWidth(-1);
			ImGui::Combo("##STRAFETYPE", &StrafeType, StrafeTypes, IM_ARRAYSIZE(StrafeTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("AirStuck", &Settings::Airstuck::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			static char buf[128] = "TODO: hotkeys";
			ImGui::InputText("##AIRSTUCKKEY", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Position Spammer", &Settings::Spammer::PositionSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::PositionSpammer::say_team);

		UI::ReverseCheckbox("Kill Spammer", &Settings::Spammer::KillSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::KillSpammer::say_team);

		UI::ReverseCheckbox("Chat Spammer", &Settings::Spammer::NormalSpammer::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Team Chat Only", &Settings::Spammer::NormalSpammer::say_team);

		UI::ReverseCheckbox("Custom Clantag", &Settings::ClanTagChanger::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::InputText("##CLANTAGTEXT", Settings::ClanTagChanger::value, 15);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Animate Clantag", &Settings::ClanTagChanger::animation);
		ImGui::SameLine();
		const char* AnimationTypes[] = { "Marquee", "Words", "Letters" };
		static int AnimationType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##ANIMATIONTYPE", &AnimationType, AnimationTypes, IM_ARRAYSIZE(AnimationTypes));
		ImGui::PopItemWidth();
	}

	ImGui::NextColumn();
	{
		UI::ReverseCheckbox("No Flash", &Settings::Noflash::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("View FOV", &Settings::FOVChanger::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Viewmodel FOV", &Settings::FOVChanger::viewmodel_enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodel_value, 0, 360);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Fake Lag", &Settings::FakeLag::enabled);
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
			ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16);
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Radar", &Settings::Radar::enabled);

		UI::ReverseCheckbox("Auto Accept", &Settings::AutoAccept::enabled);

		UI::ReverseCheckbox("Show Ranks", &Settings::ShowRanks::enabled);
		ImGui::SameLine();
		UI::ReverseCheckbox("Show Spectators", &Settings::ShowSpectators::enabled);

		static char nickname[127] = "nickname";

		ImGui::Button("No Name");
		ImGui::SameLine();

		if (ImGui::Button("Set Nickname"))
			NameChanger::SetName(nickname);
		ImGui::SameLine();

		ImGui::PushItemWidth(-1);
			ImGui::InputText("##NICKNAMETEXT", nickname, 127);
		ImGui::PopItemWidth();

		ImGui::Text("UI Main Color");
		ImGui::SameLine();
		if (ImGui::ColorButton(Settings::UI::mainColor, true))
			showMainColorPopupWindow = true;
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

	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Skin Changer", &showSkinChangerWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);

	ImGui::End();
}

void ConfigWindow()
{
	if (!showConfigWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Configs", &showConfigWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);

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
	ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

	ImGui::SameLine();
	if (ImGui::Button("Add"))
	{
		printf("%s\n", buf);
		if (strlen(buf) == 0)
			return;

		pstring path = GetConfigDirectory();
		path << buf;

		printf("path: %s\n", path.c_str());

		if (DoesFileExist(path.c_str()))
			return;

		mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		Settings::LoadDefaultsOrSave(path  << "/config.json");

		configItems = GetConfigs();
	}

	if (ImGui::ListBox("", &configItemCurrent, configItems))
	{
		pstring path = GetConfigDirectory();
		path << configItems[configItemCurrent] << "/config.json";

		Settings::LoadConfig(path);
	}

	ImGui::End();
}

void SpectatorsWindow()
{
	if (!showSpectatorsWindow)
		return;

	if (!UI::isVisible && !engine->IsInGame())
		return;

	ImGui::SetNextWindowSize(ImVec2(50, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Spectators", &showSpectatorsWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);

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

void DrawBanner()
{
	if (UI::isVisible)
		return;

	if (engine->IsInGame())
		return;

	// Make a static invisible window to draw text on
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(50, 100), ImGuiSetCond_Always);
	ImGui::Begin(
			"Banner",
			(bool*)true,
			ImVec2(100, 100),
			0.f,
			ImGuiWindowFlags_NoTitleBar
			|ImGuiWindowFlags_NoResize
			|ImGuiWindowFlags_NoMove
			|ImGuiWindowFlags_NoScrollbar
			|ImGuiWindowFlags_NoSavedSettings
			|ImGuiWindowFlags_NoInputs
	);

	ImGui::GetWindowDrawList()->AddText(
			ImGui::GetWindowFont(),
			ImGui::GetWindowFontSize(),
			ImVec2(4.f, 4.f),
			ImColor(255, 255, 255, 255),
			"AimTux",
			0,
			0.0f,
			0
	);

	ImGui::End();
}

void UI::SetupWindows()
{
	if (UI::isVisible)
	{
		SetupMainMenuBar();
		MainWindow();
		SkinChangerWindow();
		ConfigWindow();
		PopupWindows();
	}

	SpectatorsWindow();
	DrawBanner();
}

bool UI::ReverseCheckbox(std::string name, bool* toggle, int spaces /*= 18*/)
{
	std::string prefix = "##";
	std::string outputTag = prefix + name;

	std::string text = name;
	for (int i = 0; i < spaces - name.length(); i++)
		text += ' ';

	ImGui::Text(text.c_str()); ImGui::SameLine();	ImGui::Checkbox(outputTag.c_str(), toggle);
}

bool UI::ColorPicker(float *col, bool alphabar)
{
	const int EDGE_SIZE = 200; // = int(ImGui::GetWindowWidth() * 0.75f);
	const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
	const float SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
	const float HUE_PICKER_WIDTH = 20.f;
	const float CROSSHAIR_SIZE = 7.0f;

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	ImColor colors[] = { ImColor(255, 0, 0),
						 ImColor(255, 255, 0),
						 ImColor(0, 255, 0),
						 ImColor(0, 255, 255),
						 ImColor(0, 0, 255),
						 ImColor(255, 0, 255),
						 ImColor(255, 0, 0) };

	for (int i = 0; i < 6; i++)
	{
		draw_list->AddRectFilledMultiColor(
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
					   picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
				colors[i],
				colors[i],
				colors[i + 1],
				colors[i + 1]
		);
	}

	draw_list->AddLine(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
			ImColor(255, 255, 255)
	);

	if (alphabar)
	{
		float alpha = col[3];

		draw_list->AddRectFilledMultiColor(
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + HUE_PICKER_WIDTH, picker_pos.y),
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + 2 * HUE_PICKER_WIDTH, picker_pos.y + SV_PICKER_SIZE.y),
				ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(255, 255, 255), ImColor(255, 255, 255)
		);

		draw_list->AddLine(
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING - 2) + HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
				ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING + 2) + 2 * HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
				ImColor(255.f - alpha, 255.f, 255.f)
		);
	}

	const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
	const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImVec4 cHueValue(1, 1, 1, 1);
	ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
	ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

	draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
			c_oColorWhite,
			oHueColor,
			oHueColor,
			c_oColorWhite
	);

	draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
			c_oColorBlackTransparent,
			c_oColorBlackTransparent,
			c_oColorBlack,
			c_oColorBlack
	);

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.x <	0)
			mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1)
			mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		if (mouse_pos_in_canvas.y < 0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	// hue bar logic
	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.y <	0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	if (alphabar)
	{
		ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING * 2 + HUE_PICKER_WIDTH + SV_PICKER_SIZE.x, picker_pos.y));
		ImGui::InvisibleButton("alpha_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

		if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			if (mouse_pos_in_canvas.y <	0)
				mouse_pos_in_canvas.y = 0;
			else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
				mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

			float alpha = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
			col[3] = alpha;
			value_changed = true;
		}
	}

	color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10*1e-6, value > 0 ? value : 1e-6);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;

	bool widget_used;
	ImGui::PushItemWidth((alphabar ? SPACING + HUE_PICKER_WIDTH : 0) + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH - 2*ImGui::GetStyle().FramePadding.x);
	widget_used = alphabar ? ImGui::ColorEdit4("", col) : ImGui::ColorEdit3("", col);
	ImGui::PopItemWidth();

	float new_hue, new_sat, new_val;
	ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_hue, new_sat, new_val);

	if (new_hue <= 0 && hue > 0)
	{
		if (new_val <= 0 && value != new_val)
		{
			color = ImColor::HSV(hue, saturation, new_val <= 0 ? value * 0.5f : new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
		else if (new_sat <= 0)
		{
			color = ImColor::HSV(hue, new_sat <= 0 ? saturation * 0.5f : new_sat, new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
	}

	return value_changed | widget_used;
}

bool UI::ColorPicker3(float col[3])
{
	return UI::ColorPicker(col, false);
}

bool UI::ColorPicker4(float col[4])
{
	return UI::ColorPicker(col, true);
}
