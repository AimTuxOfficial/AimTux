#include "skybox.h"

#include "../settings.h"
#include "../interfaces.h"

float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f, a1 = 0.0f;

std::unordered_map<MaterialHandle_t, ImColor> skyboxMaterials;
std::unordered_map<MaterialHandle_t, ImColor> skyboxMaterials2;

const char* skyBoxNames[] = {
		"cs_baggage_skybox_", // 0
		"cs_tibet",
		"embassy",
		"italy",
		"jungle",
		"office",
		"nukeblank",
		"sky_venice",
		"sky_cs15_daylight01_hdr",
		"sky_cs15_daylight02_hdr",
		"sky_cs15_daylight03_hdr",
		"sky_cs15_daylight04_hdr",
		"sky_csgo_cloudy01",
		"sky_csgo_night_flat",
		"sky_csgo_night02",
		"sky_csgo_night02b",
		"sky_day02_05",
		"sky_day02_05_hdr",
		"sky_dust",
		"vertigo",
		"vertigo_hdr",
		"vertigoblue_hdr",
		"vietnam" // 22
};

int lastSetSkybox = -1;
bool resetSkyBox = false;

void SkyBox::FrameStageNotify(ClientFrameStage_t stage)
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

	if( engine->IsInGame() && Settings::ESP::enabled && Settings::SkyBox::enabled ) {
		if( lastSetSkybox != Settings::SkyBox::skyBoxNumber ){
			SetNamedSkyBox(skyBoxNames[Settings::SkyBox::skyBoxNumber]); // Thanks to @Flawww
			lastSetSkybox = Settings::SkyBox::skyBoxNumber;
			resetSkyBox = true;
		}
		return;
	} else if( resetSkyBox ){
		SetNamedSkyBox( cvar->FindVar("sv_skyname")->strValue );
		resetSkyBox = false;
        lastSetSkybox = -1;
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

		ImColor color = (Settings::NoSky::enabled && Settings::ESP::enabled && !Settings::SkyBox::enabled) ? Settings::NoSky::color.Color() : skyboxMaterials2.find(i)->second;

		if (skyboxMaterials.at(i) != color)
		{
			mat->ColorModulate(color);

			skyboxMaterials.at(i) = color;
		}
	}


}
