#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"
#include "../modsupport.h"

extern ForceFullUpdateFn ForceFullUpdate;
extern GetClientStateFn GetClientState;

namespace SkinChanger
{
	extern bool ForceFullUpdate;

	void FrameStageNotify(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
	void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);
	void HookCBaseViewModel();
	void UnhookCBaseViewModel();
};

extern RecvVarProxyFn fnSequenceProxyFn;