#include "skinchanger.h"

bool Settings::Skinchanger::enabled = false;
bool Settings::Skinchanger::Gloves::enabled = false;

std::unordered_map<ItemDefinitionIndex, AttribItem_t> Settings::Skinchanger::skins = {
		{ ItemDefinitionIndex::WEAPON_AK47 /*WeaponID*/, { ItemDefinitionIndex::INVALID /*itemDefinitionIndex*/, 524 /*fallbackPaintKit*/, 0.0005f /*fallbackWear*/, -1 /*fallbackSeed*/, 1337/*fallbackStatTrak*/, -1/*fallbackEntityQuality*/, "TestTux"/*customName*/ } },
		{ ItemDefinitionIndex::WEAPON_G3SG1, { ItemDefinitionIndex::INVALID, 344, 0.0005f, -1, 1337, -1, "AimTux Best Tux" } },
		{ ItemDefinitionIndex::WEAPON_GLOCK, { ItemDefinitionIndex::INVALID, 524, 0.0005f, -1, 1337, -1, "AimTux Best Tux" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE, { ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, 417, 0.0005f, -1, 1337, -1, "AimTux Best Tux" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_T, { ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, 417, 0.0005f, -1, 1337, -1, "AimTux Best Tux" } },
		{ ItemDefinitionIndex::GLOVE_T_SIDE, { ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND, 10006, 0.0005f, -1, -1, -1, "" } },
};

std::unordered_map<std::string, std::string> killIcons = {};

std::unique_ptr<RecvPropHook> SkinChanger::sequenceHook;

bool SkinChanger::forceFullUpdate = true;

void SkinChanger::FrameStageNotifyWeapons(ClientFrameStage_t stage)
{
	if (Settings::Skinchanger::enabled && ModSupport::current_mod != ModType::CSCO)
	{
		if (!engine->IsInGame())
			return;

		if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer || !localplayer->GetAlive())
			return;

		IEngineClient::player_info_t localplayer_info;
		if (!engine->GetPlayerInfo(engine->GetLocalPlayer(), &localplayer_info))
			return;

		for (size_t i = 0; localplayer->GetWeapons()[i] != (int) 0xFFFFFFFF; i++)
		{
			if (localplayer->GetWeapons()[i] == -1)
				continue;

			C_BaseAttributableItem* weapon = (C_BaseAttributableItem* ) entityList->GetClientEntity(localplayer->GetWeapons()[i] & 0xFFF);

			if (!weapon)
				continue;

			auto keyExists = Settings::Skinchanger::skins.find(*weapon->GetItemDefinitionIndex());
			if (keyExists == Settings::Skinchanger::skins.end())
				continue;

			const AttribItem_t &currentSkin = Settings::Skinchanger::skins.at(*weapon->GetItemDefinitionIndex());

			if (currentSkin.itemDefinitionIndex != ItemDefinitionIndex::INVALID && ItemDefinitionIndexMap.find(currentSkin.itemDefinitionIndex) != ItemDefinitionIndexMap.end())
			{
				*weapon->GetModelIndex() = modelInfo->GetModelIndex(ItemDefinitionIndexMap.at(currentSkin.itemDefinitionIndex).entityModel);
				if (ItemDefinitionIndexMap.find(*weapon->GetItemDefinitionIndex()) != ItemDefinitionIndexMap.end())
				{
					killIcons[ItemDefinitionIndexMap.at(*weapon->GetItemDefinitionIndex()).killIcon] = ItemDefinitionIndexMap.at(currentSkin.itemDefinitionIndex).killIcon;
					*weapon->GetItemDefinitionIndex() = currentSkin.itemDefinitionIndex;
				}
			}

			if (currentSkin.fallbackPaintKit != -1)
				*weapon->GetFallbackPaintKit() = currentSkin.fallbackPaintKit;

			if (currentSkin.fallbackSeed != -1)
				*weapon->GetFallbackSeed() = currentSkin.fallbackSeed;

			if (currentSkin.fallbackWear != -1)
				*weapon->GetFallbackWear() = currentSkin.fallbackWear;

			if (currentSkin.fallbackStatTrak != -1)
				*weapon->GetFallbackStatTrak() = currentSkin.fallbackStatTrak;

			if (currentSkin.entityQuality != -1)
				*weapon->GetEntityQuality() = currentSkin.entityQuality;

			if (currentSkin.customName != "")
				snprintf(weapon->GetCustomName(), 32, "%s", currentSkin.customName.c_str());

			*weapon->GetItemIDHigh() = -1;
			*weapon->GetAccountID() = localplayer_info.xuidlow;
		}

		C_BaseViewModel *viewmodel = (C_BaseViewModel *) entityList->GetClientEntityFromHandle(localplayer->GetViewModel());
		if (!viewmodel)
			return;

		C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon *) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
		if (!activeWeapon)
			return;

		if (ItemDefinitionIndexMap.find(*activeWeapon->GetItemDefinitionIndex()) != ItemDefinitionIndexMap.end())
		{
			const DefItem_t &override_weapon = ItemDefinitionIndexMap.at(*activeWeapon->GetItemDefinitionIndex());
			*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(override_weapon.entityModel);
		}
	}
}

void SkinChanger::FrameStageNotifyGloves(ClientFrameStage_t stage)
{
	if (Settings::Skinchanger::Gloves::enabled && ModSupport::current_mod != ModType::CSCO) {

		if (!engine->IsInGame())
			return;

		if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		IEngineClient::player_info_t localplayer_info;
		if (!engine->GetPlayerInfo(engine->GetLocalPlayer(), &localplayer_info))
			return;

		if (!localplayer->GetAlive())
		{
			C_BaseAttributableItem* glove = (C_BaseAttributableItem* ) entityList->GetClientEntity(localplayer->GetWearables()[0] & 0xFFF);
			if (!glove)
				return;

			glove->GetNetworkable()->SetDestroyedOnRecreateEntities();
			glove->GetNetworkable()->Release();
		}
		else
		{
			if (!entityList->GetClientEntityFromHandle((void *) localplayer->GetWearables()))
			{
				for (ClientClass *pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
				{
					if (pClass->m_ClassID != EClassIds::CEconWearable)
						continue;

					int entry = (entityList->GetHighestEntityIndex() + 1), serial = RandomInt(0x0, 0xFFF);

					pClass->m_pCreateFn(entry, serial);

					localplayer->GetWearables()[0] = entry | (serial << 16);

					break;
				}
			}

			C_BaseAttributableItem* glove = (C_BaseAttributableItem* ) entityList->GetClientEntity(localplayer->GetWearables()[0] & 0xFFF);
			if (!glove)
				return;

			if (Settings::Skinchanger::skins.find(ItemDefinitionIndex::GLOVE_T_SIDE) != Settings::Skinchanger::skins.end())
			{
				const AttribItem_t &currentSkin = Settings::Skinchanger::skins.at(ItemDefinitionIndex::GLOVE_T_SIDE);

				if (currentSkin.itemDefinitionIndex != ItemDefinitionIndex::INVALID && ItemDefinitionIndexMap.find(currentSkin.itemDefinitionIndex) != ItemDefinitionIndexMap.end())
				{
					glove->SetModelIndex(modelInfo->GetModelIndex(ItemDefinitionIndexMap.at(currentSkin.itemDefinitionIndex).entityModel));
					if (ItemDefinitionIndexMap.find(ItemDefinitionIndex::GLOVE_T_SIDE) != ItemDefinitionIndexMap.end())
						*glove->GetItemDefinitionIndex() = currentSkin.itemDefinitionIndex;
				}

				if (*glove->GetFallbackPaintKit() != currentSkin.fallbackPaintKit &&
					*glove->GetFallbackWear() != currentSkin.fallbackWear)
				{
					if (currentSkin.fallbackPaintKit != -1)
						*glove->GetFallbackPaintKit() = currentSkin.fallbackPaintKit;

					if (currentSkin.fallbackWear != -1)
						*glove->GetFallbackWear() = currentSkin.fallbackWear;

					*glove->GetFallbackSeed() = 0;
					*glove->GetFallbackStatTrak() = -1;
					*glove->GetEntityQuality() = 4;
					*glove->GetItemIDHigh() = -1;
					*glove->GetAccountID() = localplayer_info.xuidlow;
					glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
				}
			}
		}
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

	std::string weapon = event->GetString("weapon");

	event->SetString("weapon", killIcons.find(weapon) != killIcons.end() ? killIcons.at(weapon).c_str() : weapon.c_str());
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
		IClientEntity* pOwner = (IClientEntity*) entityList->GetClientEntity(pViewModel->GetOwner() & 0xFFF);

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
	if (!fnSequenceProxyFn)
		fnSequenceProxyFn = sequenceHook->GetOriginalFunction();
	
	fnSequenceProxyFn(pData, pStruct, pOut);
}
