#pragma once

#include <unordered_map>
#include <zconf.h>
#include <fstream>
#include <vector>
#include "json/json.h"
#include "SDK/SDK.h"
#include "fonts.h"
#include "draw.h"
#include "skinchanger.h"
#include "util.h"
#include "util_items.h"

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
	BACKWARDS,
	FAKE4,
	BACKWARDS_FAKE,
	SIDE_FLIP_FAKE,
	SIDE_FAKE_LEFT,
	SIDE_FAKE_RIGHT
};

enum AntiAimType_X : unsigned int
{
	STATIC_UP,
	STATIC_DOWN,
	STATIC_UP_FAKE,
	STATIC_DOWN_FAKE
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

enum ArmsType : unsigned int
{
	RAINBOW,
	WIREFRAME,
	NONE,
	DEFAULT
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
				extern char* family;
				extern int size;
				extern int flags;
			}

			namespace Normal
			{
				extern char* family;
				extern int size;
				extern int flags;
			}

			namespace ESP
			{
				extern char* family;
				extern int size;
				extern int flags;
			}

			namespace Mono
			{
				extern char* family;
				extern int size;
				extern int flags;
			}
		}
	}

	namespace Aimbot
	{
		extern bool enabled;
		extern bool silent;
		extern bool friendly;
		extern float fov;
		extern float errorMargin;
		extern unsigned int bone;
		extern ButtonCode_t aimkey;
		extern bool aimkey_only;

		namespace Smooth
		{
			extern bool enabled;
			extern float value;
			extern float max;

			namespace Salting
			{
				extern bool enabled;
				extern float percentage;
			}
		}

		namespace AutoAim
		{
			extern bool enabled;
		}

		namespace AutoWall
		{
			extern bool enabled;
			extern float value;
			extern std::vector<Hitbox> bones;
		}

		namespace AimStep
		{
			extern bool enabled;
			extern float value;
		}

		namespace RCS
		{
			extern bool enabled;
			extern float value;
		}

		namespace AutoPistol
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

		namespace Delay
		{
			extern bool enabled;
			extern int value;
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
		extern bool friendly;
		extern Color ally_color;
		extern Color enemy_color;
		extern Color enemy_visible_color;
		extern Color bones_color;
		extern Color bomb_color;

		namespace Glow
		{
			extern bool enabled;
			extern Color ally_color;
			extern Color enemy_color;
			extern Color enemy_visible_color;
			extern Color weapon_color;
		}

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
			extern bool showWeapon;
			extern bool colorCode;
			extern Color ally_color;
			extern Color enemy_visible_color;
			extern Color enemy_color;
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
			extern Color players_ally_color;
			extern Color players_ally_visible_color;
			extern Color players_enemy_color;
			extern Color players_enemy_visible_color;
			extern ChamsType type;

			namespace Arms
			{
				extern bool enabled;
				extern Color color;
				extern ArmsType type;
			}
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
			extern bool say_team;
			extern char* message;
		}

		namespace PositionSpammer
		{
			extern bool enabled;
			extern bool say_team;
		}

		namespace NormalSpammer
		{
			extern bool enabled;
			extern bool say_team;
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

	namespace FOVChanger
	{
		extern bool enabled;
		extern bool viewmodel_enabled;
		extern float value;
		extern float viewmodel_value;
	}

	namespace Radar
	{
		extern bool enabled;
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
			int Seed;
			float Wear;
			int StatTrak;
			std::string CustomName;
			std::string Model;

			Skin (int PaintKit, int ItemDefinitionIndex, int Seed, float Wear, int StatTrak, std::string CustomName, std::string Model)
			{
				this->PaintKit = PaintKit;
				this->Seed = Seed;
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

	namespace ClanTagChanger
	{
		extern std::string value;
		extern bool animation;
		extern bool enabled;
	}

	namespace View
	{
		namespace NoPunch
		{
			extern bool enabled;
		}
	}

	namespace NameChanger
	{
		extern bool enabled;
		extern bool last_blank;
	}

	namespace Teleport
	{
		extern bool enabled;
		extern ButtonCode_t key;
	}

	namespace FakeLag
	{
		extern bool enabled;
		extern int value;
	}

	void LoadDefaultsOrSave(const char* filename);
	void LoadSettings(const char* filename);
}
