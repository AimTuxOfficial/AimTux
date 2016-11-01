#include "hooks.h"

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientMode_vmt->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
#ifdef EXPERIMENTAL_SETTINGS
		Util::WriteSendPacket(true);
#endif

		BHop::CreateMove(cmd);
		AutoStrafe::CreateMove(cmd);
		Aimbot::CreateMove(cmd);
		Triggerbot::CreateMove(cmd);
		AntiAim::CreateMove(cmd);
		Chams::CreateMove(cmd);
		Airstuck::CreateMove(cmd);
		ShowRanks::CreateMove(cmd);
		ClanTagChanger::CreateMove(cmd);
		Spammer::CreateMove(cmd);
		NameChanger::CreateMove(cmd);
		Teleport::CreateMove(cmd);

#ifdef EXPERIMENTAL_SETTINGS
		FakeLag::CreateMove(cmd);
#endif

		if (!Settings::Aimbot::silent && !Settings::AntiAim::enabled_X && !Settings::AntiAim::enabled_Y)
			engine->SetViewAngles(cmd->viewangles);
	}

	return false;
}
