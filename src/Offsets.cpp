#include "Offsets.h"
#include "NetVarManager.h"

COffsets offsets;

void Offsets::getOffsets()
{
	std::vector<HLClient::RecvTable *> tables = NetVarManager::getTables();

	offsets.m_lifeState = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_lifeState");
	offsets.m_hMyWeapons = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
	offsets.m_iItemDefinitionIndex = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsets.m_iEntityQuality = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
	offsets.m_iItemIDHigh = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
	offsets.m_szCustomName = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_szCustomName") ;
	offsets.m_nFallbackPaintKit = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	offsets.m_nFallbackSeed = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
	offsets.m_flFallbackWear = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
	offsets.m_nFallbackStatTrak = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");
	offsets.m_nModelIndex = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
	offsets.m_hViewModel = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
	offsets.m_hWeapon = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_hWeapon");
}