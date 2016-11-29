#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include "pstring.h"

bool DoesFileExist(const char* path);
bool DoesDirectoryExist(const char* path);

struct Config
{
	std::string name;
	std::string path;

	Config(const char* name, const char* path);

	std::string GetMainConfigFile();
};

std::vector<Config> GetConfigs(const char* directory);