#pragma once

#include "../Utils/pstring.h"
#include "../Utils/util.h"
#include "../interfaces.h"
#include "../settings.h"
#include <algorithm>
#include <iostream>
#include <vector>

namespace Spammer
{
void BeginFrame(float frameTime);
void FireGameEvent(IGameEvent* event);
}
