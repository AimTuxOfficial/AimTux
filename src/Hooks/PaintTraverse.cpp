#include "hooks.h"

void Hooks::PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	static unsigned long long int panelID;
	if (!panelID && strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel") == 0)
		panelID = vgui_panel;

	if (vgui_panel != panelID)
		return;

	Dlights::PaintTraverse(vgui_panel, force_repaint, allow_force);
	ESP::PaintTraverse(vgui_panel, force_repaint, allow_force);
	Radar::PaintTraverse(vgui_panel, force_repaint, allow_force);
	Recoilcrosshair::PaintTraverse(vgui_panel, force_repaint, allow_force);
	ShowSpectators::PaintTraverse(vgui_panel, force_repaint, allow_force);

	gui->Draw();

	if (!engine->IsInGame())
		*bSendPacket = true;
}