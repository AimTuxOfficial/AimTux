#include "skinchanger_panel.h"

ItemDefinitionIndex Settings::Skinchanger::Knife::type = WEAPON_KNIFE_BAYONET;

SkinChangerPanel::SkinChangerPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{

	lb_knifetype = new StackedListBox<ItemDefinitionIndex>("knife type", LOC(10, 10), ((size.x - 20) / 2) - 5, 3, &Settings::Skinchanger::Knife::type, std::vector<LB_Element>
			{
					LB_Element ("Bayonet", WEAPON_KNIFE_BAYONET),
					LB_Element ("Flip", WEAPON_KNIFE_FLIP),
					LB_Element ("Gut", WEAPON_KNIFE_GUT),
					LB_Element ("Karambit", WEAPON_KNIFE_KARAMBIT),
					LB_Element ("M9 Bayonet", WEAPON_KNIFE_M9_BAYONET),
					LB_Element ("Huntsman", WEAPON_KNIFE_TACTICAL),
			}
	);
	AddComponent (lb_knifetype);

	updateknife_button = new OutlinedButton ("Update Knife", BELOW(lb_knifetype), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (updateknife_button);

	updateknife_button->OnClickedEvent = MFUNC (&SkinChangerPanel::update_knife_clicked, this);

  Hide();
}

void SkinChangerPanel::update_knife_clicked()
{
	for (auto i : Settings::Skinchanger::skins)
	{
		if (Util::Items::GetItemName((enum ItemDefinitionIndex) i.first) == "WEAPON_KNIFE")
		{
			Settings::Skinchanger::skins[WEAPON_KNIFE] = Settings::Skinchanger::Skin(i.second.PaintKit, Settings::Skinchanger::Knife::type,
																																							 i.second.Seed, i.second.Wear, i.second.StatTrak,
																																							 i.second.CustomName, i.second.Model);
			Settings::Skinchanger::skins[WEAPON_KNIFE_T] = Settings::Skinchanger::Skin(i.second.PaintKit, Settings::Skinchanger::Knife::type,
																																								 i.second.Seed, i.second.Wear, i.second.StatTrak,
																																								 i.second.CustomName, i.second.Model);
		}
	}
	SkinChanger::ForceFullUpdate = true;
}
