#include "offsets.h"
#include "netvarmanager.h"

COffsets offsets;

void Offsets::getOffsets()
{
	std::vector<RecvTable *> tables = NetVarManager::getTables();

	offsets.DT_BasePlayer.m_Local = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_Local");
	offsets.DT_BasePlayer.m_aimPunchAngle = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_aimPunchAngle");
	offsets.DT_BasePlayer.m_viewPunchAngle = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_viewPunchAngle");
	offsets.DT_BasePlayer.m_vecViewOffset = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
	offsets.DT_BasePlayer.m_nTickBase = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_nTickBase");
	offsets.DT_BasePlayer.m_vecVelocity = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_vecVelocity[0]");
	offsets.DT_BasePlayer.m_iHealth = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_iHealth");
	offsets.DT_BasePlayer.m_lifeState = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_lifeState");
	offsets.DT_BasePlayer.m_fFlags = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_fFlags");
	offsets.DT_BasePlayer.m_iObserverMode = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_iObserverMode");
	offsets.DT_BasePlayer.m_hObserverTarget = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_hObserverTarget");
	offsets.DT_BasePlayer.m_hViewModel = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
	offsets.DT_BasePlayer.m_szLastPlaceName = NetVarManager::getOffset(tables, "DT_BasePlayer", "m_szLastPlaceName");

	offsets.DT_BaseEntity.m_vecOrigin = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_vecOrigin");
	offsets.DT_BaseEntity.m_nRenderMode = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_nRenderMode");
	offsets.DT_BaseEntity.m_iTeamNum = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_iTeamNum");
	offsets.DT_BaseEntity.m_MoveType = offsets.DT_BaseEntity.m_nRenderMode + 1;
	offsets.DT_BaseEntity.m_Collision = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_Collision");
	offsets.DT_BaseEntity.m_bSpotted = NetVarManager::getOffset(tables, "DT_BaseEntity", "m_bSpotted");

	offsets.DT_BaseCombatCharacter.m_hActiveWeapon = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsets.DT_BaseCombatCharacter.m_hMyWeapons = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;

	offsets.DT_PlayerResource.m_iPing = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iPing");
	offsets.DT_PlayerResource.m_iKills = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iKills");
	offsets.DT_PlayerResource.m_iAssists = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iAssists");
	offsets.DT_PlayerResource.m_iDeaths = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iDeaths");
	offsets.DT_PlayerResource.m_bConnected = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_bConnected");
	offsets.DT_PlayerResource.m_iTeam = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iTeam");
	offsets.DT_PlayerResource.m_iPendingTeam = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iPendingTeam");
	offsets.DT_PlayerResource.m_bAlive = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_bAlive");
	offsets.DT_PlayerResource.m_iHealth = NetVarManager::getOffset(tables, "DT_PlayerResource", "m_iHealth");

	offsets.DT_CSPlayerResource.m_iPlayerC4 = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iPlayerC4");
	offsets.DT_CSPlayerResource.m_iPlayerVIP = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iPlayerVIP");
	offsets.DT_CSPlayerResource.m_bHostageAlive = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bHostageAlive");
	offsets.DT_CSPlayerResource.m_isHostageFollowingSomeone = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_isHostageFollowingSomeone");
	offsets.DT_CSPlayerResource.m_iHostageEntityIDs = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iHostageEntityIDs");
	offsets.DT_CSPlayerResource.m_bombsiteCenterB = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bombsiteCenterB");
	offsets.DT_CSPlayerResource.m_hostageRescueX = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_hostageRescueX");
	offsets.DT_CSPlayerResource.m_hostageRescueY = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_hostageRescueY");
	offsets.DT_CSPlayerResource.m_hostageRescueZ = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_hostageRescueZ");
	offsets.DT_CSPlayerResource.m_iMVPs = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iMVPs");
	offsets.DT_CSPlayerResource.m_iArmor = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iArmor");
	offsets.DT_CSPlayerResource.m_bHasHelmet = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bHasHelmet");
	offsets.DT_CSPlayerResource.m_bHasDefuser = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bHasDefuser");
	offsets.DT_CSPlayerResource.m_iScore = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iScore");
	offsets.DT_CSPlayerResource.m_iCompetitiveRanking = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveRanking");
	offsets.DT_CSPlayerResource.m_iCompetitiveWins = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveWins");
	offsets.DT_CSPlayerResource.m_iCompTeammateColor = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iCompTeammateColor");
	offsets.DT_CSPlayerResource.m_bControllingBot = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bControllingBot");
	offsets.DT_CSPlayerResource.m_iControlledPlayer = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iControlledPlayer");
	offsets.DT_CSPlayerResource.m_iControlledByPlayer = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iControlledByPlayer");
	offsets.DT_CSPlayerResource.m_iBotDifficulty = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iBotDifficulty");
	offsets.DT_CSPlayerResource.m_szClan = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_szClan");
	offsets.DT_CSPlayerResource.m_iTotalCashSpent = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iTotalCashSpent");
	offsets.DT_CSPlayerResource.m_iCashSpentThisRound = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_iCashSpentThisRound");
	offsets.DT_CSPlayerResource.m_nEndMatchNextMapVotes = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
	offsets.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
	offsets.DT_CSPlayerResource.m_nActiveCoinRank = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nActiveCoinRank");
	offsets.DT_CSPlayerResource.m_nMusicID = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nMusicID");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicLevel = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = NetVarManager::getOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");

	offsets.DT_PlantedC4.m_bBombTicking = NetVarManager::getOffset(tables, "DT_PlantedC4", "m_bBombTicking");
	offsets.DT_PlantedC4.m_flC4Blow = NetVarManager::getOffset(tables, "DT_PlantedC4", "m_flC4Blow");
	offsets.DT_PlantedC4.m_bBombDefused = NetVarManager::getOffset(tables, "DT_PlantedC4", "m_bBombDefused");
	offsets.DT_PlantedC4.m_hBombDefuser = NetVarManager::getOffset(tables, "DT_PlantedC4", "m_hBombDefuser");

	offsets.DT_CSPlayer.m_iShotsFired = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_iShotsFired");
	offsets.DT_CSPlayer.m_angEyeAngles[0] = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_angEyeAngles[0]");
	offsets.DT_CSPlayer.m_angEyeAngles[1] = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_angEyeAngles[1]");
	offsets.DT_CSPlayer.m_iAccount = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_iAccount");
	offsets.DT_CSPlayer.m_ArmorValue = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_ArmorValue");
	offsets.DT_CSPlayer.m_bHasDefuser = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
	offsets.DT_CSPlayer.m_bIsDefusing = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bIsDefusing");
	offsets.DT_CSPlayer.m_bIsGrabbingHostage = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bIsGrabbingHostage");
	offsets.DT_CSPlayer.m_bIsScoped = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bIsScoped");
	offsets.DT_CSPlayer.m_bGunGameImmunity = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bGunGameImmunity");
	offsets.DT_CSPlayer.m_bIsRescuing = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bIsRescuing");
	offsets.DT_CSPlayer.m_bHasHelmet = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bHasHelmet");
	offsets.DT_CSPlayer.m_bHasDefuser = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
	offsets.DT_CSPlayer.m_flFlashDuration = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_flFlashDuration");
	offsets.DT_CSPlayer.m_flFlashMaxAlpha = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_flFlashMaxAlpha");
	offsets.DT_CSPlayer.m_flLowerBodyYawTarget = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_flLowerBodyYawTarget");

	offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsets.DT_BaseAttributableItem.m_iItemIDHigh = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
	offsets.DT_BaseAttributableItem.m_iAccountID = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iAccountID");
	offsets.DT_BaseAttributableItem.m_iEntityQuality = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
	offsets.DT_BaseAttributableItem.m_szCustomName = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_szCustomName");
	offsets.DT_BaseAttributableItem.m_nFallbackPaintKit = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	offsets.DT_BaseAttributableItem.m_nFallbackSeed = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
	offsets.DT_BaseAttributableItem.m_flFallbackWear = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
	offsets.DT_BaseAttributableItem.m_nFallbackStatTrak = NetVarManager::getOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");

	offsets.DT_BaseViewModel.m_nModelIndex = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
	offsets.DT_BaseViewModel.m_hWeapon = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_hWeapon");
	offsets.DT_BaseViewModel.m_hOwner = NetVarManager::getOffset(tables, "DT_BaseViewModel", "m_hOwner");

	offsets.DT_WeaponCSBase.m_fAccuracyPenalty = NetVarManager::getOffset(tables, "DT_WeaponCSBase", "m_fAccuracyPenalty");

	offsets.DT_WeaponC4.m_bStartedArming = NetVarManager::getOffset(tables, "DT_WeaponC4", "m_bStartedArming");

	offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	offsets.DT_BaseCombatWeapon.m_hOwner = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_hOwner");
	offsets.DT_BaseCombatWeapon.m_iClip1 = NetVarManager::getOffset(tables, "DT_BaseCombatWeapon", "m_iClip1");
	offsets.DT_BaseCombatWeapon.m_bInReload = offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;

	offsets.DT_DynamicProp.m_bShouldGlow = NetVarManager::getOffset(tables, "DT_DynamicProp", "m_bShouldGlow");
}
