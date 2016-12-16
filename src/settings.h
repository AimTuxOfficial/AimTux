#pragma once

#include <unordered_map>
#include <zconf.h>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "json/json.h"
#include "SDK/SDK.h"
#include "fonts.h"
#include "draw.h"
#include "skinchanger.h"
#include "util.h"
#include "util_items.h"
#include "config.h"
#include "atgui.h"

enum TracerType : int
{
	BOTTOM,
	CURSOR
};

enum ClanTagType : int
{
	STATIC,
	MARQUEE,
	WORDS,
	LETTERS
};

enum AutostrafeType : int
{
	AS_FORWARDS,
	AS_BACKWARDS,
	AS_LEFTSIDEWAYS,
	AS_RIGHTSIDEWAYS
};

enum AntiAimType_Y : int
{
	SPIN_SLOW,
	SPIN_FAST,
	JITTER,
	SIDE,
	BACKWARDS,
	FORWARDS,
	LEFT,
	RIGHT,
	STATICAA
};

enum AntiAimType_X : int
{
	STATIC_UP,
	STATIC_DOWN,
	DANCE,
	FRONT,
	STATIC_UP_FAKE,
	STATIC_DOWN_FAKE
};

enum ChamsType : int
{
	CHAMS,
	CHAMS_FLAT
};

enum WallBoxType : int
{
	FLAT_2D,
	BOX_3D
};

enum ArmsType : int
{
	DEFAULT,
	RAINBOW,
	WIREFRAME,
	NONE
};

enum AimTargetType : int
{
	FOV,
	DISTANCE,
	HP
};

namespace Settings
{
	namespace UI
	{
		extern ImColor mainColor;
		extern ImColor bodyColor;
		extern ImColor fontColor;

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
		extern int bone;
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

		namespace ErrorMargin
		{
			extern bool enabled;
			extern float value;
		}

		namespace AutoAim
		{
			extern bool enabled;
			extern float fov;
		}

		namespace AutoWall
		{
			extern bool enabled;
			extern float value;
			extern bool bones[];
		}

		namespace AimStep
		{
			extern bool enabled;
			extern float value;
		}

		namespace RCS
		{
			extern bool enabled;
			extern bool always_on;
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

		namespace NoShoot
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
		namespace Yaw
		{
			extern bool enabled;
			extern int type;
			extern int type_fake;
		}

		namespace Pitch
		{
			extern bool enabled;
			extern int type;
		}

		namespace HeadEdge
		{
			extern bool enabled;
			extern float distance;
		}

		namespace FakeOut
		{
			extern bool enabled;
		}
	}

	namespace ESP
	{
		extern bool enabled;
		extern bool visibility_check;
		extern bool friendly;
		extern bool show_scope_border;
		extern ImColor ally_color;
		extern ImColor enemy_color;
		extern ImColor enemy_visible_color;
		extern ImColor bones_color;
		extern ImColor bomb_color;

		namespace Glow
		{
			extern bool enabled;
			extern ImColor ally_color;
			extern ImColor enemy_color;
			extern ImColor enemy_visible_color;
			extern ImColor weapon_color;
			extern ImColor grenade_color;
			extern ImColor defuser_color;
		}

		namespace Tracer
		{
			extern int type;
			extern bool enabled;
		}

		namespace Walls
		{
			extern bool enabled;
			extern int type;
		}

		namespace Info
		{
			extern bool showName;
			extern bool showHealth;
			extern bool showWeapon;
			extern bool colorCode;
			extern ImColor ally_color;
			extern ImColor enemy_visible_color;
			extern ImColor enemy_color;
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
			extern ImColor color;
		}

		namespace Chams
		{
			extern bool players;
			extern bool visibility_check;
			extern ImColor players_ally_color;
			extern ImColor players_ally_visible_color;
			extern ImColor players_enemy_color;
			extern ImColor players_enemy_visible_color;
			extern int type;

			namespace Arms
			{
				extern bool enabled;
				extern ImColor color;
				extern int type;
			}
		}
	}

	namespace Dlights
	{
		extern bool enabled;
		extern float radius;
		extern ImColor ally_color;
		extern ImColor enemy_color;
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
		extern int type;
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
		extern bool showOnlyWhenShooting;
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
		extern char* value;
		extern bool animation;
		extern bool enabled;
		extern int type;
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

	namespace AutoAccept
	{
		extern bool enabled;
	}

	namespace Resolver
	{
		extern bool enabled;
	}

	void LoadDefaultsOrSave(std::string path);
	void LoadConfig(std::string path);
	void LoadSettings();
	void DeleteConfig(std::string path);
}
