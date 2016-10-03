#include "chams.h"

bool Settings::Chams::enabled = true;
ChamsType Settings::Chams::type = CHAMS_FLAT_IGNOREZ;

void Chams::CreateMaterials()
{
	struct passwd *pw = getpwuid(getuid());
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

	asprintf(&chamsPath, "%s/%s", pw->pw_dir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo/materials/aimtux_chams.vmt");
	asprintf(&chamsIgnorezPath, "%s/%s", pw->pw_dir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo/materials/aimtux_chamsIgnorez.vmt");
	asprintf(&chamsFlatPath, "%s/%s", pw->pw_dir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo/materials/aimtux_chamsFlat.vmt");
	asprintf(&chamsFlatIgnorezPath, "%s/%s", pw->pw_dir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo/materials/aimtux_chamsFlatIgnorez.vmt");

	std::ofstream(chamsPath) << chams.str();
	std::ofstream(chamsIgnorezPath) << chamsIgnorez.str();
	std::ofstream(chamsFlatPath) << chamsFlat.str();
	std::ofstream(chamsFlatIgnorezPath) << chamsFlatIgnorez.str();
}

void Chams::DrawModelExecute(void* context, void *state, const ModelRenderInfo_t &pInfo)
{
	if (!Settings::Chams::enabled)
		return;

	if (!pInfo.pModel)
		return;

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);
	if (modelName.find("models/player") == std::string::npos)
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

	switch (Settings::Chams::type)
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
		mat->ColorModulate (0.0f, 0.3f, 0.8f);
	else if (Entity::IsVisible(localPlayer, entity, 6))
		mat->ColorModulate (1.0f, 0.5f, 0.0f);
	else
		mat->ColorModulate (1.0f, 0.0f, 0.0f);

	modelRender->ForcedMaterialOverride(mat);
}