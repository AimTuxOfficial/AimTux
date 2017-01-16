#include "resolver.h"

bool Settings::Resolver::resolve_all = false;

std::vector<int64_t> Resolver::Players = { };

std::vector<PlayerAA> player_data;

PlayerAA* GetPlayerAA(C_BasePlayer* player)
{
	unsigned int i = 0;
	for (; i < player_data.size(); i++)
	{
		if (player_data[i].player == player)
			return &player_data[i];
	}
	
	// Player was not found, add it:
	
	player_data.push_back (PlayerAA(player, *player->GetEyeAngles()));
	
	return &player_data[i+1];
}

void Resolver::HookProxies ()
{
	NetVarManager::HookProp ("DT_CSPlayer", "m_flLowerBodyYawTarget", (RecvVarProxyFn)Resolver::LowerBodyYawTargetProxy);
}

void Resolver::LowerBodyYawTargetProxy(const CRecvProxyData* pData, C_BaseEntity* ent, void* pOut)
{
	float lower_body_yaw = pData->m_Value.m_Float;
	
	C_BasePlayer* entity_player = (C_BasePlayer*)ent;
	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	
	if (entity_player == localplayer)
		return;
	
	PlayerAA* player_aa = GetPlayerAA (entity_player);
	
	player_aa->resolved_y_axis = lower_body_yaw;
	
	cvar->ConsoleDPrintf("Resolved y axis: %f\n", lower_body_yaw);
	
	*(float*)pOut = lower_body_yaw;
}

void Resolver::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < engine->GetMaxClients(); ++i)
		{
			C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(i);

			if (!player
				|| player == localplayer
				|| player->GetDormant()
				|| !player->GetAlive()
				|| player->GetImmune()
				|| player->GetTeam() == localplayer->GetTeam())
				continue;

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			if (!Settings::Resolver::resolve_all && std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) == Resolver::Players.end())
				continue;

			PlayerAA* pdata = GetPlayerAA (player);
			
			pdata->reset_y_axis = player->GetEyeAngles()->y;
			
			player->GetEyeAngles()->y = pdata->resolved_y_axis;
		}
	}
	else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (unsigned long i = 0; i < player_data.size(); i++)
		{
			PlayerAA player_aa_data = player_data[i];

			player_aa_data.player->GetEyeAngles()->y = player_aa_data.reset_y_axis;
		}
	}
}

void Resolver::PostFrameStageNotify(ClientFrameStage_t stage)
{
}

void Resolver::FireEventClientSide(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") == 0 || strcmp(event->GetName(), "cs_game_disconnected") == 0)
	{
		if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
			return;

		Resolver::Players.clear();
	}
}
