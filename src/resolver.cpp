#include "resolver.h"

std::vector<int64_t> Resolver::Players = { };

std::vector<PlayerAA> player_data;

void Resolver::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < engine->GetMaxClients(); ++i)
		{
			C_BaseEntity* entity = entitylist->GetClientEntity(i);

			if (!entity
				|| entity == localplayer
				|| entity->GetDormant()
				|| !entity->GetAlive()
				|| entity->GetImmune()
				|| entity->GetTeam() == localplayer->GetTeam())
				continue;

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			if (std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) != Resolver::Players.end())
				continue;

			C_BasePlayer* player = (C_BasePlayer*)entity;

			player_data.push_back(PlayerAA(player, *player->GetHeadRotation()));

			player->GetHeadRotation()->y = *player->GetLowerBodyYawTarget();
		}
	}
	else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (unsigned long i = 0; i < player_data.size(); i++)
		{
			PlayerAA player_aa_data = player_data[i];

			*player_aa_data.player->GetHeadRotation() = player_aa_data.angle;
		}

		player_data.clear();
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
		if (event->GetInt("userid") || engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
			return;

		Resolver::Players.clear();
	}
}