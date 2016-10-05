#include <iostream>
#include <memory.h>

#include "interfaces.h"
#include "draw.h"
#include "hooker.h"
#include "aimbot.h"
#include "esp.h"
#include "bhop.h"
#include "spammer.h"
#include "autostrafe.h"
#include "netvarmanager.h"
#include "antiaim.h"
#include "triggerbot.h"
#include "skinchanger.h"

#include "atgui.h"
#include "chams.h"
#include "noflash.h"

FONT title_font = 0;
FONT normal_font = 0;
FONT esp_font = 0;

UI_Container* gui;

void SetupFonts ()
{
	title_font = Draw::CreateFont ("Arial", 20, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	normal_font = Draw::CreateFont ("Arial", 17, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	esp_font = Draw::CreateFont ("UnGraphic, Bold", 20, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
}

static bool IsButtonPressed (ButtonCode_t code)
{
	static long buttonPressedTick = 0;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

	if (input->IsButtonDown(code) && (currentTime_ms - buttonPressedTick) > 300)
	{
		buttonPressedTick = currentTime_ms;
		return true;
	}

	return false;
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

		if (!Settings::Aimbot::silent && !Settings::AntiAim::enabled_X && !Settings::AntiAim::enabled_Y)
			engine->SetViewAngles(cmd->viewangles);
	}

	return false;
}

void hkPaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	static unsigned long long int panelID;

	if (!panelID && !strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel"))
		panelID = vgui_panel;

	if (vgui_panel != panelID)
		return;

	if (IsButtonPressed(ButtonCode_t::KEY_INSERT)) {
		gui->Toggle();
	}
	
	gui->Draw ();
	
	ESP::PaintTraverse (vgui_panel, force_repaint, allow_force);
}

/* replacement FrameStageNotify function */
void hkFrameStageNotify(void* thisptr, ClientFrameStage_t stage) {
	SkinChanger::FrameStageNotify (stage);
	Noflash::FrameStageNotify (stage);

	return client_vmt->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);
}

void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	modelRender_vmt->ReleaseVMT ();

	Chams::DrawModelExecute (context, state, pInfo);

	modelRender->DrawModelExecute (context, state, pInfo, pCustomBoneToWorld);
	modelRender->ForcedMaterialOverride (NULL);

	modelRender_vmt->ApplyVMT ();
}

/* called when the library is loading */
int __attribute__((constructor)) aimtux_init()
{
	Hooker::HookInterfaces ();
	Hooker::HookVMethods ();
	Chams::CreateMaterials ();

	PRINT ("AimTux was successfully injected.");

	client_vmt->HookVM ((void*)hkFrameStageNotify, 36);
	client_vmt->ApplyVMT ();

	panel_vmt->HookVM ((void*)hkPaintTraverse, 42);
	panel_vmt->ApplyVMT ();

	modelRender_vmt->HookVM ((void*)hkDrawModelExecute, 21);
	modelRender_vmt->ApplyVMT ();

	Hooker::HookIClientMode ();

	clientMode_vmt->HookVM ((void*)hkCreateMove, 25);
	clientMode_vmt->ApplyVMT ();
	
	SetupFonts ();

	NetVarManager::dumpNetvars ();
	Offsets::getOffsets ();
	
	gui = new UI_Container;
	
	SetupUI ();
	
	
	return 0;
}

void __attribute__((destructor)) aimtux_shutdown()
{
	engine->ExecuteClientCmd("cl_mouseenable 1");
	
	client_vmt->ReleaseVMT ();
	panel_vmt->ReleaseVMT ();
	modelRender_vmt->ReleaseVMT ();
	clientMode_vmt->ReleaseVMT ();
	
	PRINT ("AimTux has been unloaded successfully.");
}
