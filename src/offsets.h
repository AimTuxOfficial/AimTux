#pragma once

#include <cstdio>
#include "SDK/vector.h"

struct COffsets
{
	struct {
		ptrdiff_t m_Local;
		ptrdiff_t m_aimPunchAngle;
		ptrdiff_t m_viewPunchAngle;
		ptrdiff_t m_vecViewOffset;
		ptrdiff_t m_nTickBase;
		ptrdiff_t m_vecVelocity;
		ptrdiff_t m_iHealth;
		ptrdiff_t m_lifeState;
		ptrdiff_t m_fFlags;
		ptrdiff_t m_iObserverMode;
		ptrdiff_t m_hObserverTarget;
		ptrdiff_t m_hViewModel;
		ptrdiff_t m_szLastPlaceName;
	} DT_BasePlayer;

	struct
	{
		ptrdiff_t m_vecOrigin;
		ptrdiff_t m_nRenderMode;
		ptrdiff_t m_iTeamNum;
		ptrdiff_t m_MoveType;
		ptrdiff_t m_Collision;
		ptrdiff_t m_bSpotted;
	} DT_BaseEntity;

	struct
	{
		ptrdiff_t m_hActiveWeapon;
		ptrdiff_t m_hMyWeapons;
	} DT_BaseCombatCharacter;

	struct
	{
		ptrdiff_t m_iPing;
		ptrdiff_t m_iKills;
		ptrdiff_t m_iAssists;
		ptrdiff_t m_iDeaths;
		ptrdiff_t m_bConnected;
		ptrdiff_t m_iTeam;
		ptrdiff_t m_iPendingTeam;
		ptrdiff_t m_bAlive;
		ptrdiff_t m_iHealth;
	} DT_PlayerResource;

	struct
	{
		ptrdiff_t m_iPlayerC4;
		ptrdiff_t m_iPlayerVIP;
		ptrdiff_t m_bHostageAlive;
		ptrdiff_t m_isHostageFollowingSomeone;
		ptrdiff_t m_iHostageEntityIDs;
		ptrdiff_t m_bombsiteCenterB;
		ptrdiff_t m_hostageRescueX;
		ptrdiff_t m_hostageRescueY;
		ptrdiff_t m_hostageRescueZ;
		ptrdiff_t m_iMVPs;
		ptrdiff_t m_iArmor;
		ptrdiff_t m_bHasHelmet;
		ptrdiff_t m_bHasDefuser;
		ptrdiff_t m_iScore;
		ptrdiff_t m_iCompetitiveRanking;
		ptrdiff_t m_iCompetitiveWins;
		ptrdiff_t m_iCompTeammateColor;
		ptrdiff_t m_bControllingBot;
		ptrdiff_t m_iControlledPlayer;
		ptrdiff_t m_iControlledByPlayer;
		ptrdiff_t m_iBotDifficulty;
		ptrdiff_t m_szClan;
		ptrdiff_t m_iTotalCashSpent;
		ptrdiff_t m_iCashSpentThisRound;
		ptrdiff_t m_nEndMatchNextMapVotes;
		ptrdiff_t m_bEndMatchNextMapAllVoted;
		ptrdiff_t m_nActiveCoinRank;
		ptrdiff_t m_nMusicID;
		ptrdiff_t m_nPersonaDataPublicLevel;
		ptrdiff_t m_nPersonaDataPublicCommendsLeader;
		ptrdiff_t m_nPersonaDataPublicCommendsTeacher;
		ptrdiff_t m_nPersonaDataPublicCommendsFriendly;
	} DT_CSPlayerResource;

	struct
	{
		ptrdiff_t m_bBombTicking;
		ptrdiff_t m_flC4Blow;
		ptrdiff_t m_bBombDefused;
		ptrdiff_t m_hBombDefuser;
	} DT_PlantedC4;

	struct
	{
		ptrdiff_t m_iShotsFired;
		ptrdiff_t m_angEyeAngles[2];
		ptrdiff_t m_iAccount;
		ptrdiff_t m_totalHitsOnServer;
		ptrdiff_t m_ArmorValue;
		ptrdiff_t m_bHasDefuser;
		ptrdiff_t m_bIsDefusing;
		ptrdiff_t m_bIsGrabbingHostage;
		ptrdiff_t m_bIsScoped;
		ptrdiff_t m_bGunGameImmunity;
		ptrdiff_t m_bIsRescuing;
		ptrdiff_t m_bHasHelmet;
		ptrdiff_t m_flFlashDuration;
		ptrdiff_t m_flFlashMaxAlpha;
		ptrdiff_t m_flLowerBodyYawTarget;
	} DT_CSPlayer;

	struct
	{
		ptrdiff_t m_iItemDefinitionIndex;
		ptrdiff_t m_iItemIDHigh;
		ptrdiff_t m_iAccountID;
		ptrdiff_t m_iEntityQuality;
		ptrdiff_t m_szCustomName;
		ptrdiff_t m_nFallbackPaintKit;
		ptrdiff_t m_nFallbackSeed;
		ptrdiff_t m_flFallbackWear;
		ptrdiff_t m_nFallbackStatTrak;
	} DT_BaseAttributableItem;

	struct
	{
		ptrdiff_t m_nModelIndex;
		ptrdiff_t m_hWeapon;
		ptrdiff_t m_hOwner;
	} DT_BaseViewModel;

	struct
	{
		ptrdiff_t m_fAccuracyPenalty;
	} DT_WeaponCSBase;

	struct
	{
		ptrdiff_t m_bStartedArming;
	} DT_WeaponC4;

	struct
	{
		ptrdiff_t m_flNextPrimaryAttack;
		ptrdiff_t m_hOwner;
		ptrdiff_t m_iClip1;
		ptrdiff_t m_bInReload;
	} DT_BaseCombatWeapon;

	struct
	{
		ptrdiff_t m_bShouldGlow;
	} DT_DynamicProp;

	struct
	{
		ptrdiff_t m_bFreezePeriod;
		ptrdiff_t m_bMatchWaitingForResume;
		ptrdiff_t m_bWarmupPeriod;
		ptrdiff_t m_fWarmupPeriodEnd;
		ptrdiff_t m_fWarmupPeriodStart;
		ptrdiff_t m_bTerroristTimeOutActive;
		ptrdiff_t m_bCTTimeOutActive;
		ptrdiff_t m_flTerroristTimeOutRemaining;
		ptrdiff_t m_flCTTimeOutRemaining;
		ptrdiff_t m_nTerroristTimeOuts;
		ptrdiff_t m_nCTTimeOuts;
		ptrdiff_t m_iRoundTime;
		ptrdiff_t m_gamePhase;
		ptrdiff_t m_totalRoundsPlayed;
		ptrdiff_t m_nOvertimePlaying;
		ptrdiff_t m_timeUntilNextPhaseStarts;
		ptrdiff_t m_flCMMItemDropRevealStartTime;
		ptrdiff_t m_flCMMItemDropRevealEndTime;
		ptrdiff_t m_fRoundStartTime;
		ptrdiff_t m_bGameRestart;
		ptrdiff_t m_flRestartRoundTime;
		ptrdiff_t m_flGameStartTime;
		ptrdiff_t m_iHostagesRemaining;
		ptrdiff_t m_bAnyHostageReached;
		ptrdiff_t m_bMapHasBombTarget;
		ptrdiff_t m_bMapHasRescueZone;
		ptrdiff_t m_bMapHasBuyZone;
		ptrdiff_t m_bIsQueuedMatchmaking;
		ptrdiff_t m_bIsValveDS;
		ptrdiff_t m_bIsQuestEligible;
		ptrdiff_t m_bLogoMap;
		ptrdiff_t m_iNumGunGameProgressiveWeaponsCT;
		ptrdiff_t m_iNumGunGameProgressiveWeaponsT;
		ptrdiff_t m_iSpectatorSlotCount;
		ptrdiff_t m_bBombDropped;
		ptrdiff_t m_bBombPlanted;
		ptrdiff_t m_iRoundWinStatus;
		ptrdiff_t m_eRoundWinReason;
		ptrdiff_t m_flDMBonusStartTime;
		ptrdiff_t m_flDMBonusTimeLength;
		ptrdiff_t m_unDMBonusWeaponLoadoutSlot;
		ptrdiff_t m_bDMBonusActive;
		ptrdiff_t m_bTCantBuy;
		ptrdiff_t m_bCTCantBuy;
		ptrdiff_t m_flGuardianBuyUntilTime;
		ptrdiff_t m_iMatchStats_RoundResults;
		ptrdiff_t m_iMatchStats_PlayersAlive_T;
		ptrdiff_t m_iMatchStats_PlayersAlive_CT;
		ptrdiff_t m_GGProgressiveWeaponOrderC;
		ptrdiff_t m_GGProgressiveWeaponOrderT;
		ptrdiff_t m_GGProgressiveWeaponKillUpgradeOrderCT;
		ptrdiff_t m_GGProgressiveWeaponKillUpgradeOrderT;
		ptrdiff_t m_MatchDevice;
		ptrdiff_t m_bHasMatchStarted;
		ptrdiff_t m_TeamRespawnWaveTimes;
		ptrdiff_t m_flNextRespawnWave;
		ptrdiff_t m_nNextMapInMapgroup;
		ptrdiff_t m_nEndMatchMapGroupVoteOptions;
		ptrdiff_t m_bIsDroppingItems;
		ptrdiff_t m_iActiveAssassinationTargetMissionID;
		ptrdiff_t m_fMatchStartTime;
		ptrdiff_t m_szTournamentEventName;
		ptrdiff_t m_szTournamentEventStage;
		ptrdiff_t m_szTournamentPredictionsTxt;
		ptrdiff_t m_nTournamentPredictionsPct;
		ptrdiff_t m_szMatchStatTxt;
		ptrdiff_t m_nGuardianModeWaveNumber;
		ptrdiff_t m_nGuardianModeSpecialKillsRemaining;
		ptrdiff_t m_nGuardianModeSpecialWeaponNeeded;
		ptrdiff_t m_nHalloweenMaskListSeed;
		ptrdiff_t m_numGlobalGiftsGiven;
		ptrdiff_t m_numGlobalGifters;
		ptrdiff_t m_numGlobalGiftsPeriodSeconds;
		ptrdiff_t m_arrFeaturedGiftersAccounts;
		ptrdiff_t m_arrFeaturedGiftersGifts;
		ptrdiff_t m_arrTournamentActiveCasterAccounts;
	} DT_CSGameRulesProxy;
};

namespace Offsets
{
	void getOffsets();
}

extern COffsets offsets;