#include "SDK/SDK.h"
#include "settings.h"
#include <chrono>

namespace NameChanger
{
	extern int changes;

	void BeginFrame(float frameTime);
	void SetName(const char* name);
};