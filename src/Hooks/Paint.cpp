#include "hooks.h"

extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
	enginevgui_vmt->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

	if (mode & PAINT_UIPANELS)
	{
		StartDrawing(surface);

		Dlights::Paint();
		ESP::Paint();
		Recoilcrosshair::Paint();

		FinishDrawing(surface);
	}
}