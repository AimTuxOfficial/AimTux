#include "skinmodelchanger.h"

bool SkinModelChanger::showWindow = false;

static int page = 0;

void TabButtons()
{
	const char* tabs[] = {
			"Models",
			"Skins",
	};

	int tabs_size = sizeof(tabs) / sizeof(tabs[0]);
	for (int i = 0; i < tabs_size; i++)
	{
		int distance = i == page ? 0 : i > page ? i - page : page - i;

		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
				Settings::UI::mainColor.Value.x - (distance * 0.06f),
				Settings::UI::mainColor.Value.y - (distance * 0.06f),
				Settings::UI::mainColor.Value.z - (distance * 0.06f),
				Settings::UI::mainColor.Value.w
		);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / tabs_size - 9, 0)))
			page = i;

		ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor;

		if (i < tabs_size - 1)
			ImGui::SameLine();
	}
}

void ModelsTab()
{
	static int originalModelCT = 42;
	static int replacementModelCT = Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)originalModelCT) != Settings::Skinchanger::skinsCT.end() ? (int)Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)originalModelCT).itemDefinitionIndex : 42;
	static char filterOriginalModelsCT[18];
	static char filterReplacementModelsCT[18];
	static int originalModelT = 59;
	static int replacementModelT = Settings::Skinchanger::skinsT.find((ItemDefinitionIndex)originalModelT) != Settings::Skinchanger::skinsT.end() ? (int)Settings::Skinchanger::skinsT.at((ItemDefinitionIndex)originalModelT).itemDefinitionIndex : 59;
	static char filterOriginalModelsT[18];
	static char filterReplacementModelsT[18];

	ImGui::Checkbox("Enabled", &Settings::Skinchanger::Models::enabled);
	ImGui::Separator();

	ImGui::Columns(2);
	{
		ImGui::Text("Counter Terrorist Models");
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Terrorist Models");
	}
	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(4, NULL, true);
	{
		ImGui::Text("Original");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterOriginalModelCT", filterOriginalModelsCT, IM_ARRAYSIZE(filterOriginalModelsCT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##originalModelsCT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterOriginalModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			if (model.first != ItemDefinitionIndex::WEAPON_KNIFE && model.first != ItemDefinitionIndex::GLOVE_CT_SIDE)
				continue;
			const bool item_selected = ((int) model.first == originalModelCT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				originalModelCT = (int)model.first;
				replacementModelCT = (int)Settings::Skinchanger::skinsCT.at(model.first).itemDefinitionIndex;
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Replacement");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterReplacementModelCT", filterReplacementModelsCT, IM_ARRAYSIZE(filterReplacementModelsCT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##replacementModelsCT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterReplacementModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			switch(originalModelCT)
			{
				case (int) ItemDefinitionIndex::WEAPON_KNIFE:
					if(!Util::Items::isKnife(model.first))
						continue;
					break;
				case (int) ItemDefinitionIndex::GLOVE_CT_SIDE:
					if (model.first < ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND || model.first == ItemDefinitionIndex::GLOVE_T_SIDE)
						continue;
					break;
				default:
					break;
			}
			const bool item_selected = ((int) model.first == replacementModelCT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
				replacementModelCT = (int)model.first;
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Original");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterOriginalModelT", filterOriginalModelsT, IM_ARRAYSIZE(filterOriginalModelsT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##originalModelsT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterOriginalModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			if (model.first != ItemDefinitionIndex::WEAPON_KNIFE_T && model.first != ItemDefinitionIndex::GLOVE_T_SIDE)
				continue;
			const bool item_selected = ((int) model.first == originalModelT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				originalModelT = (int)model.first;
				replacementModelT = (int)Settings::Skinchanger::skinsT.at(model.first).itemDefinitionIndex;
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Replacement");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterReplacementModelT", filterReplacementModelsT, IM_ARRAYSIZE(filterReplacementModelsT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##replacementModelsT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterReplacementModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			switch(originalModelT)
			{
				case (int) ItemDefinitionIndex::WEAPON_KNIFE_T:
					if(!Util::Items::isKnife(model.first))
						continue;
					break;
				case (int) ItemDefinitionIndex::GLOVE_T_SIDE:
					if (model.first < ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND || model.first == ItemDefinitionIndex::GLOVE_CT_SIDE)
						continue;
					break;
				default:
					break;
			}
			const bool item_selected = ((int) model.first == replacementModelT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
				replacementModelT = (int)model.first;
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::Columns(2);
	{
		if(ImGui::Button("Apply", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)originalModelCT) == Settings::Skinchanger::skinsCT.end())
				Settings::Skinchanger::skinsCT[(ItemDefinitionIndex)originalModelCT] = AttribItem_t();

			Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)originalModelCT).itemDefinitionIndex = (ItemDefinitionIndex) replacementModelCT;

			SkinChanger::forceFullUpdate = true;
		}
	}
	ImGui::NextColumn();
	{
		if(ImGui::Button("Apply", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex)originalModelT) == Settings::Skinchanger::skinsT.end())
				Settings::Skinchanger::skinsT[(ItemDefinitionIndex)originalModelT] = AttribItem_t();

			Settings::Skinchanger::skinsT.at((ItemDefinitionIndex)originalModelT).itemDefinitionIndex = (ItemDefinitionIndex)replacementModelT;

			SkinChanger::forceFullUpdate = true;
		}
	}
	ImGui::Columns(1);
	ImGui::Separator();
}

void SkinsTab()
{
	static int modelCT = 1;
	static int modelSkinCT = 1;
	static float skinWearCT = 0.005f;
	static int skinSeedCT = -1;
	static int skinStatTrakCT = -1;
	static char skinNameCT[18];
	static char filterModelsCT[18];
	static char filterModelSkinsCT[18];
	static int modelT = 1;
	static int modelSkinT = 1;
	static float skinWearT = 0.005f;
	static int skinSeedT = -1;
	static int skinStatTrakT = -1;
	static char skinNameT[18];
	static char filterModelsT[18];
	static char filterModelSkinsT[18];


	if(ImGui::Checkbox("Enabled", &Settings::Skinchanger::Skins::enabled))
		SkinChanger::forceFullUpdate = true;
	ImGui::Separator();

	ImGui::Columns(2);
	{
		ImGui::Text("Counter Terrorist Skins");
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Terrorist Skins");
	}
	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(4, NULL, true);
	{
		ImGui::Text("Model");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterModelsCT", filterModelsCT, IM_ARRAYSIZE(filterModelsCT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##modelsCT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			if (Util::Items::isUtility(model.first))
				continue;
			const bool item_selected = ((int) model.first == modelCT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				modelCT = (int)model.first;
				if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)modelCT) != Settings::Skinchanger::skinsCT.end())
				{
					modelSkinCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackPaintKit;
					skinWearCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackWear;
					skinSeedCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackSeed;
					skinStatTrakCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackStatTrak;
					std::fill(std::begin(skinNameCT), std::end(skinNameCT), 0);
					std::copy(std::begin(Settings::Skinchanger::skinsCT.at(model.first).customName), std::end(Settings::Skinchanger::skinsCT.at(model.first).customName), std::begin(skinNameCT));
				}
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Skins");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterModelSkinsCT", filterModelSkinsCT, IM_ARRAYSIZE(filterModelSkinsCT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##modelSkinsCT", ImVec2(-1, 300));
		for (auto skin : itemSkins)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterModelSkinsCT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))))
				continue;
			const bool item_selected = (skin.first == modelSkinCT);
			ImGui::PushID(skin.first);
			std::string formattedName;
			if(skin.second.paintName != nullptr)
				formattedName = Util::WstringToString(localize->FindSafe(skin.second.displayName)) + " (" + skin.second.paintName + ")";
			else
				formattedName = skin.first == -1 ? skin.second.displayName : Util::WstringToString(localize->FindSafe(skin.second.displayName));
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
				modelSkinCT = skin.first;
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Model");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterModelsT", filterModelsT, IM_ARRAYSIZE(filterModelsT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##modelsT", ImVec2(-1, 300));
		for (auto model : ItemDefinitionIndexMap)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
				continue;
			if (Util::Items::isUtility(model.first))
				continue;
			const bool item_selected = ((int) model.first == modelT);
			ImGui::PushID((int)model.first);
			std::string formattedName;
			formattedName = Util::Items::GetItemDisplayName(model.first) + " (" + Util::Items::GetItemEntityName(model.first) + ")";
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				modelT = (int)model.first;
				if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex)modelT) != Settings::Skinchanger::skinsT.end())
				{
					modelSkinT = Settings::Skinchanger::skinsT.at(model.first).fallbackPaintKit;
					skinWearT = Settings::Skinchanger::skinsCT.at(model.first).fallbackWear;
					skinSeedT = Settings::Skinchanger::skinsCT.at(model.first).fallbackSeed;
					skinStatTrakT = Settings::Skinchanger::skinsCT.at(model.first).fallbackStatTrak;
					std::fill(std::begin(skinNameT), std::end(skinNameT), 0);
					std::copy(std::begin(Settings::Skinchanger::skinsT.at(model.first).customName), std::end(Settings::Skinchanger::skinsT.at(model.first).customName), std::begin(skinNameT));
				}
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Skins");
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##filterModelSkinsT", filterModelSkinsT, IM_ARRAYSIZE(filterModelSkinsT));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##modelSkinsT", ImVec2(-1, 300));
		for (auto skin : itemSkins)
		{
			if (!Util::Contains(Util::ToLower(std::string(filterModelSkinsT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))))
				continue;
			const bool item_selected = (skin.first == modelSkinT);
			ImGui::PushID(skin.first);
			std::string formattedName;
			if(skin.second.paintName != nullptr)
				formattedName = Util::WstringToString(localize->FindSafe(skin.second.displayName)) + " (" + skin.second.paintName + ")";
			else
				formattedName = skin.first == -1 ? skin.second.displayName : Util::WstringToString(localize->FindSafe(skin.second.displayName));
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
				modelSkinT = skin.first;
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("CT Settings", ImVec2(0, 0), true);
		{
			ImGui::Columns(3, NULL, false);
			{
				ImGui::InputInt("ID##CT", &modelSkinCT);
			}
			ImGui::NextColumn();
			{
				ImGui::InputInt("Seed##CT", &skinSeedCT);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##WearCT", &skinWearCT, 0.005f, 1.0f, "Wear: %0.3f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Columns(2, NULL, false);
			{
				ImGui::InputInt("StatTrak##CT", &skinStatTrakCT);
			}
			ImGui::NextColumn();
			{
				ImGui::InputText("Name##CT", skinNameCT, IM_ARRAYSIZE(skinNameCT));
			}
			ImGui::Columns(1);
			if(ImGui::Button("Apply##CT", ImVec2(-1, 0)))
			{
				if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)modelCT) == Settings::Skinchanger::skinsCT.end())
					Settings::Skinchanger::skinsCT[(ItemDefinitionIndex)modelCT] = AttribItem_t();

				Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)modelCT) = { ItemDefinitionIndex::INVALID, modelSkinCT, 0.0005f, -1, -1, -1, ""};

				SkinChanger::forceFullUpdate = true;
			}
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("T Settings", ImVec2(0, 0), true);
		{
			ImGui::Columns(3, NULL, false);
			{
				ImGui::InputInt("ID##T", &modelSkinT);
			}
			ImGui::NextColumn();
			{
				ImGui::InputInt("Seed##T", &skinSeedT);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##WearT", &skinWearT, 0.005f, 1.0f, "Wear: %0.3f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Columns(2, NULL, false);
			{
				ImGui::InputInt("StatTrak##T", &skinStatTrakT);
			}
			ImGui::NextColumn();
			{
				ImGui::InputText("Name##T", skinNameT, IM_ARRAYSIZE(skinNameT));
			}
			ImGui::Columns(1);
			if(ImGui::Button("Apply##T", ImVec2(-1, 0)))
			{
				if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex)modelT) == Settings::Skinchanger::skinsT.end())
					Settings::Skinchanger::skinsT[(ItemDefinitionIndex)modelT] = AttribItem_t();

				Settings::Skinchanger::skinsT.at((ItemDefinitionIndex)modelT) = { ItemDefinitionIndex::INVALID, modelSkinT, 0.0005f, -1, -1, -1, ""};

				SkinChanger::forceFullUpdate = true;
			}
			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}

void SkinModelChanger::RenderWindow()
{
	if(!SkinModelChanger::showWindow)
		return;

	ImGui::SetNextWindowSize(ImVec2(1200, 645), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Skin & Model Changer", &SkinModelChanger::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		TabButtons();
		ImGui::Separator();
		switch (page)
		{
			case 0:
				ModelsTab();
				break;
			case 1:
				SkinsTab();
				break;
		}
		ImGui::End();
	}
};
