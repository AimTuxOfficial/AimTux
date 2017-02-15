#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"
#include "../modsupport.h"

class RecvPropHook;

extern GetLocalClientFn GetLocalClient;

extern std::unordered_map<std::string, std::string> killIcons;

namespace SkinChanger
{
	extern bool forceFullUpdate;
	extern bool glovesUpdated;
	extern std::unique_ptr<RecvPropHook> sequenceHook;

	void FrameStageNotifySkins(ClientFrameStage_t stage);
	void FrameStageNotifyModels(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
	void FireGameEvent(IGameEvent* event);
	void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);
};

extern RecvVarProxyFn fnSequenceProxyFn;
