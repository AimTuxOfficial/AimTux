#include "skinstab.h"

void SplitSkins()
{
	static int modelCT = 1;
	static int modelSkinCT = 1;
	static float skinWearCT = 0.0005f;
	static int skinSeedCT = -1;
	static int skinStatTrakCT = -1;
	static char skinNameCT[18];
	static char filterModelsCT[18];
	static char filterModelSkinsCT[18];
	static int modelT = 1;
	static int modelSkinT = 1;
	static float skinWearT = 0.0005f;
	static int skinSeedT = -1;
	static int skinStatTrakT = -1;
	static char skinNameT[18];
	static char filterModelsT[18];
	static char filterModelSkinsT[18];

	ImGui::Columns(2);

	ImGui::Text("Counter Terrorist Skins");
	ImGui::NextColumn();

	ImGui::Text("Terrorist Skins");
	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(4);

	ImGui::Text("Model");
	ImGui::NextColumn();

	ImGui::Text("Skin");
	ImGui::NextColumn();

	ImGui::Text("Model");
	ImGui::NextColumn();

	ImGui::Text("Skin");
	ImGui::Columns(1);

	ImGui::Columns(4);

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModelsCT", filterModelsCT, IM_ARRAYSIZE(filterModelsCT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModelSkinsCT", filterModelSkinsCT, IM_ARRAYSIZE(filterModelSkinsCT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModelsT", filterModelsT, IM_ARRAYSIZE(filterModelsT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModelSkinsT", filterModelSkinsT, IM_ARRAYSIZE(filterModelSkinsT));
	ImGui::PopItemWidth();
	ImGui::Columns(1);

	ImGui::Columns(4);

	ImGui::GetCurrentContext()->FontBaseSize = 14.0f;
	ImGui::ListBoxHeader("##modelsCT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!(Util::Contains(Util::ToLower(std::string(filterModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))) || Util::Contains(Util::ToLower(std::string(filterModelsCT)), Util::ToLower(Util::Items::GetItemEntityName(model.first)))))
			continue;
		if (model.first == ItemDefinitionIndex::INVALID || Util::Items::IsUtility(model.first) || model.first == ItemDefinitionIndex::GLOVE_CT_SIDE || model.first == ItemDefinitionIndex::GLOVE_T_SIDE || Util::Items::IsTWeapon(model.first) || model.first == ItemDefinitionIndex::WEAPON_KNIFE || model.first == ItemDefinitionIndex::WEAPON_KNIFE_T)
			continue;
		const bool item_selected = ((int) model.first == modelCT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
		{
			modelCT = (int) model.first;
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex) modelCT) != Settings::Skinchanger::skinsCT.end())
			{
				modelSkinCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackPaintKit;
				skinWearCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackWear;
				skinSeedCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackSeed;
				skinStatTrakCT = Settings::Skinchanger::skinsCT.at(model.first).fallbackStatTrak;
				std::fill(std::begin(skinNameCT), std::end(skinNameCT), 0);
				std::copy(std::begin(Settings::Skinchanger::skinsCT.at(model.first).customName), std::end(Settings::Skinchanger::skinsCT.at(model.first).customName), std::begin(skinNameCT));
			}
		}
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##modelSkinsCT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto skin : itemSkins)
	{
		if (skin.second.paintName != nullptr ? !(Util::Contains(Util::ToLower(std::string(filterModelSkinsCT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))) || Util::Contains(Util::ToLower(std::string(filterModelSkinsCT)), skin.second.paintName)) : !Util::Contains(Util::ToLower(std::string(filterModelSkinsCT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))))
			continue;
		if (Util::Items::IsGlove((ItemDefinitionIndex) modelCT) && skin.first < 10006)
			continue;
		const bool item_selected = (skin.first == modelSkinCT);
		ImGui::PushID(skin.first);
		if (ImGui::Selectable(skin.first == -1 ? skin.second.displayName : Util::WstringToString(localize->FindSafe(skin.second.displayName)).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
			modelSkinCT = skin.first;
		ImGui::NextColumn();

		ImGui::Text("%s", skin.second.paintName != nullptr ? skin.second.paintName : "");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##modelsT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!(Util::Contains(Util::ToLower(std::string(filterModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))) || Util::Contains(Util::ToLower(std::string(filterModelsT)), Util::ToLower(Util::Items::GetItemEntityName(model.first)))))
			continue;
		if (model.first == ItemDefinitionIndex::INVALID || Util::Items::IsUtility(model.first) || model.first == ItemDefinitionIndex::GLOVE_CT_SIDE || model.first == ItemDefinitionIndex::GLOVE_T_SIDE || Util::Items::IsCTWeapon(model.first) || model.first == ItemDefinitionIndex::WEAPON_KNIFE || model.first == ItemDefinitionIndex::WEAPON_KNIFE_T)
			continue;
		const bool item_selected = ((int) model.first == modelT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
		{
			modelT = (int) model.first;
			if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex) modelT) != Settings::Skinchanger::skinsT.end())
			{
				modelSkinT = Settings::Skinchanger::skinsT.at(model.first).fallbackPaintKit;
				skinWearT = Settings::Skinchanger::skinsCT.at(model.first).fallbackWear;
				skinSeedT = Settings::Skinchanger::skinsCT.at(model.first).fallbackSeed;
				skinStatTrakT = Settings::Skinchanger::skinsCT.at(model.first).fallbackStatTrak;
				std::fill(std::begin(skinNameT), std::end(skinNameT), 0);
				std::copy(std::begin(Settings::Skinchanger::skinsT.at(model.first).customName), std::end(Settings::Skinchanger::skinsT.at(model.first).customName), std::begin(skinNameT));
			}
		}
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##modelSkinsT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto skin : itemSkins)
	{
		if (skin.second.paintName != nullptr ? !(Util::Contains(Util::ToLower(std::string(filterModelSkinsT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))) || Util::Contains(Util::ToLower(std::string(filterModelSkinsT)), skin.second.paintName)) : !Util::Contains(Util::ToLower(std::string(filterModelSkinsT)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))))
			continue;
		if (Util::Items::IsGlove((ItemDefinitionIndex) modelT) && skin.first < 10006)
			continue;
		const bool item_selected = (skin.first == modelSkinT);
		ImGui::PushID(skin.first);
		if (ImGui::Selectable(skin.first == -1 ? skin.second.displayName : Util::WstringToString(localize->FindSafe(skin.second.displayName)).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
			modelSkinT = skin.first;
		ImGui::NextColumn();

		ImGui::Text("%s", skin.second.paintName != nullptr ? skin.second.paintName : "");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::GetCurrentContext()->FontBaseSize = 18.0f;
	ImGui::ListBoxFooter();
	ImGui::Columns(1);

	ImGui::Columns(2);

	ImGui::BeginChild("CT Settings", ImVec2(0, 0), true);
	{
		ImGui::Columns(3);

		ImGui::InputInt("ID##CT", &modelSkinCT);
		ImGui::NextColumn();

		ImGui::InputInt("Seed##CT", &skinSeedCT);
		ImGui::NextColumn();

		ImGui::PushItemWidth(-1);
		ImGui::SliderFloat("##WearCT", &skinWearCT, 0.0005f, 1.0f, "Wear: %0f");
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		if (!Util::Items::IsGlove((ItemDefinitionIndex) modelCT))
		{
			ImGui::Columns(2, NULL, false);

			ImGui::InputInt("StatTrak##CT", &skinStatTrakCT);
			ImGui::NextColumn();

			ImGui::InputText("Name##CT", skinNameCT, IM_ARRAYSIZE(skinNameCT));
			ImGui::Columns(1);
		}

		if (ImGui::Button("Apply##skinCT", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex) modelCT) == Settings::Skinchanger::skinsCT.end())
				Settings::Skinchanger::skinsCT[(ItemDefinitionIndex) modelCT] = AttribItem_t();

			Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex) modelCT) = { ItemDefinitionIndex::INVALID, modelSkinCT, skinWearCT, skinSeedCT, skinStatTrakCT, -1, skinNameCT };

			SkinChanger::forceFullUpdate = true;

			if (Util::Items::IsGlove((ItemDefinitionIndex) modelCT))
				SkinChanger::glovesUpdated = true;
		}

		ImGui::EndChild();
	}
	ImGui::NextColumn();

	ImGui::BeginChild("T Settings", ImVec2(0, 0), true);
	{
		ImGui::Columns(3, NULL, false);

		ImGui::InputInt("ID##T", &modelSkinT);
		ImGui::NextColumn();

		ImGui::InputInt("Seed##T", &skinSeedT);
		ImGui::NextColumn();

		ImGui::PushItemWidth(-1);
		ImGui::SliderFloat("##WearT", &skinWearT, 0.0005f, 1.0f, "Wear: %0f");
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		if (!Util::Items::IsGlove((ItemDefinitionIndex) modelT))
		{
			ImGui::Columns(2, NULL, false);

			ImGui::InputInt("StatTrak##T", &skinStatTrakT);
			ImGui::NextColumn();

			ImGui::InputText("Name##T", skinNameT, IM_ARRAYSIZE(skinNameT));
			ImGui::Columns(1);
		}

		if (ImGui::Button("Apply##skinT", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex) modelT) == Settings::Skinchanger::skinsT.end())
				Settings::Skinchanger::skinsT[(ItemDefinitionIndex) modelT] = AttribItem_t();

			Settings::Skinchanger::skinsT.at((ItemDefinitionIndex) modelT) = { ItemDefinitionIndex::INVALID, modelSkinT, skinWearT, skinSeedT, skinStatTrakT, -1, skinNameT};

			SkinChanger::forceFullUpdate = true;

			if (Util::Items::IsGlove((ItemDefinitionIndex) modelT))
				SkinChanger::glovesUpdated = true;
		}

		ImGui::EndChild();
	}
	ImGui::Columns(1);
}

void CombinedSkins()
{
	static int selectedModel = 1;
	static int selectedModelSkin = 1;
	static float skinWear = 0.0005f;
	static int skinSeed = -1;
	static int skinStatTrak = -1;
	static char skinName[18];
	static char filterModels[18];
	static char filterModelSkins[18];

	ImGui::Columns(2);

	ImGui::Text("Models");
	ImGui::NextColumn();

	ImGui::Text("Skins");
	ImGui::Columns(1);

	ImGui::Columns(2);

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModels", filterModels, IM_ARRAYSIZE(filterModels));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterModelSkins", filterModelSkins, IM_ARRAYSIZE(filterModelSkins));
	ImGui::PopItemWidth();
	ImGui::Columns(1);

	ImGui::Columns(2);

	ImGui::ListBoxHeader("##models", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!(Util::Contains(Util::ToLower(std::string(filterModels)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))) || Util::Contains(Util::ToLower(std::string(filterModels)), Util::ToLower(Util::Items::GetItemEntityName(model.first)))))
			continue;
		if (Util::Items::IsUtility(model.first) || model.first == ItemDefinitionIndex::GLOVE_CT_SIDE || model.first == ItemDefinitionIndex::GLOVE_T_SIDE || model.first == ItemDefinitionIndex::WEAPON_KNIFE || model.first == ItemDefinitionIndex::WEAPON_KNIFE_T)
			continue;
		const bool item_selected = ((int) model.first == selectedModel);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
		{
			selectedModel = (int) model.first;
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)selectedModel) != Settings::Skinchanger::skinsCT.end())
			{
				selectedModelSkin = Settings::Skinchanger::skinsCT.at(model.first).fallbackPaintKit;
				skinWear = Settings::Skinchanger::skinsCT.at(model.first).fallbackWear;
				skinSeed = Settings::Skinchanger::skinsCT.at(model.first).fallbackSeed;
				skinStatTrak = Settings::Skinchanger::skinsCT.at(model.first).fallbackStatTrak;
				std::fill(std::begin(skinName), std::end(skinName), 0);
				std::copy(std::begin(Settings::Skinchanger::skinsCT.at(model.first).customName), std::end(Settings::Skinchanger::skinsCT.at(model.first).customName), std::begin(skinName));
			}
		}
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##modelSkins", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto skin : itemSkins)
	{
		if (skin.second.paintName != nullptr ? !(Util::Contains(Util::ToLower(std::string(filterModelSkins)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))) || Util::Contains(Util::ToLower(std::string(filterModelSkins)), skin.second.paintName)) : !Util::Contains(Util::ToLower(std::string(filterModelSkins)), Util::ToLower(Util::WstringToString(localize->FindSafe(skin.second.displayName)))))
			continue;
		if (Util::Items::IsGlove((ItemDefinitionIndex)selectedModel) && skin.first < 10006)
			continue;
		const bool item_selected = (skin.first == selectedModelSkin);
		ImGui::PushID(skin.first);
		if (ImGui::Selectable(skin.first == -1 ? skin.second.displayName : Util::WstringToString(localize->FindSafe(skin.second.displayName)).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
			selectedModelSkin = skin.first;
		ImGui::NextColumn();

		ImGui::Text("%s", skin.second.paintName != nullptr ? skin.second.paintName : "");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::Columns(1);

	ImGui::BeginChild("Settings", ImVec2(0, 0), true);
	{
		ImGui::Columns(3);

		ImGui::InputInt("ID##CT", &selectedModelSkin);
		ImGui::NextColumn();

		ImGui::InputInt("Seed##CT", &skinSeed);
		ImGui::NextColumn();

		ImGui::PushItemWidth(-1);
		ImGui::SliderFloat("##WearCT", &skinWear, 0.0005f, 1.0f, "Wear: %0f");
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		if (!Util::Items::IsGlove((ItemDefinitionIndex)selectedModel))
		{
			ImGui::Columns(2, NULL, false);

			ImGui::InputInt("StatTrak##Combined", &skinStatTrak);
			ImGui::NextColumn();

			ImGui::InputText("Name##Combined", skinName, IM_ARRAYSIZE(skinName));
			ImGui::Columns(1);
		}

		if (ImGui::Button("Apply##Combined", ImVec2(-1, 0)))
		{
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)selectedModel) == Settings::Skinchanger::skinsCT.end())
				Settings::Skinchanger::skinsCT[(ItemDefinitionIndex)selectedModel] = AttribItem_t();

			Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)selectedModel) = { ItemDefinitionIndex::INVALID, selectedModelSkin, skinWear, skinSeed, skinStatTrak, -1, skinName};

			SkinChanger::forceFullUpdate = true;

			if (Util::Items::IsGlove((ItemDefinitionIndex)selectedModel))
				SkinChanger::glovesUpdated = true;
		}

		ImGui::EndChild();
	}
}

void Skins::RenderTab()
{
	ImGui::Columns(2, NULL, false);

	if (ImGui::Checkbox("Enabled", &Settings::Skinchanger::Skins::enabled))
	{
		SkinChanger::forceFullUpdate = true;
		SkinChanger::glovesUpdated = true;
	}
	ImGui::NextColumn();

	if (ImGui::Checkbox("Per-Team", &Settings::Skinchanger::Skins::perTeam))
	{
		SkinChanger::forceFullUpdate = true;
		SkinChanger::glovesUpdated = true;
	}
	ImGui::NextColumn();

	ImGui::Columns(1);

	ImGui::Separator();

	if (Settings::Skinchanger::Skins::perTeam)
		SplitSkins();
	else
		CombinedSkins();
}