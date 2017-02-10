#pragma once

class CBaseClientState
{
public:
	char _pad0[0x1FC];
	int m_nDeltaTick;
	bool m_bPaused;
	char _pad1[0x3];
	int m_nViewEntity;
	char _pad2[0x8];
	char m_szLevelName[260];
	char m_szLevelNameShort[40];
};