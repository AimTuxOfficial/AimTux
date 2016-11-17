#include "knifeskin_panel.h"

KnifeSkinPanel::KnifeSkinPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	skinIDTextBox = new TextBox ("Skin ID", &skinIDText, LOC(10, 10), LOC(160, 30));
	seedIDTextBox = new TextBox ("Seed ID", &seedIDText, BELOW(skinIDTextBox), LOC(160, 30));
	wearAmountSlider = new Slider("Wear Amount", STACK(skinIDTextBox), LOC(160, 30), &wearAmount, 0.005f, 1.0f);
	stattrakTextBox = new TextBox ("Stat Trak", &stattrakText, BELOW(wearAmountSlider), LOC(160, 30));
	nameIDTextBox = new TextBox ("Name Tag", &nameIDText, BELOW(seedIDTextBox), LOC(160, 30));

	setButton = new OutlinedButton ("Set", BELOW(nameIDTextBox), LOC(330, 30));
	setButton->OnClickedEvent = MFUNC (&KnifeSkinPanel::ApplySkin, this);

	slb_knife = new ScrollingListBox<ItemDefinitionIndex>("Knife", BELOW (setButton), (size.x - 20) / 2, &knifeType, std::vector<SLB_Element>
			{
					SLB_Element ("Bayonet", WEAPON_KNIFE_BAYONET),
					SLB_Element ("Flip", WEAPON_KNIFE_FLIP),
					SLB_Element ("Gut", WEAPON_KNIFE_GUT),
					SLB_Element ("Karambit", WEAPON_KNIFE_KARAMBIT),
					SLB_Element ("M9 Bayonet", WEAPON_KNIFE_M9_BAYONET),
					SLB_Element ("Huntsman", WEAPON_KNIFE_TACTICAL),
					SLB_Element ("Falchion", WEAPON_KNIFE_FALCHION),
					SLB_Element ("Butterfly", WEAPON_KNIFE_BUTTERFLY),
					SLB_Element ("Bowie", WEAPON_KNIFE_SURVIVAL_BOWIE),
					SLB_Element ("Daggers", WEAPON_KNIFE_PUSH),

			}
	);

	cb_side = new ComboBox<Side>("Side", STACK(slb_knife), (size.x - 20) / 2 - 10, &side, std::vector<CB_Element>
			{
					CB_Element ("CT", CT),
					CB_Element ("T", T),
			}, false
	);

	AddComponent(cb_side);
	AddComponent(slb_knife);
	AddComponent(skinIDTextBox);
	AddComponent(seedIDTextBox);
	AddComponent(wearAmountSlider);
	AddComponent(stattrakTextBox);
	AddComponent(nameIDTextBox);

	AddComponent(setButton);
	Hide ();
}

// std::string KnifeSkinPanel::convertToUpper(std::string s)
// {
//	 for (int i = 0; i < s.length(); i++)
//		 s[i] = toupper(s[i]);
//	 return s;
// }

void KnifeSkinPanel::ApplySkin()
{
	Settings::Skinchanger::Skin skin = Settings::Skinchanger::Skin(
			skinIDText.empty() ? -1 : std::stoi(skinIDText),
			knifeType,
			seedIDText.empty() ? -1 : std::stoi(seedIDText),
			wearAmount,
			stattrakText.empty() ? -1 : std::stoi(stattrakText),
			nameIDText,
			""
	);

	switch(side)
	{
		case CT:
			Settings::Skinchanger::skins[WEAPON_KNIFE] = skin;
			break;
		case T:
			Settings::Skinchanger::skins[WEAPON_KNIFE_T] = skin;
			break;
	}

	SkinChanger::ForceFullUpdate = true;
}
