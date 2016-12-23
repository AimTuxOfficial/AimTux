#include "asuswalls.h"

bool Settings::ASUSWalls::enabled = false;
ImColor Settings::ASUSWalls::color = ImColor(255, 255, 255, 150);

void ASUSWalls::FrameStageNotify(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = material->FirstMaterial(); i != material->InvalidMaterial(); i = material->NextMaterial(i))
	{
		IMaterial *mat = material->GetMaterial(i);

		if (strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_WORLD) != 0)
			continue;

		if (Settings::ASUSWalls::enabled)
		{
			mat->ColorModulate(Settings::ASUSWalls::color);
			mat->AlphaModulate(Settings::ASUSWalls::color.Value.w);
		}
		else
		{
			mat->ColorModulate(1, 1, 1);
			mat->AlphaModulate(1);
		}
	}
}