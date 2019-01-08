#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
	engineVGuiVMT->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

	if (Settings::ScreenshotCleaner::enabled && engine->IsTakingScreenshot())
		return;

	if (mode & PAINT_UIPANELS)
	{
		StartDrawing(surface);

		Dlights::Paint();
		ESP::Paint();
		GrenadeHelper::Paint();
		Recoilcrosshair::Paint();
		Hitmarkers::Paint();
		SniperCrosshair::Paint();

		FinishDrawing(surface);
	}
}

void Hooks::PaintImGui()
{

}