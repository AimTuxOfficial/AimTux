/*

	Chameleon -- basic skin changer for CS:GO on 64-bit Linux.
	Copyright (C) 2016, aixxe. (www.aixxe.net)
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Chameleon. If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <memory.h>

#include "SDK.h"

/* game interface pointers */
CHLClient* clientdll = nullptr;
IVEngineClient* engine = nullptr;
IClientEntityList* entitylist = nullptr;

/* CHLClient virtual table pointers */
uintptr_t** client_vmt = nullptr;
uintptr_t* original_client_vmt = nullptr;

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
				/* AWP | Asiimov */
				case WEAPON_AWP:
					*weapon->GetFallbackPaintKit() = 279; break;

				/* AK-47 | Redline */
				case WEAPON_AK47:
					*weapon->GetFallbackPaintKit() = 282; break;

				/* M4A4 | Howl */
				case WEAPON_M4A1:
					*weapon->GetFallbackPaintKit() = 309; break;

				/* Desert Eagle | Conspiracy */
				case WEAPON_DEAGLE:
					*weapon->GetFallbackPaintKit() = 328; break;

				/* Glock-18 | Fade */
				case WEAPON_GLOCK:
					*weapon->GetFallbackPaintKit() = 38; break;

			}

			/* write to weapon name tag */
			snprintf(weapon->GetCustomName(), 32, "%s", "Skins = Skills");

			/* remove all wear */
			*weapon->GetFallbackWear() = 0.f;

			/* force our fallback values to be used */
			*weapon->GetItemIDHigh() = -1;
		}

		break;
	}

	/* call original function after we've made our changes */
	return oFrameStageNotify(thisptr, stage);
}

/* called when the library is loading */
int __attribute__((constructor)) chameleon_init() {
	/* obtain pointers to game interface classes */
	clientdll = GetInterface<CHLClient>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
	engine = GetInterface<IVEngineClient>("./bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);
	
	/* get CHLClient virtual function table */
	client_vmt = reinterpret_cast<uintptr_t**>(clientdll);

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

void __attribute__((destructor)) chameleon_shutdown() {
	/* restore CHLClient virtual table to normal */
	*client_vmt = original_client_vmt;
}
