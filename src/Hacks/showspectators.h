#pragma once

#include "../SDK/SDK.h"
#include "../Utils/entity.h"
#include "../interfaces.h"
#include "../settings.h"

namespace ShowSpectators
{
std::list<int> GetObservervators(int playerId);
void RenderWindow();
}
