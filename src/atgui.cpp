#include "atgui.h"

bool UI::isVisible = false;

ImVec4 mainColorORIG = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
ImVec4 mainColor = ImVec4(0.5f, 0.25f, 0.75f, 1.00f);
bool showMainWindow = true;
bool showSkinChangerWindow = false;
bool showConfigWindow = false;
bool showSpectatorsWindow = false;
bool showMainColorPopupWindow = false;
bool test = false;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

void UI::SetVisible(bool visible)
{
	UI::isVisible = visible;
	cvar->FindVar("cl_mouseenable")->SetValue(!UI::isVisible);
}

void UI::SetupColors()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered = ImVec4(mainColor.x + 0.1f, mainColor.y + 0.1f, mainColor.z + 0.1f, 1.00f);
	ImVec4 mainColorActive = ImVec4(mainColor.x + 0.2f, mainColor.y + 0.2f, mainColor.z + 0.2f, 1.00f);

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
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.85f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = mainColor;
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]= ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg]= mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = mainColor;
	style.Colors[ImGuiCol_ScrollbarBg] = mainColor;
	style.Colors[ImGuiCol_ScrollbarGrab] = mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = mainColor;
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = mainColor;
	style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_Header] = mainColor;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
	style.Colors[ImGuiCol_Column] = mainColor;
	style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGrip] = mainColor;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = mainColor;
	style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = mainColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = mainColor;
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
			UI::ColorPicker3((float *)&mainColor);
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
			static char buf[128] = "Text Boxes are buggy, try typing";
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

		// ImGui::PushItemWidth(-1);
		//
		// ImGui::PopItemWidth();
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
		static char buf[128] = "Text Boxes are buggy, try typing";
		ImGui::InputText("##TRIGGERKEY", buf, IM_ARRAYSIZE(buf));
	ImGui::PopItemWidth();

	ImGui::Separator();
	UI::ReverseCheckbox("Delay", &Settings::Triggerbot::Delay::enabled);
	ImGui::SameLine();

	ImGui::PushItemWidth(200);
		ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
	ImGui::PopItemWidth();

	ImGui::Separator();
	UI::ReverseCheckbox("Friendly", &Settings::Triggerbot::Filter::friendly);
	UI::ReverseCheckbox("Head", &Settings::Triggerbot::Filter::head);
	UI::ReverseCheckbox("Chest", &Settings::Triggerbot::Filter::chest);
	UI::ReverseCheckbox("Stomach", &Settings::Triggerbot::Filter::stomach);
	UI::ReverseCheckbox("Arms", &Settings::Triggerbot::Filter::arms);
	UI::ReverseCheckbox("Legs", &Settings::Triggerbot::Filter::legs);
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
		static int WallType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##WALLTYPE", &WallType, WallTypes, IM_ARRAYSIZE(WallTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Tracers", &Settings::ESP::Tracer::enabled);
		ImGui::SameLine();

		const char* TracerTypes[] = { "Bottom", "Cursor" };
		static int TracerType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##TRACERTYPE", &TracerType, TracerTypes, IM_ARRAYSIZE(TracerTypes));
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
		static int ChamsType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##CHAMSTYPE", &ChamsType, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
		ImGui::PopItemWidth();

		UI::ReverseCheckbox("Arms", &Settings::ESP::Chams::Arms::enabled);
		ImGui::SameLine();

		const char* ArmsTypes[] = { "Rainbow", "Wireframe", "None", "Default" };
		static int ArmsType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##ARMSTYPE", &ArmsType, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
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
		ImGui::SameLine();

		UI::ReverseCheckbox("X Axis", &Settings::AntiAim::enabled_X);

		const char* YFakeTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		static int YFakeType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##YFAKETYPE", &YFakeType, YFakeTypes, IM_ARRAYSIZE(YFakeTypes));
			ImGui::PopItemWidth();
		ImGui::SameLine();

		const char* XTypes[] = { "UP", "DOWN", "DANCE" };
		static int XType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##XTYPE", &XType, XTypes, IM_ARRAYSIZE(XTypes));
		ImGui::PopItemWidth();

		const char* YActualTypes[] = { "SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT" };
		static int YActualType = 0;
		ImGui::PushItemWidth(148);
			ImGui::Combo("##YACTUALTYPE", &YActualType, YActualTypes, IM_ARRAYSIZE(YActualTypes));
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

		ImGui::PushItemWidth(100);
			ImGui::ListBoxHeader("##AUTOWALLBODYPART", 10);
				ImGui::Checkbox("Head", &Settings::Aimbot::AutoWall::bones[HITBOX_HEAD]);
				ImGui::Checkbox("Neck", &Settings::Aimbot::AutoWall::bones[HITBOX_NECK]);
				ImGui::Checkbox("Pelvis", &Settings::Aimbot::AutoWall::bones[HITBOX_PELVIS]);
				ImGui::Checkbox("Spine", &Settings::Aimbot::AutoWall::bones[HITBOX_SPINE]);
				ImGui::Checkbox("Legs", &Settings::Aimbot::AutoWall::bones[HITBOX_LEGS]);
				ImGui::Checkbox("Arms", &Settings::Aimbot::AutoWall::bones[HITBOX_ARMS]);
			ImGui::ListBoxFooter();
		ImGui::PopItemWidth();
	}
}

void MiscTab()
{
	if (ImGui::ColorButton(mainColor, true))
		showMainColorPopupWindow = true;
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
