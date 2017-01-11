#include "view.h"

bool Settings::View::NoPunch::enabled = false;

QAngle old_punch_angle;
QAngle old_aim_punch_angle;

void View::NoPunch::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::View::NoPunch::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != FRAME_RENDER_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

	QAngle* punch_angle = localplayer->GetViewPunchAngle();
	QAngle* aim_punch_angle = localplayer->GetAimPunchAngle();

	old_punch_angle = QAngle(0, 0, 0);
	old_aim_punch_angle = QAngle(0, 0, 0);

	if (punch_angle)
	{
		old_punch_angle = *punch_angle;
		*punch_angle = QAngle(0, 0, 0);

		old_aim_punch_angle = *aim_punch_angle;
		*aim_punch_angle = QAngle(0, 0, 0);
	}
}

void View::NoPunch::PostFrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::View::NoPunch::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != FRAME_RENDER_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	QAngle* punch_angle = localplayer->GetViewPunchAngle();
	QAngle* aim_punch_angle = localplayer->GetAimPunchAngle();

	if (punch_angle && aim_punch_angle)
	{
		*punch_angle = old_punch_angle;
		*aim_punch_angle = old_aim_punch_angle;
	}
}

void View::FrameStageNotify(ClientFrameStage_t stage)
{
	View::NoPunch::FrameStageNotify(stage);
}

void View::PostFrameStageNotify(ClientFrameStage_t stage)
{
	View::NoPunch::PostFrameStageNotify(stage);
}
