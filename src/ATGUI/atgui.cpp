#include "atgui.h"

bool UI::isVisible = false;

bool Settings::ScreenshotCleaner::enabled = false;

ColorVar Settings::UI::mainColor = ImColor(25, 25, 25, 255);
ColorVar Settings::UI::bodyColor = ImColor(5, 5, 5, 255);
ColorVar Settings::UI::fontColor = ImColor(255, 255, 255, 255);
ColorVar Settings::UI::accentColor = ImColor(39, 106, 219, 255);

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

void SetupMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable(XORSTR("Main Window"), &Main::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Main Window"), NULL, true).x, 0.0f));
		ImGui::SameLine();

		if (ModSupport::current_mod != ModType::CSCO)
		{
			ImGui::Selectable(XORSTR("Skin & Model Changer Window"), &SkinModelChanger::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Skin & Model Changer Window"), NULL, true).x, 0.0f));
			ImGui::SameLine();
		}

		ImGui::Selectable(XORSTR("Config Window"), &Configs::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Config Window"), NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable(XORSTR("Spectators Window"), &Settings::ShowSpectators::enabled, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Spectators Window"), NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable(XORSTR("Colors Window"), &Colors::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Colors Window"), NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable(XORSTR("Player List Window"), &PlayerList::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Player List Window"), NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable(XORSTR("Walk Bot Window"), &Walk::showWindow, 0, ImVec2(ImGui::CalcTextSize(XORSTR("Walk Bot Window"), NULL, true).x, 0.0f));
		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x-ImVec2(ImGui::CalcTextSize(XORSTR("Unload   "), NULL, true)).x);

		if( ImGui::Button(XORSTR("Unload   "), ImVec2(ImGui::CalcTextSize(XORSTR("Unload   "), NULL, true).x, 0.0f)) )
		{
			Fuzion::SelfShutdown();
		}


		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void UI::SwapWindow()
{
	if (UI::isVisible)
		return;

	if (engine->IsInGame())
		return;

	Draw::ImDrawText(ImVec2(4.f, 4.f), ImColor(255, 255, 255, 255), XORSTR("Fuzion"), NULL, 0.0f, NULL, ImFontFlags_Shadow);
}

void UI::SetVisible(bool visible)
{
	UI::isVisible = visible;
	cvar->FindVar(XORSTR("cl_mouseenable"))->SetValue(!UI::isVisible);
}

void UI::SetupWindows()
{
	if (UI::isVisible)
	{
		SetupMainMenuBar();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(960, 645));
			Main::RenderWindow();
		ImGui::PopStyleVar();

		if (ModSupport::current_mod != ModType::CSCO)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1050, 645));
				SkinModelChanger::RenderWindow();
			ImGui::PopStyleVar();
		}

		Configs::RenderWindow();
		Colors::RenderWindow();
		PlayerList::RenderWindow();
		Walk::RenderWindow();
	}

	ShowSpectators::RenderWindow();
	Radar::RenderWindow();
}
