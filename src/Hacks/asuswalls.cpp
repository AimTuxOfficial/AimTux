#include "asuswalls.h"

bool Settings::ASUSWalls::enabled = false;
ColorVar Settings::ASUSWalls::color = ImColor(255, 255, 255, 150);
float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

std::unordered_map<MaterialHandle_t, ImColor> worldMaterials;
std::unordered_map<MaterialHandle_t, ImColor> worldMaterials2;

void ASUSWalls::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame() && worldMaterials.size() > 0)
	{
		for (const auto& it : worldMaterials)
		{
			IMaterial* mat = material->GetMaterial(it.first);

			if (!mat)
				continue;

			mat->GetColorModulate(&r, &g, &b);
			a = mat->GetAlphaModulation();

			mat->ColorModulate(r, g, b);
			mat->AlphaModulate(a);
		}

		worldMaterials.clear();
		worldMaterials2.clear();
	}

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = material->FirstMaterial(); i != material->InvalidMaterial(); i = material->NextMaterial(i))
	{
		IMaterial* mat = material->GetMaterial(i);

		if (!mat || strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_WORLD) != 0)
			continue;

		if (worldMaterials.find(i) == worldMaterials.end())
		{
			mat->GetColorModulate(&r, &g, &b);
			a = mat->GetAlphaModulation();
			worldMaterials.emplace(i, ImColor(r, g, b, a));
			worldMaterials2.emplace(i, ImColor(r, g, b, a));
		}

		ImColor color = (Settings::ASUSWalls::enabled && Settings::ESP::enabled) ? Settings::ASUSWalls::color.Color() : worldMaterials2.find(i)->second;

		if (worldMaterials.at(i) != color)
		{

			mat->ColorModulate(color);
			mat->AlphaModulate(color.Value.w);

			worldMaterials.at(i) = color;
		}
	}
}
