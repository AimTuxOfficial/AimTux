#ifndef __HOOKER_H_
#define __HOOKER_H_

#define CCSMODEMANAGER_INIT_SIGNATURE "\x48\x8D\x05\x00\x00\x00\x00\x48\x89\xE5\x48\x89\x05\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5D\x48"
#define CCSMODEMANAGER_INIT_MASK "xxx????xxxxxx????x????xx"

#define MSGFUNC_SERVERRANKREVEALALL_SIGNATURE "\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x08\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x8B\x10\x48\x89\xC7\xFF\x52\x28"
#define MSGFUNC_SERVERRANKREVEALALL_MASK "xxxxxxxxxxxxx????xx?????xxxxxxxxx"

#include <link.h>
#include "patternfinder.h"
#include "SDK/SDK.h"
#include "vmt.h"

namespace Hooker
{
	void HookInterfaces();
	void HookVMethods();
	void HookIClientMode();
	void HookGlobalVars();
	void HookRankReveal();
}

#endif