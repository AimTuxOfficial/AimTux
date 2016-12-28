#include "chams.h"

bool Settings::ESP::Chams::players = false;
bool Settings::ESP::Chams::visibility_check = false;
bool Settings::ESP::Chams::Arms::enabled = false;
int Settings::ESP::Chams::Arms::type = DEFAULT;
ImColor Settings::ESP::Chams::players_ally_color = ImColor(7, 98, 168, 255);
ImColor Settings::ESP::Chams::players_ally_visible_color = ImColor(40, 52, 138, 255);
ImColor Settings::ESP::Chams::players_enemy_color = ImColor(243, 24, 28, 255);
ImColor Settings::ESP::Chams::players_enemy_visible_color = ImColor(243, 159, 20, 255);
ImColor Settings::ESP::Chams::Arms::color = ImColor(117, 43, 73, 255);
int Settings::ESP::Chams::type = CHAMS;

float rainbowHue;

void Chams::CreateMaterials()
{
	char cwd[1024];
	std::stringstream chams;
	std::stringstream chamsIgnorez;
	std::stringstream chamsFlat;
	std::stringstream chamsFlatIgnorez;
	char* chamsPath;
	char* chamsArmsPath;
	char* chamsIgnorezPath;
	char* chamsFlatPath;
	char* chamsFlatIgnorezPath;

	chams << "\"VertexLitGeneric\"\n"
	"{\n"
	"\t\"$basetexture\" \"VGUI/white_additive\"\n"
	"\t\"$ignorez\" \"0\"\n"
	"\t\"$nofog\" \"1\"\n"
	"\t\"$model\" \"1\"\n"
	"\t\"$nocull\" \"1\"\n"
	"\t\"$halflambert\" \"1\"\n"
	"}\n" << std::flush;

	chamsIgnorez << "\"VertexLitGeneric\"\n"
	"{\n"
	"\t\"$basetexture\" \"VGUI/white_additive\"\n"
	"\t\"$ignorez\" \"1\"\n"
	"\t\"$nofog\" \"1\"\n"
	"\t\"$model\" \"1\"\n"
	"\t\"$nocull\" \"1\"\n"
	"\t\"$halflambert\" \"1\"\n"
	"}\n" << std::flush;

	chamsFlat << "\"UnlitGeneric\"\n"
	"{\n"
	"\t\"$basetexture\" \"VGUI/white_additive\"\n"
	"\t\"$ignorez\" \"0\"\n"
	"\t\"$nofog\" \"1\"\n"
	"\t\"$model\" \"1\"\n"
	"\t\"$nocull\" \"1\"\n"
	"\t\"$halflambert\" \"1\"\n"
	"}\n" << std::flush;

	chamsFlatIgnorez << "\"UnlitGeneric\"\n"
	"{\n"
	"\t\"$basetexture\" \"VGUI/white_additive\"\n"
	"\t\"$ignorez\" \"1\"\n"
	"\t\"$nofog\" \"1\"\n"
	"\t\"$model\" \"1\"\n"
	"\t\"$nocull\" \"1\"\n"
	"\t\"$halflambert\" \"1\"\n"
	"}\n" << std::flush;

	getcwd(cwd, sizeof(cwd));

	asprintf(&chamsPath, "%s/csgo/materials/aimtux_chams.vmt", cwd);
	asprintf(&chamsArmsPath, "%s/csgo/materials/aimtux_chams_arms.vmt", cwd);
	asprintf(&chamsIgnorezPath, "%s/csgo/materials/aimtux_chamsIgnorez.vmt", cwd);
	asprintf(&chamsFlatPath, "%s/csgo/materials/aimtux_chamsFlat.vmt", cwd);
	asprintf(&chamsFlatIgnorezPath, "%s/csgo/materials/aimtux_chamsFlatIgnorez.vmt", cwd);

	std::ofstream(chamsPath) << chams.str();
	std::ofstream(chamsArmsPath) << chams.str();
	std::ofstream(chamsIgnorezPath) << chamsIgnorez.str();
	std::ofstream(chamsFlatPath) << chamsFlat.str();
	std::ofstream(chamsFlatIgnorezPath) << chamsFlatIgnorez.str();
}

void DrawPlayer(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (!Settings::ESP::Chams::players)
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	C_BaseEntity* entity = entitylist->GetClientEntity(pInfo.entity_index);
	if (!entity
		|| entity == localPlayer
		|| entity->GetDormant()
		|| !entity->GetAlive())
		return;

	IMaterial *visible_material;
	IMaterial *hidden_material;

	switch (Settings::ESP::Chams::type)
	{
		case CHAMS:
			visible_material = material->FindMaterial("aimtux_chams", TEXTURE_GROUP_MODEL);
			hidden_material = material->FindMaterial("aimtux_chamsIgnorez", TEXTURE_GROUP_MODEL);
			break;
		case CHAMS_FLAT:
			visible_material = material->FindMaterial("aimtux_chamsFlat", TEXTURE_GROUP_MODEL);
			hidden_material = material->FindMaterial("aimtux_chamsFlatIgnorez", TEXTURE_GROUP_MODEL);
			break;
	}

	visible_material->AlphaModulate(1.0f);
	hidden_material->AlphaModulate(1.0f);

	if (entity->GetTeam() == localPlayer->GetTeam())
	{
		visible_material->ColorModulate(Settings::ESP::Chams::players_ally_visible_color);
		hidden_material->ColorModulate(Settings::ESP::Chams::players_ally_color);
	}
	else
	{
		visible_material->ColorModulate(Settings::ESP::Chams::players_enemy_visible_color);
		hidden_material->ColorModulate(Settings::ESP::Chams::players_enemy_color);
	}

	if (!Settings::ESP::Chams::visibility_check)
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
	IMaterial *mat = material->FindMaterial(Settings::ESP::Chams::Arms::enabled ? "aimtux_chams_arms" : modelName.c_str(), TEXTURE_GROUP_MODEL);

	switch (Settings::ESP::Chams::Arms::type)
	{
		case DEFAULT:
			mat->AlphaModulate(1.0f);
			mat->ColorModulate(Settings::ESP::Chams::Arms::color);
			break;
		case RAINBOW:
			Color color = Color::FromHSB(rainbowHue, 1.0f, 1.0f);
			mat->AlphaModulate(1.0f);
			mat->ColorModulate(color);
			break;
	}

	mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, Settings::ESP::Chams::Arms::type == WIREFRAME);
	mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings::ESP::Chams::Arms::type == NONE);
	modelRender->ForcedMaterialOverride(mat);
}

void Chams::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (!Settings::ESP::enabled)
		return;

	if (!pInfo.pModel)
		return;

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
