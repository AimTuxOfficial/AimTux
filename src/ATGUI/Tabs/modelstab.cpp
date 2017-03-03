#include "modelstab.h"

void Models::RenderTab()
{
	static int originalModelCT = (int) ItemDefinitionIndex::WEAPON_KNIFE;
	static int replacementModelCT = Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex) originalModelCT) != Settings::Skinchanger::skinsCT.end() ? (int) Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)originalModelCT).itemDefinitionIndex : (int) ItemDefinitionIndex::WEAPON_KNIFE;
	static char filterOriginalModelsCT[18];
	static char filterReplacementModelsCT[18];
	static int originalModelT = (int) ItemDefinitionIndex::WEAPON_KNIFE_T;
	static int replacementModelT = Settings::Skinchanger::skinsT.find((ItemDefinitionIndex) originalModelT) != Settings::Skinchanger::skinsT.end() ? (int) Settings::Skinchanger::skinsT.at((ItemDefinitionIndex)originalModelT).itemDefinitionIndex : (int) ItemDefinitionIndex::WEAPON_KNIFE_T;
	static char filterOriginalModelsT[18];
	static char filterReplacementModelsT[18];

	ImGui::Checkbox("Enabled", &Settings::Skinchanger::Models::enabled);
	ImGui::Separator();

	ImGui::Columns(2);

	ImGui::Text("Counter Terrorist Models");
	ImGui::NextColumn();

	ImGui::Text("Terrorist Models");
	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(4);

	ImGui::Text("Original");
	ImGui::NextColumn();

	ImGui::Text("Replacement");
	ImGui::NextColumn();

	ImGui::Text("Original");
	ImGui::NextColumn();

	ImGui::Text("Replacement");
	ImGui::Columns(1);

	ImGui::Columns(4);

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterOriginalModelCT", filterOriginalModelsCT, IM_ARRAYSIZE(filterOriginalModelsCT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterReplacementModelCT", filterReplacementModelsCT, IM_ARRAYSIZE(filterReplacementModelsCT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterOriginalModelT", filterOriginalModelsT, IM_ARRAYSIZE(filterOriginalModelsT));
	ImGui::PopItemWidth();
	ImGui::NextColumn();

	ImGui::PushItemWidth(-1);
	ImGui::InputText("##filterReplacementModelT", filterReplacementModelsT, IM_ARRAYSIZE(filterReplacementModelsT));
	ImGui::PopItemWidth();
	ImGui::Columns(1);

	ImGui::Columns(4);

	ImGui::GetCurrentContext()->FontBaseSize = 14.0f;
	ImGui::ListBoxHeader("##originalModelsCT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!Util::Contains(Util::ToLower(std::string(filterOriginalModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
			continue;
		if (model.first != ItemDefinitionIndex::WEAPON_KNIFE && model.first != ItemDefinitionIndex::GLOVE_CT_SIDE)
			continue;
		const bool item_selected = ((int) model.first == originalModelCT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
		{
			originalModelCT = (int) model.first;
			if (Settings::Skinchanger::skinsCT.find(model.first) != Settings::Skinchanger::skinsCT.end())
				replacementModelCT = (int) Settings::Skinchanger::skinsCT.at(model.first).itemDefinitionIndex;
		}
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##replacementModelsCT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!Util::Contains(Util::ToLower(std::string(filterReplacementModelsCT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
			continue;
		switch (originalModelCT)
		{
			case (int) ItemDefinitionIndex::WEAPON_KNIFE:
				if (!Util::Items::IsKnife(model.first))
					continue;
				break;
			case (int) ItemDefinitionIndex::GLOVE_CT_SIDE:
				if (!Util::Items::IsGlove(model.first) || model.first == ItemDefinitionIndex::GLOVE_T_SIDE)
					continue;
				break;
			default:
				break;
		}
		const bool item_selected = ((int) model.first == replacementModelCT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
			replacementModelCT = (int) model.first;
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##originalModelsT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!Util::Contains(Util::ToLower(std::string(filterOriginalModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
			continue;
		if (model.first != ItemDefinitionIndex::WEAPON_KNIFE_T && model.first != ItemDefinitionIndex::GLOVE_T_SIDE)
			continue;
		const bool item_selected = ((int) model.first == originalModelT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
		{
			originalModelT = (int) model.first;
			if (Settings::Skinchanger::skinsT.find(model.first) != Settings::Skinchanger::skinsT.end())
				replacementModelT = (int) Settings::Skinchanger::skinsT.at(model.first).itemDefinitionIndex;
		}
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::ListBoxFooter();
	ImGui::NextColumn();

	ImGui::ListBoxHeader("##replacementModelsT", ImVec2(-1, 300));
	ImGui::Columns(2);
	for (auto model : ItemDefinitionIndexMap)
	{
		if (!Util::Contains(Util::ToLower(std::string(filterReplacementModelsT)), Util::ToLower(Util::Items::GetItemDisplayName(model.first))))
			continue;
		switch (originalModelT)
		{
			case (int) ItemDefinitionIndex::WEAPON_KNIFE_T:
				if (!Util::Items::IsKnife(model.first))
					continue;
				break;
			case (int) ItemDefinitionIndex::GLOVE_T_SIDE:
				if (!Util::Items::IsGlove(model.first) || model.first == ItemDefinitionIndex::GLOVE_CT_SIDE)
					continue;
				break;
			default:
				break;
		}
		const bool item_selected = ((int) model.first == replacementModelT);
		ImGui::PushID((int) model.first);
		if (ImGui::Selectable(Util::Items::GetItemDisplayName(model.first).c_str(), item_selected, ImGuiSelectableFlags_SpanAllColumns))
			replacementModelT = (int) model.first;
		ImGui::NextColumn();

		ImGui::Text("%s", Util::Items::GetItemEntityName(model.first).c_str());
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::GetCurrentContext()->FontBaseSize = 18.0f; // Has to go specifically here, or it wont reset the size.
	ImGui::ListBoxFooter();

	ImGui::Columns(1);
	ImGui::Separator();

	ImGui::Columns(2);

	if (ImGui::Button("Apply##modelCT", ImVec2(-1, 0)))
	{
		if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)originalModelCT) == Settings::Skinchanger::skinsCT.end())
			Settings::Skinchanger::skinsCT[(ItemDefinitionIndex)originalModelCT] = AttribItem_t();

		Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)originalModelCT).itemDefinitionIndex = (ItemDefinitionIndex) replacementModelCT;

		SkinChanger::forceFullUpdate = true;
	}
	ImGui::NextColumn();

	if (ImGui::Button("Apply##modelT", ImVec2(-1, 0)))
	{
		if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex)originalModelT) == Settings::Skinchanger::skinsT.end())
			Settings::Skinchanger::skinsT[(ItemDefinitionIndex)originalModelT] = AttribItem_t();

		Settings::Skinchanger::skinsT.at((ItemDefinitionIndex)originalModelT).itemDefinitionIndex = (ItemDefinitionIndex)replacementModelT;

		if (!Settings::Skinchanger::Skins::perTeam)
		{
			if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex)originalModelT) == Settings::Skinchanger::skinsT.end())
				Settings::Skinchanger::skinsCT[(ItemDefinitionIndex)originalModelT] = AttribItem_t();

			Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex)originalModelT).itemDefinitionIndex = (ItemDefinitionIndex)replacementModelT;
		}

		SkinChanger::forceFullUpdate = true;

		SkinChanger::glovesUpdated = true;
	}
	ImGui::Columns(1);

	ImGui::Separator();
}