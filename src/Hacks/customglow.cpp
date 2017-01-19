#include "customglow.h"

std::vector<std::pair<int, int>> custom_glow_entities;

void CustomGlow::FrameStageNotify(ClientFrameStage_t stage)
{
	// Skip reserved slots that are guaranteed to be managed by the engine.
	for (int i = 64; i < entitylist->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		// Register custom entities into the glow object definitions array.
		if (engine->IsInGame() && entity && entity->GetClientClass()->m_ClassID == CBaseAnimating)
		{
			if (!glowmanager->HasGlowEffect(entity))
			{
				int array_index = glowmanager->RegisterGlowObject(entity);

				if (array_index != -1)
					custom_glow_entities.emplace_back(i, array_index);
			}
		}
		else
		{
			// Remove any entities that no longer exist.
			auto iterator = std::find_if(custom_glow_entities.begin(), custom_glow_entities.end(),
				[&] (const std::pair<int, int>& p) {
					return p.first == i;
				}
			);

			if (iterator != custom_glow_entities.end())
			{
				glowmanager->UnregisterGlowObject(iterator->second);
				custom_glow_entities.erase(iterator);
			}
		}
	}
}
