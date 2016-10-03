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
	SPIN_FAST,
	SPIN_SLOW,
	JITTER,
	SIDE,
	BACKWARDS
};

enum AntiAimType_X
{
	STATIC_UP,
	STATIC_DOWN
};

enum ChamsType
{
	CHAMS,
	CHAMS_IGNOREZ,
	CHAMS_FLAT,
	CHAMS_FLAT_IGNOREZ
};

namespace Settings
{
	namespace Aimbot
	{
		extern bool enabled;
		extern float fov;
		extern int bone;
		
		namespace AutoAim
		{
			extern bool enabled;
		}

		namespace AimStep
		{
			extern bool enabled;
			extern float value;
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
		extern bool visibility_check;
		
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

	namespace Chams
	{
		extern bool enabled;
		extern ChamsType type;
	}

	namespace Noflash
	{
		extern bool enabled;
	}
}

#endif