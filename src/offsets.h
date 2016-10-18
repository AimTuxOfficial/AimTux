#ifndef __OFFSETS_H_
#define __OFFSETS_H_

#include <cstdio>
#include "SDK/vector.h"

struct COffsets
{
	int m_bDormant;
	int m_hViewModel;
	int m_iHealth;
	int m_iTeamNum;
	int m_lifeState;
	int m_fFlags;
	int m_hMyWeapons;
	int m_ArmorValue;
	int m_bHasHelmet;
	
	int m_nTickBase;
	int m_iObserverMode;
	int m_hObserverTarget;

	int m_flFlashMaxAlpha;
	int m_bIsScoped;
	int m_iShotsFired;
	int m_Collision;
	int m_nRenderMode;
	int m_MoveType;

	int m_bBombDefused;
	int m_hBombDefuser;
	int m_bBombTicking;
	int m_flC4Blow;

	int m_Local;
	int m_aimPunchAngle;
	
	int m_vecOrigin;
	int m_vecViewOffset;
	
	int m_flFallbackWear;
	int m_iEntityQuality;
	int m_iItemDefinitionIndex;
	int m_iItemIDHigh;
	int m_nFallbackPaintKit;
	int m_nFallbackSeed;
	int m_nFallbackStatTrak;
	int m_iAccountID;
	int m_szCustomName;

	int m_iClip1;
	int m_flNextPrimaryAttack;
	int m_fAccuracyPenalty;
	int m_bInReload;

	int m_hActiveWeapon;
	int m_nModelIndex;
	int m_hWeapon;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;

#endif
