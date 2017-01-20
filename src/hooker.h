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

#define FORCEFULLUPDATE_SIGNATURE "\x55\x48\x89\xE5\x48\x89\x5D\xF0\x48\x89\xFB\x4C\x89\x65\xF8\x48\x83\xEC\x10\x49\x89\xF4\x83"
#define FORCEFULLUPDATE_MASK "xxxxxxxxxxxxxxxxxxxxxxx"

#define GETCLIENTSTATE_SIGNATURE "\xE8\x00\x00\x00\x00\x5D\x83\xB8"
#define GETCLIENTSTATE_MASK "x????xxx"

#define LINEGOESTHROUGHSMOKE_SIGNATURE "\x55\x40\x0F\xB6\xFF"
#define LINEGOESTHROUGHSMOKE_MASK "xxxxx"

#define INITKEVALUES_SIGNATURE "\x81\x27\x00\x00\x00\xFF\x55\x48\x89\xE5\x5D"
#define INITKEVALUES_MASK "xx???xxxxxx"

#define LOADFROMBUFFER_SIGNATURE "\x55\x48\x89\xE5\x48\x89\x5D\xD8\x48\x89\xD3\x4C\x89\x65\xE0\x4D\x89\xCC"
#define LOADFROMBUFFER_MASK "xxxxxxxxxxxxxxxxxx"

#define GETCSWPNDATA_SIGNATURE "\x55\x48\x89\xE5\x0F\xB7\xBF\xD4\x3A"
#define GETCSWPNDATA_MASK "xxxxxxxxx"

#include <unordered_map>
#include <sys/mman.h>
#include <link.h>
#include "Utils/patternfinder.h"
#include "SDK/SDK.h"
#include "Utils/vmt.h"
#include "Utils/util.h"
#include "glhook.h"

namespace Hooker
{
	std::unordered_map<const char*, uintptr_t> GetProcessLibraries();
	uintptr_t GetLibraryAddress(const char* moduleName);
	void FindInterfaces();
	void InitializeVMHooks();
	void FindIClientMode();
	void FindGlobalVars();
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
	void FindForceFullUpdate();
	void FindLineGoesThroughSmoke();
	void FindInitKeyValues();
	void FindLoadFromBuffer();
	void FindGetCSWpnData();
	void HookSwapWindow();
	void HookPollEvent();
	void FindSDLInput();
}
