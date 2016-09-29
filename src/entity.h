#ifndef __ENTITY_H
#define __ENTITY_H

#include "SDK.h"
#include "bone.h"
#include "interfaces.h"

namespace Entity
{
	bool IsVisible(C_BasePlayer *pLocal, C_BaseEntity *pEntity, int bone);
}

#endif
