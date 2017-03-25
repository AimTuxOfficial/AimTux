#include "walkbot.h"

bool Settings::WalkBot::enabled = false;
bool Settings::WalkBot::forceReset = false; // if a Reset is queued up by the User
bool Settings::WalkBot::autobuy = false; // autobuy during FreezeTime
int Settings::WalkBot::autobuyAt = 0;   // autobuy >= this amount of cash

static unsigned int rally;
static bool reachedEnd;
static bool hasAutobought;
static bool hasDied;
bool slowLastTick = false;


const std::vector<Vector> tRallyPoints =  { Vector(-417.1f, -707.38f, 174.8f), Vector(234.3f, -664.2f, 66.0f), Vector(-419.8f, -446.0f, 66.0f), Vector(-375.1f, 701.1f, 67.4f) };
const std::vector<Vector> ctRallyPoints = { Vector(262.8f, 2157.6f, -63.2f), Vector(-537.6f, 2110.4f, -58.4f), Vector(-383.1f, 1489.1f, -60.0f), Vector(-375.1f, 701.1f, 67.4f) };

C_BasePlayer* localPlayer;

void inline Reset()
{
	if( reachedEnd || Settings::WalkBot::forceReset || hasDied ){
		cvar->ConsoleColorPrintf(ColorRGBA(225, 225, 10), "--Reset Rally--\n");
		rally = 0;
		reachedEnd = false;
		Settings::WalkBot::forceReset = false;
		hasDied = false;
	}
}

bool DoRally( const std::vector<Vector> points, CUserCmd *cmd ) // return true if rally is completed.
{
	if( reachedEnd )
		return true;
	if( (std::abs(localPlayer->GetEyePosition().x - points[rally].x) < 0.6f) &&
		(std::abs(localPlayer->GetEyePosition().y - points[rally].y) < 0.6f) ){
		if( rally == points.size() -1 ){
			if( !reachedEnd ){
				cvar->ConsoleDPrintf("Reached Rally #%d\n", rally);
				cvar->ConsoleColorPrintf(ColorRGBA(50, 200, 100), "Finished Rally Points!\n");
				reachedEnd = true;
			}
			return true; // Finished Walking
		}
		cvar->ConsoleDPrintf("Reached Rally #%d\n", rally);
		rally++;
		cvar->ConsoleDPrintf("Moving To Rally #%d\n", rally);
	}

	QAngle move = Math::CalcAngle(localPlayer->GetEyePosition(), points[rally]);
	cmd->forwardmove = 250.0f;
	cmd->sidemove = 0;
	cmd->buttons |= IN_WALK;
	Math::CorrectMovement(move, cmd, cmd->forwardmove, cmd->sidemove);
	return false;
}

void Walkbot::CreateMove( CUserCmd *cmd )
{
	localPlayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if ( !localPlayer || !engine->IsInGame() || Settings::WalkBot::forceReset ){
		Reset();
		return;
	}
	if ( !Settings::WalkBot::enabled ){
		return;
	}
	if( (*csGameRules)->IsFreezeTime() ){
		Reset();
		if( Settings::WalkBot::autobuy && !hasAutobought && ( localPlayer->GetMoney() >= Settings::WalkBot::autobuyAt ) ){
			engine->ExecuteClientCmd("autobuy");
			hasAutobought = true;
		}
	}
	if( Settings::Aimbot::AutoSlow::goingToSlow ){
		slowLastTick = true;
		return;
	} else if( slowLastTick ){
		slowLastTick = false;
		return;
	}

	TeamID ourTeam = localPlayer->GetTeam();
	if( !localPlayer->GetAlive() ){
		if( ourTeam == TeamID::TEAM_UNASSIGNED ){
			engine->ExecuteClientCmd("teammenu"); // this will trigger the auto select timer
			return;
		} else {
			hasDied = true;
			hasAutobought = false;
			return;
		}
	}

	if( ourTeam == TeamID::TEAM_TERRORIST ){
		DoRally( tRallyPoints, cmd );
	} else if( ourTeam == TeamID::TEAM_COUNTER_TERRORIST ){
		DoRally( ctRallyPoints, cmd );
	}
}
