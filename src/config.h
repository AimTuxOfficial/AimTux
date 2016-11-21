#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <vector>
#include "pstring.h"


bool DoesFileExist(pstring path, const char* file);
bool DoesDirectoryExist(pstring path, const char* directory);

struct Config
{
	const char* name;
	const char* path;
	
	Config (const char* name, const char* path);
	
	char* GetMainConfigFile();
};

std::vector<Config> GetConfigs (const char* directory);