#include <iostream>
#include "settings.h"

std::unordered_map<int, std::tuple<int, int, float, int, const char*, const char *>> Settings::SkinChanger::getSettings() {
	std::unordered_map<int, std::tuple<int, int, float, int, const char*, const char *>> settings;

	// PaintKit, ItemDefinitionIndex, Wear, StatTrak, CustomName, Model
	settings[WEAPON_AWP] = std::make_tuple(344, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_AK47] = std::make_tuple(524, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_M4A1] = std::make_tuple(512, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_M4A1_SILENCER] = std::make_tuple(548, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_DEAGLE] = std::make_tuple(277, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_GLOCK] = std::make_tuple(38, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_USP_SILENCER] = std::make_tuple(332, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_FIVESEVEN] = std::make_tuple(252, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_SCAR20] = std::make_tuple(391, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_ELITE] = std::make_tuple(249, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_SSG08] = std::make_tuple(319, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_TEC9] = std::make_tuple(179, 0, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_KNIFE] = std::make_tuple(417, WEAPON_KNIFE_M9_BAYONET, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_KNIFE_T] = std::make_tuple(417, WEAPON_KNIFE_KARAMBIT, 0.00000000f, 1337, "AimTux", "");
	settings[WEAPON_KNIFE_M9_BAYONET] = std::make_tuple(417, WEAPON_KNIFE_M9_BAYONET, 0.00000000f, 1337, "AimTux", "models/weapons/v_knife_m9_bay.mdl");
	settings[WEAPON_KNIFE_KARAMBIT] = std::make_tuple(417, WEAPON_KNIFE_KARAMBIT, 0.00000000f, 1337, "AimTux", "models/weapons/v_knife_karam.mdl");

	return settings;
}