#include "skinchange_panel.h"

SkinChangePanel::SkinChangePanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{

	lb_knifetype = new StackedListBox<KnifeType>("knife type", LOC(10, 10), ((size.x - 20) / 2) - 5, 3, &Settings::Skinchanger::Knife::type, std::vector<LB_Element>
			{
					LB_Element ("Bayonet", BAYONET),
					LB_Element ("Flip", FLIP),
					LB_Element ("Gut", GUT),
					LB_Element ("Karambit", KARAMBIT),
					LB_Element ("M9 Bayonet", M9_BAYONET),
					LB_Element ("Huntsman", TACTICAL),
		//			LB_Element ("Falchion", FALCHION), Broken animations, no point being able to select them just yet.
		//			LB_Element ("Bowie", SURVIVAL_BOWIE),
		//			LB_Element ("Butterfly", BUTTERFLY),
		//			LB_Element ("Daggers", PUSH)
			}
	);
	AddComponent (lb_knifetype);

	updateButton = new OutlinedButton ("Update Knife", BELOW(lb_knifetype), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (updateButton);

	updateButton->OnClickedEvent = MFUNC (&SkinChangePanel::UpdateButtonClicked, this);

	Hide();
}

void SkinChangePanel::UpdateButtonClicked()
{
	gameEvents_vmt->HookVM((void*) Hooks::FireEventClientSide, 10);
	gameEvents_vmt->ApplyVMT();
	SkinChanger::ForceFullUpdate = true;
}
