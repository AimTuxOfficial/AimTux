#include "hooks.h"

void Hooks::PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (ESP::PrePaintTraverse(vgui_panel, force_repaint, allow_force))
		panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	if (!engine->IsInGame())
	{
		CreateMove::SendPacket = true;
		*bSendPacket = CreateMove::SendPacket;
	}
}