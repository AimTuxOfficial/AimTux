#pragma once

#include <cstdint>
#include <elf.h> // you will need this to check flags for PF_R/PF_W/PF_X

namespace MemoryProtection
{
    unsigned int GetProtectionFlags( uintptr_t address );
}