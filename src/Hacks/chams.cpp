#include "chams.h"

bool Settings::ESP::Chams::enabled = false;
bool Settings::ESP::Chams::Arms::enabled = false;
ArmsType Settings::ESP::Chams::Arms::type = ArmsType::DEFAULT;
ImColor Settings::ESP::Chams::ally_color = ImColor(7, 98, 168, 255);
ImColor Settings::ESP::Chams::ally_visible_color = ImColor(40, 52, 138, 255);
ImColor Settings::ESP::Chams::enemy_color = ImColor(243, 24, 28, 255);
ImColor Settings::ESP::Chams::enemy_visible_color = ImColor(243, 159, 20, 255);
bool Settings::ESP::Chams::hp_ally_color = false;
bool Settings::ESP::Chams::hp_ally_visible_color = false;
bool Settings::ESP::Chams::hp_enemy_color = false;
bool Settings::ESP::Chams::hp_enemy_visible_color = false;
ImColor Settings::ESP::Chams::Arms::color = ImColor(117, 43, 73, 255);
ChamsType Settings::ESP::Chams::type = ChamsType::CHAMS;

float rainbowHue;

IMaterial* materialChams;
IMaterial* materialChamsIgnorez;
IMaterial* materialChamsFlat;
IMaterial* materialChamsFlatIgnorez;
IMaterial* materialChamsArms;

void DrawPlayer(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (!Settings::ESP::Chams::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BasePlayer* entity = (C_BasePlayer*) entitylist->GetClientEntity(pInfo.entity_index);
	if (!entity
		|| entity == localplayer
		|| entity->GetDormant()
		|| !entity->GetAlive())
		return;

	IMaterial *visible_material;
	IMaterial *hidden_material;

	switch (Settings::ESP::Chams::type)
	{
		case ChamsType::CHAMS:
		case ChamsType::CHAMS_XQZ:
			visible_material = materialChams;
			hidden_material = materialChamsIgnorez;
			break;
		case ChamsType::CHAMS_FLAT:
		case ChamsType::CHAMS_FLAT_XQZ:
			visible_material = materialChamsFlat;
			hidden_material = materialChamsFlatIgnorez;
			break;
		default:
			break;
	}

	visible_material->AlphaModulate(1.0f);
	hidden_material->AlphaModulate(1.0f);

	if (Settings::ESP::Filters::allies && entity->GetTeam() == localplayer->GetTeam())
	{
		Color visColor = Settings::ESP::Chams::hp_ally_visible_color ? ESP::GetHealthColor(entity) : Color::FromImColor(Settings::ESP::Chams::ally_visible_color);
		Color color = Settings::ESP::Chams::hp_ally_color ? ESP::GetHealthColor(entity) : Color::FromImColor(Settings::ESP::Chams::ally_color);
		visible_material->ColorModulate(visColor);
		hidden_material->ColorModulate(color);
	}
	else if (Settings::ESP::Filters::enemies && entity->GetTeam() != localplayer->GetTeam())
	{
		Color visColor = Settings::ESP::Chams::hp_enemy_visible_color ? ESP::GetHealthColor(entity) : Color::FromImColor(Settings::ESP::Chams::enemy_visible_color);
		Color color = Settings::ESP::Chams::hp_enemy_color ? ESP::GetHealthColor(entity) : Color::FromImColor(Settings::ESP::Chams::enemy_color);
		visible_material->ColorModulate(visColor);
		hidden_material->ColorModulate(color);
	}
	else
		return;

	if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ))
	{
		modelRender->ForcedMaterialOverride(hidden_material);
		modelRender_vmt->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
	}

	modelRender->ForcedMaterialOverride(visible_material);
	modelRender_vmt->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void DrawArms(const ModelRenderInfo_t &pInfo)
{
	if (!Settings::ESP::Chams::Arms::enabled)
		return;

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);
	IMaterial *mat;

	if (Settings::ESP::Chams::Arms::enabled)
		mat = materialChamsArms;
	else
		mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);

	switch (Settings::ESP::Chams::Arms::type)
	{
		default:
			break;
		case ArmsType::DEFAULT:
			mat->AlphaModulate(1.0f);
			mat->ColorModulate(Settings::ESP::Chams::Arms::color);
			break;
		case ArmsType::RAINBOW:
			Color color = Color::FromHSB(rainbowHue, 1.0f, 1.0f);
			mat->AlphaModulate(1.0f);
			mat->ColorModulate(color);
			break;
	}

	mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, Settings::ESP::Chams::Arms::type == ArmsType::WIREFRAME);
	mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings::ESP::Chams::Arms::type == ArmsType::NONE);
	modelRender->ForcedMaterialOverride(mat);
}

void Chams::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (!engine->IsInGame())
		return;

	if (!Settings::ESP::enabled)
		return;

	if (!pInfo.pModel)
		return;

	static bool materialsCreated = false;
	if (!materialsCreated)
	{
		materialChams = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialChamsIgnorez = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", true, true, true, true, true);
		materialChamsFlat = Util::CreateMaterial("UnlitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialChamsFlatIgnorez = Util::CreateMaterial("UnlitGeneric", "VGUI/white_additive", true, true, true, true, true);
		materialChamsArms = Util::CreateMaterial("VertexLitGeneric", "VGUI/white_additive", false, true, true, true, true);
		materialsCreated = true;
	}

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);

	if (modelName.find("models/player") != std::string::npos)
		DrawPlayer(thisptr, context, state, pInfo, pCustomBoneToWorld);
	else if (modelName.find("arms") != std::string::npos)
		DrawArms(pInfo);
}

void Chams::CreateMove(CUserCmd* cmd)
{
	if (rainbowHue >= 1.f)
		rainbowHue = 0.f;
	else
		rainbowHue += 0.002;
}
