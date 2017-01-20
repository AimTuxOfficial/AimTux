#pragma once

class IPrediction
{
public:
	void SetupMove(IClientEntity* player, CUserCmd* cmd, IMoveHelper* helper, CMoveData* move) 
	{
		typedef void (* oSetupMove)(void*, IClientEntity*, CUserCmd*, IMoveHelper*, CMoveData*);
		return getvfunc<oSetupMove>(this, 21)(this, player, cmd, helper, move);
	}

	void FinishMove(IClientEntity* player, CUserCmd* cmd, CMoveData* move)
	{
		typedef void (* oFinishMove)(void*, IClientEntity*, CUserCmd*, CMoveData*);
		return getvfunc<oFinishMove>(this, 22)(this, player, cmd, move);
	}
};