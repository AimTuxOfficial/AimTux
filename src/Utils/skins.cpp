#include "skins.h"

std::vector<std::pair<int, const char*>> guns = {
		{ -1, "<-Default->"},
		{ WEAPON_AK47, "#SFUI_WPNHUD_AK47" },
		{ WEAPON_AUG, "#SFUI_WPNHUD_Aug" },
		{ WEAPON_AWP, "#SFUI_WPNHUD_AWP" },
		{ WEAPON_CZ75A, "#SFUI_WPNHUD_CZ75" },
		{ WEAPON_DEAGLE, "#SFUI_WPNHUD_DesertEagle" },
		{ WEAPON_ELITE, "#SFUI_WPNHUD_Elites" },
		{ WEAPON_FAMAS, "#SFUI_WPNHUD_Famas" },
		{ WEAPON_FIVESEVEN, "#SFUI_WPNHUD_FiveSeven" },
		{ WEAPON_GALILAR, "#SFUI_WPNHUD_GalilAR" },
		{ WEAPON_G3SG1, "#SFUI_WPNHUD_G3SG1" },
		{ WEAPON_GLOCK, "#SFUI_WPNHUD_Glock18" },
		{ WEAPON_M249, "#SFUI_WPNHUD_M249" },
		{ WEAPON_M4A1_SILENCER, "#SFUI_WPNHUD_M4_SILENCER" },
		{ WEAPON_M4A1, "#SFUI_WPNHUD_M4A1" },
		{ WEAPON_MAC10, "#SFUI_WPNHUD_MAC10" },
		{ WEAPON_MAG7, "#SFUI_WPNHUD_Mag7" },
		{ WEAPON_MP7, "#SFUI_WPNHUD_MP7" },
		{ WEAPON_MP9, "#SFUI_WPNHUD_MP9" },
		{ WEAPON_NEGEV, "#SFUI_WPNHUD_Negev" },
		{ WEAPON_NOVA, "#SFUI_WPNHUD_Nova" },
		{ WEAPON_HKP2000, "#SFUI_WPNHUD_HKP2000" },
		{ WEAPON_P250, "#SFUI_WPNHUD_P250" },
		{ WEAPON_P90, "#SFUI_WPNHUD_P90" },
		{ WEAPON_BIZON, "#SFUI_WPNHUD_Bizon" },
		{ WEAPON_REVOLVER, "#SFUI_WPNHUD_REVOLVER" },
		{ WEAPON_SAWEDOFF, "#SFUI_WPNHUD_Sawedoff" },
		{ WEAPON_SCAR20, "#SFUI_WPNHUD_SCAR20" },
		{ WEAPON_SG556, "#SFUI_WPNHUD_SG556" },
		{ WEAPON_SSG08, "#SFUI_WPNHUD_SSG08" },
		{ WEAPON_TEC9, "#SFUI_WPNHUD_Tec9" },
		{ WEAPON_UMP45, "#SFUI_WPNHUD_UMP45" },
		{ WEAPON_USP_SILENCER, "#SFUI_WPNHUD_USP_SILENCER" },
		{ WEAPON_XM1014, "#SFUI_WPNHUD_xm1014" },
};

std::vector<std::pair<int, const char*>> knives = {
		{ 0,					"#SFUI_WPNHUD_KnifeBayonet" },
		{ 5,					"#SFUI_WPNHUD_KnifeFlip" },
		{ 6,					"#SFUI_WPNHUD_KnifeGut" },
		{ 7,					"#SFUI_WPNHUD_KnifeKaram" },
		{ 8,					"#SFUI_WPNHUD_KnifeM9" },
		{ 9,					"#SFUI_WPNHUD_KnifeTactical" },
		{ 12,					"#SFUI_WPNHUD_knife_falchion_advanced" },
		{ 14,					"#SFUI_WPNHUD_knife_survival_bowie" },
		{ 15,					"#SFUI_WPNHUD_Knife_Butterfly" },
		{ 16,					"#SFUI_WPNHUD_knife_push" },
};

void LocalizeGuns()
{
	int index = -1;

	for (auto it : guns)
	{
		index++;

		if (it.first == -1)
			continue;

		std::string localized = Util::WstringToString(localize->FindSafe(it.second));
		guns[index] = { it.first, strdup(localized.c_str()) };
	}
}

void LocalizeKnives()
{
	int index = -1;

	for (auto it : knives)
	{
		index++;

		if (it.first == -1)
			continue;

		std::string localized = Util::WstringToString(localize->FindSafe(it.second));
		knives[index] = { it.first, strdup(localized.c_str()) };
	}
}

void Skins::Localize()
{
	static bool isLocalized = false;
	if (isLocalized)
		return;

	if (guns.size() == 0 || knives.size() == 0)
		return;

	LocalizeGuns();
	LocalizeKnives();

	isLocalized = true;
}
