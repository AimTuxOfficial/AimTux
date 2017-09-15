#pragma once
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <sys/stat.h>

#include "hooker.h"
#include "interfaces.h"
#include "Utils/util.h"

namespace Fuzion
{
	void SelfShutdown();
	extern void *prev, *curr, *next;
	extern char buildPath[PATH_MAX];
}
