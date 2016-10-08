#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include <unordered_map>
#include <zconf.h>
#include <fstream>
#include "json/json.h"
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
	namespace UI
	{
		extern Color mainColor;
		extern Color bodyColor;
	}
	
	namespace Aimbot
	{
		extern bool enabled;
		extern bool silent;
		extern float fov;
		extern int bone;

		namespace Smooth
		{
			extern bool enabled;
			extern float value;
		}
		
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

		namespace Hitchance
		{
			extern bool enabled;
			extern float value;
		}
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
		extern Color ally_color;
		extern Color enemy_color;
		extern Color enemy_visible_color;
		extern Color bones_color;
		extern Color bomb_color;

		namespace Tracer
		{
			extern TracerType type;
			extern bool enabled;
		}
		
		namespace Walls
		{
			extern bool enabled;
		}
		
		namespace Info
		{
			extern bool showName;
			extern bool showHealth;
		}
		
		namespace Bones
		{
			extern bool enabled;
		}

		namespace Bomb
		{
			extern bool enabled;
		}
		
		namespace Chams
		{
			extern bool players;
			extern bool arms;
			extern bool rainbow_arms;
			extern Color players_ally_color;
			extern Color players_enemy_color;
			extern Color players_enemy_visible_color;
			extern Color arms_color;
			extern ChamsType type;
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

	namespace Noflash
	{
		extern bool enabled;
		extern float value;
	}

	namespace Recoilcrosshair
	{
		extern bool enabled;
	}

	namespace Airstuck
	{
		extern bool enabled;
	}

	namespace Skinchanger
	{
		struct Skin
		{
			int PaintKit;
			int ItemDefinitionIndex;
			float Wear;
			int StatTrak;
			const char* CustomName;
			const char* Model;

			Skin (int PaintKit, int ItemDefinitionIndex, float Wear, int StatTrak, const char* CustomName, const char* Model)
			{
				this->PaintKit = PaintKit;
				this->ItemDefinitionIndex = ItemDefinitionIndex;
				this->Wear = Wear;
				this->StatTrak = StatTrak;
				this->CustomName = CustomName;
				this->Model = Model;
			}

			Skin() { };
		};

		extern bool enabled;
		extern std::unordered_map<int, Skin> skins;
	}

	void LoadOrSave();
	void LoadSettings();
}

#endif
