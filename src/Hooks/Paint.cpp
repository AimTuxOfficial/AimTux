#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/draw.h"
#include "../fonts.h"

#include "../Hacks/esp.h"
#include "../Hacks/dlights.h"
#include "../Hacks/grenadehelper.h"
#include "../Hacks/recoilcrosshair.h"
#include "../Hacks/hitmarkers.h"
#include "../Hacks/snipercrosshair.h"
#include "../Hacks/angleindicator.h"

#include <mutex>

extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;

std::mutex drawMutex;

typedef void (*PaintFn) (void*, PaintMode_t);

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
	engineVGuiVMT->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

	if (Settings::ScreenshotCleaner::enabled && engine->IsTakingScreenshot())
		return;

	if (mode & PAINT_UIPANELS)
	{
        int prevRecords = Draw::drawRequests.size(); // # of requests from last call

        ESP::PaintToUpdateMatrix(); // Just for updating the viewMatrix
        /* These functions make drawRequests */
        Dlights::Paint();
        ESP::Paint();
        GrenadeHelper::Paint();
        Recoilcrosshair::Paint();
        Hitmarkers::Paint();
        SniperCrosshair::Paint();
        AngleIndicator::Paint();

        if( Settings::ESP::backend == DrawingBackend::SURFACE ){
            StartDrawing(surface);
            for( long unsigned int i = 0; i < Draw::drawRequests.size(); i++ ){
                #define value Draw::drawRequests[i]
                switch( value.type ){
                    case DRAW_LINE:
                        Draw::Line( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_RECT:
                        Draw::Rectangle( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_RECT_FILLED:
                        Draw::FilledRectangle( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_CIRCLE:
                        Draw::Circle( Vector2D( value.x0, value.y0 ), value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_CIRCLE_FILLED:
                        Draw::FilledCircle( Vector2D( value.x0, value.y0 ), value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_CIRCLE_3D:
                        Draw::Circle3D( value.pos, value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                        break;
                    case DRAW_TEXT:
                        Draw::Text( value.x0, value.y0, value.text, esp_font, Color::FromImColor( value.color ) );
                        break;
                }
            }
            FinishDrawing(surface);
        }
        std::unique_lock<std::mutex> lock( drawMutex );
        Draw::drawRequests.erase( Draw::drawRequests.begin( ), Draw::drawRequests.begin( ) + prevRecords );
    }
}

void Hooks::PaintImGui()
{
	if( Settings::ESP::backend != DrawingBackend::IMGUI )
        return;

    std::unique_lock<std::mutex> lock( drawMutex );

    for( long unsigned int i = 0; i < Draw::drawRequests.size(); i++ ){
        #define value Draw::drawRequests[i]
        switch( value.type ){
            case DRAW_LINE:
                Draw::ImLine( ImVec2( value.x0, value.y0 ), ImVec2( value.x1, value.y1 ), value.color );
                break;
            case DRAW_RECT:
                Draw::ImRect( value.x0, value.y0, value.x1, value.y1, value.color );
                break;
            case DRAW_RECT_FILLED:
                Draw::ImRectFilled( value.x0, value.y0, value.x1, value.y1, value.color );
                break;
            case DRAW_CIRCLE:
                Draw::ImCircle( ImVec2( value.x0, value.y0 ), value.color, value.circleRadius, value.circleSegments, value.thickness );
                break;
            case DRAW_CIRCLE_FILLED:
                Draw::ImCircleFilled( ImVec2( value.x0, value.y0 ), value.color, value.circleRadius, value.circleSegments );
                break;
            case DRAW_CIRCLE_3D:
                Draw::ImCircle3D( value.pos, value.circleSegments, value.circleRadius, value.color );
                break;
            case DRAW_TEXT:
                Draw::ImText( ImVec2( value.x0, value.y0 ), value.color, value.text, nullptr, 0.0f, nullptr, value.fontflags );
                break;
        }
    }
}