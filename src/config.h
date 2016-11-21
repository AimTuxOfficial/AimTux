#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <vector>
#include "pstring.h"


bool DoesFileExist(const char*, const char* file);
bool DoesDirectoryExist(const char*, const char* directory);

struct Config
{
	std::string name;
	std::string path;
	
	Config (const char* name, const char* path);
	
	char* GetMainConfigFile();
};

std::vector<Config> GetConfigs (const char* directory);