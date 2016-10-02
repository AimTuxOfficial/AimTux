#include "noflash.h"

bool Settings::Noflash::enabled = true;

void Noflash::DrawModelExecute(void* context, void *state, const ModelRenderInfo_t &pInfo)
{
	if (!Settings::Noflash::enabled)
		return;

	if (!pInfo.pModel)
		return;

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);
	if (modelName.find("flash") == std::string::npos)
		return;

	IMaterial* Flash = material->FindMaterial("effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);
	IMaterial* FlashWhite = material->FindMaterial("effects\\flashbang_white", TEXTURE_GROUP_CLIENT_EFFECTS);

	Flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
	FlashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

	modelRender->ForcedMaterialOverride(Flash);
	modelRender->ForcedMaterialOverride(FlashWhite);
}
