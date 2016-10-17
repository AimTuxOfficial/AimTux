#ifndef __ICLIENTENTITY_H
#define __ICLIENTENTITY_H

#include "vector.h"

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

class ICollideable
{
public:
	virtual void pad0( );
	virtual const Vector& OBBMins( ) const;
	virtual const Vector& OBBMaxs( ) const;
};

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {};
};

class IClientUnknown : public IHandleEntity {};
class IClientRenderable
{
public:
	virtual ~IClientRenderable() {};

	model_t* GetModel()
	{
		typedef model_t* (* oGetModel)(void*);
		getvfunc<oGetModel>(this, 8)(this);
	}

	bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
	{
		typedef bool (* oSetupBones)(void*, matrix3x4_t*, int, int, float);
		getvfunc<oSetupBones>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
	}
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};

	ClientClass* GetClientClass()
	{
		typedef int (* oGetClientClass)(void*);
		getvfunc<oGetClientClass>(this, 2)(this);
	}
};

class IClientThinkable
{
public:
	virtual ~IClientThinkable() {};
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual ~IClientEntity() {};
};

class C_BaseEntity : public IClientEntity
{
public:
	int* GetModelIndex()
	{
		return (int*)((uintptr_t)this + offsets.m_nModelIndex);
	}

	int GetHealth()
	{
		return *(int*)((uintptr_t)this + offsets.m_iHealth);
	}

	int GetTeam()
	{
		return *(int*)((uintptr_t)this + offsets.m_iTeamNum);
	}

	bool GetDormant()
	{
		return *(bool*)((uintptr_t)this + 0x121);
	}

	unsigned char GetLifeState()
	{
		return *(unsigned char*)((uintptr_t)this + offsets.m_lifeState);
	}

	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + offsets.m_hMyWeapons);
	}

	void* GetViewModel()
	{
		return (void*)((uintptr_t)this + offsets.m_hViewModel);
	}

	Vector GetVecOrigin()
	{
		return *(Vector*)((uintptr_t)this + offsets.m_vecOrigin);
	}

	Vector GetVecViewOffset()
	{
		return *(Vector*)((uintptr_t)this + offsets.m_vecViewOffset);
	}

	Vector GetEyePosition()
	{
		return this->GetVecOrigin() + this->GetVecViewOffset();
	}

	int GetFlags()
	{
		return *(int*)((uintptr_t)this + offsets.m_fFlags);
	}

	MoveType_t GetMoveType()
	{
		return *(MoveType_t*)((uintptr_t)this + offsets.m_MoveType);
	}

	float* GetFlashMaxAlpha()
	{
		return (float*)((uintptr_t)this + offsets.m_flFlashMaxAlpha);
	}

	bool IsScoped()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bIsScoped);
	}

	inline Vector GetBonePosition(int boneIndex)
	{
		matrix3x4_t BoneMatrix[MAXSTUDIOBONES];

		if (!this->SetupBones(BoneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
			return this->GetVecOrigin();

		matrix3x4_t hitbox = BoneMatrix[boneIndex];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	int* GetObserverMode()
	{
		return (int*)((uintptr_t)this + offsets.m_iObserverMode);
	}

	void* GetObserverTarget()
	{
		return (void*)((uintptr_t)this + offsets.m_hObserverTarget);
	}

	ICollideable* GetCollideable ()
	{
		return (ICollideable*)((uintptr_t)this + offsets.m_Collision);
	}
};

/* generic game classes */
class C_BasePlayer : public C_BaseEntity
{
public:
	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + offsets.m_hMyWeapons);
	}

	QAngle GetAimPunchAngle()
	{
		return *(QAngle*)((uintptr_t)this + offsets.m_aimPunchAngle);
	}

	void* GetActiveWeapon()
	{
		return (void*)((uintptr_t)this + offsets.m_hActiveWeapon);
	}

	unsigned int GetTickBase()
	{
		return *(unsigned int*)((uintptr_t)this + offsets.m_nTickBase);
	}

	int GetShotsFired()
	{
		return *(int*)((uintptr_t)this + offsets.m_iShotsFired);
	}
};

class C_BasePlantedC4 : public C_BaseEntity
{
public:
	bool IsBombTicking()
	{
		return (bool)((uintptr_t)this + offsets.m_bBombTicking);
	}

	float GetBombTime()
	{
		return *(float*)((uintptr_t)this + offsets.m_flC4Blow);
	}

	bool IsBombDefused()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bBombDefused);
	}

	int GetBombDefuser()
	{
		return *(int*)((uintptr_t)this + offsets.m_hBombDefuser);
	}
};

class C_BaseAttributableItem : public C_BaseEntity
{
public:
	int* GetItemDefinitionIndex()
	{
		return (int*)((uintptr_t)this + offsets.m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		return (int*)((uintptr_t)this + offsets.m_iItemIDHigh);
	}

	int* GetEntityQuality()
	{
		return (int*)((uintptr_t)this + offsets.m_iEntityQuality);
	}

	char* GetCustomName()
	{
		return (char*)((uintptr_t)this + offsets.m_szCustomName);
	}

	int* GetFallbackPaintKit()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackPaintKit);
	}

	int* GetFallbackSeed()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackSeed);
	}

	float* GetFallbackWear()
	{
		return (float*)((uintptr_t)this + offsets.m_flFallbackWear);
	}

	int* GetFallbackStatTrak()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackStatTrak);
	}

	int* GetAccountID()
	{
		return (int*)((uintptr_t)this + offsets.m_iAccountID);
	}

	bool isPistol()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_DEAGLE:
			case WEAPON_ELITE:
			case WEAPON_FIVESEVEN:
			case WEAPON_GLOCK:
			case WEAPON_TEC9:
			case WEAPON_HKP2000:
			case WEAPON_USP_SILENCER:
			case WEAPON_P250:
			case WEAPON_CZ75A:
			case WEAPON_REVOLVER:
				return true;
			default:
				return false;
		}
	}

	bool isAutomatic()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_AK47:
			case WEAPON_AUG:
			case WEAPON_FAMAS:
			case WEAPON_GALILAR:
			case WEAPON_M249:
			case WEAPON_M4A1:
			case WEAPON_M4A1_SILENCER:
			case WEAPON_MAC10:
			case WEAPON_P90:
			case WEAPON_UMP45:
			case WEAPON_BIZON:
			case WEAPON_NEGEV:
			case WEAPON_MP7:
			case WEAPON_MP9:
			case WEAPON_SG556:
				return true;
			default:
				return false;
		}
	}

	bool isKnife()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_KNIFE:
			case WEAPON_KNIFE_T:
			case WEAPON_KNIFE_GUT:
			case WEAPON_KNIFE_FLIP:
			case WEAPON_KNIFE_BAYONET:
			case WEAPON_KNIFE_M9_BAYONET:
			case WEAPON_KNIFE_KARAMBIT:
			case WEAPON_KNIFE_TACTICAL:
			case WEAPON_KNIFE_BUTTERFLY:
			case WEAPON_KNIFE_SURVIVAL_BOWIE:
			case WEAPON_KNIFE_FALCHION:
			case WEAPON_KNIFE_PUSH:
				return true;
			default:
				return false;
		}
	}
	
	bool isGrenade()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_SMOKEGRENADE:
			case WEAPON_HEGRENADE:
			case WEAPON_INCGRENADE:
			case WEAPON_FLASHBANG:
			case WEAPON_MOLOTOV:
			case WEAPON_DECOY:
				return true;
			default:
				return false;
		}
	}

	bool CanScope()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_AUG:
			case WEAPON_AWP:
			case WEAPON_G3SG1:
			case WEAPON_SCAR20:
			case WEAPON_SG556:
			case WEAPON_SSG08:
				return true;
			default:
				return false;
		}
	}
};

class C_BaseViewModel: public C_BaseEntity {
public:
	int GetWeapon()
	{
		return *(int*)((uintptr_t)this + offsets.m_hWeapon);
	}
};

class C_BaseCombatWeapon: public C_BaseAttributableItem
{
public:
	unsigned int GetAmmo()
	{
		return *(unsigned int*)((uintptr_t)this + offsets.m_iClip1);
	}

	bool IsReloading()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bInReload);
	}

	float GetNextPrimaryAttack()
	{
		return *(float*)((uintptr_t)this + offsets.m_flNextPrimaryAttack);
	}

	float GetAccuracyPenalty()
	{
		return *(float*)((uintptr_t)this + offsets.m_fAccuracyPenalty);
	}
};

#endif
