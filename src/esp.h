#ifndef __ESP_H_
#define __ESP_H_

#include "settings.h"
#include "SDK.h"
#include "draw.h"
#include "interfaces.h"
#include "pstring.h"
#include "bone.h"

#define CONV(c) cwConvert(c)

namespace ESP
{
	void Tick ();
	void DrawTracer (C_BasePlayer* localPlayer, C_BaseEntity* entity);
	void DrawPlayerBox (C_BasePlayer* localPlayer, C_BaseEntity* entity);
	void DrawPlayerName (C_BasePlayer* localPlayer, C_BaseEntity* entity, int entityIndex);
	void DrawBones (C_BaseEntity* entity);
}

#endif