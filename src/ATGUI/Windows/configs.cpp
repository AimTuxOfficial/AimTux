#include "configs.h"

bool Configs::showWindow = false;

void Configs::RenderWindow()
{
	if (!Configs::showWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(195, 260), ImGuiSetCond_Always);
	if (ImGui::Begin("Configs", &Configs::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		static std::vector<std::string> configItems = GetConfigs();
		static int configItemCurrent = -1;

		if (ImGui::Button("Refresh"))
			configItems = GetConfigs();

		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			if (configItems.size() > 0 && (configItemCurrent >= 0 && configItemCurrent < (int) configItems.size()))
			{
				pstring path = GetConfigDirectory();
				path << configItems[configItemCurrent] << "/config.json";

				Settings::LoadDefaultsOrSave(path);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Remove"))
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
		if (ImGui::Button("Add") && strlen(buf) > 0)
		{
			pstring path = GetConfigDirectory();
			path << buf;

			if (!DoesFileExist(path.c_str()))
			{
				mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				Settings::LoadDefaultsOrSave(path << "/config.json");

				configItems = GetConfigs();
				configItemCurrent = -1;
			}
		}

		ImGui::PushItemWidth(178);
		if (ImGui::ListBox("", &configItemCurrent, configItems, 7))
		{
			pstring path = GetConfigDirectory();
			path << configItems[configItemCurrent] << "/config.json";

			Settings::LoadConfig(path);
			UI::ReloadWeaponSettings();
		}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}