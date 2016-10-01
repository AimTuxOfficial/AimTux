#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "weapons.h"
#include "SDK.h"

enum TracerType
{
	BOTTOM,
	CURSOR
};

enum AntiAimType_Y
{
	SPIN,
	JITTER,
	SIDE,
	BACKWARDS
};

enum AntiAimType_X
{
	STATIC_UP,
	STATIC_DOWN
};

namespace Settings
{
	namespace Aimbot
	{
		extern bool enabled;
		extern float fov;
		
		namespace AutoAim
		{
			extern bool enabled;
		}
		
		namespace RCS
		{
			extern bool enabled;
		}
		
		namespace AutoShoot
		{
			extern bool enabled;
		}
		

		namespace AutoCrouch
		{
			extern bool enabled;
		}

		namespace AutoStop
		{
			extern bool enabled;
		}
	}

	namespace Triggerbot
	{
		extern bool enabled;
		extern ButtonCode_t key;
	}

	namespace AntiAim
	{
		extern bool enabled_Y;
		extern bool enabled_X;
		extern AntiAimType_Y type_Y;
		extern AntiAimType_X type_X;
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
			extern bool showHealth;
		}
		
		namespace Bones
		{
			extern bool enabled;
		}
	}
	
	namespace Spammer
	{
		extern bool enabled;
	}
	
	namespace BHop
	{
		extern bool enabled;
	}

	namespace AutoStrafe
	{
		extern bool enabled;
	}
}

#endif