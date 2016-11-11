#include "skinchanger.h"

bool Settings::Skinchanger::enabled = true;
std::unordered_map<int, Settings::Skinchanger::Skin> Settings::Skinchanger::skins = {
		{ WEAPON_AWP, Settings::Skinchanger::Skin(344, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_AK47, Settings::Skinchanger::Skin(524, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_M4A1, Settings::Skinchanger::Skin(512, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_M4A1_SILENCER, Settings::Skinchanger::Skin(548, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_DEAGLE, Settings::Skinchanger::Skin(277, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_GLOCK, Settings::Skinchanger::Skin(38, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_USP_SILENCER, Settings::Skinchanger::Skin(332, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_FIVESEVEN, Settings::Skinchanger::Skin(252, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_SCAR20, Settings::Skinchanger::Skin(391, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_ELITE, Settings::Skinchanger::Skin(249, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_SSG08, Settings::Skinchanger::Skin(319, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_TEC9, Settings::Skinchanger::Skin(179, -1, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_M9_BAYONET, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE_T, Settings::Skinchanger::Skin(417, WEAPON_KNIFE_KARAMBIT, 0, 0.0005f, 1337, "AimTux", "") },
		{ WEAPON_KNIFE_GUT, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_gut.mdl") },
		{ WEAPON_KNIFE_FLIP, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_flip.mdl") },
		{ WEAPON_KNIFE_BAYONET, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_bayonet.mdl") },
		{ WEAPON_KNIFE_M9_BAYONET, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_m9_bay.mdl") },
		{ WEAPON_KNIFE_KARAMBIT, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_karam.mdl") },
		{ WEAPON_KNIFE_TACTICAL, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_tactical.mdl") },
		{ WEAPON_KNIFE_BUTTERFLY, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_butterfly.mdl") },
		{ WEAPON_KNIFE_SURVIVAL_BOWIE, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_survival_bowie.mdl") },
		{ WEAPON_KNIFE_FALCHION, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_falchion_advanced.mdl") },
		{ WEAPON_KNIFE_PUSH, Settings::Skinchanger::Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_push.mdl") }
};

bool SkinChanger::ForceFullUpdate = true;

const char* KnifeToName(int id)
{
	Settings::Skinchanger::Skin skin = Settings::Skinchanger::skins[id];

	switch (skin.ItemDefinitionIndex)
	{
		case WEAPON_KNIFE_BAYONET:
			return "bayonet";
		case WEAPON_KNIFE_FLIP:
			return "knife_flip";
		case WEAPON_KNIFE_GUT:
			return "knife_gut";
		case WEAPON_KNIFE_KARAMBIT:
			return "knife_karambit";
		case WEAPON_KNIFE_M9_BAYONET:
			return "knife_m9_bayonet";
		case WEAPON_KNIFE_TACTICAL:
			return "knife_tactical";
		case WEAPON_KNIFE_FALCHION:
			return "knife_falchion";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "knife_survival_bowie";
		case WEAPON_KNIFE_BUTTERFLY:
			return "knife_butterfly";
		case WEAPON_KNIFE_PUSH:
			return "knife_push";
		default:
			return NULL;
	}
}

void SkinChanger::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::Skinchanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	/* get our player entity */
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
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

		C_BaseAttributableItem* weapon = (C_BaseAttributableItem*)entitylist->GetClientEntity(weapons[i] & 0xFFF);

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

		if (currentSkin.Seed != -1)
			*weapon->GetFallbackSeed() = currentSkin.Seed;

		if (currentSkin.Wear != -1)
			*weapon->GetFallbackWear() = currentSkin.Wear;

		if (currentSkin.StatTrak != -1)
		{
			*weapon->GetFallbackStatTrak() = currentSkin.StatTrak;

			IEngineClient::player_info_t localplayer_info;

			if (engine->GetPlayerInfo(engine->GetLocalPlayer(), &localplayer_info))
				*weapon->GetAccountID() = localplayer_info.xuidlow;
		}

		if (currentSkin.CustomName != "")
			snprintf(weapon->GetCustomName(), 32, "%s", currentSkin.CustomName.c_str());

		/* force our fallback values to be used */
		*weapon->GetItemIDHigh() = -1;
	}

	/* viewmodel replacements */
	C_BaseViewModel* viewmodel = (C_BaseViewModel*)entitylist->GetClientEntityFromHandle(localplayer->GetViewModel());
	if (!viewmodel)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	auto keyExists = Settings::Skinchanger::skins.find(*active_weapon->GetItemDefinitionIndex());
	if (keyExists == Settings::Skinchanger::skins.end())
		return;

	Settings::Skinchanger::Skin currentSkin = Settings::Skinchanger::skins[*active_weapon->GetItemDefinitionIndex()];

	if (currentSkin.Model != "")
		*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(currentSkin.Model.c_str());

	if (SkinChanger::ForceFullUpdate)
	{
		cvar->FindVar("cl_fullupdate")->nFlags &= ~FCVAR_CHEAT;
		engine->ExecuteClientCmd("cl_fullupdate");
		cvar->FindVar("cl_fullupdate")->nFlags |= FCVAR_CHEAT;

		SkinChanger::ForceFullUpdate = false;
	}
}

void SkinChanger::FireEventClientSide(IGameEvent* event)
{
	if (!Settings::Skinchanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (!event || strcmp(event->GetName(), "player_death") != 0)
		return;

	if (!event->GetInt("attacker") || engine->GetPlayerForUserID(event->GetInt("attacker")) != engine->GetLocalPlayer())
		return;

	const char* weapon = event->GetString("weapon");
	if (strcmp(weapon, "knife_default_ct") == 0) {
		const char* name = KnifeToName(WEAPON_KNIFE);
		event->SetString("weapon", name ?: weapon);
	} else if (strcmp(weapon, "knife_t") == 0) {
		const char* name = KnifeToName(WEAPON_KNIFE_T);
		event->SetString("weapon", name ?: weapon);
	}
}