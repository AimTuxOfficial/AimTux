#include "tracereffect.h"

bool Settings::TracerEffects::enabled = false;
bool Settings::TracerEffects::serverSide = false;
TracerEffects_t Settings::TracerEffects::effect = TracerEffects_t::TASER;
int Settings::TracerEffects::frequency = 1;

struct tracerRecord
{
    tracerRecord(void* addr, char *weapName, char *effName, int freq)
    {
        address = addr;
        strncpy(weaponName, weapName, 32);
        strncpy(effectName, effName, 32);
        frequency = freq;
    }
    void* address;
    char weaponName[32];
    char effectName[32];
    int frequency;
};

static bool wait = false;
static long waitUntil = 0; // Epoch in ms
static std::string lastGun;
/* Used for Restoring the Original Tracer Effect */
static std::vector<tracerRecord> tracerRecords;


static const char *tracerEffectNames[] = {
    "weapon_tracers_assrifle", // 0
    "weapon_tracers_pistol",
    "weapon_tracers_smg",
    "weapon_tracers_rifle",
    "weapon_tracers_taser",
    "weapon_tracers_mach",
    "weapon_tracers_shot",
    "weapon_tracers_taser_fallback",
    "weapon_tracers_taser_fallback2",
    "weapon_tracers_taser_wire1a",
    "weapon_tracers_taser_wire2",
    "weapon_tracers_taser_wire1b",
    "weapon_tracers_original",
    "weapon_tracers_backup",
    "weapon_tracers_50cal",
    "weapon_tracers_50cal_glow",
    "weapon_tracers_50cal_low",
    "weapon_tracers_50cal_low_glow", // 17
};

const std::map<std::string, short> drawTimes = {
    {"weapon_cz75a", 1880},
    {"weapon_mp9", 1330},
    {"weapon_awp", 1900},
    {"weapon_aug", 1285},
    {"weapon_m249", 1180},
    {"weapon_m4a1", 1170},
    {"weapon_m4a1_silencer", 1170},
    {"weapon_galilar", 1175},
    {"weapon_bizon", 1150},
    {"weapon_glock", 1150},
    {"weapon_negev", 1130},
    {"weapon_sawedoff", 1120},
    {"weapon_elite", 1100},
    {"weapon_ump45", 1085},
    {"weapon_nova", 1070},
    {"weapon_scar20", 1050},
    {"weapon_g3sg1", 1050},
    {"weapon_famas", 1050},
    {"weapon_mp7", 1055},
    {"weapon_fiveseven", 1050},
    {"weapon_ak47", 1050},
    {"weapon_mac10", 1030},
    {"weapon_usp_silencer", 1030},
    {"weapon_deagle", 1030},
    {"weapon_ssg08", 1150},
    {"weapon_xm1014", 1020},
    {"weapon_hkp2000", 1020},
    {"weapon_p250", 1050},
    {"weapon_tec9", 1050},
    {"weapon_sg556", 1025},
    {"weapon_mag7", 1025},
};

void TracerEffect::RestoreTracers( )
{
    if( tracerRecords.size() <= 0 )
        return;
    for( unsigned int i = 0; i < tracerRecords.size(); i++ )
    {
        CCSWeaponInfo *swag = (CCSWeaponInfo*)tracerRecords[i].address;
        *swag->GetTracerFrequency() = tracerRecords[i].frequency;
        strncpy(swag->GetTracerEffect(), tracerRecords[i].effectName, strlen(tracerRecords[i].effectName));
    }
    tracerRecords.clear();
}
void TracerEffect::CreateMove(CUserCmd* cmd) {
    if ( !Settings::TracerEffects::enabled )
    {
        RestoreTracers();
        return;
    }

    C_BasePlayer *localplayer = ( C_BasePlayer * )entityList->GetClientEntity( engine->GetLocalPlayer( ) );
    if ( !engine->IsInGame( ) || !localplayer || !localplayer->GetAlive( ) )
        return;
    C_BaseCombatWeapon *localWeapon = ( C_BaseCombatWeapon * )entityList->GetClientEntityFromHandle( localplayer->GetActiveWeapon( ) );
    if ( !localWeapon || localWeapon->GetInReload() )
        return;

    if ( localWeapon->GetNextPrimaryAttack() > globalVars->curtime )
        return;
    if ( !( cmd->buttons & IN_ATTACK ) )
    {
        /* On One-taps, it doesn't get to the taser part, so we need to switch back to the gun here */
        if ( strcmp(localWeapon->GetCSWpnData()->GetConsoleName(), "weapon_taser") == 0 && Settings::TracerEffects::serverSide )
            engine->ExecuteClientCmd("lastinv");
        return;
    }

    if( wait )
    {
        if( Util::GetEpochTime() <= waitUntil )
        {
            cmd->buttons = cmd->buttons & ~IN_ATTACK;
            return;
        }

        wait = false;
    }

    if( localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_MACHINEGUN ||
        localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_PISTOL ||
        localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_RIFLE ||
        localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_SUBMACHINEGUN ||
        localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_SHOTGUN ||
        localWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_SNIPER_RIFLE )
    {
        if( strcmp(lastGun.c_str(), localWeapon->GetCSWpnData()->GetConsoleName()) != 0 )
        {
            RestoreTracers();
        }
        /* Search for record by weaponName, add to tracerRecords struct if not already there. */
        auto pred = [&](const tracerRecord & record) {
            return (strcmp(record.weaponName, localWeapon->GetCSWpnData()->GetConsoleName()) == 0);
        };
        if( std::find_if(std::begin(tracerRecords), std::end(tracerRecords), pred) == std::end(tracerRecords) )
        {
            /* Add new weapon */
            tracerRecords.push_back(tracerRecord((void*)localWeapon->GetCSWpnData(),
                                                 localWeapon->GetCSWpnData()->GetConsoleName(),
                                                 localWeapon->GetCSWpnData()->GetTracerEffect(),
                                                 *localWeapon->GetCSWpnData()->GetTracerFrequency()));
        }

        /* The Server-sided glitch normally doesn't show on the localClient. We ignore the user settings to show the taser glitch accurately */
        if( Settings::TracerEffects::serverSide )
        {
            *localWeapon->GetCSWpnData()->GetTracerFrequency() = 1;
            if( strlen(localWeapon->GetCSWpnData()->GetTracerEffect()) > strlen(tracerEffectNames[(int)TracerEffects_t::TASER]) )
            {
                strncpy(localWeapon->GetCSWpnData()->GetTracerEffect(),
                        tracerEffectNames[(int)TracerEffects_t::TASER],
                        strlen(localWeapon->GetCSWpnData()->GetTracerEffect()));
            }
            else
            {   /* This could lead to some bad juju later, since we are making the string bigger */
                strncpy(localWeapon->GetCSWpnData()->GetTracerEffect(),
                        tracerEffectNames[(int)TracerEffects_t::TASER],
                        strlen(tracerEffectNames[(int)TracerEffects_t::TASER]));
            }
            /* Gun is out, we need to Swap to taser and then quickly Fire to trigger the glitch
             * The Glitch is that the server will use the tracer effect of your currently selected weapon
             * Instead of the one you took the shot with */
            lastGun = localWeapon->GetCSWpnData()->GetConsoleName();
            engine->ClientCmd_Unrestricted("use weapon_taser;"); // needs to be unrestricted
            cmd->buttons = cmd->buttons | IN_ATTACK;
            wait = true;
            waitUntil = Util::GetEpochTime() + 125;
        }
        else /* Just do some Client-Sided Effects for Fun based on the Settings */
        {
            *localWeapon->GetCSWpnData()->GetTracerFrequency() = Settings::TracerEffects::frequency;
            if( strlen(localWeapon->GetCSWpnData()->GetTracerEffect()) > strlen(tracerEffectNames[(int)Settings::TracerEffects::effect]) )
            {
                strncpy(localWeapon->GetCSWpnData()->GetTracerEffect(),
                        tracerEffectNames[(int)Settings::TracerEffects::effect],
                        strlen(localWeapon->GetCSWpnData()->GetTracerEffect()));
            }
            else
            {
                strncpy(localWeapon->GetCSWpnData()->GetTracerEffect(),
                        tracerEffectNames[(int)Settings::TracerEffects::effect],
                        strlen(tracerEffectNames[(int)Settings::TracerEffects::effect]));
            }
        }
    }
    else if ( strcmp(localWeapon->GetCSWpnData()->GetConsoleName(), "weapon_taser") == 0 )
    {
        if( !Settings::TracerEffects::serverSide )
            return;
        /* Taser is out, we need to switch back to the gun and wait for it to be cocked */
        if( drawTimes.find(lastGun) == drawTimes.end() )
        {
            cvar->ConsoleDPrintf(XORSTR("(TracerEffect::CreateMove): Warning: Gun \"%s\" not found in drawTimes map\n"), localWeapon->GetCSWpnData()->GetConsoleName());
        }
        else
        {
            wait = true;
            waitUntil = Util::GetEpochTime() + drawTimes.at(lastGun);
        }

        engine->ExecuteClientCmd("lastinv");
        cmd->buttons = cmd->buttons & ~IN_ATTACK;

    }
}