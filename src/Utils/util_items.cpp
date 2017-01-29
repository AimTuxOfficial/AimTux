#include "util_items.h"

namespace Util
{
	namespace Items
	{
		using i = ItemDefinitionIndex;
		const std::map<std::string, ItemDefinitionIndex> ItemNames = {
			{ "ITEM_INVALID",					i::INVALID },	 // Convention (see config file)
			{ "WEAPON_DEAGLE",					i::WEAPON_DEAGLE },
			{ "WEAPON_ELITE",					i::WEAPON_ELITE },
			{ "WEAPON_FIVESEVEN",				i::WEAPON_FIVESEVEN },
			{ "WEAPON_GLOCK",					i::WEAPON_GLOCK },
			{ "WEAPON_AK47",					i::WEAPON_AK47 },
			{ "WEAPON_AUG",						i::WEAPON_AUG },
			{ "WEAPON_AWP",						i::WEAPON_AWP },
			{ "WEAPON_FAMAS",					i::WEAPON_FAMAS },
			{ "WEAPON_G3SG1",					i::WEAPON_G3SG1 },
			{ "WEAPON_GALILAR",					i::WEAPON_GALILAR },
			{ "WEAPON_M249",					i::WEAPON_M249 },
			{ "WEAPON_M4A1",					i::WEAPON_M4A1 },
			{ "WEAPON_MAC10",					i::WEAPON_MAC10 },
			{ "WEAPON_P90",						i::WEAPON_P90 },
			{ "WEAPON_UMP45",					i::WEAPON_UMP45 },
			{ "WEAPON_XM1014",					i::WEAPON_XM1014 },
			{ "WEAPON_BIZON",					i::WEAPON_BIZON },
			{ "WEAPON_MAG7",					i::WEAPON_MAG7 },
			{ "WEAPON_NEGEV",					i::WEAPON_NEGEV },
			{ "WEAPON_SAWEDOFF",				i::WEAPON_SAWEDOFF },
			{ "WEAPON_TEC9",					i::WEAPON_TEC9 },
			{ "WEAPON_TASER",					i::WEAPON_TASER },
			{ "WEAPON_HKP2000",					i::WEAPON_HKP2000 },
			{ "WEAPON_MP7",						i::WEAPON_MP7 },
			{ "WEAPON_MP9",						i::WEAPON_MP9 },
			{ "WEAPON_NOVA",					i::WEAPON_NOVA },
			{ "WEAPON_P250",					i::WEAPON_P250 },
			{ "WEAPON_SCAR20",					i::WEAPON_SCAR20 },
			{ "WEAPON_SG556",					i::WEAPON_SG556 },
			{ "WEAPON_SSG08",					i::WEAPON_SSG08 },
			{ "WEAPON_KNIFE",					i::WEAPON_KNIFE },
			{ "WEAPON_FLASHBANG",				i::WEAPON_FLASHBANG },
			{ "WEAPON_HEGRENADE",				i::WEAPON_HEGRENADE },
			{ "WEAPON_SMOKEGRENADE",			i::WEAPON_SMOKEGRENADE },
			{ "WEAPON_MOLOTOV",					i::WEAPON_MOLOTOV },
			{ "WEAPON_DECOY",					i::WEAPON_DECOY },
			{ "WEAPON_INCGRENADE",				i::WEAPON_INCGRENADE },
			{ "WEAPON_C4",						i::WEAPON_C4 },
			{ "WEAPON_KNIFE_T",					i::WEAPON_KNIFE_T },
			{ "WEAPON_M4A1_SILENCER",			i::WEAPON_M4A1_SILENCER },
			{ "WEAPON_USP_SILENCER",			i::WEAPON_USP_SILENCER },
			{ "WEAPON_CZ75A",					i::WEAPON_CZ75A },
			{ "WEAPON_REVOLVER",				i::WEAPON_REVOLVER },
			{ "WEAPON_KNIFE_BAYONET",			i::WEAPON_KNIFE_BAYONET },
			{ "WEAPON_KNIFE_FLIP",				i::WEAPON_KNIFE_FLIP },
			{ "WEAPON_KNIFE_GUT",				i::WEAPON_KNIFE_GUT },
			{ "WEAPON_KNIFE_KARAMBIT",			i::WEAPON_KNIFE_KARAMBIT },
			{ "WEAPON_KNIFE_M9_BAYONET",		i::WEAPON_KNIFE_M9_BAYONET },
			{ "WEAPON_KNIFE_TACTICAL",			i::WEAPON_KNIFE_TACTICAL },
			{ "WEAPON_KNIFE_FALCHION",			i::WEAPON_KNIFE_FALCHION },
			{ "WEAPON_KNIFE_SURVIVAL_BOWIE",	i::WEAPON_KNIFE_SURVIVAL_BOWIE },
			{ "WEAPON_KNIFE_BUTTERFLY",			i::WEAPON_KNIFE_BUTTERFLY },
			{ "WEAPON_KNIFE_PUSH",				i::WEAPON_KNIFE_PUSH },
			{ "GLOVE_STUDDED_BLOODHOUND",	i::GLOVE_STUDDED_BLOODHOUND},
			{ "GLOVE_CT_SIDE",	i::GLOVE_CT_SIDE},
			{ "GLOVE_T_SIDE",	i::GLOVE_T_SIDE},
			{ "GLOVE_SPORTY",	i::GLOVE_SPORTY},
			{ "GLOVE_SLICK",	i::GLOVE_SLICK},
			{ "GLOVE_LEATHER_WRAP",	i::GLOVE_LEATHER_WRAP},
			{ "GLOVE_MOTORCYCLE",	i::GLOVE_MOTORCYCLE},
			{ "GLOVE_SPECIALIST",	i::GLOVE_SPECIALIST},

		};  // ItemNames

		std::string GetItemName(const enum ItemDefinitionIndex index)
		{
			return Util::MapReverseSearchOrDefault<std::string, ItemDefinitionIndex>(&ItemNames, index, "ITEM_INVALID");
		}

		ItemDefinitionIndex GetItemIndex(const std::string itemName)
		{
			return Util::MapSearchOrDefault<std::string, ItemDefinitionIndex>(&ItemNames, itemName, ItemDefinitionIndex::INVALID);
		}
	}
}
