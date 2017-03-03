#include "util_items.h"
#include "skins.h"

namespace Util
{
	namespace Items
	{
		using i = ItemDefinitionIndex;
		const std::map<std::string, ItemDefinitionIndex> ItemNames = {
			{ ItemDefinitionIndexMap.at(i::INVALID).entityName,						i::INVALID },	 // Convention (see config file)
			{ ItemDefinitionIndexMap.at(i::WEAPON_DEAGLE).entityName,				i::WEAPON_DEAGLE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_ELITE).entityName,				i::WEAPON_ELITE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_FIVESEVEN).entityName,			i::WEAPON_FIVESEVEN },
			{ ItemDefinitionIndexMap.at(i::WEAPON_GLOCK).entityName,				i::WEAPON_GLOCK },
			{ ItemDefinitionIndexMap.at(i::WEAPON_AK47).entityName,					i::WEAPON_AK47 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_AUG).entityName,					i::WEAPON_AUG },
			{ ItemDefinitionIndexMap.at(i::WEAPON_AWP).entityName,					i::WEAPON_AWP },
			{ ItemDefinitionIndexMap.at(i::WEAPON_FAMAS).entityName,				i::WEAPON_FAMAS },
			{ ItemDefinitionIndexMap.at(i::WEAPON_G3SG1).entityName,				i::WEAPON_G3SG1 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_GALILAR).entityName,				i::WEAPON_GALILAR },
			{ ItemDefinitionIndexMap.at(i::WEAPON_M249).entityName,					i::WEAPON_M249 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_M4A1).entityName,					i::WEAPON_M4A1 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_MAC10).entityName,				i::WEAPON_MAC10 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_P90).entityName,					i::WEAPON_P90 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_UMP45).entityName,				i::WEAPON_UMP45 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_XM1014).entityName,				i::WEAPON_XM1014 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_BIZON).entityName,				i::WEAPON_BIZON },
			{ ItemDefinitionIndexMap.at(i::WEAPON_MAG7).entityName,					i::WEAPON_MAG7 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_NEGEV).entityName,				i::WEAPON_NEGEV },
			{ ItemDefinitionIndexMap.at(i::WEAPON_SAWEDOFF).entityName,				i::WEAPON_SAWEDOFF },
			{ ItemDefinitionIndexMap.at(i::WEAPON_TEC9).entityName,					i::WEAPON_TEC9 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_TASER).entityName,				i::WEAPON_TASER },
			{ ItemDefinitionIndexMap.at(i::WEAPON_HKP2000).entityName,				i::WEAPON_HKP2000 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_MP7).entityName,					i::WEAPON_MP7 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_MP9).entityName,					i::WEAPON_MP9 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_NOVA).entityName,					i::WEAPON_NOVA },
			{ ItemDefinitionIndexMap.at(i::WEAPON_P250).entityName,					i::WEAPON_P250 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_SCAR20).entityName,				i::WEAPON_SCAR20 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_SG556).entityName,				i::WEAPON_SG556 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_SSG08).entityName,				i::WEAPON_SSG08 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE).entityName,				i::WEAPON_KNIFE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_FLASHBANG).entityName,			i::WEAPON_FLASHBANG },
			{ ItemDefinitionIndexMap.at(i::WEAPON_HEGRENADE).entityName,			i::WEAPON_HEGRENADE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_SMOKEGRENADE).entityName,			i::WEAPON_SMOKEGRENADE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_MOLOTOV).entityName,				i::WEAPON_MOLOTOV },
			{ ItemDefinitionIndexMap.at(i::WEAPON_DECOY).entityName,				i::WEAPON_DECOY },
			{ ItemDefinitionIndexMap.at(i::WEAPON_INCGRENADE).entityName,			i::WEAPON_INCGRENADE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_C4).entityName,					i::WEAPON_C4 },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_T).entityName,				i::WEAPON_KNIFE_T },
			{ ItemDefinitionIndexMap.at(i::WEAPON_M4A1_SILENCER).entityName,		i::WEAPON_M4A1_SILENCER },
			{ ItemDefinitionIndexMap.at(i::WEAPON_USP_SILENCER).entityName,			i::WEAPON_USP_SILENCER },
			{ ItemDefinitionIndexMap.at(i::WEAPON_CZ75A).entityName,				i::WEAPON_CZ75A },
			{ ItemDefinitionIndexMap.at(i::WEAPON_REVOLVER).entityName,				i::WEAPON_REVOLVER },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_BAYONET).entityName,		i::WEAPON_KNIFE_BAYONET },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_FLIP).entityName,			i::WEAPON_KNIFE_FLIP },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_GUT).entityName,			i::WEAPON_KNIFE_GUT },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_KARAMBIT).entityName,		i::WEAPON_KNIFE_KARAMBIT },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_M9_BAYONET).entityName,		i::WEAPON_KNIFE_M9_BAYONET },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_TACTICAL).entityName,		i::WEAPON_KNIFE_TACTICAL },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_FALCHION).entityName,		i::WEAPON_KNIFE_FALCHION },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_SURVIVAL_BOWIE).entityName,	i::WEAPON_KNIFE_SURVIVAL_BOWIE },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_BUTTERFLY).entityName,		i::WEAPON_KNIFE_BUTTERFLY },
			{ ItemDefinitionIndexMap.at(i::WEAPON_KNIFE_PUSH).entityName,			i::WEAPON_KNIFE_PUSH },
			{ ItemDefinitionIndexMap.at(i::GLOVE_STUDDED_BLOODHOUND).entityName, 	i::GLOVE_STUDDED_BLOODHOUND},
			{ ItemDefinitionIndexMap.at(i::GLOVE_CT_SIDE).entityName,				i::GLOVE_CT_SIDE},
			{ ItemDefinitionIndexMap.at(i::GLOVE_T_SIDE).entityName,				i::GLOVE_T_SIDE},
			{ ItemDefinitionIndexMap.at(i::GLOVE_SPORTY).entityName,				i::GLOVE_SPORTY},
			{ ItemDefinitionIndexMap.at(i::GLOVE_SLICK).entityName,					i::GLOVE_SLICK},
			{ ItemDefinitionIndexMap.at(i::GLOVE_LEATHER_WRAP).entityName,			i::GLOVE_LEATHER_WRAP},
			{ ItemDefinitionIndexMap.at(i::GLOVE_MOTORCYCLE).entityName,			i::GLOVE_MOTORCYCLE},
			{ ItemDefinitionIndexMap.at(i::GLOVE_SPECIALIST).entityName,			i::GLOVE_SPECIALIST},

		};  // ItemNames

		std::string GetItemName(const enum ItemDefinitionIndex index)
		{
			return Util::MapReverseSearchOrDefault<std::string, ItemDefinitionIndex>(&ItemNames, index, "ITEM_INVALID");
		}

		std::string GetItemEntityName(ItemDefinitionIndex index)
		{
			if (ItemDefinitionIndexMap.find(index) != ItemDefinitionIndexMap.end())
			{
				std::string entityName = ItemDefinitionIndexMap.at(index).entityName;

				if (entityName.find("weapon_") != std::string::npos)
					entityName.erase(entityName.find("weapon_"), std::string("weapon_").length());

				return entityName;
			}

			return "INVALID";
		}

		std::string GetItemConfigEntityName(ItemDefinitionIndex index)
		{
			if (ItemDefinitionIndexMap.find(index) != ItemDefinitionIndexMap.end())
				return  ItemDefinitionIndexMap.at(index).entityName;

			return "INVALID";
		}

		std::string GetItemDisplayName(ItemDefinitionIndex index)
		{
			if (ItemDefinitionIndexMap.find(index) != ItemDefinitionIndexMap.end())
			{
				if (ItemDefinitionIndexMap.find(index) != ItemDefinitionIndexMap.end() && index != ItemDefinitionIndex::INVALID)
					return Util::WstringToString(localize->FindSafe(ItemDefinitionIndexMap.at(index).displayName));

				return ItemDefinitionIndexMap.at(index).displayName;
			}

			return "INVALID";
		}

		ItemDefinitionIndex GetItemIndex(const std::string itemName)
		{
			return Util::MapSearchOrDefault<std::string, ItemDefinitionIndex>(&ItemNames, Util::ToLower(itemName), ItemDefinitionIndex::INVALID);
		}

		bool IsKnife(ItemDefinitionIndex index)
		{
			switch (index)
			{
				case ItemDefinitionIndex::WEAPON_KNIFE:
				case ItemDefinitionIndex::WEAPON_KNIFE_T:
				case ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
				case ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
				case ItemDefinitionIndex::WEAPON_KNIFE_GUT:
				case ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
				case ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
				case ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
				case ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
				case ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
				case ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
				case ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
					return true;
				default:
					return false;
			}
		}

		bool IsUtility(ItemDefinitionIndex index)
		{
			switch (index)
			{
				case ItemDefinitionIndex::WEAPON_C4:
				case ItemDefinitionIndex::WEAPON_FLASHBANG:
				case ItemDefinitionIndex::WEAPON_HEGRENADE:
				case ItemDefinitionIndex::WEAPON_INCGRENADE:
				case ItemDefinitionIndex::WEAPON_MOLOTOV:
				case ItemDefinitionIndex::WEAPON_SMOKEGRENADE:
				case ItemDefinitionIndex::WEAPON_DECOY:
					return true;
				default:
					return false;
			}
		}

		bool IsGlove(ItemDefinitionIndex index)
		{
			switch (index)
			{
				case ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND:
				case ItemDefinitionIndex::GLOVE_SPECIALIST:
				case ItemDefinitionIndex::GLOVE_CT_SIDE:
				case ItemDefinitionIndex::GLOVE_T_SIDE:
				case ItemDefinitionIndex::GLOVE_MOTORCYCLE:
				case ItemDefinitionIndex::GLOVE_SLICK:
				case ItemDefinitionIndex::GLOVE_SPORTY:
				case ItemDefinitionIndex::GLOVE_LEATHER_WRAP:
					return true;
				default:
					return false;
			}
		}

		bool IsCTWeapon(ItemDefinitionIndex index)
		{
			switch (index)
			{
				case ItemDefinitionIndex::WEAPON_M4A1:
				case ItemDefinitionIndex::WEAPON_M4A1_SILENCER:
				case ItemDefinitionIndex::WEAPON_HKP2000:
				case ItemDefinitionIndex::WEAPON_FIVESEVEN:
				case ItemDefinitionIndex::WEAPON_USP_SILENCER:
				case ItemDefinitionIndex::WEAPON_AUG:
				case ItemDefinitionIndex::WEAPON_SCAR20:
				case ItemDefinitionIndex::WEAPON_FAMAS:
				case ItemDefinitionIndex::WEAPON_MAG7:
				case ItemDefinitionIndex::WEAPON_MP9:
					return true;
				default:
					return false;
			}
		}

		bool IsTWeapon(ItemDefinitionIndex index)
		{
			switch (index)
			{
				case ItemDefinitionIndex::WEAPON_AK47:
				case ItemDefinitionIndex::WEAPON_GALILAR:
				case ItemDefinitionIndex::WEAPON_GLOCK:
				case ItemDefinitionIndex::WEAPON_SG556:
				case ItemDefinitionIndex::WEAPON_G3SG1:
				case ItemDefinitionIndex::WEAPON_TEC9:
				case ItemDefinitionIndex::WEAPON_SAWEDOFF:
				case ItemDefinitionIndex::WEAPON_MAC10:
					return true;
				default:
					return false;
			}
		}
	}
}
