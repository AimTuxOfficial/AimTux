#pragma once

// Special values for GlowObjectDefinition_t::m_nNextFreeSlot
#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

struct GlowObjectDefinition_t
{
	C_BaseEntity* m_pEntity;
	float m_flGlowColor[3];
	float m_flGlowAlpha;
	char unknown[4];
	float flUnk;
	float m_flBloomAmount;
	float localplayeriszeropoint3;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloomRender;
	char unknown1[1];
	int m_nFullBloomStencilTestValue;
	int iUnk;
	int m_nSplitScreenSlot;
	int m_nNextFreeSlot;

	bool IsUnused() const {
		return m_nNextFreeSlot != ENTRY_IN_USE;
	}
};

class CGlowObjectManager
{
public:
	int RegisterGlowObject(C_BaseEntity* entity)
	{
		// FIXME: No remaining slots, see issue #158.
		if (m_nFirstFreeSlot == END_OF_FREE_LIST)
			return -1;

		int index = m_nFirstFreeSlot;
		m_nFirstFreeSlot = m_GlowObjectDefinitions[index].m_nNextFreeSlot;

		m_GlowObjectDefinitions[index].m_pEntity = entity;
		m_GlowObjectDefinitions[index].flUnk = 0.0f;
		m_GlowObjectDefinitions[index].localplayeriszeropoint3 = 0.0f;
		m_GlowObjectDefinitions[index].m_bFullBloomRender = false;
		m_GlowObjectDefinitions[index].m_nFullBloomStencilTestValue = 0;
		m_GlowObjectDefinitions[index].m_nSplitScreenSlot = -1;
		m_GlowObjectDefinitions[index].m_nNextFreeSlot = ENTRY_IN_USE;

		return index;
	}

	void UnregisterGlowObject(int index)
	{
		m_GlowObjectDefinitions[index].m_nNextFreeSlot = m_nFirstFreeSlot;
		m_GlowObjectDefinitions[index].m_pEntity = NULL;
		m_nFirstFreeSlot = index;
	}

	bool HasGlowEffect(C_BaseEntity* entity)
	{
		for (int i = 0; i < m_GlowObjectDefinitions.Count(); ++i) {
			if (!m_GlowObjectDefinitions[i].IsUnused() && m_GlowObjectDefinitions[i].m_pEntity == entity) {
				return true;
			}
		}

		return false;
	};

	CUtlVector<GlowObjectDefinition_t> m_GlowObjectDefinitions;
	int m_nFirstFreeSlot;
};
