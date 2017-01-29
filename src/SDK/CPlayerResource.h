#pragma once

class CPlayerResource {};

class C_CSPlayerResource : public CPlayerResource
{
public:
	int GetPing(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iPing + index * 4);
	}

	int GetKills(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iKills + index * 4);
	}

	int GetAssists(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iAssists + index * 4);
	}

	int GetDeaths(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iDeaths + index * 4);
	}

	bool GetConnected(int index)
	{
		return *(bool*)((uintptr_t)this + offsets.DT_PlayerResource.m_bConnected + index);
	}

	TeamID GetTeam(int index)
	{
		return *(TeamID*)((uintptr_t)this + offsets.DT_PlayerResource.m_iTeam + index * 4);
	}

	int GetPendingTeam(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iPendingTeam + index * 4);
	}

	bool GetAlive(int index)
	{
		return *(bool*)((uintptr_t)this + offsets.DT_PlayerResource.m_bAlive + index);
	}

	int GetHealth(int index)
	{
		return *(int*)((uintptr_t)this + offsets.DT_PlayerResource.m_iHealth + index * 4);
	}

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

	const char* GetClan(int index)
	{
		return (const char*)((uintptr_t)this + offsets.DT_CSPlayerResource.m_szClan + index * 16);
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