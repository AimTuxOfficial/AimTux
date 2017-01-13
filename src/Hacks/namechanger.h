#pragma once
#include "../SDK/SDK.h"
#include "../settings.h"

enum NC_Type
{
	NC_NORMAL,
	NC_RAINBOW,
	NC_SOLID
};

namespace NameChanger
{
	
	extern int changes;
	extern NC_Type type;

	void BeginFrame(float frameTime);
	void SetName(const char* name);
};
