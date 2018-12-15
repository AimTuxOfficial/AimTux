#include "hooks.h"

bool CreateMove::sendPacket = true;
QAngle CreateMove::lastTickViewAngles = QAngle(0, 0, 0);

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientModeVMT->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
        // Special thanks to Gre-- I mean Heep ( https://www.unknowncheats.me/forum/counterstrike-global-offensive/290258-updating-bsendpacket-linux.html )
        uintptr_t rbp;
        asm volatile("mov %%rbp, %0" : "=r" (rbp));
        bool *sendPacket = ((*(bool **)rbp) - 0x18);
        *sendPacket = CreateMove::sendPacket;
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
        if (inputSystem->IsButtonDown( ButtonCode_t::KEY_F ) )
            cvar->ConsoleDPrintf("mousedx/y: %d,%d\n", cmd->mousedx, cmd->mousedy);
	}

	return false;
}
