#include "hooks.h"

bool CreateMove::sendPacket = true;
QAngle CreateMove::lastTickViewAngles = QAngle(0, 0, 0);

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientModeVMT->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
		*bSendPacket = CreateMove::sendPacket;
		CreateMove::sendPacket = true;

		BHop::CreateMove(cmd);
		Chams::CreateMove(cmd);
		ShowRanks::CreateMove(cmd);
		AutoDefuse::CreateMove(cmd);
		EdgeJump::PrePredictionCreateMove(cmd);

		PredictionSystem::StartPrediction(cmd);
		Autoblock::CreateMove(cmd);
		Aimbot::CreateMove(cmd);
		Triggerbot::CreateMove(cmd);
		AntiAim::CreateMove(cmd);
		AutoStrafe::CreateMove(cmd);
		Airstuck::CreateMove(cmd);
		Teleport::CreateMove(cmd);
		FakeLag::CreateMove(cmd);
		ESP::CreateMove(cmd);
		PredictionSystem::EndPrediction();

		EdgeJump::PostPredictionCreateMove(cmd);

		if (CreateMove::sendPacket)
			CreateMove::lastTickViewAngles = cmd->viewangles;
	}

	return false;
}