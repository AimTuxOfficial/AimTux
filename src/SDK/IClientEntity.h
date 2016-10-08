#ifndef __ICLIENTENTITY_H
#define __ICLIENTENTITY_H

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
		return GetVirtualFunction<model_t*(*)(void*)>(this, 8)(this);
	}

	bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
	{
		return GetVirtualFunction<bool(*)(void*, matrix3x4_t*, int, int, float)>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
	}
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};

	ClientClass* GetClientClass()
	{
		return GetVirtualFunction<ClientClass*(*)(void*)>(this, 2)(this);
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
		return *(MoveType_t*)((uintptr_t)this + 0x290);
	}

	float* GetFlashMaxAlpha()
	{
		return (float*)((uintptr_t)this + offsets.m_flFlashMaxAlpha);
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

	bool IsBombTicking()
	{
		return (bool)((uintptr_t)this + offsets.m_bBombTicking);
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

	float GetTickBase()
	{
		return *(float*)((uintptr_t)this + offsets.m_nTickBase);
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


	bool isPistol()
	{
		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_DEAGLE:
				return true;
			case WEAPON_ELITE:
				return true;
			case WEAPON_FIVESEVEN:
				return true;
			case WEAPON_GLOCK:
				return true;
			case WEAPON_TEC9:
				return true;
			case WEAPON_HKP2000:
				return true;
			case WEAPON_USP_SILENCER:
				return true;
			case WEAPON_P250:
				return true;
			case WEAPON_CZ75A:
				return true;
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
				return true;
			case WEAPON_AUG:
				return true;
			case WEAPON_FAMAS:
				return true;
			case WEAPON_GALILAR:
				return true;
			case WEAPON_M249:
				return true;
			case WEAPON_M4A1:
				return true;
			case WEAPON_M4A1_SILENCER:
				return true;
			case WEAPON_MAC10:
				return true;
			case WEAPON_P90:
				return true;
			case WEAPON_UMP45:
				return true;
			case WEAPON_BIZON:
				return true;
			case WEAPON_NEGEV:
				return true;
			case WEAPON_MP7:
				return true;
			case WEAPON_MP9:
				return true;
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
				return true;
			case WEAPON_KNIFE_T:
				return true;
			case WEAPON_KNIFE_GUT:
				return true;
			case WEAPON_KNIFE_FLIP:
				return true;
			case WEAPON_KNIFE_BAYONET:
				return true;
			case WEAPON_KNIFE_M9_BAYONET:
				return true;
			case WEAPON_KNIFE_KARAMBIT:
				return true;
			case WEAPON_KNIFE_TACTICAL:
				return true;
			case WEAPON_KNIFE_BUTTERFLY:
				return true;
			case WEAPON_KNIFE_SURVIVAL_BOWIE:
				return true;
			case WEAPON_KNIFE_FALCHION:
				return true;
			case WEAPON_KNIFE_PUSH:
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
};

#endif
