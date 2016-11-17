#include "skinchanger_panel.h"

SkinChangerPanel::SkinChangerPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	// ** INITIALIZE GUNS COMPONENTS ** //
	ba_gun = new Banner("Guns", LOC(10, 10), (size.x - 20) / 2 - 5);
	cb_gun = new ComboBox<ItemDefinitionIndex>("Guns", BELOW (ba_gun), (size.x - 20) / 6.75, &gun, std::vector<CB_Element>
		{
			CB_Element("AK47", WEAPON_AK47),
			CB_Element("M4A1-S", WEAPON_M4A1_SILENCER),
			CB_Element("M4A4", WEAPON_M4A1),
			CB_Element("AWP", WEAPON_AWP),
			CB_Element("P2000", WEAPON_HKP2000),
			CB_Element("USP", WEAPON_USP_SILENCER),
			CB_Element("Glock", WEAPON_GLOCK),
			CB_Element("Deagle", WEAPON_DEAGLE),
			CB_Element("P250", WEAPON_P250),
			CB_Element("Tec-9", WEAPON_TEC9),
			CB_Element("Five SeveN", WEAPON_FIVESEVEN),
			CB_Element("CZ-75", WEAPON_CZ75A),
			CB_Element("Revolver", WEAPON_REVOLVER),
		}, false
	);
	gunIDTextBox = new TextBox("Or type weapon name e.g weapon_ak47", &gunIDText, STACK(cb_gun), LOC((size.x - 20) / 3.375 + 10, 30));
	gunSkinIDTextBox = new NumberBox ("Skin ID", &gunSkinIDText, BELOW(gunIDTextBox), LOC((size.x - 20) / 6.75, 30));
	gunSeedIDTextBox = new NumberBox ("Seed", &gunSeedIDText, STACK(gunSkinIDTextBox), LOC((size.x - 20) / 6.75, 30));
	gunWearAmountSlider = new Slider("Wear Amount", BELOW(gunSkinIDTextBox), LOC((size.x - 20) / 3.375 + 10, 30), &gunWearAmount, 0.005f, 1.0f);
	gunStattrakTextBox = new NumberBox ("Stat Trak", &gunStattrakText, BELOW(gunWearAmountSlider), LOC((size.x - 20) / 6.75, 30));
	gunNameIDTextBox = new TextBox ("Name Tag", &gunNameIDText, STACK(gunStattrakTextBox), LOC((size.x - 20) / 6.75, 30));

	gunSetButton = new OutlinedButton ("Apply", BELOW(gunStattrakTextBox), LOC((size.x - 20) / 6.75, 30));
	gunSetButton->OnClickedEvent = MFUNC (&SkinChangerPanel::ApplyGunSkin, this);

	gunLoadButton = new OutlinedButton ("Load", STACK(gunSetButton), LOC ((size.x - 20) / 6.75, 30));
	gunLoadButton->OnClickedEvent = MFUNC (&SkinChangerPanel::LoadGunSkin, this);

	// ** DRAW GUNS COMPONENTS ** //
	AddComponent(ba_gun);
	AddComponent(cb_gun);
	AddComponent(gunIDTextBox);
	AddComponent(gunSkinIDTextBox);
	AddComponent(gunSeedIDTextBox);
	AddComponent(gunWearAmountSlider);
	AddComponent(gunStattrakTextBox);
	AddComponent(gunNameIDTextBox);
	AddComponent(gunSetButton);
	AddComponent(gunLoadButton);

	// ** INITIALIZE KNIFE COMPONENTS ** //
	side = CT;

	ba_knife = new Banner("Knife", STACK(ba_gun), (size.x - 20) / 2 - 5);
	cb_knife = new ComboBox<ItemDefinitionIndex>("Knife", BELOW(ba_knife), (size.x - 20) / 6.75, &knife, std::vector<CB_Element>
		{
			CB_Element ("Bayonet", WEAPON_KNIFE_BAYONET),
			CB_Element ("Flip", WEAPON_KNIFE_FLIP),
			CB_Element ("Gut", WEAPON_KNIFE_GUT),
			CB_Element ("Karambit", WEAPON_KNIFE_KARAMBIT),
			CB_Element ("M9 Bayonet", WEAPON_KNIFE_M9_BAYONET),
			CB_Element ("Huntsman", WEAPON_KNIFE_TACTICAL),
			CB_Element ("Falchion", WEAPON_KNIFE_FALCHION),
			CB_Element ("Butterfly", WEAPON_KNIFE_BUTTERFLY),
			CB_Element ("Bowie", WEAPON_KNIFE_SURVIVAL_BOWIE),
			CB_Element ("Daggers", WEAPON_KNIFE_PUSH),
		}, false
	);
	cb_side = new ComboBox<Side>("Side", STACK (cb_knife), (size.x - 20) / 6.75, &side, std::vector<CB_Element>
			{
					CB_Element ("CT", CT),
					CB_Element ("T", T),
			}, false
	);
	knifeSkinIDTextBox = new NumberBox ("Skin ID", &knifeSkinIDText, BELOW(cb_knife), LOC((size.x - 20) / 6.75, 30));
	knifeSeedIDTextBox = new NumberBox ("Seed", &knifeSeedIDText, STACK(knifeSkinIDTextBox), LOC((size.x - 20) / 6.75, 30));
	knifeWearAmountSlider = new Slider("Wear Amount", BELOW(knifeSkinIDTextBox), LOC((size.x - 20) / 3.375 + 10, 30), &knifeWearAmount, 0.005f, 1.0f);
	knifeStattrakTextBox = new NumberBox ("StatTrak", &knifeStattrakText, BELOW(knifeWearAmountSlider), LOC((size.x - 20) / 6.75, 30));
	knifeNameIDTextBox = new TextBox ("Name Tag", &knifeNameIDText, STACK(knifeStattrakTextBox), LOC((size.x - 20) / 6.75, 30));

	knifeSetButton = new OutlinedButton ("Apply", BELOW(knifeStattrakTextBox), LOC((size.x - 20) / 6.75, 30));
	knifeSetButton->OnClickedEvent = MFUNC (&SkinChangerPanel::ApplyKnifeSkin, this);

	knifeLoadButton = new OutlinedButton ("Load", STACK(knifeSetButton), LOC ((size.x - 20) / 6.75, 30));
	knifeLoadButton->OnClickedEvent = MFUNC (&SkinChangerPanel::LoadKnifeSkin, this);

	// ** DRAW KINFE COMPONENTS **//
	AddComponent(ba_knife);
	AddComponent(cb_side);
	AddComponent(cb_knife);
	AddComponent(knifeSkinIDTextBox);
	AddComponent(knifeSeedIDTextBox);
	AddComponent(knifeWearAmountSlider);
	AddComponent(knifeStattrakTextBox);
	AddComponent(knifeNameIDTextBox);
	AddComponent(knifeSetButton);
	AddComponent(knifeLoadButton);
}

std::string convertInputToUpper(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);

	return s;
}

void SkinChangerPanel::ApplyGunSkin()
{
	int weaponID = Util::Items::GetItemIndex(convertInputToUpper(gunIDText));

	Settings::Skinchanger::skins[gunIDText.empty() ? gun : weaponID] = Settings::Skinchanger::Skin(
		gunSkinIDText.empty() ? -1 : std::stoi(gunSkinIDText),
		-1,
		gunSeedIDText.empty() ? -1 : std::stoi(gunSeedIDText),
		gunWearAmount,
		gunStattrakText.empty() ? -1 : std::stoi(gunStattrakText),
		gunNameIDText,
		""
	);

	SkinChanger::ForceFullUpdate = true;
}


void SkinChangerPanel::LoadKnifeSkin()
{
	auto keyExists = Settings::Skinchanger::skins.find(side == CT ? WEAPON_KNIFE : WEAPON_KNIFE_T);
	if (keyExists == Settings::Skinchanger::skins.end())
		return;

	Settings::Skinchanger::Skin skin = Settings::Skinchanger::skins[side == CT ? WEAPON_KNIFE : WEAPON_KNIFE_T];

	knifeWearAmount = skin.Wear;
	knifeSkinIDText = std::to_string(skin.PaintKit);
	knifeSeedIDText = std::to_string(skin.Seed);
	knifeStattrakText = std::to_string(skin.StatTrak);
	knifeNameIDText = skin.CustomName;
	knife = (enum ItemDefinitionIndex) skin.ItemDefinitionIndex;
}

void SkinChangerPanel::LoadGunSkin()
{
	int weaponID = Util::Items::GetItemIndex(convertInputToUpper(gunIDText));

	Settings::Skinchanger::Skin skin = Settings::Skinchanger::skins[gunIDText.empty() ? gun : weaponID];

	gunWearAmount = skin.Wear;
	gunSkinIDText = std::to_string(skin.PaintKit);
	gunSeedIDText = std::to_string(skin.Seed);
	gunStattrakText = std::to_string(skin.StatTrak);
	gunNameIDText = skin.CustomName;
}

void SkinChangerPanel::ApplyKnifeSkin()
{
	Settings::Skinchanger::Skin skin = Settings::Skinchanger::Skin(
			knifeSkinIDText.empty() ? -1 : std::stoi(knifeSkinIDText),
			knife,
			knifeSeedIDText.empty() ? -1 : std::stoi(knifeSeedIDText),
			knifeWearAmount,
			knifeStattrakText.empty() ? -1 : std::stoi(knifeStattrakText),
			knifeNameIDText,
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
