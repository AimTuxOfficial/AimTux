#include "config.h"

Config::Config(const char* name, const char* path)
{
	this->name = (char*)name;
	this->path = (char*)path;
}

bool DoesFileExist(const char* path)
{
	struct stat info;
	return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

bool DoesDirectoryExist(const char* path)
{
	struct stat info;
	return stat(path, &info) == 0 && S_ISDIR(info.st_mode);
}

bool DoesConform(const char* config_path)
{
	pstring path;
	path << config_path << "/config.json";

	return DoesFileExist(path.c_str());
}

std::string Config::GetMainConfigFile()
{
	pstring path;
	path << this->path << "/config.json";

	return path;
}

std::vector<Config> GetConfigs(const char* directory)
{
	std::vector<Config> configs;

	DIR* dir;
	dirent* pdir;

	dir = opendir(directory);

	while ((pdir = readdir(dir)))
	{
		if (pdir->d_type == DT_DIR && strcmp(pdir->d_name, ".") != 0 && strcmp(pdir->d_name, "..") != 0)
		{
			pstring config_path;
			config_path << directory << pdir->d_name;

			if (DoesConform(config_path.c_str()))
			{
				Config new_config(pdir->d_name, config_path.c_str());
				configs.push_back(new_config);
			}
		}
	}

	return configs;
}