#ifndef __OFFSETS_H_
#define __OFFSETS_H_

#include <cstdio>
#include "vector.h"

struct COffsets
{
	int m_bDormant = 0x112;
	int m_hViewModel;
	int m_iHealth;
	int m_iTeamNum;
	int m_lifeState;

	int m_hMyWeapons;
	
	int m_viewPunch;
	
	int m_flFallbackWear;
	int m_iEntityQuality;
	int m_iItemDefinitionIndex;
	int m_iItemIDHigh;
	int m_nFallbackPaintKit;
	int m_nFallbackSeed;
	int m_nFallbackStatTrak;
	int m_szCustomName;

	int m_nModelIndex;
	int m_hWeapon;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;

#endif