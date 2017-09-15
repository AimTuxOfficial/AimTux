#include "util.h"
#include "../settings.h"

struct link_map_wrapper
{
    void* pointers[3];
    struct link_map_wrapper* ptr;
};

std::string Util::ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;

	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}

	return subject;
}

int Util::RandomInt(int min, int max)
{
	return rand()%(max-min + 1) + min;
}
/* https://stackoverflow.com/questions/3596781/how-to-detect-if-the-current-process-is-being-run-by-gdb */
// This seems to be the best method. Forking and ptracing is ghetto
int Util::IsDebuggerPresent()
{
	char buf[1024];
	int debugger_present = 0;

	int status_fd = open("/proc/self/status", O_RDONLY);
	if (status_fd == -1)
		return 0;

	ssize_t num_read = read(status_fd, buf, sizeof(buf)-1);

	if (num_read > 0)
	{
		static const char TracerPid[] = "TracerPid:";
		char *tracer_pid;

		buf[num_read] = 0;
		tracer_pid    = strstr(buf, TracerPid);
		if (tracer_pid)
			debugger_present = !!atoi(tracer_pid + sizeof(TracerPid) - 1);
	}

	close(status_fd);
	return debugger_present;
}
/* Sets prev/curr/next addresses so you can restore */
void Util::RemoveLinkMapEntry(char *name, void **prev, void **curr, void **next)
{
    void *handle = dlopen(NULL, RTLD_NOW);
    link_map_wrapper *p = (reinterpret_cast<link_map_wrapper*>(handle))->ptr;
    link_map *map = reinterpret_cast<link_map*>((p->ptr));

    while( map )
    {
        if( strcmp(name, map->l_name) == 0 ) {
            /* Record info */
            *prev = map->l_prev;
            *curr = map;
            *next = map->l_next;
            /* Skip this node Entry */
            map->l_prev->l_next = map->l_next;
            map->l_next->l_prev = map->l_prev;
            return;
        }
        map = map->l_next;
    }
}

bool Util::SearchLinkMap(char *name)
{
    void *handle = dlopen(NULL, RTLD_NOW);
    link_map_wrapper *p = (reinterpret_cast<link_map_wrapper*>(handle))->ptr;
    link_map *map = reinterpret_cast<link_map*>((p->ptr));

    while( map )
    {
        //cvar->ConsoleDPrintf("%s\n", map->l_name);
        if( strcmp(name, map->l_name) == 0 ) {
            return true;
        }
        map = map->l_next;
    }
    return false;
}
/* Will this memory ever get de-allocated? Hopefully not */
void Util::RestoreLinkMapEntry(void *prev, void *curr, void *next)
{
    link_map *previousEntry = reinterpret_cast<link_map*>(prev);
    link_map *nextEntry = reinterpret_cast<link_map*>(next);

    previousEntry->l_next = reinterpret_cast<link_map*>(curr);
    nextEntry->l_prev = reinterpret_cast<link_map*>(curr);
}
void Util::StdReplaceStr(std::string& replaceIn, const std::string& replace, const std::string& replaceWith)
{
	size_t const span = replace.size();
	size_t const step = replaceWith.size();
	size_t index = 0;

	while (true)
	{
		index = replaceIn.find(replace, index);

		if (index == std::string::npos)
			break;

		replaceIn.replace(index, span, replaceWith);
		index += step;
	}
}

const char* Util::PadStringRight(std::string text, size_t value)
{
	text.insert(text.length(), value - text.length(), ' ');

	return text.c_str();
}

void Util::ProtectAddr(void* addr, int prot)
{
	long pagesize = sysconf(_SC_PAGESIZE);
	void* address = (void *)((long)(uintptr_t)addr & ~(pagesize - 1));

	mprotect(address, sizeof(address), prot);
}

bool Util::Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string Util::ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int (*)(int))std::tolower);

	return str;
}

std::string Util::ToUpper(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int (*)(int))std::toupper);

	return str;
}

std::string Util::WstringToString(std::wstring wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.to_bytes(wstr);
	}
	catch (std::range_error)
	{
		std::stringstream s;
		s << wstr.c_str();
		return s.str();
	}
}

std::wstring Util::StringToWstring(std::string str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.from_bytes(str);
	}
	catch (std::range_error)
	{
		std::wostringstream s;
		s << str.c_str();
		return s.str();
	}
}
/* Get Epoch timestamp in ms */
long Util::GetEpochTime()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

const std::map<int,int> * Util::GetModelTypeBoneMap(C_BasePlayer* player)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(player->GetModel());

	switch( pStudioModel->numbones ) {
		case 84: // Anarchists or Leet Krew
			if (memchr(pStudioModel->name, 'h', sizeof(pStudioModel->name)) != NULL)// Anarchist
			{
				return &BoneMapT_Anarchist;
			}
			else // Leet Krew
			{
				return &BoneMapT_Leet;
			}
		case 86: // Balkan, Phoenix, and Separatists
			if (memchr(pStudioModel->name, 'h', sizeof(pStudioModel->name)) != NULL) // Phoenix
			{
				return &BoneMapT_Phoenix;
			}
			else if (memmem(pStudioModel->name, sizeof(pStudioModel->name), "ba", 2) != NULL) // balkan
			{
				return &BoneMapT_Balkan;
			} else // Separatist
			{
				return &BoneMapT_Separatist;
			}
		case 89: // FBI, GSG, and SEALS
			if (memchr(pStudioModel->name, 'f', sizeof(pStudioModel->name)) != NULL) // FBI
			{
				return &BoneMapCT_FBI;
			}
			else if( memmem(pStudioModel->name, sizeof(pStudioModel->name), "sg", 2) != NULL ) // GSG
			{
				return &BoneMapCT_GSG;
			}
			else // Seals
			{
				return &BoneMapCT_Seals;
			}
		case 91: // SWAT, Professionals
			if (memchr(pStudioModel->name, 'w', sizeof(pStudioModel->name)) != NULL) // SWAT
			{
				return &BoneMapCT_SWAT;
			}
			else // Professionals
			{
				return &BoneMapT_Professional;
			}
		case 93: // GIGN
			return &BoneMapCT_GIGN;
		case 94: // IDF
			return &BoneMapCT_IDF;
		case 98: // SAS
			return &BoneMapCT_SAS;
		default:
			cvar->ConsoleDPrintf(XORSTR("(Util::GetModelTypeBoneMap)- Warning. Model type Unknown. Using Generic boneMap\n"));
			return &BoneMapGeneric;
	}
}

ModelType Util::GetModelTypeID(C_BasePlayer* player)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(player->GetModel());

	switch( pStudioModel->numbones ) {
		case 84: // Anarchists or Leet Krew
			if (memchr(pStudioModel->name, 'h', sizeof(pStudioModel->name)) != NULL)// Anarchist
			{
				return ModelType::ANARCHIST;
			}
			else // Leet Krew
			{
				return ModelType::LEETKREW;
			}
		case 86: // Balkan, Phoenix, and Separatists
			if (memchr(pStudioModel->name, 'h', sizeof(pStudioModel->name)) != NULL) // Phoenix
			{
				return ModelType::PHOENIX;
			}
			else if (memmem(pStudioModel->name, sizeof(pStudioModel->name), "ba", 2) != NULL) // balkan
			{
				return ModelType::BALKAN;
			} else // Separatist
			{
				return ModelType::SEPARATIST;
			}
		case 89: // FBI, GSG, and SEALS
			if (memchr(pStudioModel->name, 'f', sizeof(pStudioModel->name)) != NULL) // FBI
			{
				return ModelType::FBI;
			}
			else if( memmem(pStudioModel->name, sizeof(pStudioModel->name), "sg", 2) != NULL ) // GSG
			{
				return ModelType::GSG;
			}
			else // Seals
			{
				return ModelType::SEALS;
			}
		case 91: // SWAT, Professionals
			if (memchr(pStudioModel->name, 'w', sizeof(pStudioModel->name)) != NULL) // SWAT
			{
				return ModelType::SWAT;
			}
			else // Professionals
			{
				return ModelType::PROFESSIONAL;
			}
		case 93: // GIGN
			return ModelType::GIGN;
		case 94: // IDF
			return ModelType::IDF;
		case 98: // SAS
			return ModelType::SAS;
		default:
			return ModelType::UNKNOWN;
	}
}
/*
std::string Util::ModelTypeToString(ModelType model)
{
	switch( model )
	{
		case ModelType::FBI:
			return std::string("FBI");
		case ModelType::GIGN:
			return std::string("GIGN");
		case ModelType::GSG:
			return std::string("GSG");
		case ModelType::IDF:
			return std::string("IDF");
		case ModelType::SAS:
			return std::string("SAS");
		case ModelType::SEALS:
			return std::string("SEALS");
		case ModelType::SWAT:
			return std::string("SWAT");
		case ModelType::ANARCHIST:
			return std::string("ANARCHIST");
		case ModelType::BALKAN:
			return std::string("BALKAN");
		case ModelType::LEETKREW:
			return std::string("LEETKREW");
		case ModelType::PHOENIX:
			return std::string("PHOENIX");
		case ModelType::PROFESSIONAL:
			return std::string("PROFESSIONAL");
		case ModelType::SEPARATIST:
			return std::string("SEPARATIST");
		case ModelType::UNKNOWN:
			return std::string("UNKNOWN");
	}
}
*/
/*
std::string Util::BoneToString(const std::map<int,int> * model, int boneID )
{
	int boneKey = (int)Bone::INVALID;
	for( const std::pair<const int, int> &kv : (*model) )
	{
		if( kv.second == boneID )
		{
			boneKey = kv.first;
			break;
		}
	}
	if( boneKey == (int)Bone::INVALID )
		return std::string("Unknown Bone");

	switch( boneKey )
	{
		case (int)DesiredBones::BONE_PELVIS:
			return std::string("Pelvis");
		case (int)DesiredBones::BONE_HIP:
			return std::string("Hip");
		case (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN:
			return std::string("Lower Spine");
		case (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN:
			return std::string("Middle Spine");
		case (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN:
			return std::string("Upper Spine");
		case (int)DesiredBones::BONE_NECK:
			return std::string("Neck");
		case (int)DesiredBones::BONE_HEAD:
			return std::string("Head");

		case (int)DesiredBones::BONE_LEFT_COLLARBONE:
			return std::string("Left Collarbone");
		case (int)DesiredBones::BONE_LEFT_SHOULDER:
			return std::string("Left Shoulder ");
		case (int)DesiredBones::BONE_LEFT_ARMPIT:
			return std::string("Left Armpit");
		case (int)DesiredBones::BONE_LEFT_BICEP:
			return std::string("Left Bicep");
		case (int)DesiredBones::BONE_LEFT_ELBOW:
			return std::string("Left Elbow");
		case (int)DesiredBones::BONE_LEFT_FOREARM:
			return std::string("Left Forearm");
		case (int)DesiredBones::BONE_LEFT_WRIST:
			return std::string("Left Wrist");

		case (int)DesiredBones::BONE_RIGHT_COLLARBONE:
			return std::string("Right Collarbone");
		case (int)DesiredBones::BONE_RIGHT_SHOULDER:
			return std::string("Right Shoulder");
		case (int)DesiredBones::BONE_RIGHT_ARMPIT:
			return std::string("Right Armpit");
		case (int)DesiredBones::BONE_RIGHT_BICEP:
			return std::string("Right Bicep");
		case (int)DesiredBones::BONE_RIGHT_FOREARM:
			return std::string("Right Forearm");
		case (int)DesiredBones::BONE_RIGHT_WRIST:
			return std::string("Right Wrist");

		case (int)DesiredBones::BONE_LEFT_BUTTCHEEK:
			return std::string("Left Buttcheek");
		case (int)DesiredBones::BONE_LEFT_THIGH:
			return std::string("Left Thigh");
		case (int)DesiredBones::BONE_LEFT_KNEE:
			return std::string("Left Knee");
		case (int)DesiredBones::BONE_LEFT_ANKLE:
			return std::string("Left Ankle");
		case (int)DesiredBones::BONE_LEFT_SOLE:
			return std::string("Left Sole");

		case (int)DesiredBones::BONE_RIGHT_BUTTCHEEK:
			return std::string("Right Buttcheek");
		case (int)DesiredBones::BONE_RIGHT_THIGH:
			return std::string("Right Thigh");
		case (int)DesiredBones::BONE_RIGHT_KNEE:
			return std::string("Right Knee");
		case (int)DesiredBones::BONE_RIGHT_ANKLE:
			return std::string("Right Ankle");
		case (int)DesiredBones::BONE_RIGHT_SOLE:
			return std::string("Right Sole");

		default:
			return std::string("Bone not Indexed"); // be sure to use the DesiredBones enum. Some of the bones are not on all models.
	}
}
*/
ImColor Util::GetRainbowColor(float speed)
{
	speed = 0.002f * speed;
	long now = Util::GetEpochTime();
	float hue = (now % (int)(1.0f / speed)) * speed;

	return ImColor::HSV(hue, 1.0f, 1.0f);
}

Color Util::GetHealthColor(int hp)
{
	return Color(
			std::min(510 * (100 - hp) / 100, 255),
			std::min(510 * hp / 100, 255),
			25
	);
}

Color Util::GetHealthColor(C_BasePlayer* player)
{
	return Color(
			std::min(510 * (100 - player->GetHealth()) / 100, 255),
			std::min(510 * player->GetHealth() / 100, 255),
			25
	);
}
