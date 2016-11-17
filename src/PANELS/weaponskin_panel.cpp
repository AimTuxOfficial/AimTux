#include "weaponskin_panel.h"

WeaponSkinPanel::WeaponSkinPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	weaponIDTextBox = new TextBox ("Weapon Name", &weaponIDText, LOC(10, 10), LOC(160, 30));
	skinIDTextBox = new NumberBox ("Skin ID", &skinIDText, BELOW(weaponIDTextBox), LOC(160, 30));
	seedIDTextBox = new NumberBox ("Seed", &seedIDText, BELOW(skinIDTextBox), LOC(160, 30));
	wearAmountSlider = new Slider("Wear Amount", STACK(weaponIDTextBox), LOC(160, 30), &wearAmount, 0.005f, 1.0f);
	stattrakTextBox = new NumberBox ("Stat Trak", &stattrakText, BELOW(wearAmountSlider), LOC(160, 30));
	nameIDTextBox = new TextBox ("Name Tag", &nameIDText, BELOW(stattrakTextBox), LOC(160, 30));

	setButton = new OutlinedButton ("Set", BELOW(seedIDTextBox), LOC(330, 30));
	setButton->OnClickedEvent = MFUNC (&WeaponSkinPanel::ApplySkin, this);

	AddComponent(weaponIDTextBox);
	AddComponent(skinIDTextBox);
	AddComponent(seedIDTextBox);
	AddComponent(wearAmountSlider);
	AddComponent(stattrakTextBox);
	AddComponent(nameIDTextBox);

	AddComponent(setButton);
	Hide ();
}

std::string convertToUpper(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);

	return s;
}

void WeaponSkinPanel::ApplySkin()
{
	int weaponID = Util::Items::GetItemIndex(convertToUpper(weaponIDText));
	if (weaponID == -1)
		return;

	Settings::Skinchanger::skins[weaponID] = Settings::Skinchanger::Skin(
			skinIDText.empty() ? -1 : std::stoi(skinIDText),
			-1,
			seedIDText.empty() ? -1 : std::stoi(seedIDText),
			wearAmount,
			stattrakText.empty() ? -1 : std::stoi(stattrakText),
			nameIDText,
			""
	);

	SkinChanger::ForceFullUpdate = true;
}
