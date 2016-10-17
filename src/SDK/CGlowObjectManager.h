#ifndef __CGLOWOBJECTMANAGER_H
#define __CGLOWOBJECTMANAGER_H

struct GlowObjectDefinition_t {
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
};

struct CGlowObjectManager {
	GlowObjectDefinition_t* m_GlowObjectDefinitions;
	int max_size;
	int pad;
	int size;
	GlowObjectDefinition_t* m_GlowObjectDefinitions2;
	int currentObjects;
};

// Special values for GlowObjectDefinition_t::m_nNextFreeSlot
#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2


#endif