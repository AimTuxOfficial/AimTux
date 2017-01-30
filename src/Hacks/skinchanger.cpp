#include "skinchanger.h"

bool Settings::Skinchanger::enabled = false;
bool Settings::Skinchanger::Gloves::enabled = false;
std::unordered_map<ItemDefinitionIndex, Settings::Skinchanger::Skin> Settings::Skinchanger::skins = {
		{ ItemDefinitionIndex::WEAPON_AWP, Settings::Skinchanger::Skin(344, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_AK47, Settings::Skinchanger::Skin(524, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_M4A1, Settings::Skinchanger::Skin(512, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_M4A1_SILENCER, Settings::Skinchanger::Skin(548, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_DEAGLE, Settings::Skinchanger::Skin(277, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_GLOCK, Settings::Skinchanger::Skin(38, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_USP_SILENCER, Settings::Skinchanger::Skin(332, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_FIVESEVEN, Settings::Skinchanger::Skin(252, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_SCAR20, Settings::Skinchanger::Skin(391, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_ELITE, Settings::Skinchanger::Skin(249, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_SSG08, Settings::Skinchanger::Skin(319, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_TEC9, Settings::Skinchanger::Skin(179, ItemDefinitionIndex::INVALID, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_KNIFE, Settings::Skinchanger::Skin(417, ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_T, Settings::Skinchanger::Skin(417, ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT, 0, 0.0005f, 1337, "AimTux", "") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_GUT, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_gut.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_FLIP, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_flip.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_BAYONET, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_bayonet.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_m9_bay.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_karam.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_tactical.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_butterfly.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_survival_bowie.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_falchion_advanced.mdl") },
		{ ItemDefinitionIndex::WEAPON_KNIFE_PUSH, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_knife_push.mdl") },
		{ ItemDefinitionIndex::GLOVE_T_SIDE, Settings::Skinchanger::Skin(10007, ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND, -1, 0.0005f, -1, "", "")},
		{ ItemDefinitionIndex::GLOVE_CT_SIDE, Settings::Skinchanger::Skin(10007, ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND, -1, 0.0005f, -1, "", "")},
		{ ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl")},
		{ ItemDefinitionIndex::GLOVE_SPORTY, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl")},
		{ ItemDefinitionIndex::GLOVE_SLICK, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl")},
		{ ItemDefinitionIndex::GLOVE_LEATHER_WRAP, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl")},
		{ ItemDefinitionIndex::GLOVE_MOTORCYCLE, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl")},
		{ ItemDefinitionIndex::GLOVE_SPECIALIST, Settings::Skinchanger::Skin(-1, ItemDefinitionIndex::INVALID, -1, -1, -1, "", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl")},
};

bool SkinChanger::ForceFullUpdate = true;

const char* GetModelByItemIndex(ItemDefinitionIndex id)
{
	switch (id)
	{
		case ItemDefinitionIndex::WEAPON_KNIFE_GUT:
			return "models/weapons/v_knife_gut.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
			return "models/weapons/v_knife_flip.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
			return "models/weapons/v_knife_bayonet.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
			return "models/weapons/v_knife_m9_bay.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
			return "models/weapons/v_knife_karam.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
			return "models/weapons/v_knife_tactical.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
			return "models/weapons/v_knife_butterfly.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "models/weapons/v_knife_survival_bowie.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
			return "models/weapons/v_knife_falchion_advanced.mdl";
		case ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
			return "models/weapons/v_knife_push.mdl";
		case ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND:
			return "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
		case ItemDefinitionIndex::GLOVE_SPORTY:
			return "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
		case ItemDefinitionIndex::GLOVE_SLICK:
			return "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
		case ItemDefinitionIndex::GLOVE_LEATHER_WRAP:
			return "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
		case ItemDefinitionIndex::GLOVE_MOTORCYCLE:
			return "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
		case ItemDefinitionIndex::GLOVE_SPECIALIST:
			return "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
		default:
			return NULL;
	}
}

const char* KnifeToName(ItemDefinitionIndex id)
{
	Settings::Skinchanger::Skin skin = Settings::Skinchanger::skins[id];

	switch (skin._ItemDefinitionIndex)
	{
		case ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
			return "bayonet";
		case ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
			return "knife_flip";
		case ItemDefinitionIndex::WEAPON_KNIFE_GUT:
			return "knife_gut";
		case ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
			return "knife_karambit";
		case ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
			return "knife_m9_bayonet";
		case ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
			return "knife_tactical";
		case ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
			return "knife_falchion";
		case ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "knife_survival_bowie";
		case ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
			return "knife_butterfly";
		case ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
			return "knife_push";
		default:
			return NULL;
	}
}

void SkinChanger::FrameStageNotify(ClientFrameStage_t stage)
{
	if (Settings::Skinchanger::enabled && ModSupport::current_mod != ModType::CSCO)
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

			if (currentSkin._ItemDefinitionIndex != ItemDefinitionIndex::INVALID)
				*weapon->GetItemDefinitionIndex() = currentSkin._ItemDefinitionIndex;

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

	if (Settings::Skinchanger::Gloves::enabled && ModSupport::current_mod != ModType::CSCO)
	{
		if (!engine->IsInGame())
			return;

		if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		/* get our player entity */
		C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		if(!localplayer->GetAlive())
		{
			C_BaseAttributableItem* glove = (C_BaseAttributableItem*) entitylist->GetClientEntity(localplayer->GetWearables()[0] & 0xFFF);
			if (!glove)
				return;

			glove->GetNetworkable()->SetDestroyedOnRecreateEntities();
			glove->GetNetworkable()->Release();
		}
		else
		{
			if (!entitylist->GetClientEntityFromHandle((void*) localplayer->GetWearables()))
			{
				for (ClientClass* pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
				{
					if (pClass->m_ClassID != EClassIds::CEconWearable)
						continue;

					// Gets last entityindex entry and just add 1 | Random Serial.
					int iEntry = (entitylist->GetHighestEntityIndex() + 1), iSerial = RandomInt(0x0, 0xFFF);

					// Create the entity, adds it to the enum of Entities.
					pClass->m_pCreateFn(iEntry, iSerial);

					// Assign Wearable[0] (gloves) with the entry value and serial.
					localplayer->GetWearables()[0] = iEntry | (iSerial << 16);

					break;
				}
			}

			C_BaseAttributableItem* glove = (C_BaseAttributableItem*) entitylist->GetClientEntity(localplayer->GetWearables()[0] & 0xFFF);
			if (!glove)
				return;

			IEngineClient::player_info_t localplayer_info;
			engine->GetPlayerInfo(engine->GetLocalPlayer(), &localplayer_info);

			// Have to use  this because there is no preset ItemDefinitionIndex
			Settings::Skinchanger::Skin currentSkin = Settings::Skinchanger::skins[ItemDefinitionIndex::GLOVE_CT_SIDE];

			if (*glove->GetFallbackPaintKit() != currentSkin.PaintKit &&
					*glove->GetItemDefinitionIndex() != currentSkin._ItemDefinitionIndex &&
					*glove->GetFallbackWear() != currentSkin.Wear)
			{

				if (currentSkin.PaintKit != -1)
					*glove->GetFallbackPaintKit() = currentSkin.PaintKit;

				if (currentSkin._ItemDefinitionIndex != ItemDefinitionIndex::INVALID)
					*glove->GetItemDefinitionIndex() = currentSkin._ItemDefinitionIndex;

				if (currentSkin.Wear != -1)
					*glove->GetFallbackWear() = currentSkin.Wear;

				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetEntityQuality() = 4;
				*glove->GetItemIDHigh() = -1;
				*glove->GetAccountID() = localplayer_info.xuidlow;

				glove->SetModelIndex(modelInfo->GetModelIndex(GetModelByItemIndex(*glove->GetItemDefinitionIndex())));
				glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
	}

	if (SkinChanger::ForceFullUpdate)
	{
		::ForceFullUpdate(GetClientState());
		SkinChanger::ForceFullUpdate = false;
	}
}

void SkinChanger::FireEventClientSide(IGameEvent* event)
{
	if (!Settings::Skinchanger::enabled || ModSupport::current_mod == ModType::CSCO)
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
		const char* name = KnifeToName(ItemDefinitionIndex::WEAPON_KNIFE);
		event->SetString("weapon", name ?: weapon);
	}
	else if (strcmp(weapon, "knife_t") == 0)
	{
		const char* name = KnifeToName(ItemDefinitionIndex::WEAPON_KNIFE_T);
		event->SetString("weapon", name ?: weapon);
	}
}

void SkinChanger::SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	if (ModSupport::current_mod == ModType::CSCO)
		return;

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
	if (ModSupport::current_mod == ModType::CSCO)
		return;

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
	if (ModSupport::current_mod == ModType::CSCO)
		return;

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
