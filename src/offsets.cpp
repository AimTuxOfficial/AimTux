#include "offsets.h"
#include "Utils/netvarmanager.h"

COffsets offsets;

void Offsets::GetOffsets()
{
	std::vector<RecvTable *> tables = NetVarManager::GetTables();

	offsets.DT_BasePlayer.m_Local = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_Local");
	offsets.DT_BasePlayer.m_aimPunchAngle = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_aimPunchAngle");
	offsets.DT_BasePlayer.m_viewPunchAngle = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_viewPunchAngle");
	offsets.DT_BasePlayer.m_vecViewOffset = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
	offsets.DT_BasePlayer.m_nTickBase = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_nTickBase");
	offsets.DT_BasePlayer.m_vecVelocity = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_vecVelocity[0]");
	offsets.DT_BasePlayer.m_iHealth = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_iHealth");
	offsets.DT_BasePlayer.m_lifeState = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_lifeState");
	offsets.DT_BasePlayer.m_fFlags = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_fFlags");
	offsets.DT_BasePlayer.m_iObserverMode = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_iObserverMode");
	offsets.DT_BasePlayer.m_hObserverTarget = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_hObserverTarget");
	offsets.DT_BasePlayer.m_hViewModel = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
	offsets.DT_BasePlayer.m_szLastPlaceName = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_szLastPlaceName");
	offsets.DT_BasePlayer.deadflag = NetVarManager::GetOffset(tables, "DT_BasePlayer", "deadflag");

	offsets.DT_BaseEntity.m_flAnimTime = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_flAnimTime");
	offsets.DT_BaseEntity.m_flSimulationTime = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_flSimulationTime");
	offsets.DT_BaseEntity.m_vecOrigin = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_vecOrigin");
	offsets.DT_BaseEntity.m_nRenderMode = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_nRenderMode");
	offsets.DT_BaseEntity.m_iTeamNum = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_iTeamNum");
	offsets.DT_BaseEntity.m_MoveType = offsets.DT_BaseEntity.m_nRenderMode + 1;
	offsets.DT_BaseEntity.m_Collision = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_Collision");
	offsets.DT_BaseEntity.m_bSpotted = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_bSpotted");

	offsets.DT_BaseCombatCharacter.m_hActiveWeapon = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsets.DT_BaseCombatCharacter.m_hMyWeapons = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
	offsets.DT_BaseCombatCharacter.m_hMyWearables = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWearables");

	offsets.DT_PlayerResource.m_iPing = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iPing");
	offsets.DT_PlayerResource.m_iKills = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iKills");
	offsets.DT_PlayerResource.m_iAssists = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iAssists");
	offsets.DT_PlayerResource.m_iDeaths = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iDeaths");
	offsets.DT_PlayerResource.m_bConnected = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_bConnected");
	offsets.DT_PlayerResource.m_iTeam = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iTeam");
	offsets.DT_PlayerResource.m_iPendingTeam = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iPendingTeam");
	offsets.DT_PlayerResource.m_bAlive = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_bAlive");
	offsets.DT_PlayerResource.m_iHealth = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iHealth");

	offsets.DT_CSPlayerResource.m_iPlayerC4 = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerC4");
	offsets.DT_CSPlayerResource.m_iPlayerVIP = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerVIP");
	offsets.DT_CSPlayerResource.m_bHostageAlive = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHostageAlive");
	offsets.DT_CSPlayerResource.m_isHostageFollowingSomeone = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_isHostageFollowingSomeone");
	offsets.DT_CSPlayerResource.m_iHostageEntityIDs = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iHostageEntityIDs");
	offsets.DT_CSPlayerResource.m_bombsiteCenterB = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bombsiteCenterB");
	offsets.DT_CSPlayerResource.m_hostageRescueX = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueX");
	offsets.DT_CSPlayerResource.m_hostageRescueY = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueY");
	offsets.DT_CSPlayerResource.m_hostageRescueZ = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueZ");
	offsets.DT_CSPlayerResource.m_iMVPs = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iMVPs");
	offsets.DT_CSPlayerResource.m_iArmor = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iArmor");
	offsets.DT_CSPlayerResource.m_bHasHelmet = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHasHelmet");
	offsets.DT_CSPlayerResource.m_bHasDefuser = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHasDefuser");
	offsets.DT_CSPlayerResource.m_iScore = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iScore");
	offsets.DT_CSPlayerResource.m_iCompetitiveRanking = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveRanking");
	offsets.DT_CSPlayerResource.m_iCompetitiveWins = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveWins");
	offsets.DT_CSPlayerResource.m_iCompTeammateColor = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompTeammateColor");
	offsets.DT_CSPlayerResource.m_bControllingBot = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bControllingBot");
	offsets.DT_CSPlayerResource.m_iControlledPlayer = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledPlayer");
	offsets.DT_CSPlayerResource.m_iControlledByPlayer = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledByPlayer");
	offsets.DT_CSPlayerResource.m_iBotDifficulty = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iBotDifficulty");
	offsets.DT_CSPlayerResource.m_szClan = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_szClan");
	offsets.DT_CSPlayerResource.m_iTotalCashSpent = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iTotalCashSpent");
	offsets.DT_CSPlayerResource.m_iCashSpentThisRound = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCashSpentThisRound");
	offsets.DT_CSPlayerResource.m_nEndMatchNextMapVotes = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
	offsets.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
	offsets.DT_CSPlayerResource.m_nActiveCoinRank = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nActiveCoinRank");
	offsets.DT_CSPlayerResource.m_nMusicID = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nMusicID");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicLevel = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
	offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");

	offsets.DT_PlantedC4.m_bBombTicking = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_bBombTicking");
	offsets.DT_PlantedC4.m_flC4Blow = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_flC4Blow");
	offsets.DT_PlantedC4.m_bBombDefused = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_bBombDefused");
	offsets.DT_PlantedC4.m_hBombDefuser = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_hBombDefuser");

	offsets.DT_CSPlayer.m_iShotsFired = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_iShotsFired");
	offsets.DT_CSPlayer.m_angEyeAngles[0] = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[0]");
	offsets.DT_CSPlayer.m_angEyeAngles[1] = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[1]");
	offsets.DT_CSPlayer.m_iAccount = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_iAccount");
	offsets.DT_CSPlayer.m_totalHitsOnServer = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_totalHitsOnServer");
	offsets.DT_CSPlayer.m_ArmorValue = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_ArmorValue");
	offsets.DT_CSPlayer.m_bIsDefusing = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsDefusing");
	offsets.DT_CSPlayer.m_bIsGrabbingHostage = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsGrabbingHostage");
	offsets.DT_CSPlayer.m_bIsScoped = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsScoped");
	offsets.DT_CSPlayer.m_bGunGameImmunity = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bGunGameImmunity");
	offsets.DT_CSPlayer.m_bIsRescuing = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsRescuing");
	offsets.DT_CSPlayer.m_bHasHelmet = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bHasHelmet");
	offsets.DT_CSPlayer.m_bHasDefuser = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
	offsets.DT_CSPlayer.m_flFlashDuration = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flFlashDuration");
	offsets.DT_CSPlayer.m_flFlashMaxAlpha = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flFlashMaxAlpha");
	offsets.DT_CSPlayer.m_flLowerBodyYawTarget = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flLowerBodyYawTarget");

	offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsets.DT_BaseAttributableItem.m_iItemIDHigh = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
	offsets.DT_BaseAttributableItem.m_iAccountID = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iAccountID");
	offsets.DT_BaseAttributableItem.m_iEntityQuality = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
	offsets.DT_BaseAttributableItem.m_szCustomName = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_szCustomName");
	offsets.DT_BaseAttributableItem.m_nFallbackPaintKit = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	offsets.DT_BaseAttributableItem.m_nFallbackSeed = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
	offsets.DT_BaseAttributableItem.m_flFallbackWear = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
	offsets.DT_BaseAttributableItem.m_nFallbackStatTrak = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");

	offsets.DT_BaseViewModel.m_nModelIndex = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
	offsets.DT_BaseViewModel.m_hWeapon = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_hWeapon");
	offsets.DT_BaseViewModel.m_hOwner = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_hOwner");

	offsets.DT_WeaponCSBase.m_fAccuracyPenalty = NetVarManager::GetOffset(tables, "DT_WeaponCSBase", "m_fAccuracyPenalty");

	offsets.DT_WeaponC4.m_bStartedArming = NetVarManager::GetOffset(tables, "DT_WeaponC4", "m_bStartedArming");

	offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	offsets.DT_BaseCombatWeapon.m_hOwner = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_hOwner");
	offsets.DT_BaseCombatWeapon.m_iClip1 = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_iClip1");
	offsets.DT_BaseCombatWeapon.m_bInReload = offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;

	offsets.DT_BaseCSGrenade.m_bRedraw = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_bRedraw");
	offsets.DT_BaseCSGrenade.m_bIsHeldByPlayer = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_bIsHeldByPlayer");
	offsets.DT_BaseCSGrenade.m_bPinPulled = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_bPinPulled");
	offsets.DT_BaseCSGrenade.m_fThrowTime = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_fThrowTime");
	offsets.DT_BaseCSGrenade.m_bLoopingSoundPlaying = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_bLoopingSoundPlaying");
	offsets.DT_BaseCSGrenade.m_flThrowStrength = NetVarManager::GetOffset(tables, "DT_BaseCSGrenade", "m_flThrowStrength");

	offsets.DT_DynamicProp.m_bShouldGlow = NetVarManager::GetOffset(tables, "DT_DynamicProp", "m_bShouldGlow");

	offsets.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bBombPlanted");
	offsets.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bIsValveDS");

	offsets.DT_CSGameRulesProxy.m_bFreezePeriod = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bFreezePeriod");
	offsets.DT_CSGameRulesProxy.m_bMatchWaitingForResume = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bMatchWaitingForResume");
	offsets.DT_CSGameRulesProxy.m_bWarmupPeriod = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bWarmupPeriod");
	offsets.DT_CSGameRulesProxy.m_fWarmupPeriodEnd = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_fWarmupPeriodEnd");
	offsets.DT_CSGameRulesProxy.m_fWarmupPeriodStart = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_fWarmupPeriodStart");
	offsets.DT_CSGameRulesProxy.m_bTerroristTimeOutActive = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bTerroristTimeOutActive");
	offsets.DT_CSGameRulesProxy.m_bCTTimeOutActive = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bCTTimeOutActive");
	offsets.DT_CSGameRulesProxy.m_flTerroristTimeOutRemaining = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flTerroristTimeOutRemaining");
	offsets.DT_CSGameRulesProxy.m_flCTTimeOutRemaining = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flCTTimeOutRemaining");
	offsets.DT_CSGameRulesProxy.m_nTerroristTimeOuts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nTerroristTimeOuts");
	offsets.DT_CSGameRulesProxy.m_nCTTimeOuts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nCTTimeOuts");
	offsets.DT_CSGameRulesProxy.m_iRoundTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iRoundTime");
	offsets.DT_CSGameRulesProxy.m_gamePhase = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_gamePhase");
	offsets.DT_CSGameRulesProxy.m_totalRoundsPlayed = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_totalRoundsPlayed");
	offsets.DT_CSGameRulesProxy.m_nOvertimePlaying = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nOvertimePlaying");
	offsets.DT_CSGameRulesProxy.m_timeUntilNextPhaseStarts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_timeUntilNextPhaseStarts");
	offsets.DT_CSGameRulesProxy.m_flCMMItemDropRevealStartTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flCMMItemDropRevealStartTime");
	offsets.DT_CSGameRulesProxy.m_flCMMItemDropRevealEndTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flCMMItemDropRevealEndTime");
	offsets.DT_CSGameRulesProxy.m_fRoundStartTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_fRoundStartTime");
	offsets.DT_CSGameRulesProxy.m_bGameRestart = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bGameRestart");
	offsets.DT_CSGameRulesProxy.m_flRestartRoundTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flRestartRoundTime");
	offsets.DT_CSGameRulesProxy.m_flGameStartTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flGameStartTime");
	offsets.DT_CSGameRulesProxy.m_iHostagesRemaining = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iHostagesRemaining");
	offsets.DT_CSGameRulesProxy.m_bAnyHostageReached = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bAnyHostageReached");
	offsets.DT_CSGameRulesProxy.m_bMapHasBombTarget = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasBombTarget");
	offsets.DT_CSGameRulesProxy.m_bMapHasRescueZone = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasRescueZone");
	offsets.DT_CSGameRulesProxy.m_bMapHasBuyZone = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasBuyZone");
	offsets.DT_CSGameRulesProxy.m_bIsQueuedMatchmaking = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bIsQueuedMatchmaking");
	offsets.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bIsValveDS");
	offsets.DT_CSGameRulesProxy.m_bIsQuestEligible = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bIsQuestEligible");
	offsets.DT_CSGameRulesProxy.m_bLogoMap = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bLogoMap");
	offsets.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsCT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsCT");
	offsets.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsT");
	offsets.DT_CSGameRulesProxy.m_iSpectatorSlotCount = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iSpectatorSlotCount");
	offsets.DT_CSGameRulesProxy.m_bBombDropped = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bBombDropped");
	offsets.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bBombPlanted");
	offsets.DT_CSGameRulesProxy.m_iRoundWinStatus = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iRoundWinStatus");
	offsets.DT_CSGameRulesProxy.m_eRoundWinReason = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_eRoundWinReason");
	offsets.DT_CSGameRulesProxy.m_flDMBonusStartTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flDMBonusStartTime");
	offsets.DT_CSGameRulesProxy.m_flDMBonusTimeLength = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flDMBonusTimeLength");
	offsets.DT_CSGameRulesProxy.m_unDMBonusWeaponLoadoutSlot = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_unDMBonusWeaponLoadoutSlot");
	offsets.DT_CSGameRulesProxy.m_bDMBonusActive = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bDMBonusActive");
	offsets.DT_CSGameRulesProxy.m_bTCantBuy = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bTCantBuy");
	offsets.DT_CSGameRulesProxy.m_bCTCantBuy = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bCTCantBuy");
	offsets.DT_CSGameRulesProxy.m_flGuardianBuyUntilTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flGuardianBuyUntilTime");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_RoundResults = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_RoundResults");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_T = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_T");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_CT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_CT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderC = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderC");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderCT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderCT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderT = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderT");
	offsets.DT_CSGameRulesProxy.m_MatchDevice = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_MatchDevice");
	offsets.DT_CSGameRulesProxy.m_bHasMatchStarted = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bHasMatchStarted");
	offsets.DT_CSGameRulesProxy.m_TeamRespawnWaveTimes = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_TeamRespawnWaveTimes");
	offsets.DT_CSGameRulesProxy.m_flNextRespawnWave = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_flNextRespawnWave");
	offsets.DT_CSGameRulesProxy.m_nNextMapInMapgroup = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nNextMapInMapgroup");
	offsets.DT_CSGameRulesProxy.m_nEndMatchMapGroupVoteOptions = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nEndMatchMapGroupVoteOptions");
	offsets.DT_CSGameRulesProxy.m_bIsDroppingItems = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_bIsDroppingItems");
	offsets.DT_CSGameRulesProxy.m_iActiveAssassinationTargetMissionID = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_iActiveAssassinationTargetMissionID");
	offsets.DT_CSGameRulesProxy.m_fMatchStartTime = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_fMatchStartTime");
	offsets.DT_CSGameRulesProxy.m_szTournamentEventName = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentEventName");
	offsets.DT_CSGameRulesProxy.m_szTournamentEventStage = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentEventStage");
	offsets.DT_CSGameRulesProxy.m_szTournamentPredictionsTxt = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentPredictionsTxt");
	offsets.DT_CSGameRulesProxy.m_nTournamentPredictionsPct = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nTournamentPredictionsPct");
	offsets.DT_CSGameRulesProxy.m_szMatchStatTxt = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_szMatchStatTxt");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeWaveNumber = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeWaveNumber");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeSpecialKillsRemaining = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeSpecialKillsRemaining");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeSpecialWeaponNeeded = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeSpecialWeaponNeeded");
	offsets.DT_CSGameRulesProxy.m_nHalloweenMaskListSeed = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_nHalloweenMaskListSeed");
	offsets.DT_CSGameRulesProxy.m_numGlobalGiftsGiven = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGiftsGiven");
	offsets.DT_CSGameRulesProxy.m_numGlobalGifters = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGifters");
	offsets.DT_CSGameRulesProxy.m_numGlobalGiftsPeriodSeconds = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGiftsPeriodSeconds");
	offsets.DT_CSGameRulesProxy.m_arrFeaturedGiftersAccounts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_arrFeaturedGiftersAccounts");
	offsets.DT_CSGameRulesProxy.m_arrFeaturedGiftersGifts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_arrFeaturedGiftersGifts");
	offsets.DT_CSGameRulesProxy.m_arrTournamentActiveCasterAccounts = NetVarManager::GetOffset(tables, "DT_CSGameRulesProxy", "m_arrTournamentActiveCasterAccounts");
}
