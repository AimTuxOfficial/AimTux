#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

#include "../Hacks/bhop.h"
#include "../Hacks/noduckcooldown.h"
#include "../Hacks/autostrafe.h"
#include "../Hacks/showranks.h"
#include "../Hacks/autodefuse.h"
#include "../Hacks/jumpthrow.h"
#include "../Hacks/grenadehelper.h"
#include "../Hacks/grenadeprediction.h"
#include "../Hacks/edgejump.h"
#include "../Hacks/autoblock.h"
#include "../Hacks/predictionsystem.h"
#include "../Hacks/aimbot.h"
#include "../Hacks/triggerbot.h"
#include "../Hacks/autoknife.h"
#include "../Hacks/antiaim.h"
#include "../Hacks/airstuck.h"
#include "../Hacks/fakelag.h"
#include "../Hacks/esp.h"
#include "../Hacks/tracereffect.h"
#include "../Hacks/nofall.h"

bool CreateMove::sendPacket = true;
QAngle CreateMove::lastTickViewAngles = QAngle(0, 0, 0);

typedef bool (*CreateMoveFn) (void*, float, CUserCmd*);

bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
	clientModeVMT->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

	if (cmd && cmd->command_number)
	{
        // Special thanks to Gre-- I mean Heep ( https://www.unknowncheats.me/forum/counterstrike-global-offensive/290258-updating-bsendpacket-linux.html )
        uintptr_t rbp;
        asm volatile("mov %%rbp, %0" : "=r" (rbp));
        bool *sendPacket = ((*(bool **)rbp) - 0x18);
        CreateMove::sendPacket = true;

		/* run code that affects movement before prediction */
		BHop::CreateMove(cmd);
		NoDuckCooldown::CreateMove(cmd);
		AutoStrafe::CreateMove(cmd);
		ShowRanks::CreateMove(cmd);
		AutoDefuse::CreateMove(cmd);
		JumpThrow::CreateMove(cmd);
		GrenadeHelper::CreateMove(cmd);
        GrenadePrediction::CreateMove( cmd );
        EdgeJump::PrePredictionCreateMove(cmd);
		Autoblock::CreateMove(cmd);
		NoFall::PrePredictionCreateMove(cmd);

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
		NoFall::PostPredictionCreateMove(cmd);

        *sendPacket = CreateMove::sendPacket;

        if (CreateMove::sendPacket) {
            CreateMove::lastTickViewAngles = cmd->viewangles;
        }
	}

	return false;
}
