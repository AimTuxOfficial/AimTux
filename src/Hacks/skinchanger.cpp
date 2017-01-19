#include "skinchanger.h"

bool Settings::Skinchanger::enabled = false;
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

const char* GetModelByItemIndex(int id)
{
	switch (id)
	{
		case WEAPON_KNIFE_GUT:
			return "models/weapons/v_knife_gut.mdl";
		case WEAPON_KNIFE_FLIP:
			return "models/weapons/v_knife_flip.mdl";
		case WEAPON_KNIFE_BAYONET:
			return "models/weapons/v_knife_bayonet.mdl";
		case WEAPON_KNIFE_M9_BAYONET:
			return "models/weapons/v_knife_m9_bay.mdl";
		case WEAPON_KNIFE_KARAMBIT:
			return "models/weapons/v_knife_karam.mdl";
		case WEAPON_KNIFE_TACTICAL:
			return "models/weapons/v_knife_tactical.mdl";
		case WEAPON_KNIFE_BUTTERFLY:
			return "models/weapons/v_knife_butterfly.mdl";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "models/weapons/v_knife_survival_bowie.mdl";
		case WEAPON_KNIFE_FALCHION:
			return "models/weapons/v_knife_falchion_advanced.mdl";
		case WEAPON_KNIFE_PUSH:
			return "models/weapons/v_knife_push.mdl";
		default:
			return NULL;
	}
}

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
	if (Settings::Skinchanger::enabled)
	{
		if (!engine->IsInGame())
			return;

		if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		/* get our player entity */
		C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
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

			C_BaseAttributableItem* weapon = (C_BaseAttributableItem*) entitylist->GetClientEntity(weapons[i] & 0xFFF);

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

			if (const char* modelFilename = GetModelByItemIndex(*weapon->GetItemDefinitionIndex()))
				*weapon->GetModelIndex() = modelInfo->GetModelIndex(modelFilename);

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
		C_BaseViewModel* viewmodel = (C_BaseViewModel*) entitylist->GetClientEntityFromHandle(localplayer->GetViewModel());
		if (!viewmodel)
			return;

		C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
		if (!active_weapon)
			return;

		auto keyExists = Settings::Skinchanger::skins.find(*active_weapon->GetItemDefinitionIndex());
		if (keyExists == Settings::Skinchanger::skins.end())
			return;

		Settings::Skinchanger::Skin currentSkin = Settings::Skinchanger::skins[*active_weapon->GetItemDefinitionIndex()];

		if (currentSkin.Model != "")
			*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(currentSkin.Model.c_str());
	}

	if (SkinChanger::ForceFullUpdate)
	{
		::ForceFullUpdate(GetClientState());
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
	if (strcmp(weapon, "knife_default_ct") == 0)
	{
		const char* name = KnifeToName(WEAPON_KNIFE);
		event->SetString("weapon", name ?: weapon);
	}
	else if (strcmp(weapon, "knife_t") == 0)
	{
		const char* name = KnifeToName(WEAPON_KNIFE_T);
		event->SetString("weapon", name ?: weapon);
	}
}

void SkinChanger::SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	// Make the incoming data editable.
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	// Confirm that we are replacing our view model and not someone elses.
	C_BaseViewModel* pViewModel = (C_BaseViewModel*) pStruct;

	if (pViewModel)
	{
		IClientEntity* pOwner = (IClientEntity*) entitylist->GetClientEntity(pViewModel->GetOwner() & 0xFFF);

		// Compare the owner entity of this view model to the local player entity.
		if (pOwner && pOwner->GetIndex() == engine->GetLocalPlayer())
		{
			// Get the filename of the current view model.
			model_t* pModel = modelInfo->GetModel(*pViewModel->GetModelIndex());
			std::string szModel = modelInfo->GetModelName(pModel);

			// Store the current sequence.
			int m_nSequence = pData->m_Value.m_Int;
			if (szModel == "models/weapons/v_knife_butterfly.mdl")
			{
				// Fix animations for the Butterfly Knife.
				switch (m_nSequence)
				{
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
						break;
					default:
						m_nSequence++;
				}
			}
			else if (szModel == "models/weapons/v_knife_falchion_advanced.mdl")
			{
				// Fix animations for the Falchion Knife.
				switch (m_nSequence)
				{
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
						break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence--;
				}
			}
			else if (szModel == "models/weapons/v_knife_push.mdl")
			{
				// Fix animations for the Shadow Daggers.
				switch (m_nSequence)
				{
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
						m_nSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
						break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
						break;
					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence += 3; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence += 2;
				}
			}
			else if (szModel == "models/weapons/v_knife_survival_bowie.mdl")
			{
				// Fix animations for the Bowie Knife.
				switch (m_nSequence)
				{
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_BOWIE_IDLE1;
						break;
					default:
						m_nSequence--;
				}
			}

			// Set the fixed sequence.
			pData->m_Value.m_Int = m_nSequence;
		}
	}

	// Call original function with the modified data.
	fnSequenceProxyFn(pData, pStruct, pOut);
}

void SkinChanger::HookCBaseViewModel()
{
	for (ClientClass* pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		if (strcmp(pClass->m_pNetworkName, "CBaseViewModel") == 0)
		{
			// Search for the 'm_nModelIndex' property.
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, "m_nSequence") != 0)
					continue;

				// Store the original proxy function.
				fnSequenceProxyFn = pProp->m_ProxyFn;

				// Replace the proxy function with our sequence changer.
				pProp->m_ProxyFn = (RecvVarProxyFn)SetViewModelSequence;

				break;
			}

			break;
		}
	}
}

void SkinChanger::UnhookCBaseViewModel()
{
	for (ClientClass* pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		if (strcmp(pClass->m_pNetworkName, "CBaseViewModel") == 0)
		{
			// Search for the 'm_nModelIndex' property.
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, "m_nSequence") != 0)
					continue;

				pProp->m_ProxyFn = fnSequenceProxyFn;

				break;
			}

			break;
		}
	}
}
