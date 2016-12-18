#pragma once

class CPlayerResource {};

class C_CSPlayerResource : public CPlayerResource
{
public:
	int GetPlayerC4()
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iPlayerC4);
	}

	int GetMVPs(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iMVPs + index * 4);
	}

	int GetArmor(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iArmor + index * 4);
	}

	int GetScore(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iScore + index * 4);
	}

	int* GetCompetitiveRanking(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iCompetitiveRanking + index * 4);
	}

	int* GetCompetitiveWins(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iCompetitiveWins + index * 4);
	}

	int GetCompTeammateColor(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_iCompTeammateColor + index * 4);
	}

	char* GetClan(int index)
	{
		return (char*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_szClan + index * 16);
	}

	int* GetActiveCoinRank(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_nActiveCoinRank + index * 4);
	}

	int* GetMusicID(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_nMusicID + index * 4);
	}

	int* GetPersonaDataPublicCommendsLeader(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader + index * 4);
	}

	int* GetPersonaDataPublicCommendsTeacher(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher + index * 4);
	}

	int* GetPersonaDataPublicCommendsFriendly(int index)
	{
		return (int*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly + index * 4);
	}
};