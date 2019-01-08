#include "config.h"

#include "Utils/xorstring.h"
#include "interfaces.h"

#include <sstream>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <algorithm>

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
	std::ostringstream path;
	path << config_path << XORSTR("/config.json");

	return DoesFileExist(path.str().c_str());
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

        std::ostringstream configPath;
        configPath << directory << pdir->d_name;

		if (!DoesConform(configPath.str().c_str()))
			continue;

		Config new_config(pdir->d_name, configPath.str().c_str());
		configs.push_back(new_config);
	}

	return configs;
}

std::string GetConfigDirectory()
{
	std::ostringstream directory;
	directory << getenv(XORSTR("HOME")) << XORSTR("/.config");

	if (!DoesDirectoryExist(directory.str().c_str()))
		mkdir(directory.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	directory << XORSTR("/Fuzion/");

	if (!DoesDirectoryExist(directory.str().c_str()))
		mkdir(directory.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	cvar->ConsoleDPrintf(XORSTR("Config Directory: %s\n"), directory.str().c_str());
	return directory.str();
}

std::vector<std::string> GetConfigs()
{
	std::vector<Config> vConfigs = GetConfigs(GetConfigDirectory().c_str());
	std::vector<std::string> configs;

	for (auto config = vConfigs.begin(); config != vConfigs.end(); config++)
		configs.push_back(config->name);

	std::sort(configs.begin(), configs.end());

	return configs;
}

std::string GetGhConfigDirectory()
{
	std::ostringstream directory;
	directory << getenv(XORSTR("HOME")) << XORSTR("/.config");

	if (!DoesDirectoryExist(directory.str().c_str()))
		mkdir(directory.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	directory << XORSTR("/FuzionGH/");

	if (!DoesDirectoryExist(directory.str().c_str()))
		mkdir(directory.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	return directory.str();
}