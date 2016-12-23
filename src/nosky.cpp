#include "nosky.h"

bool Settings::NoSky::enabled = false;
ImColor Settings::NoSky::color = ImColor(0, 0, 0, 255);

void NoSky::FrameStageNotify(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = material->FirstMaterial(); i != material->InvalidMaterial(); i = material->NextMaterial(i))
	{
		IMaterial *mat = material->GetMaterial(i);

		if (strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX) != 0)
			continue;

		if (Settings::NoSky::enabled)
		{
			mat->ColorModulate(
				Settings::NoSky::color.Value.x,
				Settings::NoSky::color.Value.y,
				Settings::NoSky::color.Value.z
			);
		}
		else
		{
			mat->ColorModulate(1, 1, 1);
		}
	}
}