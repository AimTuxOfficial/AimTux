#ifndef __HOOKER_H_
#define __HOOKER_H_

#define CCSMODEMANAGER_INIT_SIGNATURE "\x48\x8D\x05\x00\x00\x00\x00\x48\x89\xE5\x48\x89\x05\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5D\x48"
#define CCSMODEMANAGER_INIT_MASK "xxx????xxxxxx????x????xx"

#include <link.h>
#include "patternfinder.h"
#include "SDK.h"
#include "vmt.h"

namespace Hooker
{
	void HookInterfaces ();
	void HookVMethods ();
	void HookIClientMode ();
}

#endif