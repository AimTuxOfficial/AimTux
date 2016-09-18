#include <iostream>
#include <memory.h>

#include "SDK.h"
#include "Weapons.h"

HLClient* client;
ISurface* surface;	//VGUI
IPanel* panel;		//VGUI2
CEngineClient* engine;
IClientEntityList* entitylist;

/* CHLClient virtual table pointers */
uintptr_t** client_vmt = nullptr;
uintptr_t* original_client_vmt = nullptr;

typedef void(*oPaintTraverse)(void*,unsigned long long, bool, bool);
void PaintTraverseHook(void* v1, unsigned long long vguiPanel, bool forceRepaint, bool allowForce)
{
}

/* original FrameStageNotify function */
FrameStageNotifyFn oFrameStageNotify = 0;

/* replacement FrameStageNotify function */
void hkFrameStageNotify(void* thisptr, ClientFrameStage_t stage) {
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

		for (int i = 0; i < 64; i++) {
			/* check if the handle is invalid */
			if (weapons[i] == -1)
				continue;

			C_BaseAttributableItem* weapon = reinterpret_cast<C_BaseAttributableItem*>(entitylist->GetClientEntity(weapons[i] & 0xFFF));

			/* check if the weapon pointer is invalid */
			if (!weapon)
				continue;

			switch (*weapon->GetItemDefinitionIndex()) {
				/* AWP | Dragon Lore */
				case WEAPON_AWP:
					*weapon->GetFallbackPaintKit() = 344; break;

				/* AK-47 | Fuel Injector */
				case WEAPON_AK47:
					*weapon->GetFallbackPaintKit() = 524; break;

				case WEAPON_M4A1:
					*weapon->GetFallbackPaintKit() = 512; break;
				
				//	548
				case WEAPON_M4A1_SILENCER:
					*weapon->GetFallbackPaintKit() = 548; break;
				
				/* Desert Eagle | Conspiracy */
				case WEAPON_DEAGLE:
					*weapon->GetFallbackPaintKit() = 277; break;

				/* Glock-18 | Fade */
				case WEAPON_GLOCK:
					*weapon->GetFallbackPaintKit() = 38; break;

				/* USP-S | Stainless */
				case WEAPON_USP_SILENCER:
					*weapon->GetFallbackPaintKit() = 332; break;
				
				case WEAPON_FIVESEVEN:
					*weapon->GetFallbackPaintKit() = 252; break;
				
				//Cardiac
				case WEAPON_SCAR20:
					*weapon->GetFallbackPaintKit() = 391; break;
				
				case WEAPON_ELITE:
					*weapon->GetFallbackPaintKit() = 249; break;
					
				//Detour
				case WEAPON_SSG08:
					*weapon->GetFallbackPaintKit() = 319; break;
				
				case WEAPON_TEC9:
					*weapon->GetFallbackPaintKit() = 179; break;
			}

			/* write to weapon name tag */
			snprintf(weapon->GetCustomName(), 32, "%s", "AimTux");
			
			/* remove all wear */
			*weapon->GetFallbackWear() = 0.00000000f;
			*weapon->GetFallbackStatTrak() = 1337;
			
			/* force our fallback values to be used */
			*weapon->GetItemIDHigh() = -1;
		}

		break;
	}

	/* call original function after we've made our changes */
	return oFrameStageNotify(thisptr, stage);
}

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init() {
	/* obtain pointers to game interface classes */
	client = GetInterface<HLClient>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
	engine = GetInterface<CEngineClient>("./bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);
	surface = GetInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", SURFACE_INTERFACE_VERSION);
	panel = GetInterface<IPanel>("./bin/linux64/vgui2_client.so", PANEL_INTERFACE_VERSION);
		
	/* get CHLClient virtual function table */
	client_vmt = reinterpret_cast<uintptr_t**>(client);

	/* create backup of the original table */
	original_client_vmt = *client_vmt;

	size_t total_functions = 0;

	while (reinterpret_cast<uintptr_t*>(*client_vmt)[total_functions])
		total_functions++;

	/* create replacement virtual table */
	uintptr_t* new_client_vmt = new uintptr_t[total_functions];

	/* copy original table contents into new table */
	memcpy(new_client_vmt, original_client_vmt, (sizeof(uintptr_t) * total_functions));

	/* store original function in oFrameStageNotify variable */
	oFrameStageNotify = reinterpret_cast<FrameStageNotifyFn>(original_client_vmt[36]);

	/* overwrite the FrameStageNotify function pointer with our hook function */
	new_client_vmt[36] = reinterpret_cast<uintptr_t>(hkFrameStageNotify);

	/* write the new virtual table */
	*client_vmt = new_client_vmt;

	return 0;
}

void __attribute__((destructor)) aimtux_shutdown() {
	/* restore CHLClient virtual table to normal */
	*client_vmt = original_client_vmt;
}