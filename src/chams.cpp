#include "chams.h"

bool Settings::ESP::Chams::players = true;
bool Settings::ESP::Chams::arms = true;
bool Settings::ESP::Chams::rainbow_arms = false;
Color Settings::ESP::Chams::players_ally_color = Color(7, 98, 168);
Color Settings::ESP::Chams::players_enemy_color = Color(243, 54, 48);
Color Settings::ESP::Chams::players_enemy_visible_color = Color(243, 107, 40);
Color Settings::ESP::Chams::arms_color = Color(117, 43, 73);
ChamsType Settings::ESP::Chams::type = CHAMS_IGNOREZ;

float rainbowHue;

void Chams::CreateMaterials()
{
	char cwd[1024];
	std::stringstream chams;
	std::stringstream chamsIgnorez;
	std::stringstream chamsFlat;
	std::stringstream chamsFlatIgnorez;
	char* chamsPath;
	char* chamsIgnorezPath;
	char* chamsFlatPath;
	char* chamsFlatIgnorezPath;

	chams << "\"VertexLitGeneric\"" << std::endl;
	chams << "{" << std::endl;
	chams << "\t\"$basetexture\" \"VGUI/white_additive\"" << std::endl;
	chams << "\t\"$ignorez\" \"0\"" << std::endl;
	chams << "\t\"$nofog\" \"1\"" << std::endl;
	chams << "\t\"$model\" \"1\"" << std::endl;
	chams << "\t\"$nocull\" \"1\"" << std::endl;
	chams << "\t\"$halflambert\" \"1\"" << std::endl;
	chams << "}" << std::endl;

	chamsIgnorez << "\"VertexLitGeneric\"" << std::endl;
	chamsIgnorez << "{" << std::endl;
	chamsIgnorez << "\t\"$basetexture\" \"VGUI/white_additive\"" << std::endl;
	chamsIgnorez << "\t\"$ignorez\" \"1\"" << std::endl;
	chamsIgnorez << "\t\"$nofog\" \"1\"" << std::endl;
	chamsIgnorez << "\t\"$model\" \"1\"" << std::endl;
	chamsIgnorez << "\t\"$nocull\" \"1\"" << std::endl;
	chamsIgnorez << "\t\"$halflambert\" \"1\"" << std::endl;
	chamsIgnorez << "}" << std::endl;

	chamsFlat << "\"UnlitGeneric\"" << std::endl;
	chamsFlat << "{" << std::endl;
	chamsFlat << "\t\"$basetexture\" \"VGUI/white_additive\"" << std::endl;
	chamsFlat << "\t\"$ignorez\" \"0\"" << std::endl;
	chamsFlat << "\t\"$nofog\" \"1\"" << std::endl;
	chamsFlat << "\t\"$model\" \"1\"" << std::endl;
	chamsFlat << "\t\"$nocull\" \"1\"" << std::endl;
	chamsFlat << "\t\"$halflambert\" \"1\"" << std::endl;
	chamsFlat << "}" << std::endl;

	chamsFlatIgnorez << "\"UnlitGeneric\"" << std::endl;
	chamsFlatIgnorez << "{" << std::endl;
	chamsFlatIgnorez << "\t\"$basetexture\" \"VGUI/white_additive\"" << std::endl;
	chamsFlatIgnorez << "\t\"$ignorez\" \"1\"" << std::endl;
	chamsFlatIgnorez << "\t\"$nofog\" \"1\"" << std::endl;
	chamsFlatIgnorez << "\t\"$model\" \"1\"" << std::endl;
	chamsFlatIgnorez << "\t\"$nocull\" \"1\"" << std::endl;
	chamsFlatIgnorez << "\t\"$halflambert\" \"1\"" << std::endl;
	chamsFlatIgnorez << "}" << std::endl;

	getcwd(cwd, sizeof(cwd));

	asprintf(&chamsPath, "%s/csgo/materials/aimtux_chams.vmt", cwd);
	asprintf(&chamsIgnorezPath, "%s/csgo/materials/aimtux_chamsIgnorez.vmt", cwd);
	asprintf(&chamsFlatPath, "%s/csgo/materials/aimtux_chamsFlat.vmt", cwd);
	asprintf(&chamsFlatIgnorezPath, "%s/csgo/materials/aimtux_chamsFlatIgnorez.vmt", cwd);

	std::ofstream(chamsPath) << chams.str();
	std::ofstream(chamsIgnorezPath) << chamsIgnorez.str();
	std::ofstream(chamsFlatPath) << chamsFlat.str();
	std::ofstream(chamsFlatIgnorezPath) << chamsFlatIgnorez.str();
}

void DrawPlayer(const ModelRenderInfo_t &pInfo)
{
	if (!Settings::ESP::Chams::players)
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	C_BaseEntity* entity = entitylist->GetClientEntity(pInfo.entity_index);
	if (!entity
		|| entity == (C_BaseEntity*)localPlayer
		|| entity->GetDormant()
		|| entity->GetLifeState() != LIFE_ALIVE
		|| entity->GetHealth() <= 0)
		return;

	IMaterial *mat;

	switch (Settings::ESP::Chams::type)
	{
		case CHAMS:
			mat = material->FindMaterial ("aimtux_chams", TEXTURE_GROUP_MODEL);
			break;
		case CHAMS_IGNOREZ:
			mat = material->FindMaterial ("aimtux_chamsIgnorez", TEXTURE_GROUP_MODEL);
			break;
		case CHAMS_FLAT:
			mat = material->FindMaterial ("aimtux_chamsFlat", TEXTURE_GROUP_MODEL);
			break;
		case CHAMS_FLAT_IGNOREZ:
			mat = material->FindMaterial ("aimtux_chamsFlatIgnorez", TEXTURE_GROUP_MODEL);
			break;
	}

	mat->AlphaModulate (1.0f);

	if (entity->GetTeam() == localPlayer->GetTeam())
		mat->ColorModulate (Settings::ESP::Chams::players_ally_color.r / 255.0f,
							Settings::ESP::Chams::players_ally_color.g / 255.0f,
							Settings::ESP::Chams::players_ally_color.b / 255.0f);
	else if (Entity::IsVisible(localPlayer, entity, 6))
		mat->ColorModulate (Settings::ESP::Chams::players_enemy_visible_color.r / 255.0f,
							Settings::ESP::Chams::players_enemy_visible_color.g / 255.0f,
							Settings::ESP::Chams::players_enemy_visible_color.b / 255.0f);
	else
		mat->ColorModulate (Settings::ESP::Chams::players_enemy_color.r / 255.0f,
							Settings::ESP::Chams::players_enemy_color.g / 255.0f,
							Settings::ESP::Chams::players_enemy_color.b / 255.0f);

	modelRender->ForcedMaterialOverride(mat);
}

void DrawArms(const ModelRenderInfo_t &pInfo)
{
	if (!Settings::ESP::Chams::arms)
		return;

	IMaterial *mat = material->FindMaterial ("aimtux_chams", TEXTURE_GROUP_MODEL);
	
	Color color = Settings::ESP::Chams::arms_color;
	
	if (Settings::ESP::Chams::rainbow_arms)
		color = Color::FromHSB(rainbowHue, 1.0f, 1.0f);
	
	mat->AlphaModulate (1.0f);
	mat->ColorModulate (color.r / 255.0f,
						color.g / 255.0f,
						color.b / 255.0f);

	modelRender->ForcedMaterialOverride(mat);
}

void Chams::DrawModelExecute(void* context, void *state, const ModelRenderInfo_t &pInfo)
{
	if (!pInfo.pModel)
		return;

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);

	if (modelName.find("models/player") != std::string::npos)
		DrawPlayer (pInfo);
	else if (modelName.find("arms") != std::string::npos)
		DrawArms (pInfo);
}

void Chams::CreateMove(CUserCmd* cmd)
{
	if (rainbowHue >= 1.f)
		rainbowHue = 0.f;
	else
		rainbowHue += 0.002;
}