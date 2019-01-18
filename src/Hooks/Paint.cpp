#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/draw.h"


#include "../Hacks/esp.h"
#include "../Hacks/dlights.h"
#include "../Hacks/grenadehelper.h"
#include "../Hacks/recoilcrosshair.h"
#include "../Hacks/hitmarkers.h"
#include "../Hacks/snipercrosshair.h"
#include "../Hacks/angleindicator.h"

extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;

bool hasFinished = true;

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
	engineVGuiVMT->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

	if (Settings::ScreenshotCleaner::enabled && engine->IsTakingScreenshot())
		return;

	if (mode & PAINT_UIPANELS)
	{
		StartDrawing(surface);
			ESP::PaintToUpdateMatrix(); // Just for updating the viewMatrix
			Dlights::Paint();

			// Settings::ESP::backend has a chance to be changed by the user during drawing.
			// So we use and set Draw::currentBackend
			if( Settings::ESP::backend == DrawingBackend::SURFACE && hasFinished ){
				Draw::currentBackend = DrawingBackend::SURFACE;
				hasFinished = false;

				ESP::PaintHybrid();
				GrenadeHelper::PaintHybrid();
				Recoilcrosshair::PaintHybrid();
				Hitmarkers::PaintHyrbid();
				SniperCrosshair::PaintHybrid();
				AngleIndicator::PaintHybrid();
			}
		FinishDrawing(surface);
		hasFinished = true;
	}
}

void Hooks::PaintImGui()
{
	if( Settings::ESP::backend == DrawingBackend::IMGUI && hasFinished ){
		Draw::currentBackend = DrawingBackend::IMGUI;
		hasFinished = false;

		ESP::PaintHybrid();
		GrenadeHelper::PaintHybrid();
		Recoilcrosshair::PaintHybrid();
		Hitmarkers::PaintHyrbid();
		SniperCrosshair::PaintHybrid();
		AngleIndicator::PaintHybrid();

		hasFinished = true;
	}
}