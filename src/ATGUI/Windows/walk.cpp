#include "walk.h"

bool Walk::showWindow = false;

void Walk::RenderWindow()
{
	if( Settings::UI::Windows::Walkbot::reload )
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Walkbot::posX, Settings::UI::Windows::Walkbot::posY), ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Walkbot::sizeX, Settings::UI::Windows::Walkbot::sizeY), ImGuiSetCond_Always);
		Settings::UI::Windows::Walkbot::reload = false;
		Walk::showWindow = Settings::UI::Windows::Walkbot::open;
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Walkbot::posX, Settings::UI::Windows::Walkbot::posY), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Walkbot::sizeX, Settings::UI::Windows::Walkbot::sizeY), ImGuiSetCond_FirstUseEver);
	}
	if( !Walk::showWindow )
	{
		Settings::UI::Windows::Walkbot::open = false;
		return;
	}

	if (ImGui::Begin(XORSTR("Walkbot"), &Walk::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		Settings::UI::Windows::Walkbot::open = true;
		ImVec2 temp = ImGui::GetWindowSize();
		Settings::UI::Windows::Walkbot::sizeX = (int)temp.x;
		Settings::UI::Windows::Walkbot::sizeY = (int)temp.y;
		temp = ImGui::GetWindowPos();
		Settings::UI::Windows::Walkbot::posX = (int)temp.x;
		Settings::UI::Windows::Walkbot::posY = (int)temp.y;

		ImGui::Text(XORSTR("Dust 2 Walkbot"));

		if (ImGui::Checkbox(XORSTR("Enable"), &Settings::WalkBot::enabled)){
			cvar->ConsoleDPrintf(XORSTR("\n---WalkBot %s---\n"), Settings::WalkBot::enabled ? XORSTR("ON") : XORSTR("OFF"));
		}

		ImGui::SameLine();
		if (ImGui::Button(XORSTR("Reset"))){
			Settings::WalkBot::forceReset = true;
		}

		ImGui::Separator();

		if (ImGui::Checkbox(XORSTR("Autobuy"), &Settings::WalkBot::autobuy)){
			cvar->ConsoleColorPrintf(ColorRGBA(100, 150, 90), XORSTR("\n---WalkBot-AutoBuy %s---\n"), Settings::WalkBot::autobuy ?XORSTR("ON") : XORSTR("OFF"));
		}
		ImGui::SameLine();
		ImGui::SliderInt("", &Settings::WalkBot::autobuyAt, 0, 16000, XORSTR("Autobuy At $%0.f"));

		ImGui::End();
	}
}
