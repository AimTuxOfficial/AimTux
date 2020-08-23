#include "bonemaps.h"

#include "../interfaces.h"

static bool boneMapsBuilt = false;
static std::unordered_map<int, std::unordered_map<int,int>> maps;

// Generic Bonemap for unknown models
static const std::unordered_map<int,int> boneMapGeneric =
{
    { BONE_PELVIS, 0 },
    { BONE_HIP, 3 },
    { BONE_LOWER_SPINAL_COLUMN, 4 },
    { BONE_MIDDLE_SPINAL_COLUMN,5 },
    { BONE_UPPER_SPINAL_COLUMN, 6 },
    { BONE_NECK, 7 },
    { BONE_HEAD, 8 },
    { BONE_LEFT_COLLARBONE, BONE_INVALID },
    { BONE_LEFT_SHOULDER, BONE_INVALID },
    { BONE_LEFT_ARMPIT, BONE_INVALID },
    { BONE_LEFT_BICEP, BONE_INVALID },
    { BONE_LEFT_ELBOW, BONE_INVALID },
    { BONE_LEFT_FOREARM, BONE_INVALID },
    { BONE_LEFT_WRIST, BONE_INVALID },
    { BONE_RIGHT_COLLARBONE, BONE_INVALID },
    { BONE_RIGHT_SHOULDER, BONE_INVALID },
    { BONE_RIGHT_ARMPIT, BONE_INVALID },
    { BONE_RIGHT_BICEP, BONE_INVALID },
    { BONE_RIGHT_ELBOW, BONE_INVALID },
    { BONE_RIGHT_FOREARM, BONE_INVALID },
    { BONE_RIGHT_WRIST, BONE_INVALID },
    { BONE_LEFT_BUTTCHEEK, BONE_INVALID },
    { BONE_LEFT_THIGH, BONE_INVALID },
    { BONE_LEFT_KNEE, BONE_INVALID },
    { BONE_LEFT_ANKLE, BONE_INVALID },
    { BONE_LEFT_SOLE, BONE_INVALID },
    { BONE_RIGHT_BUTTCHEEK, BONE_INVALID },
    { BONE_RIGHT_THIGH, BONE_INVALID },
    { BONE_RIGHT_KNEE, BONE_INVALID },
    { BONE_RIGHT_ANKLE, BONE_INVALID },
    { BONE_RIGHT_SOLE, BONE_INVALID }
};

bool BoneMaps::BuildAllBonemaps( ) {
    // Bonemaps do not seem to be valid between maps
    //if( boneMapsBuilt )
    //    return true;

    // Iterate over the Economy Item Schema.
    // Luckily, valve sells the models from other maps as skins.
    for( int i = 0; i < itemSystem->GetItemDefinitionCount(); i++ ){
        CEconItemDefinition* item = itemSystem->GetItemDefinitionByIndex( i );
        if( !item )
            continue;

        if( !strstr( item->m_szItemTypeName, "#Type_CustomPlayer" ) )
            continue;

        int modelIndex = modelInfo->GetModelIndex( item->m_szModel );
        model_t* model = modelInfo->GetModel( modelIndex );
        if( !model )
            continue;

        studiohdr_t *studioModel = modelInfo->GetStudioModel( model );
        if( !studioModel )
            continue;

        // default bonemap - this is the same for all models.
        std::unordered_map<int,int> bonemap = boneMapGeneric;

        // Search for desired bones by name. The models can vary quite a lot, the bone selection here is a good compromise.
        for( int i = 1; i < studioModel->numbones; i++ ){
            mstudiobone_t* pBone = studioModel->pBone( i );
            if( !pBone )
                continue;

            if( !strcmp( pBone->pszName(), "clavicle_L" ) ){
                bonemap[BONE_LEFT_COLLARBONE] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_L" ) ){
                bonemap[BONE_LEFT_SHOULDER] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_L_TWIST" ) ){
                bonemap[BONE_LEFT_ARMPIT] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_L_TWIST1" ) ){
                bonemap[BONE_LEFT_BICEP] = i;
            } else if( !strcmp( pBone->pszName(), "arm_lower_L" ) ) {
                bonemap[BONE_LEFT_ELBOW] = i;
            } else if( !strcmp( pBone->pszName(), "arm_lower_L_TWIST1" ) ){
                bonemap[BONE_LEFT_FOREARM] = i;
            } else if( !strcmp( pBone->pszName(), "hand_L" ) ){
                bonemap[BONE_LEFT_WRIST] = i;
            }

            else if( !strcmp( pBone->pszName(), "clavicle_R" ) ){
                bonemap[BONE_RIGHT_COLLARBONE] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_R" ) ){
                bonemap[BONE_RIGHT_SHOULDER] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_R_TWIST" ) ){
                bonemap[BONE_RIGHT_ARMPIT] = i;
            } else if( !strcmp( pBone->pszName(), "arm_upper_R_TWIST1" ) ){
                bonemap[BONE_RIGHT_BICEP] = i;
            } else if( !strcmp( pBone->pszName(), "arm_lower_R" ) ) {
                bonemap[BONE_RIGHT_ELBOW] = i;
            } else if( !strcmp( pBone->pszName(), "arm_lower_R_TWIST1" ) ){
                bonemap[BONE_RIGHT_FOREARM] = i;
            } else if( !strcmp( pBone->pszName(), "hand_R" ) ){
                bonemap[BONE_RIGHT_WRIST] = i;
            }

            else if( !strcmp( pBone->pszName(), "leg_upper_L" ) ){
                bonemap[BONE_LEFT_BUTTCHEEK] = i;
            } else if( !strcmp( pBone->pszName(), "leg_upper_L_TWIST1" ) ){
                bonemap[BONE_LEFT_THIGH] = i;
            } else if( !strcmp( pBone->pszName(), "leg_lower_L" ) ){
                bonemap[BONE_LEFT_KNEE] = i;
            } else if( !strcmp( pBone->pszName(), "ankle_L" ) ){
                bonemap[BONE_LEFT_ANKLE] = i;
            } else if( !strcmp( pBone->pszName(), "ball_L" ) ){
                bonemap[BONE_LEFT_SOLE] = i;
            }

            else if( !strcmp( pBone->pszName(), "leg_upper_R" ) ){
                bonemap[BONE_RIGHT_BUTTCHEEK] = i;
            } else if( !strcmp( pBone->pszName(), "leg_upper_R_TWIST1" ) ){
                bonemap[BONE_RIGHT_THIGH] = i;
            } else if( !strcmp( pBone->pszName(), "leg_lower_R" ) ){
                bonemap[BONE_RIGHT_KNEE] = i;
            } else if( !strcmp( pBone->pszName(), "ankle_R" ) ){
                bonemap[BONE_RIGHT_ANKLE] = i;
            } else if( !strcmp( pBone->pszName(), "ball_R" ) ){
                bonemap[BONE_RIGHT_SOLE] = i;
            }
        }

        // check if they were all set.
        for( int i = BONE_PELVIS; i < NUM_OF_BONES; i++ ){
            if( bonemap[i] == BONE_INVALID ){
                cvar->ConsoleColorPrintf( ColorRGBA( 200, 200, 5 ), "[%s]Warning! Model (%s) does not have desired bone %d\n", __FUNCTION__, studioModel->name, i );
            }
        }

        // Add this bonemap to the list. The key is the model's checksum.
        maps.insert( { studioModel->checksum, bonemap } );
        cvar->ConsoleDPrintf("Parsed Bonemaps for Model: (%s)\n", studioModel->name);
    }

    boneMapsBuilt = true;
    return true;
}

const std::unordered_map<int,int> * BoneMaps::GetModelTypeBoneMap(C_BasePlayer* player)
{
    model_t *model = player->GetModel();
    studiohdr_t *studioModel;

    if( !model ){
        return &boneMapGeneric;
    }

    studioModel = modelInfo->GetStudioModel( model );
    if( !studioModel ){
        return &boneMapGeneric;
    }

    const std::unordered_map<int,int> * map = &maps[studioModel->checksum];
    if( !map ){
        cvar->ConsoleColorPrintf( ColorRGBA( 225, 100, 5 ), "Couldn't find map for model (%s)\n", studioModel->name );
        return &boneMapGeneric;
    }

    return map;
}