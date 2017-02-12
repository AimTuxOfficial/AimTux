#pragma once

#include <cstdio>
#include "SDK/vector.h"

struct COffsets
{
	struct
	{
		std::ptrdiff_t m_Local;
		std::ptrdiff_t m_aimPunchAngle;
		std::ptrdiff_t m_viewPunchAngle;
		std::ptrdiff_t m_vecViewOffset;
		std::ptrdiff_t m_nTickBase;
		std::ptrdiff_t m_vecVelocity;
		std::ptrdiff_t m_iHealth;
		std::ptrdiff_t m_lifeState;
		std::ptrdiff_t m_fFlags;
		std::ptrdiff_t m_iObserverMode;
		std::ptrdiff_t m_hObserverTarget;
		std::ptrdiff_t m_hViewModel;
		std::ptrdiff_t m_szLastPlaceName;
		std::ptrdiff_t deadflag;
	} DT_BasePlayer;

	struct
	{
		std::ptrdiff_t m_flAnimTime;
		std::ptrdiff_t m_flSimulationTime;
		std::ptrdiff_t m_vecOrigin;
		std::ptrdiff_t m_nRenderMode;
		std::ptrdiff_t m_iTeamNum;
		std::ptrdiff_t m_MoveType;
		std::ptrdiff_t m_Collision;
		std::ptrdiff_t m_bSpotted;
	} DT_BaseEntity;

	struct
	{
		std::ptrdiff_t m_hActiveWeapon;
		std::ptrdiff_t m_hMyWeapons;
		std::ptrdiff_t m_hMyWearables;
	} DT_BaseCombatCharacter;

	struct
	{
		std::ptrdiff_t m_iPing;
		std::ptrdiff_t m_iKills;
		std::ptrdiff_t m_iAssists;
		std::ptrdiff_t m_iDeaths;
		std::ptrdiff_t m_bConnected;
		std::ptrdiff_t m_iTeam;
		std::ptrdiff_t m_iPendingTeam;
		std::ptrdiff_t m_bAlive;
		std::ptrdiff_t m_iHealth;
	} DT_PlayerResource;

	struct
	{
		std::ptrdiff_t m_iPlayerC4;
		std::ptrdiff_t m_iPlayerVIP;
		std::ptrdiff_t m_bHostageAlive;
		std::ptrdiff_t m_isHostageFollowingSomeone;
		std::ptrdiff_t m_iHostageEntityIDs;
		std::ptrdiff_t m_bombsiteCenterB;
		std::ptrdiff_t m_hostageRescueX;
		std::ptrdiff_t m_hostageRescueY;
		std::ptrdiff_t m_hostageRescueZ;
		std::ptrdiff_t m_iMVPs;
		std::ptrdiff_t m_iArmor;
		std::ptrdiff_t m_bHasHelmet;
		std::ptrdiff_t m_bHasDefuser;
		std::ptrdiff_t m_iScore;
		std::ptrdiff_t m_iCompetitiveRanking;
		std::ptrdiff_t m_iCompetitiveWins;
		std::ptrdiff_t m_iCompTeammateColor;
		std::ptrdiff_t m_bControllingBot;
		std::ptrdiff_t m_iControlledPlayer;
		std::ptrdiff_t m_iControlledByPlayer;
		std::ptrdiff_t m_iBotDifficulty;
		std::ptrdiff_t m_szClan;
		std::ptrdiff_t m_iTotalCashSpent;
		std::ptrdiff_t m_iCashSpentThisRound;
		std::ptrdiff_t m_nEndMatchNextMapVotes;
		std::ptrdiff_t m_bEndMatchNextMapAllVoted;
		std::ptrdiff_t m_nActiveCoinRank;
		std::ptrdiff_t m_nMusicID;
		std::ptrdiff_t m_nPersonaDataPublicLevel;
		std::ptrdiff_t m_nPersonaDataPublicCommendsLeader;
		std::ptrdiff_t m_nPersonaDataPublicCommendsTeacher;
		std::ptrdiff_t m_nPersonaDataPublicCommendsFriendly;
	} DT_CSPlayerResource;

	struct
	{
		std::ptrdiff_t m_bBombTicking;
		std::ptrdiff_t m_flC4Blow;
		std::ptrdiff_t m_bBombDefused;
		std::ptrdiff_t m_hBombDefuser;
	} DT_PlantedC4;

	struct
	{
		std::ptrdiff_t m_iShotsFired;
		std::ptrdiff_t m_angEyeAngles[2];
		std::ptrdiff_t m_iAccount;
		std::ptrdiff_t m_totalHitsOnServer;
		std::ptrdiff_t m_ArmorValue;
		std::ptrdiff_t m_bHasDefuser;
		std::ptrdiff_t m_bIsDefusing;
		std::ptrdiff_t m_bIsGrabbingHostage;
		std::ptrdiff_t m_bIsScoped;
		std::ptrdiff_t m_bGunGameImmunity;
		std::ptrdiff_t m_bIsRescuing;
		std::ptrdiff_t m_bHasHelmet;
		std::ptrdiff_t m_flFlashDuration;
		std::ptrdiff_t m_flFlashMaxAlpha;
		std::ptrdiff_t m_flLowerBodyYawTarget;
	} DT_CSPlayer;

	struct
	{
		std::ptrdiff_t m_iItemDefinitionIndex;
		std::ptrdiff_t m_iItemIDHigh;
		std::ptrdiff_t m_iAccountID;
		std::ptrdiff_t m_iEntityQuality;
		std::ptrdiff_t m_szCustomName;
		std::ptrdiff_t m_nFallbackPaintKit;
		std::ptrdiff_t m_nFallbackSeed;
		std::ptrdiff_t m_flFallbackWear;
		std::ptrdiff_t m_nFallbackStatTrak;
	} DT_BaseAttributableItem;

	struct
	{
		std::ptrdiff_t m_nModelIndex;
		std::ptrdiff_t m_hWeapon;
		std::ptrdiff_t m_hOwner;
	} DT_BaseViewModel;

	struct
	{
		std::ptrdiff_t m_fAccuracyPenalty;
	} DT_WeaponCSBase;

	struct
	{
		std::ptrdiff_t m_bStartedArming;
	} DT_WeaponC4;

	struct
	{
		std::ptrdiff_t m_bRedraw;
		std::ptrdiff_t m_bIsHeldByPlayer;
		std::ptrdiff_t m_bPinPulled;
		std::ptrdiff_t m_fThrowTime;
		std::ptrdiff_t m_bLoopingSoundPlaying;
		std::ptrdiff_t m_flThrowStrength;
	} DT_BaseCSGrenade;

	struct
	{
		std::ptrdiff_t m_flNextPrimaryAttack;
		std::ptrdiff_t m_hOwner;
		std::ptrdiff_t m_iClip1;
		std::ptrdiff_t m_bInReload;
	} DT_BaseCombatWeapon;

	struct
	{
		std::ptrdiff_t m_bShouldGlow;
	} DT_DynamicProp;

	struct
	{
		std::ptrdiff_t m_bFreezePeriod;
		std::ptrdiff_t m_bMatchWaitingForResume;
		std::ptrdiff_t m_bWarmupPeriod;
		std::ptrdiff_t m_fWarmupPeriodEnd;
		std::ptrdiff_t m_fWarmupPeriodStart;
		std::ptrdiff_t m_bTerroristTimeOutActive;
		std::ptrdiff_t m_bCTTimeOutActive;
		std::ptrdiff_t m_flTerroristTimeOutRemaining;
		std::ptrdiff_t m_flCTTimeOutRemaining;
		std::ptrdiff_t m_nTerroristTimeOuts;
		std::ptrdiff_t m_nCTTimeOuts;
		std::ptrdiff_t m_iRoundTime;
		std::ptrdiff_t m_gamePhase;
		std::ptrdiff_t m_totalRoundsPlayed;
		std::ptrdiff_t m_nOvertimePlaying;
		std::ptrdiff_t m_timeUntilNextPhaseStarts;
		std::ptrdiff_t m_flCMMItemDropRevealStartTime;
		std::ptrdiff_t m_flCMMItemDropRevealEndTime;
		std::ptrdiff_t m_fRoundStartTime;
		std::ptrdiff_t m_bGameRestart;
		std::ptrdiff_t m_flRestartRoundTime;
		std::ptrdiff_t m_flGameStartTime;
		std::ptrdiff_t m_iHostagesRemaining;
		std::ptrdiff_t m_bAnyHostageReached;
		std::ptrdiff_t m_bMapHasBombTarget;
		std::ptrdiff_t m_bMapHasRescueZone;
		std::ptrdiff_t m_bMapHasBuyZone;
		std::ptrdiff_t m_bIsQueuedMatchmaking;
		std::ptrdiff_t m_bIsValveDS;
		std::ptrdiff_t m_bIsQuestEligible;
		std::ptrdiff_t m_bLogoMap;
		std::ptrdiff_t m_iNumGunGameProgressiveWeaponsCT;
		std::ptrdiff_t m_iNumGunGameProgressiveWeaponsT;
		std::ptrdiff_t m_iSpectatorSlotCount;
		std::ptrdiff_t m_bBombDropped;
		std::ptrdiff_t m_bBombPlanted;
		std::ptrdiff_t m_iRoundWinStatus;
		std::ptrdiff_t m_eRoundWinReason;
		std::ptrdiff_t m_flDMBonusStartTime;
		std::ptrdiff_t m_flDMBonusTimeLength;
		std::ptrdiff_t m_unDMBonusWeaponLoadoutSlot;
		std::ptrdiff_t m_bDMBonusActive;
		std::ptrdiff_t m_bTCantBuy;
		std::ptrdiff_t m_bCTCantBuy;
		std::ptrdiff_t m_flGuardianBuyUntilTime;
		std::ptrdiff_t m_iMatchStats_RoundResults;
		std::ptrdiff_t m_iMatchStats_PlayersAlive_T;
		std::ptrdiff_t m_iMatchStats_PlayersAlive_CT;
		std::ptrdiff_t m_GGProgressiveWeaponOrderC;
		std::ptrdiff_t m_GGProgressiveWeaponOrderT;
		std::ptrdiff_t m_GGProgressiveWeaponKillUpgradeOrderCT;
		std::ptrdiff_t m_GGProgressiveWeaponKillUpgradeOrderT;
		std::ptrdiff_t m_MatchDevice;
		std::ptrdiff_t m_bHasMatchStarted;
		std::ptrdiff_t m_TeamRespawnWaveTimes;
		std::ptrdiff_t m_flNextRespawnWave;
		std::ptrdiff_t m_nNextMapInMapgroup;
		std::ptrdiff_t m_nEndMatchMapGroupVoteOptions;
		std::ptrdiff_t m_bIsDroppingItems;
		std::ptrdiff_t m_iActiveAssassinationTargetMissionID;
		std::ptrdiff_t m_fMatchStartTime;
		std::ptrdiff_t m_szTournamentEventName;
		std::ptrdiff_t m_szTournamentEventStage;
		std::ptrdiff_t m_szTournamentPredictionsTxt;
		std::ptrdiff_t m_nTournamentPredictionsPct;
		std::ptrdiff_t m_szMatchStatTxt;
		std::ptrdiff_t m_nGuardianModeWaveNumber;
		std::ptrdiff_t m_nGuardianModeSpecialKillsRemaining;
		std::ptrdiff_t m_nGuardianModeSpecialWeaponNeeded;
		std::ptrdiff_t m_nHalloweenMaskListSeed;
		std::ptrdiff_t m_numGlobalGiftsGiven;
		std::ptrdiff_t m_numGlobalGifters;
		std::ptrdiff_t m_numGlobalGiftsPeriodSeconds;
		std::ptrdiff_t m_arrFeaturedGiftersAccounts;
		std::ptrdiff_t m_arrFeaturedGiftersGifts;
		std::ptrdiff_t m_arrTournamentActiveCasterAccounts;
	} DT_CSGameRulesProxy;
};

namespace Offsets
{
	void GetOffsets();
}

extern COffsets offsets;
