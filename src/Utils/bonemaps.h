#pragma once

#include <unordered_map>
#include "../SDK/IClientEntity.h" // cbaseplayer

namespace BoneMaps
{
    bool BuildAllBonemaps();
    const std::unordered_map<int,int> * GetModelTypeBoneMap(C_BasePlayer* player);
}