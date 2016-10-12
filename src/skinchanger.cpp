#include "skinchanger.h"

bool Settings::Skinchanger::enabled = true;
std::unordered_map<int, Settings::Skinchanger::Skin> Settings::Skinchanger::skins = {
		{ WEAPON_AWP, Settings::Skinchanger::Skin(344, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_AK47, Settings::Skinchanger::Skin(524, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_M4A1, Settings::Skinchanger::Skin(512, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_M4A1_SILENCER, Settings::Skinchanger::Skin(548, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_DEAGLE, Settings::Skinchanger::Skin(277, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_GLOCK, Settings::Skinchanger::Skin(38, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_USP_SILENCER, Settings::Skinchanger::Skin(332, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_FIVESEVEN, Settings::Skinchanger::Skin(252, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_SCAR20, Settings::Skinchanger::Skin(391, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_ELITE, Settings::Skinchanger::Skin(249, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_SSG08, Settings::Skinchanger::Skin(319, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_TEC9, Settings::Skinchanger::Skin(179, -1, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_M9_BAYONET, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE_T, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_KARAMBIT, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE_M9_BAYONET, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_M9_BAYONET, 0.0005f, 1337, "AimTux", "models/weapons/v_knife_m9_bay.mdl") },
		{ WEAPON_KNIFE_KARAMBIT, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_KARAMBIT, 0.0005f, 1337, "AimTux", "models/weapons/v_knife_karam.mdl") }
};

void SkinChanger::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::Skinchanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	/* get our player entity */
	int localplayer_index = engine->GetLocalPlayer();
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(localplayer_index));

	if (!localplayer || localplayer->GetLifeState() != LIFE_ALIVE)
		return;

	/* get a list of weapon we're holding */
	int* weapons = localplayer->GetWeapons();

	if (!weapons)
		return;

	for (int i = 0; i < 64; i++)
	{
		/* check if the handle is invalid */
		if (weapons[i] == -1)
			continue;

		C_BaseAttributableItem* weapon = reinterpret_cast<C_BaseAttributableItem*>(entitylist->GetClientEntity(weapons[i] & 0xFFF));

		/* check if the weapon pointer is invalid */
		if (!weapon)
			continue;

		auto keyExists = Settings::Skinchanger::skins.find(*weapon->GetItemDefinitionIndex());
		if (keyExists == Settings::Skinchanger::skins.end())
			continue;

		Settings::Skinchanger::Skin currentSkin = Settings::Skinchanger::skins[*weapon->GetItemDefinitionIndex()];

		if (currentSkin.PaintKit != -1)
			*weapon->GetFallbackPaintKit() = currentSkin.PaintKit;

		if (currentSkin.ItemDefinitionIndex != -1)
			*weapon->GetItemDefinitionIndex() = currentSkin.ItemDefinitionIndex;

		if (currentSkin.Wear != -1)
			*weapon->GetFallbackWear() = currentSkin.Wear;

		if (currentSkin.StatTrak != -1)
		{
			*weapon->GetFallbackStatTrak() = currentSkin.StatTrak;

			IEngineClient::player_info_t localplayer_info;

			if (engine->GetPlayerInfo(localplayer_index, &localplayer_info))
			{
				*weapon->GetAccountID() = localplayer_info.xuidlow;
			}
		}

		if (currentSkin.CustomName != "")
			snprintf(weapon->GetCustomName(), 32, "%s", currentSkin.CustomName.c_str());

		/* force our fallback values to be used */
		*weapon->GetItemIDHigh() = -1;
	}

	/* viewmodel replacements */
	C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntityFromHandle(localplayer->GetViewModel()));
	if (!viewmodel)
		return;

	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon()));
	if (!active_weapon)
		return;

	auto keyExists = Settings::Skinchanger::skins.find(*active_weapon->GetItemDefinitionIndex());
	if (keyExists == Settings::Skinchanger::skins.end())
		return;

	Settings::Skinchanger::Skin currentSkin = Settings::Skinchanger::skins[*active_weapon->GetItemDefinitionIndex()];

	if (currentSkin.Model != "")
		*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(currentSkin.Model.c_str());
}