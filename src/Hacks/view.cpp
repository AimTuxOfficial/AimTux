#include "view.h"

bool Settings::View::NoAimPunch::enabled = false;
bool Settings::View::NoViewPunch::enabled = false;

QAngle old_view_punch_angle;
QAngle old_aim_punch_angle;

void View::FrameStageNotify(ClientFrameStage_t stage)
{
	if ((!Settings::View::NoAimPunch::enabled && !Settings::View::NoViewPunch::enabled) || !Settings::ESP::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_RENDER_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	if (Settings::View::NoAimPunch::enabled)
	{
		QAngle* aim_punch_angle = localplayer->GetAimPunchAngle();

		old_aim_punch_angle = QAngle(0, 0, 0);

		if (aim_punch_angle)
		{
			old_aim_punch_angle = *aim_punch_angle;
			*aim_punch_angle = QAngle(0, 0, 0);
		}
	}

	if (Settings::View::NoViewPunch::enabled)
	{
		QAngle* view_punch_angle = localplayer->GetViewPunchAngle();

		old_view_punch_angle = QAngle(0, 0, 0);

		if (view_punch_angle)
		{
			old_view_punch_angle = *view_punch_angle;
			*view_punch_angle = QAngle(0, 0, 0);
		}
	}
}

void View::PostFrameStageNotify(ClientFrameStage_t stage)
{
	if ((!Settings::View::NoAimPunch::enabled && !Settings::View::NoViewPunch::enabled) || !Settings::ESP::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_RENDER_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	if (Settings::View::NoAimPunch::enabled)
	{
		QAngle* aim_punch_angle = localplayer->GetAimPunchAngle();

		if (aim_punch_angle)
			*aim_punch_angle = old_aim_punch_angle;
	}

	if (Settings::View::NoViewPunch::enabled)
	{
		QAngle* view_punch_angle = localplayer->GetViewPunchAngle();

		if (view_punch_angle)
			*view_punch_angle = old_view_punch_angle;
	}
}
