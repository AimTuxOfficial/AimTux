#ifndef OFFSETS_H_INCLUDED
#define OFFSETS_H_INCLUDED

struct COffsets
{
	int m_lifeState;
	int m_hMyWeapons;
	int m_iItemDefinitionIndex;
	int m_iEntityQuality;
	int m_iItemIDHigh;
	int m_szCustomName;
	int m_nFallbackPaintKit;
	int m_nFallbackSeed;
	int m_flFallbackWear;
	int m_nFallbackStatTrak;
	int m_nModelIndex;
	int m_hViewModel;
	int m_hWeapon;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;

#endif