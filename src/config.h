#pragma once

#include <unistd.h>
#include <string>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include "Utils/xorstring.h"
#include "interfaces.h"

bool DoesFileExist(const char* path);
bool DoesDirectoryExist(const char* path);

struct Config
{
	std::string name;
	std::string path;

	Config(const char* name, const char* path);
};

std::vector<Config> GetConfigs(const char* directory);
std::vector<std::string> GetConfigs();

std::string GetConfigDirectory();
std::string GetGhConfigDirectory();