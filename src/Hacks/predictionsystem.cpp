#include "predictionsystem.h"

float m_flOldCurtime;
float m_flOldFrametime;

void PredictionSystem::StartPrediction(CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	*nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

	m_flOldCurtime = globalVars->curtime;
	m_flOldFrametime = globalVars->frametime;

	globalVars->curtime = localplayer->GetTickBase() * globalVars->interval_per_tick;
	globalVars->frametime = globalVars->interval_per_tick;

	gameMovement->StartTrackPredictionErrors(localplayer);

	moveHelper->SetHost(localplayer);
	prediction->SetupMove(localplayer, cmd, moveHelper, g_MoveData);
	gameMovement->ProcessMovement(localplayer, g_MoveData);
	prediction->FinishMove(localplayer, cmd, g_MoveData);
}

void PredictionSystem::EndPrediction()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	gameMovement->FinishTrackPredictionErrors(localplayer);
	moveHelper->SetHost(0);

	*nPredictionRandomSeed = -1;

	globalVars->curtime = m_flOldCurtime;
	globalVars->frametime = m_flOldFrametime;
}
