#include "walk.h"

bool Walk::showWindow = false;


void Walk::RenderWindow()
{
	if( !Walk::showWindow )
		return;

	ImGui::SetNextWindowSize(ImVec2(320, 240), ImGuiSetCond_Always);
	if (ImGui::Begin("Walkbot", &Walk::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Dust 2 Walkbot");

		if (ImGui::Checkbox("Enable", &Settings::WalkBot::enabled)){
			cvar->ConsoleDPrintf("\n---WalkBot %s---\n", Settings::WalkBot::enabled ? "ON" : "OFF");
		}
		SetTooltip("Turn On/Off the Dust2 Bot");

		ImGui::SameLine();
		if (ImGui::Button("Reset")){
			Settings::WalkBot::forceReset = true;
		}
		SetTooltip("Resets the Waypoints");

		ImGui::Separator();

		if (ImGui::Checkbox("Autobuy", &Settings::WalkBot::autobuy)){
			cvar->ConsoleColorPrintf(ColorRGBA(100, 150, 90), "\n---WalkBot-AutoBuy %s---\n", Settings::WalkBot::autobuy ? "ON" : "OFF");
		}
		ImGui::SameLine();
		ImGui::SliderInt("autobuyAt", &Settings::WalkBot::autobuyAt, 0, 16000, "Autobuy At $%0.f");
		SetTooltip("The amount of Money you will start to autobuy At\n (Ctrl-Click) to Type");

		ImGui::End();
	}
}