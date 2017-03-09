#include "nosky.h"

bool Settings::NoSky::enabled = false;
ColorVar Settings::NoSky::color = ImColor(0, 0, 0, 255);
float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f, a1 = 0.0f;

std::unordered_map<MaterialHandle_t, ImColor> skyboxMaterials;
std::unordered_map<MaterialHandle_t, ImColor> skyboxMaterials2;

void NoSky::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame() && skyboxMaterials.size() > 0)
	{
		for (const auto& it: skyboxMaterials)
		{
			IMaterial* mat = material->GetMaterial(it.first);

			if (!mat)
				continue;

			mat->GetColorModulate(&r1, &g1, &b1);
			a1 = mat->GetAlphaModulation();

			mat->ColorModulate(r1, g1, b1);
			mat->AlphaModulate(a1);
		}

		skyboxMaterials.clear();
		skyboxMaterials2.clear();
	}
	
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = material->FirstMaterial(); i != material->InvalidMaterial(); i = material->NextMaterial(i))
	{
		IMaterial* mat = material->GetMaterial(i);

		if (!mat || strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX) != 0)
			continue;

		if (skyboxMaterials.find(i) == skyboxMaterials.end())
		{
			mat->GetColorModulate(&r1, &g1, &b1);
			a1 = mat->GetAlphaModulation();
			skyboxMaterials.emplace(i, ImColor(r1, g1, b1, a1));
			skyboxMaterials2.emplace(i, ImColor(r1, g1, b1, a1));
		}

		ImColor color = (Settings::NoSky::enabled && Settings::ESP::enabled) ? Settings::NoSky::color.Color() : skyboxMaterials2.find(i)->second;

		if (skyboxMaterials.at(i) != color)
		{
			mat->ColorModulate(color);

			skyboxMaterials.at(i) = color;
		}
	}
}
