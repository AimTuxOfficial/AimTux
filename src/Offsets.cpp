#include "Offsets.h"
#include "NetVarManager.h"

COffsets offsets;

void Offsets::getOffsets()
{
	std::vector<HLClient::RecvTable *> tables = NetVarManager::getTables();

	offsets.m_hViewModel = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
	offsets.m_iHealth = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_iHealth");
	offsets.m_iTeamNum = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_iTeamNum");
	offsets.m_lifeState = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_lifeState");
	offsets.m_bDormant = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_bDormant");
	offsets.m_Local = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_Local");
	offsets.m_aimPunchAngle = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_aimPunchAngle");
	offsets.m_fFlags = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_fFlags");
	offsets.m_nTickBase = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_nTickBase");
	
	offsets.m_vecOrigin = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_vecOrigin");
	offsets.m_vecViewOffset = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
	
	offsets.m_iClip1 = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_iClip1");
	offsets.m_bInReload = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_bInReload");
	offsets.m_flNextPrimaryAttack = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	
	
	offsets.m_hMyWeapons = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
	offsets.m_hActiveWeapon = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	
	offsets.m_flFallbackWear = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
	offsets.m_iEntityQuality = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
	offsets.m_iItemDefinitionIndex = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsets.m_iItemIDHigh = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
	offsets.m_nFallbackPaintKit = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	offsets.m_nFallbackSeed = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
	offsets.m_nFallbackStatTrak = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");
	offsets.m_szCustomName = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_szCustomName") ;

	offsets.m_nModelIndex = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
	offsets.m_hWeapon = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_hWeapon");
}