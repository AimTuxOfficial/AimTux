#pragma once

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
		return getvfunc<oGetModel>(this, 8)(this);
	}

	bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
	{
		typedef bool (* oSetupBones)(void*, matrix3x4_t*, int, int, float);
		return getvfunc<oSetupBones>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
	}
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};

	ClientClass* GetClientClass()
	{
		typedef ClientClass* (* oGetClientClass)(void*);
		return getvfunc<oGetClientClass>(this, 2)(this);
	}

	bool GetDormant()
	{
		typedef bool (* oGetDormant)(void*);
		return getvfunc<oGetDormant>(this, 9)(this);
	}

	int GetIndex()
	{
		typedef int (* oGetIndex)(void*);
		return getvfunc<oGetIndex>(this, 10)(this);
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
		return (int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_nModelIndex);
	}

	int GetTeam()
	{
		return *(int*)((uintptr_t)this + offsets.DT_BaseEntity.m_iTeamNum);
	}

	Vector GetVecOrigin()
	{
		return *(Vector*)((uintptr_t)this + offsets.DT_BaseEntity.m_vecOrigin);
	}

	MoveType_t GetMoveType()
	{
		return *(MoveType_t*)((uintptr_t)this + offsets.DT_BaseEntity.m_MoveType);
	}

	ICollideable* GetCollideable()
	{
		return (ICollideable*)((uintptr_t)this + offsets.DT_BaseEntity.m_Collision);
	}

	bool* GetSpotted()
	{
		return (bool*)((uintptr_t)this + offsets.DT_BaseEntity.m_bSpotted);
	}
};

/* generic game classes */
class C_BasePlayer : public C_BaseEntity
{
public:
	QAngle* GetViewPunchAngle()
	{
		return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_viewPunchAngle);
	}

	QAngle* GetAimPunchAngle()
	{
		return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_aimPunchAngle);
	}

	Vector GetVecViewOffset()
	{
		return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecViewOffset);
	}

	unsigned int GetTickBase()
	{
		return *(unsigned int*)((uintptr_t)this + offsets.DT_BasePlayer.m_nTickBase);
	}

	Vector GetVelocity()
	{
		return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecVelocity);
	}

	int GetHealth()
	{
		return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iHealth);
	}

	unsigned char GetLifeState()
	{
		return *(unsigned char*)((uintptr_t)this + offsets.DT_BasePlayer.m_lifeState);
	}

	int GetFlags()
	{
		return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_fFlags);
	}

	int* GetObserverMode()
	{
		return (int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iObserverMode);
	}

	void* GetObserverTarget()
	{
		return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hObserverTarget);
	}

	void* GetViewModel()
	{
		return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hViewModel);
	}

	const char* GetLastPlaceName()
	{
		return (const char*)((uintptr_t)this + offsets.DT_BasePlayer.m_szLastPlaceName);
	}

	int GetShotsFired()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_iShotsFired);
	}

	QAngle* GetEyeAngles()
	{
		return (QAngle*)((uintptr_t)this + offsets.DT_CSPlayer.m_angEyeAngles[0]);
	}

	int GetMoney()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_iAccount);
	}

	int GetHits()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_totalHitsOnServer);
	}

	int GetArmor()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_ArmorValue);
	}

	int HasDefuser()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasDefuser);
	}

	bool IsDefusing()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsDefusing);
	}

	bool IsGrabbingHostage()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsGrabbingHostage);
	}

	bool IsScoped()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsScoped);
	}

	bool GetImmune()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bGunGameImmunity);
	}

	bool IsRescuing()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsRescuing);
	}

	int HasHelmet()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasHelmet);
	}

	float GetFlashBangTime()
	{
		return *(float*)((uintptr_t)this + 0xABE4);
	}

	float GetFlashDuration()
	{
		return *(float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashDuration);
	}

	float* GetFlashMaxAlpha()
	{
		return (float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashMaxAlpha);
	}

	float* GetLowerBodyYawTarget()
	{
		return (float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flLowerBodyYawTarget);
	}

	void* GetActiveWeapon()
	{
		return (void*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hActiveWeapon);
	}

	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hMyWeapons);
	}

	bool GetAlive()
	{
		return this->GetHealth() > 0 && this->GetLifeState() == LIFE_ALIVE;
	}

	Vector GetEyePosition()
	{
		return this->GetVecOrigin() + this->GetVecViewOffset();
	}

	inline Vector GetBonePosition(int boneIndex)
	{
		matrix3x4_t BoneMatrix[MAXSTUDIOBONES];

		if (!this->SetupBones(BoneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
			return this->GetVecOrigin();

		matrix3x4_t hitbox = BoneMatrix[boneIndex];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}
};

class C_PlantedC4 : public C_BaseEntity
{
public:
	bool IsBombTicking()
	{
		return (bool)((uintptr_t)this + offsets.DT_PlantedC4.m_bBombTicking);
	}

	float GetBombTime()
	{
		return *(float*)((uintptr_t)this + offsets.DT_PlantedC4.m_flC4Blow);
	}

	bool IsBombDefused()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_PlantedC4.m_bBombDefused);
	}

	int GetBombDefuser()
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlantedC4.m_hBombDefuser);
	}
};

class C_BaseAttributableItem : public C_BaseEntity
{
public:
	int* GetItemDefinitionIndex()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemIDHigh);
	}

	int* GetEntityQuality()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iEntityQuality);
	}

	char* GetCustomName()
	{
		return (char*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_szCustomName);
	}

	int* GetFallbackPaintKit()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackPaintKit);
	}

	int* GetFallbackSeed()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackSeed);
	}

	float* GetFallbackWear()
	{
		return (float*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_flFallbackWear);
	}

	int* GetFallbackStatTrak()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackStatTrak);
	}

	int* GetAccountID()
	{
		return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iAccountID);
	}
	
	float GetInaccuracy()
	{
		typedef float (* oGetIndex)(void*);
		return getvfunc<oGetIndex>(this, 478)(this);
	}
	
	float GetSpread()
	{
		typedef float (* oGetIndex)(void*);
		return getvfunc<oGetIndex>(this, 479)(this);
	}

	bool IsPistol()
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

	bool IsAutomatic()
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

	bool IsKnife()
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

	bool IsGrenade()
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

	bool IsBomb()
	{
		return *this->GetItemDefinitionIndex() == WEAPON_C4;
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
		return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hWeapon);
	}

	int GetOwner()
	{
		return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hOwner);
	}
};

class C_BaseCombatWeapon: public C_BaseAttributableItem
{
public:
	int GetOwner()
	{
		return *(int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_hOwner);
	}

	unsigned int GetAmmo()
	{
		return *(unsigned int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_iClip1);
	}

	float GetNextPrimaryAttack()
	{
		return *(float*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack);
	}

	bool GetInReload()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_bInReload);
	}

	float GetAccuracyPenalty()
	{
		return *(float*)((uintptr_t)this + offsets.DT_WeaponCSBase.m_fAccuracyPenalty);
	}

	WeaponInfo_t GetWeaponData()
	{
		WeaponInfo_t weaponInfo;

		switch (*this->GetItemDefinitionIndex())
		{
			case WEAPON_TASER:
				weaponInfo.m_flWeaponArmorRatio = 2;
				weaponInfo.m_flPenetration = 0;
				weaponInfo.m_iDamage = 500;
				weaponInfo.m_flRange = 190;
				weaponInfo.m_flRangeModifier = 0.0049;
				break;
			case WEAPON_XM1014:
				weaponInfo.m_flWeaponArmorRatio = 1.6;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 20;
				weaponInfo.m_flRange = 3000;
				weaponInfo.m_flRangeModifier = 0.70;
				break;
			case WEAPON_AWP:
				weaponInfo.m_flWeaponArmorRatio = 1.95;
				weaponInfo.m_flPenetration = 2.5;
				weaponInfo.m_iDamage = 115;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_FLASHBANG:
				weaponInfo.m_flWeaponArmorRatio = 1;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 50;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_MAG7:
				weaponInfo.m_flWeaponArmorRatio = 1.5;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 30;
				weaponInfo.m_flRange = 1400;
				weaponInfo.m_flRangeModifier = 0.45;
				break;
			case WEAPON_FAMAS:
				weaponInfo.m_flWeaponArmorRatio = 1.4;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 30;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.96;
				break;
			case WEAPON_NEGEV:
				weaponInfo.m_flWeaponArmorRatio = 1.5;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 35;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.97;
				break;
			case WEAPON_M4A1:
			case WEAPON_M4A1_SILENCER:
				weaponInfo.m_flWeaponArmorRatio = 1.4;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 33;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.97;
				break;
			case WEAPON_UMP45:
				weaponInfo.m_flWeaponArmorRatio = 1.3;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 35;
				weaponInfo.m_flRange = 3700;
				weaponInfo.m_flRangeModifier = 0.85;
				break;
			case WEAPON_DEAGLE:
			case WEAPON_REVOLVER:
				weaponInfo.m_flWeaponArmorRatio = 1.864;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 63;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.81;
				break;
			case WEAPON_SSG08:
				weaponInfo.m_flWeaponArmorRatio = 1.7;
				weaponInfo.m_flPenetration = 2.5;
				weaponInfo.m_iDamage = 88;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_DECOY:
				weaponInfo.m_flWeaponArmorRatio = 1;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 50;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_P90:
				weaponInfo.m_flWeaponArmorRatio = 1.38;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 26;
				weaponInfo.m_flRange = 3700;
				weaponInfo.m_flRangeModifier = 0.86;
				break;
			case WEAPON_MOLOTOV:
				weaponInfo.m_flWeaponArmorRatio = 1.8;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 40;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_MP7:
				weaponInfo.m_flWeaponArmorRatio = 1.25;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 29;
				weaponInfo.m_flRange = 3600;
				weaponInfo.m_flRangeModifier = 0.85;
				break;
			case WEAPON_BIZON:
				weaponInfo.m_flWeaponArmorRatio = 1.15;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 27;
				weaponInfo.m_flRange = 3600;
				weaponInfo.m_flRangeModifier = 0.80;
				break;
			case WEAPON_MAC10:
				weaponInfo.m_flWeaponArmorRatio = 1.15;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 29;
				weaponInfo.m_flRange = 3600;
				weaponInfo.m_flRangeModifier = 0.80;
				break;
			case WEAPON_AK47:
				weaponInfo.m_flWeaponArmorRatio = 1.55;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 36;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_KNIFE:
				weaponInfo.m_flWeaponArmorRatio = 1.7;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 50;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_FIVESEVEN:
				weaponInfo.m_flWeaponArmorRatio = 1.823;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 32;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.81;
				break;
			case WEAPON_HKP2000:
			case WEAPON_USP_SILENCER:
				weaponInfo.m_flWeaponArmorRatio = 1.01;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 35;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.91;
				break;
			case WEAPON_SMOKEGRENADE:
				weaponInfo.m_flWeaponArmorRatio = 1.0;
				weaponInfo.m_flPenetration = 0;
				weaponInfo.m_iDamage = 50;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_M249:
				weaponInfo.m_flWeaponArmorRatio = 1.6;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 32;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.97;
				break;
			case WEAPON_ELITE:
				weaponInfo.m_flWeaponArmorRatio = 1.15;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 38;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.79;
				break;
			case WEAPON_INCGRENADE:
				weaponInfo.m_flWeaponArmorRatio = 1.475;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 40;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_GLOCK:
				weaponInfo.m_flWeaponArmorRatio = 0.94;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 28;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.9;
				break;
			case WEAPON_C4:
				weaponInfo.m_flWeaponArmorRatio = 1.0;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 50;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_TEC9:
				weaponInfo.m_flWeaponArmorRatio = 1.812;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 33;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.79;
				break;
			case WEAPON_SAWEDOFF:
				weaponInfo.m_flWeaponArmorRatio = 1.5;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 32;
				weaponInfo.m_flRange = 650;
				weaponInfo.m_flRangeModifier = 0.45;
				break;
			case WEAPON_SCAR20:
				weaponInfo.m_flWeaponArmorRatio = 1.65;
				weaponInfo.m_flPenetration = 2.5;
				weaponInfo.m_iDamage = 80;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_SG556:
				weaponInfo.m_flWeaponArmorRatio = 2.0;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 30;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_NOVA:
				weaponInfo.m_flWeaponArmorRatio = 1.0;
				weaponInfo.m_flPenetration = 0;
				weaponInfo.m_iDamage = 26;
				weaponInfo.m_flRange = 3000;
				weaponInfo.m_flRangeModifier = 0.70;
				break;
			case WEAPON_GALILAR:
				weaponInfo.m_flWeaponArmorRatio = 1.55;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 30;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_MP9:
				weaponInfo.m_flWeaponArmorRatio = 1.20;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 26;
				weaponInfo.m_flRange = 3600;
				weaponInfo.m_flRangeModifier = 0.87;
				break;
			case WEAPON_AUG:
				weaponInfo.m_flWeaponArmorRatio = 1.8;
				weaponInfo.m_flPenetration = 2;
				weaponInfo.m_iDamage = 28;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
			case WEAPON_HEGRENADE:
				weaponInfo.m_flWeaponArmorRatio = 1.2;
				weaponInfo.m_iDamage = 99;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_flRange = 350;
				weaponInfo.m_flRangeModifier = 0.99;
				break;
			case WEAPON_P250:
			case WEAPON_CZ75A:
				weaponInfo.m_flWeaponArmorRatio = 1.553;
				weaponInfo.m_flPenetration = 1;
				weaponInfo.m_iDamage = 35;
				weaponInfo.m_flRange = 4096;
				weaponInfo.m_flRangeModifier = 0.85;
				break;
			case WEAPON_G3SG1:
				weaponInfo.m_flWeaponArmorRatio = 1.65;
				weaponInfo.m_flPenetration = 2.5;
				weaponInfo.m_iDamage = 80;
				weaponInfo.m_flRange = 8192;
				weaponInfo.m_flRangeModifier = 0.98;
				break;
		}

		return weaponInfo;
	}
};

class C_WeaponC4 : C_BaseCombatWeapon
{
public:
	bool GetStartedArming()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_WeaponC4.m_bStartedArming);
	}
};

class C_Chicken : C_BaseEntity
{
public:
	bool* GetShouldGlow()
	{
		return (bool*)((uintptr_t)this + offsets.DT_DynamicProp.m_bShouldGlow);
	}
};

class C_BaseCSGrenade : C_BaseCombatWeapon
{
public:
	bool IsHeldByPlayer()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_bIsHeldByPlayer);
	}

	bool GetPinPulled()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_bPinPulled);
	}

	float GetThrowTime()
	{
		return *(float*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_fThrowTime);
	}

	float GetThrowStrength()
	{
		return *(float*)((uintptr_t)this + offsets.DT_BaseCSGrenade.m_flThrowStrength);
	}
};
