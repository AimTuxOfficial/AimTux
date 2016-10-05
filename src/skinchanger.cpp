#include "skinchanger.h"

std::unordered_map<int, SkinChanger::Skin> SkinChanger::skins = {
		{ WEAPON_AWP, SkinChanger::Skin(344, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_AK47, SkinChanger::Skin(524, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_M4A1, SkinChanger::Skin(512, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_M4A1_SILENCER, SkinChanger::Skin(548, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_DEAGLE, SkinChanger::Skin(277, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_GLOCK, SkinChanger::Skin(38, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_USP_SILENCER, SkinChanger::Skin(332, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_FIVESEVEN, SkinChanger::Skin(252, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_SCAR20, SkinChanger::Skin(391, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_ELITE, SkinChanger::Skin(249, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_SSG08, SkinChanger::Skin(319, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_TEC9, SkinChanger::Skin(179, 0, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_KNIFE, SkinChanger::Skin(417, WEAPON_KNIFE_M9_BAYONET, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_KNIFE_T, SkinChanger::Skin(417, WEAPON_KNIFE_KARAMBIT, 0.00000000f, 1337, "AimTux", NULL) },
		{ WEAPON_KNIFE_M9_BAYONET, SkinChanger::Skin(417, WEAPON_KNIFE_M9_BAYONET, 0.00000000f, 1337, "AimTux", "models/weapons/v_knife_m9_bay.mdl") },
		{ WEAPON_KNIFE_KARAMBIT, SkinChanger::Skin(417, WEAPON_KNIFE_KARAMBIT, 0.00000000f, 1337, "AimTux", "models/weapons/v_knife_karam.mdl") }
};

void SkinChanger::FrameStageNotify(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	/* get our player entity */
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

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

		auto keyExists = SkinChanger::skins.find(*weapon->GetItemDefinitionIndex());
		if (keyExists == SkinChanger::skins.end())
			continue;

		SkinChanger::Skin currentSkin = SkinChanger::skins[*weapon->GetItemDefinitionIndex()];

		if (currentSkin.PaintKit != 0)
			*weapon->GetFallbackPaintKit() = currentSkin.PaintKit;

		if (currentSkin.ItemDefinitionIndex != 0)
			*weapon->GetItemDefinitionIndex() = currentSkin.ItemDefinitionIndex;

		if (currentSkin.Wear != 0)
			*weapon->GetFallbackWear() = currentSkin.Wear;

		if (currentSkin.StatTrak != 0)
			*weapon->GetFallbackStatTrak() = currentSkin.StatTrak;

		if (currentSkin.CustomName != NULL)
			snprintf(weapon->GetCustomName(), 32, "%s", currentSkin.CustomName);

		/* force our fallback values to be used */
		*weapon->GetItemIDHigh() = -1;
	}

	/* viewmodel replacements */
	C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntity(localplayer->GetViewModel() & 0xFFF));

	if (!viewmodel)
		return;

	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntity(viewmodel->GetWeapon() & 0xFFF));

	if (!active_weapon)
		return;

	auto keyExists = SkinChanger::skins.find(*active_weapon->GetItemDefinitionIndex());
	if (keyExists == SkinChanger::skins.end())
		return;

	SkinChanger::Skin currentSkin = SkinChanger::skins[*active_weapon->GetItemDefinitionIndex()];

	if (currentSkin.Model != NULL)
		*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(currentSkin.Model);
}