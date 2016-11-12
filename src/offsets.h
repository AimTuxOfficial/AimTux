#pragma once

#include <cstdio>
#include "SDK/vector.h"

struct COffsets
{
	struct
	{
		int m_Local;
		int m_aimPunchAngle;
		int m_viewPunchAngle;
		int m_vecViewOffset;
		int m_nTickBase;
		int m_vecVelocity;
		int m_iHealth;
		int m_lifeState;
		int m_fFlags;
		int m_iObserverMode;
		int m_hObserverTarget;
		int m_hViewModel;
		int m_szLastPlaceName;
	} DT_BasePlayer;

	struct
	{
		int m_vecOrigin;
		int m_nRenderMode;
		int m_iTeamNum;
		int m_MoveType;
		int m_Collision;
		int m_bSpotted;
	} DT_BaseEntity;

	struct
	{
		int m_hActiveWeapon;
		int m_hMyWeapons;
	} DT_BaseCombatCharacter;

	struct
	{
		int m_bBombTicking;
		int m_flC4Blow;
		int m_bBombDefused;
		int m_hBombDefuser;
	} DT_PlantedC4;

	struct
	{
		int m_iShotsFired;
		int m_ArmorValue;
		int m_bIsScoped;
		int m_bGunGameImmunity;
		int m_bHasHelmet;
		int m_flFlashMaxAlpha;
	} DT_CSPlayer;

	struct
	{
		int m_iItemDefinitionIndex;
		int m_iItemIDHigh;
		int m_iAccountID;
		int m_iEntityQuality;
		int m_szCustomName;
		int m_nFallbackPaintKit;
		int m_nFallbackSeed;
		int m_flFallbackWear;
		int m_nFallbackStatTrak;
	} DT_BaseAttributableItem;

	struct
	{
		int m_nModelIndex;
		int m_hWeapon;
		int m_hOwner;
	} DT_BaseViewModel;

	struct
	{
		int m_fAccuracyPenalty;
	} DT_WeaponCSBase;

	struct
	{
		int m_flNextPrimaryAttack;
		int m_iClip1;
		int m_bInReload;
	} DT_BaseCombatWeapon;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;