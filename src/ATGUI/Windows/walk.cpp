#include "walk.h"

bool Walk::showWindow = false;


void Walk::RenderWindow()
{
	if( !Walk::showWindow )
		return;

	ImGui::SetNextWindowSize(ImVec2(280, 110), ImGuiSetCond_Always);
	if (ImGui::Begin(XORSTR("Walkbot"), &Walk::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
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
