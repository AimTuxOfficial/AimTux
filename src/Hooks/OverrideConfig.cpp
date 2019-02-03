#include "hooks.h"

#include "../interfaces.h"
#include "../Hacks/materialconfig.h"

typedef void ( *OverrideConfigFn)( void*, MaterialSystem_Config_t *config, bool );

void Hooks::OverrideConfig( void *thisptr, MaterialSystem_Config_t *config, bool forceUpdate ) {

    MaterialConfig::OverrideConfig( config, forceUpdate );

    materialVMT->GetOriginalMethod<OverrideConfigFn>( 21 )( thisptr, config, forceUpdate );
}