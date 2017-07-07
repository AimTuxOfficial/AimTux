#include "configs.h"

bool Configs::showWindow = false;

void Configs::RenderWindow()
{
	if( Settings::UI::Windows::Config::reload )
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Config::posX, Settings::UI::Windows::Config::posY), ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Config::sizeX, Settings::UI::Windows::Config::sizeY), ImGuiSetCond_Always);
		Settings::UI::Windows::Config::reload = false;
		Configs::showWindow = Settings::UI::Windows::Config::open;
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Config::posX, Settings::UI::Windows::Config::posY), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Config::sizeX, Settings::UI::Windows::Config::sizeY), ImGuiSetCond_FirstUseEver);
	}
	if (!Configs::showWindow)
	{
		Settings::UI::Windows::Config::open = false;
		return;
	}

	if (ImGui::Begin(XORSTR("Configs"), &Configs::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		Settings::UI::Windows::Config::open = true;
		ImVec2 temp = ImGui::GetWindowSize();
		Settings::UI::Windows::Config::sizeX = (int)temp.x;
		Settings::UI::Windows::Config::sizeY = (int)temp.y;
		temp = ImGui::GetWindowPos();
		Settings::UI::Windows::Config::posX = (int)temp.x;
		Settings::UI::Windows::Config::posY = (int)temp.y;

		static std::vector<std::string> configItems = GetConfigs();
		static int configItemCurrent = -1;

		if (ImGui::Button(XORSTR("Refresh")))
			configItems = GetConfigs();

		ImGui::SameLine();
		if (ImGui::Button(XORSTR("Save")))
		{
			if (configItems.size() > 0 && (configItemCurrent >= 0 && configItemCurrent < (int) configItems.size()))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent] << XORSTR("/config.json");

				Settings::LoadDefaultsOrSave(path);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(XORSTR("Remove")))
		{
			if (configItems.size() > 0 && (configItemCurrent >= 0 && configItemCurrent < (int) configItems.size()))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent];

				Settings::DeleteConfig(path);

				configItems = GetConfigs();
				configItemCurrent = -1;
			}
		}

		static char buf[128] = "";
		ImGui::PushItemWidth(138);
		ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button(XORSTR("Add")) && strlen(buf) > 0)
		{
			pstring path = GetConfigDirectory();
			path << buf;

			if (!DoesFileExist(path.c_str()))
			{
				mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				Settings::LoadDefaultsOrSave(path << XORSTR("/config.json"));

				configItems = GetConfigs();
				configItemCurrent = -1;
			}
		}

		ImGui::PushItemWidth(178);
		if (ImGui::ListBox("", &configItemCurrent, configItems, 7))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent] << XORSTR("/config.json");

			Settings::LoadConfig(path);
			UI::ReloadWeaponSettings();
		}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}
