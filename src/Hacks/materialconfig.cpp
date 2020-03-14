#include "materialconfig.h"

#include "../settings.h"

MaterialSystem_Config_t MaterialConfig::backupConfig = {};

void MaterialConfig::OverrideConfig( MaterialSystem_Config_t *gameConfig, bool forceUpdate ) {
    static bool bFirst = true;
    if ( bFirst ) {
        MaterialConfig::backupConfig = *gameConfig; // backup to restore to
        Settings::MaterialConfig::config = *gameConfig; // starting point for changes
        bFirst = false;
    }

    if ( !Settings::MaterialConfig::enabled ) {
        return;
    }

    *gameConfig = Settings::MaterialConfig::config;
}