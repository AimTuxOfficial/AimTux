#include "offsets.h"
#include "Utils/netvarmanager.h"

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
	offsets.DT_BaseCombatCharacter.m_hMyWearables = NetVarManager::getOffset(tables, "DT_BaseCombatCharacter", "m_hMyWearables");

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
	offsets.DT_CSPlayer.m_totalHitsOnServer = NetVarManager::getOffset(tables, "DT_CSPlayer", "m_totalHitsOnServer");
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

	offsets.DT_BaseCSGrenade.m_bRedraw = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_bRedraw");
	offsets.DT_BaseCSGrenade.m_bIsHeldByPlayer = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_bIsHeldByPlayer");
	offsets.DT_BaseCSGrenade.m_bPinPulled = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_bPinPulled");
	offsets.DT_BaseCSGrenade.m_fThrowTime = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_fThrowTime");
	offsets.DT_BaseCSGrenade.m_bLoopingSoundPlaying = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_bLoopingSoundPlaying");
	offsets.DT_BaseCSGrenade.m_flThrowStrength = NetVarManager::getOffset(tables, "DT_BaseCSGrenade", "m_flThrowStrength");

	offsets.DT_DynamicProp.m_bShouldGlow = NetVarManager::getOffset(tables, "DT_DynamicProp", "m_bShouldGlow");

	offsets.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bBombPlanted");
	offsets.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bIsValveDS");

	offsets.DT_CSGameRulesProxy.m_bFreezePeriod = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bFreezePeriod");
	offsets.DT_CSGameRulesProxy.m_bMatchWaitingForResume = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bMatchWaitingForResume");
	offsets.DT_CSGameRulesProxy.m_bWarmupPeriod = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bWarmupPeriod");
	offsets.DT_CSGameRulesProxy.m_fWarmupPeriodEnd = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_fWarmupPeriodEnd");
	offsets.DT_CSGameRulesProxy.m_fWarmupPeriodStart = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_fWarmupPeriodStart");
	offsets.DT_CSGameRulesProxy.m_bTerroristTimeOutActive = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bTerroristTimeOutActive");
	offsets.DT_CSGameRulesProxy.m_bCTTimeOutActive = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bCTTimeOutActive");
	offsets.DT_CSGameRulesProxy.m_flTerroristTimeOutRemaining = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flTerroristTimeOutRemaining");
	offsets.DT_CSGameRulesProxy.m_flCTTimeOutRemaining = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flCTTimeOutRemaining");
	offsets.DT_CSGameRulesProxy.m_nTerroristTimeOuts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nTerroristTimeOuts");
	offsets.DT_CSGameRulesProxy.m_nCTTimeOuts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nCTTimeOuts");
	offsets.DT_CSGameRulesProxy.m_iRoundTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iRoundTime");
	offsets.DT_CSGameRulesProxy.m_gamePhase = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_gamePhase");
	offsets.DT_CSGameRulesProxy.m_totalRoundsPlayed = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_totalRoundsPlayed");
	offsets.DT_CSGameRulesProxy.m_nOvertimePlaying = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nOvertimePlaying");
	offsets.DT_CSGameRulesProxy.m_timeUntilNextPhaseStarts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_timeUntilNextPhaseStarts");
	offsets.DT_CSGameRulesProxy.m_flCMMItemDropRevealStartTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flCMMItemDropRevealStartTime");
	offsets.DT_CSGameRulesProxy.m_flCMMItemDropRevealEndTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flCMMItemDropRevealEndTime");
	offsets.DT_CSGameRulesProxy.m_fRoundStartTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_fRoundStartTime");
	offsets.DT_CSGameRulesProxy.m_bGameRestart = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bGameRestart");
	offsets.DT_CSGameRulesProxy.m_flRestartRoundTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flRestartRoundTime");
	offsets.DT_CSGameRulesProxy.m_flGameStartTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flGameStartTime");
	offsets.DT_CSGameRulesProxy.m_iHostagesRemaining = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iHostagesRemaining");
	offsets.DT_CSGameRulesProxy.m_bAnyHostageReached = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bAnyHostageReached");
	offsets.DT_CSGameRulesProxy.m_bMapHasBombTarget = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasBombTarget");
	offsets.DT_CSGameRulesProxy.m_bMapHasRescueZone = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasRescueZone");
	offsets.DT_CSGameRulesProxy.m_bMapHasBuyZone = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bMapHasBuyZone");
	offsets.DT_CSGameRulesProxy.m_bIsQueuedMatchmaking = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bIsQueuedMatchmaking");
	offsets.DT_CSGameRulesProxy.m_bIsValveDS = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bIsValveDS");
	offsets.DT_CSGameRulesProxy.m_bIsQuestEligible = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bIsQuestEligible");
	offsets.DT_CSGameRulesProxy.m_bLogoMap = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bLogoMap");
	offsets.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsCT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsCT");
	offsets.DT_CSGameRulesProxy.m_iNumGunGameProgressiveWeaponsT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iNumGunGameProgressiveWeaponsT");
	offsets.DT_CSGameRulesProxy.m_iSpectatorSlotCount = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iSpectatorSlotCount");
	offsets.DT_CSGameRulesProxy.m_bBombDropped = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bBombDropped");
	offsets.DT_CSGameRulesProxy.m_bBombPlanted = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bBombPlanted");
	offsets.DT_CSGameRulesProxy.m_iRoundWinStatus = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iRoundWinStatus");
	offsets.DT_CSGameRulesProxy.m_eRoundWinReason = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_eRoundWinReason");
	offsets.DT_CSGameRulesProxy.m_flDMBonusStartTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flDMBonusStartTime");
	offsets.DT_CSGameRulesProxy.m_flDMBonusTimeLength = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flDMBonusTimeLength");
	offsets.DT_CSGameRulesProxy.m_unDMBonusWeaponLoadoutSlot = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_unDMBonusWeaponLoadoutSlot");
	offsets.DT_CSGameRulesProxy.m_bDMBonusActive = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bDMBonusActive");
	offsets.DT_CSGameRulesProxy.m_bTCantBuy = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bTCantBuy");
	offsets.DT_CSGameRulesProxy.m_bCTCantBuy = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bCTCantBuy");
	offsets.DT_CSGameRulesProxy.m_flGuardianBuyUntilTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flGuardianBuyUntilTime");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_RoundResults = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_RoundResults");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_T = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_T");
	offsets.DT_CSGameRulesProxy.m_iMatchStats_PlayersAlive_CT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iMatchStats_PlayersAlive_CT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderC = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderC");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponOrderT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponOrderT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderCT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderCT");
	offsets.DT_CSGameRulesProxy.m_GGProgressiveWeaponKillUpgradeOrderT = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_GGProgressiveWeaponKillUpgradeOrderT");
	offsets.DT_CSGameRulesProxy.m_MatchDevice = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_MatchDevice");
	offsets.DT_CSGameRulesProxy.m_bHasMatchStarted = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bHasMatchStarted");
	offsets.DT_CSGameRulesProxy.m_TeamRespawnWaveTimes = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_TeamRespawnWaveTimes");
	offsets.DT_CSGameRulesProxy.m_flNextRespawnWave = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_flNextRespawnWave");
	offsets.DT_CSGameRulesProxy.m_nNextMapInMapgroup = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nNextMapInMapgroup");
	offsets.DT_CSGameRulesProxy.m_nEndMatchMapGroupVoteOptions = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nEndMatchMapGroupVoteOptions");
	offsets.DT_CSGameRulesProxy.m_bIsDroppingItems = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_bIsDroppingItems");
	offsets.DT_CSGameRulesProxy.m_iActiveAssassinationTargetMissionID = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_iActiveAssassinationTargetMissionID");
	offsets.DT_CSGameRulesProxy.m_fMatchStartTime = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_fMatchStartTime");
	offsets.DT_CSGameRulesProxy.m_szTournamentEventName = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentEventName");
	offsets.DT_CSGameRulesProxy.m_szTournamentEventStage = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentEventStage");
	offsets.DT_CSGameRulesProxy.m_szTournamentPredictionsTxt = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_szTournamentPredictionsTxt");
	offsets.DT_CSGameRulesProxy.m_nTournamentPredictionsPct = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nTournamentPredictionsPct");
	offsets.DT_CSGameRulesProxy.m_szMatchStatTxt = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_szMatchStatTxt");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeWaveNumber = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeWaveNumber");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeSpecialKillsRemaining = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeSpecialKillsRemaining");
	offsets.DT_CSGameRulesProxy.m_nGuardianModeSpecialWeaponNeeded = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nGuardianModeSpecialWeaponNeeded");
	offsets.DT_CSGameRulesProxy.m_nHalloweenMaskListSeed = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_nHalloweenMaskListSeed");
	offsets.DT_CSGameRulesProxy.m_numGlobalGiftsGiven = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGiftsGiven");
	offsets.DT_CSGameRulesProxy.m_numGlobalGifters = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGifters");
	offsets.DT_CSGameRulesProxy.m_numGlobalGiftsPeriodSeconds = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_numGlobalGiftsPeriodSeconds");
	offsets.DT_CSGameRulesProxy.m_arrFeaturedGiftersAccounts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_arrFeaturedGiftersAccounts");
	offsets.DT_CSGameRulesProxy.m_arrFeaturedGiftersGifts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_arrFeaturedGiftersGifts");
	offsets.DT_CSGameRulesProxy.m_arrTournamentActiveCasterAccounts = NetVarManager::getOffset(tables, "DT_CSGameRulesProxy", "m_arrTournamentActiveCasterAccounts");
}
