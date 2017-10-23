#include "hooks.h"

bool CreateMove::sendPacket = true;
QAngle CreateMove::lastTickViewAngles = QAngle(0, 0, 0);

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientModeVMT->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
		//register uintptr_t *pFrame asm("rbp");
		//cvar->ConsoleDPrintf("*RBP: %#x | Final Address: %#x | Sending? (%d)\n", *pFrame, (((bool*)*pFrame)-0x3B4), *(((bool*)*pFrame)-0x3B4));
		//*(((bool*)*pFrame)-0x1018) = CreateMove::sendPacket;
		*bSendPacket = CreateMove::sendPacket;
		CreateMove::sendPacket = true;

		/* run code that affects movement before prediction */
		BHop::CreateMove(cmd);
		AutoStrafe::CreateMove(cmd);
		ShowRanks::CreateMove(cmd);
		AutoDefuse::CreateMove(cmd);
		JumpThrow::CreateMove(cmd);
		GrenadeHelper::CreateMove(cmd);
		EdgeJump::PrePredictionCreateMove(cmd);
		Walkbot::CreateMove(cmd);
		Autoblock::CreateMove(cmd);

		PredictionSystem::StartPrediction(cmd);
			Aimbot::CreateMove(cmd);
			Triggerbot::CreateMove(cmd);
			AutoKnife::CreateMove(cmd);
			AntiAim::CreateMove(cmd);
			Airstuck::CreateMove(cmd);
			FakeLag::CreateMove(cmd);
			ESP::CreateMove(cmd);
			TracerEffect::CreateMove(cmd);
		PredictionSystem::EndPrediction();

		EdgeJump::PostPredictionCreateMove(cmd);

		if (CreateMove::sendPacket)
			CreateMove::lastTickViewAngles = cmd->viewangles;
	}

	return false;
}
