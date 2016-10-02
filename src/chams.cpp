#include "chams.h"

bool Settings::Chams::enabled = true;

void Chams::CreateMaterials()
{
	std::stringstream ss;
	std::ofstream file;

	ss << "\"UnlitGeneric\"" << std::endl;
	ss << "{" << std::endl;
	ss << "\t\"$basetexture\" \"VGUI/white_additive\"" << std::endl;
	ss << "\t\"$ignorez\" \"1\"" << std::endl;
	ss << "\t\"$nofog\" \"1\"" << std::endl;
	ss << "\t\"$model\" \"1\"" << std::endl;
	ss << "\t\"$nocull\" \"1\"" << std::endl;
	ss << "\t\"$halflambert\" \"1\"" << std::endl;
	ss << "}" << std::endl;

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;

	char* path;
	asprintf(&path, "%s/%s", homedir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo/materials/aimtux_chams.vmt");

	file.open(path);
	file << ss.str();
	file.close();
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

	IMaterial *mat = material->FindMaterial ("aimtux_chams", TEXTURE_GROUP_MODEL);
	mat->AlphaModulate (1.0f);

	if (entity->GetTeam() == localPlayer->GetTeam())
		mat->ColorModulate (0.0f, 0.3f, 0.8f);
	else if (Entity::IsVisible(localPlayer, entity, 6))
		mat->ColorModulate (1.0f, 0.5f, 0.0f);
	else
		mat->ColorModulate (1.0f, 0.0f, 0.0f);

	modelRender->ForcedMaterialOverride(mat);
}