#include "skinmodelchanger.h"

bool SkinModelChanger::showWindow = false;

static int page = 0;

void TabButtons()
{
	const char* tabs[] = {
			"Models",
			"Skins",
	};

	for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
	{
		int distance = i == page ? 0 : i > page ? i - page : page - i;

		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
				Settings::UI::mainColor.Value.x - (distance * 0.06f),
				Settings::UI::mainColor.Value.y - (distance * 0.06f),
				Settings::UI::mainColor.Value.z - (distance * 0.06f),
				Settings::UI::mainColor.Value.w
		);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
			page = i;

		ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor;

		if (i < IM_ARRAYSIZE(tabs) - 1)
			ImGui::SameLine();
	}
}

void SkinModelChanger::RenderWindow()
{
	if (!SkinModelChanger::showWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(1050, 645), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin & Model Changer", &SkinModelChanger::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		TabButtons();
		ImGui::Separator();
		switch (page)
		{
			case 0:
				Models::RenderTab();
				break;
			case 1:
				Skins::RenderTab();
				break;
		}
		ImGui::End();
	}
};
