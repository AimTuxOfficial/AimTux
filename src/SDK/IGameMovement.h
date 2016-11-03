#pragma once

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions;
	bool m_bGameCodeMovedPlayer;
	bool m_bNoAirControl;
	unsigned long m_nPlayerHandle;
	int m_nImpulseCommand;
	QAngle m_vecViewAngles;
	QAngle m_vecAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vector m_vecVelocity;
	Vector m_vecOldVelocity;
	float somefloat;
	QAngle m_vecAngles;
	QAngle m_vecOldAngles;
	float m_outStepHeight;
	Vector m_outWishVel;
	Vector m_outJumpVel;
	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	bool m_bConstraintPastRadius;
	Vector m_vecAbsOrigin;
};

class IGameMovement
{
public:
	void ProcessMovement(IClientEntity* player, CMoveData* move)
	{
		typedef void (* oProcessMovement)(void*, IClientEntity*, CMoveData*);
		getvfunc<oProcessMovement>(this, 2)(this, player, move);
	}

	void StartTrackPredictionErrors(IClientEntity* player)
	{
		typedef void (* oStartTrackPredictionErrors)(void*, IClientEntity*);
		getvfunc<oStartTrackPredictionErrors>(this, 4)(this, player);
	}

	void FinishTrackPredictionErrors(IClientEntity* player)
	{
		typedef void (* oFinishTrackPredictionErrors)(void*, IClientEntity*);
		getvfunc<oFinishTrackPredictionErrors>(this, 5)(this, player);
	}
};

class IMoveHelper
{
public:
	void SetHost(IClientEntity* host)
	{
		typedef void (* oSetHost)(void*, IClientEntity*);
		return getvfunc<oSetHost>(this, 2)(this, host);
	}
};