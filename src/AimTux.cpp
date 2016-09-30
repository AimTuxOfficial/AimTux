#include <iostream>
#include <memory.h>
#include <chrono>

#include "interfaces.h"
#include "draw.h"
#include "hooker.h"
#include "settings.h"
#include "aimbot.h"
#include "esp.h"
#include "bhop.h"
#include "spammer.h"
#include "autostrafe.h"
#include "NetVarManager.h"
#include "antiaim.h"
#include "triggerbot.h"

#define CONV(c) cwConvert(c)

FONT title_font = 0;
FONT normal_font = 0;
FONT esp_font = 0;

std::unordered_map<int, std::tuple<int, int, float, int, const char*, const char *>> skinChangerSettings;

void DrawHackInfo ();

static wchar_t* cwConvert(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
}


void SetupFonts ()
{
	title_font		= Draw::CreateFont ("Arial", 20, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	normal_font		= Draw::CreateFont ("Arial", 17, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	esp_font		= Draw::CreateFont ("TeX Gyre Adventor", 17, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
}

bool hkCreateMove (void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientMode_vmt->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);
	
	// This code should be moved into a tick hook of some sorts...
	Spammer::Tick ();
	
	
	if (cmd && cmd->command_number)
	{
		BHop::CreateMove (cmd);
		AutoStrafe::CreateMove (cmd);
		Aimbot::CreateMove (cmd);
		Triggerbot::CreateMove (cmd);
		AntiAim::CreateMove (cmd);
	}
	
	return false;
}


void hkPaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	if (strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel"))
		return;

	DrawHackInfo ();
	ESP::Tick ();
}

void DrawHackInfo ()
{
	int width = 350;
	
	Draw::DrawRect (LOC(15, 15), LOC (width, 190), Color(0, 0, 0, 120));
	Draw::DrawBox (LOC(15, 15), LOC (width, 190), Color(190, 190, 190, 120));
	Draw::DrawString (L"AimTux", LOC(width / 2, 20), Color(190, 190, 190), title_font, true);
	Draw::DrawString (L"Test normal font", LOC(20, 50), Color(190, 190, 190), normal_font, false);
}

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
	
	return client_vmt->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);
}

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Hooker::HookInterfaces ();
	Hooker::HookVMethods ();
	
	PRINT ("AimTux was successfully injected.");
	
	client_vmt->HookVM ((void*)hkFrameStageNotify, 36);
	client_vmt->ApplyVMT ();
	
	panel_vmt->HookVM ((void*)hkPaintTraverse, 42);
	panel_vmt->ApplyVMT ();
	
	Hooker::HookIClientMode ();
	
	clientMode_vmt->HookVM ((void*)hkCreateMove, 25);
	clientMode_vmt->ApplyVMT ();
	
	SetupFonts ();
	
	NetVarManager::dumpNetvars ();
	Offsets::getOffsets ();
	
	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	client_vmt->ReleaseVMT ();
	panel_vmt->ReleaseVMT ();
	clientMode_vmt->ReleaseVMT ();
	
	PRINT ("AimTux has been unloaded successfully.");
}
