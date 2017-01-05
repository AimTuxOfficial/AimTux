#include "nosky.h"

bool Settings::NoSky::enabled = false;
ImColor Settings::NoSky::color = ImColor(0, 0, 0, 255);

std::unordered_map<MaterialHandle_t, ImColor> skyboxMaterials;

void NoSky::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame() && skyboxMaterials.size() > 0)
	{
		for (const auto& it: skyboxMaterials)
		{
			IMaterial *mat = material->GetMaterial(it.first);

			if (!mat)
				continue;

			mat->ColorModulate(1, 1, 1);
			mat->AlphaModulate(1);
		}

		skyboxMaterials.clear();
	}
	
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = material->FirstMaterial(); i != material->InvalidMaterial(); i = material->NextMaterial(i))
	{
		IMaterial *mat = material->GetMaterial(i);

		if (!mat || strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX) != 0)
			continue;

		if (skyboxMaterials.find(i) == skyboxMaterials.end())
			skyboxMaterials.emplace(i, ImColor());

		ImColor color = Settings::NoSky::enabled ? Settings::NoSky::color: ImColor(255, 255, 255, 255);

		if (skyboxMaterials.at(i) != color)
		{
			mat->ColorModulate(color);

			skyboxMaterials.at(i) = color;
		}
	}
}