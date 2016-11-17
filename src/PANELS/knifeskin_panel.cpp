#include "knifeskin_panel.h"

KnifeSkinPanel::KnifeSkinPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	side = CT;
	skinIDTextBox = new NumberBox ("Skin ID", &skinIDText, LOC(10, 10), LOC(160, 30));
	seedIDTextBox = new NumberBox ("Seed", &seedIDText, BELOW(skinIDTextBox), LOC(160, 30));
	wearAmountSlider = new Slider("Wear Amount", STACK(skinIDTextBox), LOC(160, 30), &wearAmount, 0.005f, 1.0f);
	stattrakTextBox = new NumberBox ("Stat Trak", &stattrakText, BELOW(wearAmountSlider), LOC(160, 30));
	nameIDTextBox = new TextBox ("Name Tag", &nameIDText, BELOW(seedIDTextBox), LOC(160, 30));

	loadButton = new OutlinedButton ("Load", BELOW(nameIDTextBox), LOC ((size.x - 20) / 2 - 5, 40));
	loadButton->OnClickedEvent = MFUNC (&KnifeSkinPanel::LoadSkin, this);

	setButton = new OutlinedButton ("Set", STACK(loadButton), LOC ((size.x - 20) / 2 - 5, 40));
	setButton->OnClickedEvent = MFUNC (&KnifeSkinPanel::ApplySkin, this);

	slb_knife = new ScrollingListBox<ItemDefinitionIndex>("Knife", BELOW (loadButton), (size.x - 20) / 2, &knifeType, std::vector<SLB_Element>
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

	cb_side = new ComboBox<Side>("Side", STACK(nameIDTextBox), 160, &side, std::vector<CB_Element>
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

	AddComponent(loadButton);
	AddComponent(setButton);
	Hide ();
}

void KnifeSkinPanel::LoadSkin()
{
	auto keyExists = Settings::Skinchanger::skins.find(side == CT ? WEAPON_KNIFE : WEAPON_KNIFE_T);
	if (keyExists == Settings::Skinchanger::skins.end())
		return;

	Settings::Skinchanger::Skin skin = Settings::Skinchanger::skins[side == CT ? WEAPON_KNIFE : WEAPON_KNIFE_T];

	wearAmount = skin.Wear;
	skinIDText = std::to_string(skin.PaintKit);
	seedIDText = std::to_string(skin.Seed);
	stattrakText = std::to_string(skin.StatTrak);
	nameIDText = skin.CustomName;
	knifeType = (enum ItemDefinitionIndex) skin.ItemDefinitionIndex;
}

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

	Settings::Skinchanger::skins[WEAPON_KNIFE_GUT] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_gut.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_FLIP] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_flip.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_BAYONET] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_bayonet.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_M9_BAYONET] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_m9_bay.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_KARAMBIT] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_karam.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_TACTICAL] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_tactical.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_BUTTERFLY] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_butterfly.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_SURVIVAL_BOWIE] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_survival_bowie.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_FALCHION] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_falchion_advanced.mdl");
	Settings::Skinchanger::skins[WEAPON_KNIFE_PUSH] = Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_push.mdl");

	Settings::Skinchanger::skins[side == CT ? WEAPON_KNIFE : WEAPON_KNIFE_T] = skin;

	SkinChanger::ForceFullUpdate = true;
}
