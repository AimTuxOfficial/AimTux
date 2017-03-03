#pragma once

#define GLOWOBJECT_SIGNATURE "\xE8\x00\x00\x00\x00\x48\x8B\x3D\x00\x00\x00\x00\xBE\x01\x00\x00\x00\xC7"
#define GLOWOBJECT_MASK "x????xxx????xxxxxx"

#define MSGFUNC_SERVERRANKREVEALALL_SIGNATURE "\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x08\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x8B\x10\x48\x89\xC7\xFF\x52\x28"
#define MSGFUNC_SERVERRANKREVEALALL_MASK "xxxxxxxxxxxxx????xx?????xxxxxxxxx"

#define SENDCLANTAG_SIGNATURE "\x55\x48\x89\xE5\x48\x89\x5D\xE8\x4C\x89\x65\xF0\x49\x89\xFC\xBF\x48\x00\x00\x00\x4C\x89\x6D\xF8\x48\x83\xEC\x20\x49"
#define SENDCLANTAG_MASK "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

#define VIEWRENDER_SIGNATURE "\xB8\xFF\xFF\x7F\x7F\x31\xD2\x55\x89\x05\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00"
#define VIEWRENDER_MASK "xxxxxxxxxx????xxx????"

#define BSENDPACKET_SIGNATURE "\x41\xBD\x01\x00\x00\x00\xE9\x2A\xFE"
#define BSENDPACKET_MASK "xxx???xxx"

#define PREDICTION_RANDOM_SEED_SIGNATURE "\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x11\x45\xDC\xF3"
#define PREDICTION_RANDOM_SEED_MASK "xxx????xxxxxx"

#define CLIENT_MOVEHELPER_SIGNATURE "\x00\x48\x89\x3D\x00\x00\x00\x00\xC3"
#define CLIENT_MOVEHELPER_MASK "xxxx????x"

#define CLIENT_MOVEDATA_SIGNATURE "\x48\x8B\x0D\x00\x00\x00\x00\x4C\x89\xF2"
#define CLIENT_MOVEDATA_MASK "xxx????xxx"

#define ISREADY_CALLBACK_SIGNATURE "\x48\x83\x3D\x00\x00\x00\x00\x00\x55\x48\x89\xE5\x41"
#define ISREADY_CALLBACK_MASK "xxx????xxxxxx"

#define GETSDLMGR_SIGNATURE "\x55\x48\x89\xE5\x53\x48\x83\xEC\x18"
#define GETSDLMGR_MASK "xxxxxxxxx"

#define PLAYERRESOURCES_SIGNATURE "\x48\x8B\x05\x00\x00\x00\x00\x55\x48\x89\xE5\x48\x85\xC0\x74\x10\x48"
#define PLAYERRESOURCES_MASK "xxx????xxxxxxxxxx"

#define GAMERULES_SIGNATURE "\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x00\x0F\x84"
#define GAMERULES_MASK "xxx????xx?xx"

#define CMATSYSTEMSURFACE_STARTDRAWING_SIGNATURE "\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x28\x80"
#define CMATSYSTEMSURFACE_STARTDRAWING_MASK "xxxxxxxxxxxxx"

#define CMATSYSTEMSURFACE_FINISHDRAWING_SIGNATURE "\x55\x31\xFF\x48\x89"
#define CMATSYSTEMSURFACE_FINISHDRAWING_MASK "xxxxx"

#define LINEGOESTHROUGHSMOKE_SIGNATURE "\x55\x40\x0F\xB6\xFF"
#define LINEGOESTHROUGHSMOKE_MASK "xxxxx"

#define INITKEYVALUES_SIGNATURE "\x81\x27\x00\x00\x00\xFF\x55\x48\x89\xE5\x5D"
#define INITKEYVALUES_MASK "xx???xxxxxx"

#define LOADFROMBUFFER_SIGNATURE "\x55\x48\x89\xE5\x48\x89\x5D\xD8\x48\x89\xD3\x4C\x89\x65\xE0\x4D\x89\xCC"
#define LOADFROMBUFFER_MASK "xxxxxxxxxxxxxxxxxx"

#define OVERRIDEPOSTPROCESSINGDISABLE_SIGNATURE "\x80\x3D\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x85\xC9"
#define OVERRIDEPOSTPROCESSINGDISABLE_MASK "xx????xxx????xx"

#define CROSSHAIRWEAPONTYPECHECK_SIGNATURE "\x83\xF8\x05\x0F\x84\x00\x00\x00\x00\x49\x8B\x07"
#define CROSSHAIRWEAPONTYPECHECK_MASK "xxxxx????xxx"

#define CAMTHINK_SVCHEATSCHECK_SIGNATURE "\x74\x00\x49\x83\x00\x00\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x49\x8B"
#define CAMTHINK_SVCHEATSCHECK_MASK "x?xx??????xxx????xx"

#include <memory>
#include <unordered_map>
#include <sys/mman.h>
#include <link.h>
#include "Utils/patternfinder.h"
#include "Utils/recvproxyhook.h"
#include "SDK/SDK.h"
#include "Utils/vmt.h"
#include "Utils/util.h"
#include "glhook.h"
#include "interfaces.h"

struct dlinfo_t
{
	const char* library = nullptr;
	uintptr_t address = 0;
	size_t size = 0;
};

namespace Hooker
{
	bool GetLibraryInformation(const char* library, uintptr_t* address, size_t* size);
	void InitializeVMHooks();
	bool HookRecvProp(const char* className, const char* propertyName, std::unique_ptr<RecvPropHook>& recvPropHook);
	void FindIClientMode();
	void FindGlobalVars();
	void FindCInput();
	void FindGlowManager();
	void FindPlayerResource();
	void FindGameRules();
	void FindRankReveal();
	void FindSendClanTag();
	void FindViewRender();
	void FindSendPacket();
	void FindPrediction();
	void FindIsReadyCallback();
	void FindSurfaceDrawing();
	void FindGetLocalClient();
	void FindLineGoesThroughSmoke();
	void FindInitKeyValues();
	void FindLoadFromBuffer();
	void FindVstdlibFunctions();
	void FindOverridePostProcessingDisable();
	void FindCrosshairWeaponTypeCheck();
	void FindCamThinkSvCheatsCheck();
	void HookSwapWindow();
	void HookPollEvent();
	void FindSDLInput();
}
