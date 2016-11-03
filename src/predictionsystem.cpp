#include "predictionsystem.h"

float m_flOldCurtime;
float m_flOldFrametime;

void PredictionSystem::StartPrediction(CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

	*nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

	m_flOldCurtime = globalvars->curtime;
	m_flOldFrametime = globalvars->frametime;

	globalvars->curtime = localplayer->GetTickBase() * globalvars->interval_per_tick;
	globalvars->frametime = globalvars->interval_per_tick;

	gamemovement->StartTrackPredictionErrors(localplayer);

	CMoveData m_MoveData;
	memset(&m_MoveData, 0, sizeof(m_MoveData));
	movehelper->SetHost(localplayer);
	prediction->SetupMove(localplayer, cmd, movehelper, &m_MoveData);
	gamemovement->ProcessMovement(localplayer, &m_MoveData);
	prediction->FinishMove(localplayer, cmd, &m_MoveData);
}

void PredictionSystem::EndPrediction()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

	gamemovement->FinishTrackPredictionErrors(localplayer);
	movehelper->SetHost(0);

	*nPredictionRandomSeed = -1;

	globalvars->curtime = m_flOldCurtime;
	globalvars->frametime = m_flOldFrametime;
}