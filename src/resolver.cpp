#include "resolver.h"

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
		//
		
		for (int i = 1; i < entitylist->GetHighestEntityIndex(); ++i)
		{
			C_BaseEntity* entity = entitylist->GetClientEntity(i);
			
			if (!entity
				|| entity == localplayer
				|| entity->GetDormant()
				|| !entity->GetAlive()
				|| entity->GetImmune()
				|| entity->GetTeam() == localplayer->GetTeam())
				continue;
			
			ClientClass* client = entity->GetClientClass();
			if (client->m_ClassID == CCSPlayer)
			{
				C_BasePlayer* player = (C_BasePlayer*)entity;
				
				player_data.push_back (PlayerAA(player, *player->GetHeadRotation()));
				
				player->GetHeadRotation()->y = *player->GetLowerBodyYawTarget();
				
			}
		}
	}
	else
	if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (int i = 0; i < player_data.size(); i++)
		{
			PlayerAA player_aa_data = player_data[i];
			
			*player_aa_data.player->GetHeadRotation () = player_aa_data.angle;
		}
		
		player_data.clear();
		
	}
}



void Resolver::PostFrameStageNotify(ClientFrameStage_t stage)
{
}



