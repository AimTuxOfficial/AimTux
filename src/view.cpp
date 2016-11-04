#include "view.h"

bool Settings::View::NoPunch::enabled = false;

QAngle old_punch_angle;


void View::NoPunch::FrameStageNotify (ClientFrameStage_t stage)
{
	if (!Settings::View::NoPunch::enabled)
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

void View::NoPunch::PostFrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::View::NoPunch::enabled)
		return;
	
	
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	
	QAngle* punch_angle = localplayer->GetViewPunchAngle ();
	
	if (stage == FRAME_RENDER_START && punch_angle && engine->IsInGame())
	{
		*punch_angle = old_punch_angle;
	}
}


void View::FrameStageNotify(ClientFrameStage_t stage)
{
	View::NoPunch::FrameStageNotify (stage);
}

void View::PostFrameStageNotify(ClientFrameStage_t stage)
{
	View::NoPunch::PostFrameStageNotify (stage);
}