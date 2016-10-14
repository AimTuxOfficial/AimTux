#include "hooks.h"

static bool IsButtonPressed(ButtonCode_t code)
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

void Hooks::PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	static unsigned long long int panelID;
	if (!panelID && !strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel"))
		panelID = vgui_panel;

	if (vgui_panel != panelID)
		return;

	if (IsButtonPressed(ButtonCode_t::KEY_INSERT))
		gui->Toggle();

	Dlights::PaintTraverse(vgui_panel, force_repaint, allow_force);
	ESP::PaintTraverse(vgui_panel, force_repaint, allow_force);
	Recoilcrosshair::PaintTraverse(vgui_panel, force_repaint, allow_force);
	ShowSpectators::PaintTraverse(vgui_panel, force_repaint, allow_force);

	gui->Draw();
}