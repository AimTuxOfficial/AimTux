#include "hooks.h"

#include "../interfaces.h"
#include "../Utils/bonemaps.h"

typedef void (* LevelInitPostEntityFn)( void );

/* Called when loading a new level */
void Hooks::LevelInitPostEntity( ) {
    BoneMaps::BuildAllBonemaps();

    clientVMT->GetOriginalMethod<LevelInitPostEntityFn>( 6 )();
}