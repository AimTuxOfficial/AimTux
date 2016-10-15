#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include <unordered_map>
#include <zconf.h>
#include <fstream>
#include "json/json.h"
#include "SDK/SDK.h"
#include "fonts.h"
#include "draw.h"

enum TracerType : unsigned int
{
	BOTTOM,
	CURSOR
};

enum AntiAimType_Y : unsigned int
{
	SPIN_FAST,
	SPIN_SLOW,
	JITTER,
	SIDE,
	BACKWARDS
};

enum AntiAimType_X : unsigned int
{
	STATIC_UP,
	STATIC_DOWN
};

enum ChamsType : unsigned int
{
	CHAMS,
	CHAMS_FLAT
};

enum WallBoxType : unsigned int
{
	FLAT_2D,
	BOX_3D
};

namespace Settings
{
	namespace UI
	{
		extern Color mainColor;
		extern Color bodyColor;

		namespace Fonts
		{
			namespace Title
			{
				extern char family[64];
				extern int size;
			}

			namespace Normal
			{
				extern char family[64];
				extern int size;
			}

			namespace ESP
			{
				extern char family[64];
				extern int size;
			}
		}
	}

	namespace Aimbot
	{
		extern bool enabled;
		extern bool silent;
		extern float fov;
		extern int bone;
		extern ButtonCode_t aimkey;

		namespace Smooth
		{
			extern bool enabled;
			extern float value;
			extern float max;
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
			extern bool autoscope;
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

		namespace Filter
		{
			extern bool friendly;
			extern bool head;
			extern bool chest;
			extern bool stomach;
			extern bool arms;
			extern bool legs;
		}

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
			extern WallBoxType type;
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

		namespace Weapons
		{
			extern bool enabled;
		}

		namespace FOVCrosshair
		{
			extern bool enabled;
		}

		namespace Chams
		{
			extern bool players;
			extern bool visibility_check;
			extern bool arms;
			extern bool rainbow_arms;
			extern Color players_ally_color;
			extern Color players_ally_visible_color;
			extern Color players_enemy_color;
			extern Color players_enemy_visible_color;
			extern Color arms_color;
			extern ChamsType type;
		}
	}

	namespace Dlights
	{
		extern bool enabled;
		extern float radius;
		extern Color ally_color;
		extern Color enemy_color;
	}

	namespace Spammer
	{
		namespace KillSpammer
		{
			extern bool enabled;
		}
		
		namespace NormalSpammer
		{
			extern bool enabled;
		}
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
		extern ButtonCode_t key;
	}

	namespace Skinchanger
	{
		struct Skin
		{
			int PaintKit;
			int ItemDefinitionIndex;
			float Wear;
			int StatTrak;
			std::string CustomName;
			std::string Model;

			Skin (int PaintKit, int ItemDefinitionIndex, float Wear, int StatTrak, std::string CustomName, std::string Model)
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

	namespace ShowRanks
	{
		extern bool enabled;
	}

	namespace ShowSpectators
	{
		extern bool enabled;
	}

	void LoadDefaultsOrSave(const char* filename);
	void LoadSettings(const char* filename);
}

#endif
