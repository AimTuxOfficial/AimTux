#include "hooks.h"

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientMode_vmt->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
		*bSendPacket = true;

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
		FakeLag::CreateMove(cmd);

		if (!Settings::Aimbot::silent && !Settings::AntiAim::enabled_X && !Settings::AntiAim::enabled_Y)
			engine->SetViewAngles(cmd->viewangles);
	}

	return false;
}
