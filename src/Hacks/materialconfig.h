#pragma once

#include "../SDK/Materialsystem_config.h"

namespace MaterialConfig
{
    extern MaterialSystem_Config_t backupConfig;

    void OverrideConfig( MaterialSystem_Config_t* gameConfig, bool forceUpdate );
}