#pragma once

#include <memory>
#include <unordered_map>

#include "../SDK/definitions.h"
#include "../SDK/IGameEvent.h"

#include "../Utils/recvproxyhook.h"

extern GetLocalClientFn GetLocalClient;

extern std::unordered_map<std::string, std::string> killIcons;

namespace SkinChanger
{
	extern bool forceFullUpdate;
	extern bool glovesUpdated;
	extern std::unique_ptr<RecvPropHook> sequenceHook;

	//Hooks
	void FrameStageNotifySkins(ClientFrameStage_t stage);
	void FrameStageNotifyModels(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
	void FireGameEvent(IGameEvent* event);

	void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);
};

extern RecvVarProxyFn fnSequenceProxyFn;
