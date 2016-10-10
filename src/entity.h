#ifndef __ENTITY_H
#define __ENTITY_H

#include <list>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Entity
{
	bool IsVisible(C_BasePlayer *pLocal, C_BaseEntity *pEntity, int bone);
	std::list<std::string> GetObservervators(C_BaseEntity* entity);
}

#endif
