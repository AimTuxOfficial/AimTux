#include "thirdperson.h"

bool Settings::ThirdPerson::enabled = false;
float Settings::ThirdPerson::distance = 30.f;

void ThirdPerson::BeginFrame()
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (Settings::ThirdPerson::enabled)
	{
		for (ptrdiff_t off = 0; off < 0x2; off++)
			*(CamThinkSvCheatsCheck + off) = 0x90;
	}
	else
	{
		*CamThinkSvCheatsCheck = 0x74;
		*(CamThinkSvCheatsCheck + 0x1) = 0x64;
	}
}

void ThirdPerson::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		input->m_fCameraInThirdPerson = Settings::ThirdPerson::enabled && localplayer->GetAlive();

		if (Settings::ThirdPerson::enabled)
		{
			QAngle viewAngles;
			engine->GetViewAngles(viewAngles);

			input->m_vecCameraOffset.z = Settings::ThirdPerson::distance;

			*localplayer->GetVAngles() = CreateMove::lastTickViewAngles;
		}

	}
}