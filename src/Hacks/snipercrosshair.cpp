#include "snipercrosshair.h"

#include "../settings.h"
#include "../interfaces.h"

#include "../Utils/xorstring.h"
#include "../Utils/draw.h"

bool Settings::SniperCrosshair::enabled = false;


void SniperCrosshair::Paint( )
{
    if( !Settings::ESP::enabled || !Settings::SniperCrosshair::enabled )
        return;

    if( !engine->IsInGame() )
        return;

    C_BasePlayer* localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if ( !localPlayer || !localPlayer->GetAlive() )
        return;

    C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon*)entityList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
    if( activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_SNIPER_RIFLE )
        return;

    int width, height;
    engine->GetScreenSize( width, height );

    int x = width / 2;
    int y = height / 2;

    // outline horizontal
    Draw::FilledRectangle( Vector2D( x - 4, y - 1 ), Vector2D( x + 5, y + 2 ), Color( 0, 0, 0, 170 ) );
    // outline vertical
    Draw::FilledRectangle( Vector2D( x - 1, y - 4 ), Vector2D( x + 2, y + 5 ), Color( 0, 0, 0, 170 ) );

    int r = cvar->FindVar(XORSTR("cl_crosshaircolor_r"))->GetInt();
    int g = cvar->FindVar(XORSTR("cl_crosshaircolor_g"))->GetInt();
    int b = cvar->FindVar(XORSTR("cl_crosshaircolor_b"))->GetInt();
    int alpha = cvar->FindVar(XORSTR("cl_crosshairalpha"))->GetInt();

    // line horizontal
    Draw::Line( Vector2D( x - 3, y ), Vector2D( x + 4, y ), Color(r, g, b, alpha));
    // line vertical
    Draw::Line( Vector2D( x, y + 3 ), Vector2D( x, y - 4 ), Color(r, g, b, alpha));
}
