#ifndef __CHANTAGCHANGER_H
#define __CHANTAGCHANGER_H

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"

namespace ClanTagChanger
{
	void CreateMove(CUserCmd* cmd);
}

extern SendClanTagFn SendClanTag;

#endif