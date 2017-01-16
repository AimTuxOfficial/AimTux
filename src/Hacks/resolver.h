#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../Utils/draw.h"
#include "../interfaces.h"
#include "../Utils/pstring.h"
#include "../Utils/entity.h"
#include "../Utils/netvarmanager.h"

struct PlayerAA
{
	C_BasePlayer* player;
	float resolved_y_axis;
	float reset_y_axis;

	PlayerAA(C_BasePlayer* player, QAngle angle)
	{
		this->player = player;
		resolved_y_axis = 0.0f;
		reset_y_axis = 0.0f;
	}
};

namespace Resolver
{
	extern std::vector<int64_t> Players;

	void HookProxies();

	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
	void LowerBodyYawTargetProxy(const CRecvProxyData* pData, C_BaseEntity* ent, void* pOut);
}
