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
				Settings::UI::mainColor.Color().Value.x - (distance * 0.06f),
				Settings::UI::mainColor.Color().Value.y - (distance * 0.06f),
				Settings::UI::mainColor.Color().Value.z - (distance * 0.06f),
				Settings::UI::mainColor.Color().Value.w
		);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
			page = i;

		ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor.Color();

		if (i < IM_ARRAYSIZE(tabs) - 1)
			ImGui::SameLine();
	}
}

void SkinModelChanger::RenderWindow()
{
	if( Settings::UI::Windows::Skinmodel::reload )
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Skinmodel::posX, Settings::UI::Windows::Skinmodel::posY), ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Skinmodel::sizeX, Settings::UI::Windows::Skinmodel::sizeY), ImGuiSetCond_Always);
		Settings::UI::Windows::Skinmodel::reload = false;
		SkinModelChanger::showWindow = Settings::UI::Windows::Skinmodel::open;
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Skinmodel::posX, Settings::UI::Windows::Skinmodel::posY), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Skinmodel::sizeX, Settings::UI::Windows::Skinmodel::sizeY), ImGuiSetCond_FirstUseEver);
	}
	if (!SkinModelChanger::showWindow)
	{
		Settings::UI::Windows::Skinmodel::open = false;
		return;
	}

	if (ImGui::Begin(XORSTR("Skin & Model Changer"), &SkinModelChanger::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		Settings::UI::Windows::Skinmodel::open = true;
		ImVec2 temp = ImGui::GetWindowSize();
		Settings::UI::Windows::Skinmodel::sizeX = (int)temp.x;
		Settings::UI::Windows::Skinmodel::sizeY = (int)temp.y;
		temp = ImGui::GetWindowPos();
		Settings::UI::Windows::Skinmodel::posX = (int)temp.x;
		Settings::UI::Windows::Skinmodel::posY = (int)temp.y;
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
