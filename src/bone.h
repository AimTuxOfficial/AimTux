#ifndef __BONE_H_
#define __BONE_H_

#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100

#include "SDK.h"

inline Vector GetBone (C_BaseEntity* entity, int boneIndex)
{
	matrix3x4_t BoneMatrix[MAXSTUDIOBONES];
	
	if (!entity->SetupBones(BoneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
		return entity->GetVecOrigin();
	
	matrix3x4_t hitbox = BoneMatrix[boneIndex];
	
	return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
}

#endif