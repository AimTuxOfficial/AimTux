#include "skinchanger.h"

static std::unordered_map<int, std::tuple<int, int, float, int, const char*, const char *>> skinChangerSettings;

void SkinChanger::FrameStageNotify(ClientFrameStage_t stage)
{
	/* perform replacements during postdataupdate */
	while (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		/* get our player entity */
		C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

		if (!localplayer || localplayer->GetLifeState() != LIFE_ALIVE)
			break;

		/* get a list of weapon we're holding */
		int* weapons = localplayer->GetWeapons();

		if (!weapons)
			break;

		if (skinChangerSettings.empty())
			skinChangerSettings = Settings::SkinChanger::getSettings();

		for (int i = 0; i < 64; i++)
		{
			/* check if the handle is invalid */
			if (weapons[i] == -1)
				continue;

			C_BaseAttributableItem* weapon = reinterpret_cast<C_BaseAttributableItem*>(entitylist->GetClientEntity(weapons[i] & 0xFFF));

			/* check if the weapon pointer is invalid */
			if (!weapon)
				continue;

			std::tuple<int, int, float, int, const char*, const char *> settings = skinChangerSettings[*weapon->GetItemDefinitionIndex()];

			if (std::get<0>(settings) != 0)
				*weapon->GetFallbackPaintKit() = std::get<0>(settings);

			if (std::get<1>(settings) != 0)
				*weapon->GetItemDefinitionIndex() = std::get<1>(settings);

			if (std::get<2>(settings) != 0)
				*weapon->GetFallbackWear() = std::get<2>(settings);

			if (std::get<3>(settings) != 0)
				*weapon->GetFallbackStatTrak() = std::get<3>(settings);

			if (std::get<4>(settings) != NULL && strlen(std::get<4>(settings)) > 0)
				snprintf(weapon->GetCustomName(), 32, "%s", std::get<4>(settings));

			/* force our fallback values to be used */
			*weapon->GetItemIDHigh() = -1;
		}

		/* viewmodel replacements */
		C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntity(localplayer->GetViewModel() & 0xFFF));

		if (!viewmodel)
			break;

		C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntity(viewmodel->GetWeapon() & 0xFFF));

		if (!active_weapon)
			break;

		std::tuple<int, int, float, int, const char*, const char *> settings = skinChangerSettings[*active_weapon->GetItemDefinitionIndex()];

		if (std::get<5>(settings) != NULL && strlen(std::get<5>(settings)) > 0)
			*viewmodel->GetModelIndex() = modelInfo->GetModelIndex(std::get<5>(settings));

		break;
	}
}