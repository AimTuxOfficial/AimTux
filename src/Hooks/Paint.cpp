#include "hooks.h"

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
	enginevgui_vmt->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

	if (mode & PAINT_UIPANELS)
	{
		Dlights::Paint();
		ESP::Paint();
		Recoilcrosshair::Paint();
	}
}