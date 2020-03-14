#include "angleindicator.h"

#include "../interfaces.h"
#include "../settings.h"
#include "antiaim.h"
#include "../Utils/draw.h"
#include "../Utils/math.h"
#include "../Hooks/hooks.h"

void AngleIndicator::Paint( ) {
    if( !Settings::AngleIndicator::enabled || !engine->IsInGame() )
        return;

    C_BasePlayer* localPlayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );

    if ( !localPlayer || !localPlayer->GetAlive() )
        return;

    int radius = 55;
    int centerX = Paint::engineWidth / 3;
    int centerY = Paint::engineHeight / 2;
    int northY = centerY - radius;

    float maxDesync = AntiAim::GetMaxDelta( localPlayer->GetAnimState() );
    float realDiff = AntiAim::fakeAngle.y - AntiAim::realAngle.y;
    float lbyDiff = localPlayer->GetVAngles()->y - *localPlayer->GetLowerBodyYawTarget();
    Math::NormalizeYaw( realDiff );
    Math::NormalizeYaw( lbyDiff );

    int leftDesyncMaxX = radius * cos( DEG2RAD( 90 + maxDesync ) ) + centerX;
    int leftDesyncMaxY = centerY - ( radius * sin( DEG2RAD( 90 + maxDesync ) ) );
    int rightDesyncMaxX = radius * cos( DEG2RAD( 90 - maxDesync ) ) + centerX;
    int rightDesyncMaxY = centerY - ( radius * sin( DEG2RAD( 90 - maxDesync ) ) );
    int realX = radius * cos( DEG2RAD( 90 - realDiff ) ) + centerX;
    int realY = centerY - ( radius * sin( DEG2RAD( 90 - realDiff ) ) );
    int lbyX = radius * cos( DEG2RAD( 90 - lbyDiff ) ) + centerX;
    int lbyY = centerY - ( radius * sin( DEG2RAD( 90 - lbyDiff ) ) );

    static ImColor basicColor = ImColor( 0, 0, 0 );
    static ImColor fakeColor = ImColor( 5, 200, 5 );
    static ImColor realColor = ImColor( 225, 5, 5 );
    static ImColor lbyColor = ImColor( 135, 235, 169 );

    Draw::AddCircle( centerX, centerY, radius, basicColor, 32 );

    Draw::AddLine( centerX, centerY, centerX, northY, fakeColor ); // Const North line
    Draw::AddLine( centerX, centerY, leftDesyncMaxX, leftDesyncMaxY, basicColor ); // Left Max
    Draw::AddLine( centerX, centerY, rightDesyncMaxX, rightDesyncMaxY, basicColor ); // Right Max

    if( Settings::AntiAim::Yaw::enabled && ( Settings::AntiAim::Yaw::typeFake != Settings::AntiAim::Yaw::type)  ){
        Draw::AddLine( centerX, centerY, realX, realY, realColor ); // Real Line
    }
    if( Settings::AntiAim::LBYBreaker::enabled ){
        Draw::AddLine( centerX, centerY, lbyX, lbyY, lbyColor ); // LBY Line
    }
}