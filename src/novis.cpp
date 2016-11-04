#include "novis.h"

bool Settings::NoVis::enabled = false;

QAngle old_punch_angle;

void NoVis::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::NoVis::enabled)
		return;
	
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	
	QAngle* punch_angle = localplayer->GetViewPunchAngle ();
	old_punch_angle = QAngle (0, 0, 0);
	
	if (stage == FRAME_RENDER_START && punch_angle && engine->IsInGame())
	{
		old_punch_angle = *punch_angle;
		*punch_angle = QAngle (0, 0, 0);
	}
	
}

void NoVis::PostFrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::NoVis::enabled)
		return;
	
	
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	
	QAngle* punch_angle = localplayer->GetViewPunchAngle ();
	
	if (stage == FRAME_RENDER_START && punch_angle && engine->IsInGame())
	{
		*punch_angle = old_punch_angle;
	}
}