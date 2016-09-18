#include <iostream>
#include <memory.h>

#include "SDK.h"
#include "Weapons.h"

HLClient* client;
ISurface* surface;	//VGUI
IPanel* panel;		//VGUI2
CEngineClient* engine;
IClientEntityList* entitylist;
CDraw g_Draw;

/* CHLClient virtual table pointers */
uintptr_t** client_vmt = nullptr;
uintptr_t** panel_vmt = nullptr;
uintptr_t* original_client_vmt = nullptr;
uintptr_t* original_panel_vmt = nullptr;

unsigned long long font;

PaintTraverseFn oPaintTraverse = 0;

void hkPaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	oPaintTraverse (thisptr, vgui_panel, force_repaint, allow_force);
	
	if (strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel")) // 37
		return;
 
	surface->DrawSetTextColor(150, 255, 150, 255); // 25
	surface->DrawSetTextFont(font); // 23
	surface->DrawSetTextPos(15, 15); // 26
	surface->DrawPrintText(L"Hello world!", 12); // 28
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
int __attribute__((constructor)) aimtux_init()
{
	/* obtain pointers to game interface classes */
	client = GetInterface<HLClient>("./csgo/bin/linux64/client_client.so", CLIENT_DLL_INTERFACE_VERSION);
	engine = GetInterface<CEngineClient>("./bin/linux64/engine_client.so", VENGINE_CLIENT_INTERFACE_VERSION);
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", VCLIENTENTITYLIST_INTERFACE_VERSION);
	surface = GetInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", SURFACE_INTERFACE_VERSION);
	panel = GetInterface<IPanel>("./bin/linux64/vgui2_client.so", PANEL_INTERFACE_VERSION);
	
	
	/*--------------------------
	
	CLIENT VMT
	
	-------------------------*/
	
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
	new_client_vmt[36] = reinterpret_cast<uintptr_t>(hkPaintTraverse);
	
	/* write the new virtual table */
	*client_vmt = new_client_vmt;
	
	
	font = surface->CreateFont ();
	surface->SetFontGlyphSet (font, "Tahoma", 32, 0, 0, 0, true);
	
	
	/*--------------------------
	
	PANEL VMT
	
	-------------------------*/
	
	panel_vmt = reinterpret_cast<uintptr_t**>(panel);
	
	original_panel_vmt = *panel_vmt;
	
	total_functions = 0;
	
	while (reinterpret_cast<uintptr_t*>(*panel_vmt)[total_functions])
		total_functions++;
		
	uintptr_t* new_panel_vmt = new uintptr_t[total_functions];
	
	memcpy(new_panel_vmt, original_panel_vmt, (sizeof(uintptr_t) * total_functions));
	
	oPaintTraverse = reinterpret_cast<PaintTraverseFn>(original_panel_vmt[42]);
	new_panel_vmt[42] = reinterpret_cast<uintptr_t>(hkPaintTraverse);
	
	*panel_vmt = new_panel_vmt;
	
	
	engine->SendClientCommand ("say AimTux");
	
	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	/* restore CHLClient virtual table to normal */
	*client_vmt = original_client_vmt;
}