#pragma once

#include <cstdio>
#include "SDK/vector.h"

struct COffsets
{
	struct {
		int m_Local;
		int m_aimPunchAngle;
		int m_viewPunchAngle;
		int m_vecViewOffset;
		int m_nTickBase;
		int m_vecVelocity;
		int m_iHealth;
		int m_lifeState;
		int m_fFlags;
		int m_iObserverMode;
		int m_hObserverTarget;
		int m_hViewModel;
		int m_szLastPlaceName;
	} DT_BasePlayer;

	struct
	{
		int m_vecOrigin;
		int m_nRenderMode;
		int m_iTeamNum;
		int m_MoveType;
		int m_Collision;
		int m_bSpotted;
	} DT_BaseEntity;

	struct
	{
		int m_hActiveWeapon;
		int m_hMyWeapons;
	} DT_BaseCombatCharacter;

	struct
	{
		int m_iPing;
		int m_iKills;
		int m_iAssists;
		int m_iDeaths;
		int m_bConnected;
		int m_iTeam;
		int m_iPendingTeam;
		int m_bAlive;
		int m_iHealth;
	} DT_PlayerResource;

	struct
	{
		int m_iPlayerC4;
		int m_iPlayerVIP;
		int m_bHostageAlive;
		int m_isHostageFollowingSomeone;
		int m_iHostageEntityIDs;
		int m_bombsiteCenterB;
		int m_hostageRescueX;
		int m_hostageRescueY;
		int m_hostageRescueZ;
		int m_iMVPs;
		int m_iArmor;
		int m_bHasHelmet;
		int m_bHasDefuser;
		int m_iScore;
		int m_iCompetitiveRanking;
		int m_iCompetitiveWins;
		int m_iCompTeammateColor;
		int m_bControllingBot;
		int m_iControlledPlayer;
		int m_iControlledByPlayer;
		int m_iBotDifficulty;
		int m_szClan;
		int m_iTotalCashSpent;
		int m_iCashSpentThisRound;
		int m_nEndMatchNextMapVotes;
		int m_bEndMatchNextMapAllVoted;
		int m_nActiveCoinRank;
		int m_nMusicID;
		int m_nPersonaDataPublicLevel;
		int m_nPersonaDataPublicCommendsLeader;
		int m_nPersonaDataPublicCommendsTeacher;
		int m_nPersonaDataPublicCommendsFriendly;
	} DT_CSPlayerResource;

	struct
	{
		int m_bBombTicking;
		int m_flC4Blow;
		int m_bBombDefused;
		int m_hBombDefuser;
	} DT_PlantedC4;

	struct
	{
		int m_iShotsFired;
		int m_angEyeAngles[2];
		int m_iAccount;
		int m_totalHitsOnServer;
		int m_ArmorValue;
		int m_bHasDefuser;
		int m_bIsDefusing;
		int m_bIsGrabbingHostage;
		int m_bIsScoped;
		int m_bGunGameImmunity;
		int m_bIsRescuing;
		int m_bHasHelmet;
		int m_flFlashDuration;
		int m_flFlashMaxAlpha;
		int m_flLowerBodyYawTarget;
	} DT_CSPlayer;

	struct
	{
		int m_iItemDefinitionIndex;
		int m_iItemIDHigh;
		int m_iAccountID;
		int m_iEntityQuality;
		int m_szCustomName;
		int m_nFallbackPaintKit;
		int m_nFallbackSeed;
		int m_flFallbackWear;
		int m_nFallbackStatTrak;
	} DT_BaseAttributableItem;

	struct
	{
		int m_nModelIndex;
		int m_hWeapon;
		int m_hOwner;
	} DT_BaseViewModel;

	struct
	{
		int m_fAccuracyPenalty;
	} DT_WeaponCSBase;

	struct
	{
		int m_bStartedArming;
	} DT_WeaponC4;

	struct
	{
		int m_flNextPrimaryAttack;
		int m_hOwner;
		int m_iClip1;
		int m_bInReload;
	} DT_BaseCombatWeapon;

	struct
	{
		int m_bShouldGlow;
	} DT_DynamicProp;

	struct
	{
		int m_bFreezePeriod;
		int m_bMatchWaitingForResume;
		int m_bWarmupPeriod;
		int m_fWarmupPeriodEnd;
		int m_fWarmupPeriodStart;
		int m_bTerroristTimeOutActive;
		int m_bCTTimeOutActive;
		int m_flTerroristTimeOutRemaining;
		int m_flCTTimeOutRemaining;
		int m_nTerroristTimeOuts;
		int m_nCTTimeOuts;
		int m_iRoundTime;
		int m_gamePhase;
		int m_totalRoundsPlayed;
		int m_nOvertimePlaying;
		int m_timeUntilNextPhaseStarts;
		int m_flCMMItemDropRevealStartTime;
		int m_flCMMItemDropRevealEndTime;
		int m_fRoundStartTime;
		int m_bGameRestart;
		int m_flRestartRoundTime;
		int m_flGameStartTime;
		int m_iHostagesRemaining;
		int m_bAnyHostageReached;
		int m_bMapHasBombTarget;
		int m_bMapHasRescueZone;
		int m_bMapHasBuyZone;
		int m_bIsQueuedMatchmaking;
		int m_bIsValveDS;
		int m_bIsQuestEligible;
		int m_bLogoMap;
		int m_iNumGunGameProgressiveWeaponsCT;
		int m_iNumGunGameProgressiveWeaponsT;
		int m_iSpectatorSlotCount;
		int m_bBombDropped;
		int m_bBombPlanted;
		int m_iRoundWinStatus;
		int m_eRoundWinReason;
		int m_flDMBonusStartTime;
		int m_flDMBonusTimeLength;
		int m_unDMBonusWeaponLoadoutSlot;
		int m_bDMBonusActive;
		int m_bTCantBuy;
		int m_bCTCantBuy;
		int m_flGuardianBuyUntilTime;
		int m_iMatchStats_RoundResults;
		int m_iMatchStats_PlayersAlive_T;
		int m_iMatchStats_PlayersAlive_CT;
		int m_GGProgressiveWeaponOrderC;
		int m_GGProgressiveWeaponOrderT;
		int m_GGProgressiveWeaponKillUpgradeOrderCT;
		int m_GGProgressiveWeaponKillUpgradeOrderT;
		int m_MatchDevice;
		int m_bHasMatchStarted;
		int m_TeamRespawnWaveTimes;
		int m_flNextRespawnWave;
		int m_nNextMapInMapgroup;
		int m_nEndMatchMapGroupVoteOptions;
		int m_bIsDroppingItems;
		int m_iActiveAssassinationTargetMissionID;
		int m_fMatchStartTime;
		int m_szTournamentEventName;
		int m_szTournamentEventStage;
		int m_szTournamentPredictionsTxt;
		int m_nTournamentPredictionsPct;
		int m_szMatchStatTxt;
		int m_nGuardianModeWaveNumber;
		int m_nGuardianModeSpecialKillsRemaining;
		int m_nGuardianModeSpecialWeaponNeeded;
		int m_nHalloweenMaskListSeed;
		int m_numGlobalGiftsGiven;
		int m_numGlobalGifters;
		int m_numGlobalGiftsPeriodSeconds;
		int m_arrFeaturedGiftersAccounts;
		int m_arrFeaturedGiftersGifts;
		int m_arrTournamentActiveCasterAccounts;
	} DT_CSGameRulesProxy;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;