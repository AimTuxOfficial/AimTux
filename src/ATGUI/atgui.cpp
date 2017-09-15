#include "atgui.h"

bool UI::isVisible = false;

bool Settings::ScreenshotCleaner::enabled = false;

ColorVar Settings::UI::mainColor = ImColor(25, 25, 25, 255);
ColorVar Settings::UI::bodyColor = ImColor(5, 5, 5, 255);
ColorVar Settings::UI::fontColor = ImColor(255, 255, 255, 255);
ColorVar Settings::UI::accentColor = ImColor(39, 106, 219, 255);
/* Window Position/Size Defaults */
int Settings::UI::Windows::Colors::sizeX = 540;
int Settings::UI::Windows::Colors::sizeY = 325;
int Settings::UI::Windows::Colors::posX = 540;
int Settings::UI::Windows::Colors::posY = 325;

int Settings::UI::Windows::Config::sizeX = 185;
int Settings::UI::Windows::Config::sizeY = 250;
int Settings::UI::Windows::Config::posX = 185;
int Settings::UI::Windows::Config::posY = 250;

int Settings::UI::Windows::Main::sizeX = 960;
int Settings::UI::Windows::Main::sizeY = 645;
int Settings::UI::Windows::Main::posX = 20;
int Settings::UI::Windows::Main::posY = 20;

int Settings::UI::Windows::Playerlist::sizeX = 700;
int Settings::UI::Windows::Playerlist::sizeY = 500;
int Settings::UI::Windows::Playerlist::posX = 700;
int Settings::UI::Windows::Playerlist::posY = 500;

int Settings::UI::Windows::Skinmodel::sizeX = 1050;
int Settings::UI::Windows::Skinmodel::sizeY = 645;
int Settings::UI::Windows::Skinmodel::posX = 1050;
int Settings::UI::Windows::Skinmodel::posY = 645;

int Settings::UI::Windows::Spectators::sizeX = 50;
int Settings::UI::Windows::Spectators::sizeY = 100;
int Settings::UI::Windows::Spectators::posX = 50;
int Settings::UI::Windows::Spectators::posY = 100;

int Settings::UI::Windows::Walkbot::sizeX = 280;
int Settings::UI::Windows::Walkbot::sizeY = 110;
int Settings::UI::Windows::Walkbot::posX = 280;
int Settings::UI::Windows::Walkbot::posY = 110;

bool Settings::UI::Windows::Main::open = false;
bool Settings::UI::Windows::Colors::open = false;
bool Settings::UI::Windows::Config::open = false;
bool Settings::UI::Windows::Playerlist::open = false;
bool Settings::UI::Windows::Skinmodel::open = false;
bool Settings::UI::Windows::Walkbot::open = false;

bool Settings::UI::Windows::Main::reload = false;
bool Settings::UI::Windows::Colors::reload = false;
bool Settings::UI::Windows::Config::reload = false;
bool Settings::UI::Windows::Playerlist::reload = false;
bool Settings::UI::Windows::Skinmodel::reload = false;
bool Settings::UI::Windows::Spectators::reload = false;
bool Settings::UI::Windows::Walkbot::reload = false;


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

    Draw::ImText( ImVec2( 4.f, 4.f ), ImColor( 255, 255, 255, 255 ), XORSTR( "Fuzion" ), NULL, 0.0f, NULL,
                  ImFontFlags_Shadow );
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
