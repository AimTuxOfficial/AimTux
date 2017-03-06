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

std::vector<Config> GetConfigs(const char* directory)
{
	std::vector<Config> configs;

	DIR* dir;
	dirent* pdir;

	dir = opendir(directory);

	while ((pdir = readdir(dir)))
	{
		if (pdir->d_type != DT_DIR || strcmp(pdir->d_name, ".") == 0 || strcmp(pdir->d_name, "..") == 0)
			continue;

		pstring config_path;
		config_path << directory << pdir->d_name;

		if (!DoesConform(config_path.c_str()))
			continue;

		Config new_config(pdir->d_name, config_path.c_str());
		configs.push_back(new_config);
	}

	return configs;
}

pstring GetConfigDirectory()
{
	pstring directory = getenv("HOME");
	directory << "/.config";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	directory << "/AimTux/";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	return directory;
}

std::vector<std::string> GetConfigs()
{
	pstring configDirectory = GetConfigDirectory();
	std::vector<Config> vConfigs = GetConfigs(configDirectory.c_str());
	std::vector<std::string> configs;

	for (auto config = vConfigs.begin(); config != vConfigs.end(); config++)
		configs.push_back(config->name);

	std::sort(configs.begin(), configs.end());

	return configs;
}

pstring GetGhConfigDirectory()
{
	pstring directory = getenv("HOME");
	directory << "/.config";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	directory << "/AimTuxGH/";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	return directory;
}