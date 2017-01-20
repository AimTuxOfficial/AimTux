#pragma once

class CMoveData;

class IGameMovement
{
public:
	void ProcessMovement(IClientEntity* player, CMoveData* move)
	{
		typedef void (* oProcessMovement)(void*, IClientEntity*, CMoveData*);
		return getvfunc<oProcessMovement>(this, 2)(this, player, move);
	}

	void StartTrackPredictionErrors(IClientEntity* player)
	{
		typedef void (* oStartTrackPredictionErrors)(void*, IClientEntity*);
		return getvfunc<oStartTrackPredictionErrors>(this, 4)(this, player);
	}

	void FinishTrackPredictionErrors(IClientEntity* player)
	{
		typedef void (* oFinishTrackPredictionErrors)(void*, IClientEntity*);
		return getvfunc<oFinishTrackPredictionErrors>(this, 5)(this, player);
	}
};

class IMoveHelper
{
public:
	void SetHost(IClientEntity* host)
	{
		typedef void (* oSetHost)(void*, IClientEntity*);
		return getvfunc<oSetHost>(this, 1)(this, host);
	}
};