#pragma once

class C_CSGameRules
{
public:
	bool IsValveDS()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSGameRulesProxy.m_bIsValveDS);
	}

	bool IsBombDropped()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSGameRulesProxy.m_bBombDropped);
	}

	bool IsBombPlanted()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSGameRulesProxy.m_bBombPlanted);
	}
	bool IsFreezeTime()
	{
		return *(bool *) ((uintptr_t) this + offsets.DT_CSGameRulesProxy.m_bFreezePeriod);
	}
};