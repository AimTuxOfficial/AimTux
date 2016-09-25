#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include <unordered_map>
#include "Weapons.h"

enum TracerType
{
	BOTTOM,
	CURSOR
};

namespace Settings
{
	namespace Aimbot
	{
		extern bool enabled;
	}
	
	namespace ESP
	{
		extern bool enabled;
		
		namespace Tracer
		{
			extern TracerType type;
			extern bool enabled;
		}
		
		namespace Walls
		{
			extern bool enabled;
		}
		
		namespace Name
		{
			extern bool enabled;
		}
	}

	namespace SkinChanger
	{
		extern std::unordered_map<int, std::tuple<int, int, float, int, const char*, const char *>> getSettings();
	}
}

#endif