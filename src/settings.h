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

enum BoxType : int
{
	FLAT_2D,
	FRAME_2D
};

enum BarType : int
{
	VERTICAL,
	HORIZONTAL,
	HORIZONTAL_UP,
	INTERWEBZ
};

enum BarColorType : int
{
	STATIC_COLOR,
	HEALTH_BASED
};

enum TeamColorType : int
{
	ABSOLUTE,
	RELATIVE
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
			namespace ESP
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
			extern bool walls;
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
		extern int team_color_type;
		extern ImColor enemy_color;
		extern ImColor ally_color;
		extern ImColor enemy_visible_color;
		extern ImColor ally_visible_color;
		extern ImColor ct_color;
		extern ImColor t_color;
		extern ImColor ct_visible_color;
		extern ImColor t_visible_color;
		extern ImColor bomb_color;
		extern ImColor bomb_defusing_color;
		extern ImColor hostage_color;
		extern ImColor defuser_color;
		extern ImColor weapon_color;
		extern ImColor chicken_color;
		extern ImColor fish_color;
		extern ImColor smoke_color;
		extern ImColor decoy_color;
		extern ImColor flashbang_color;
		extern ImColor grenade_color;
		extern ImColor molotov_color;

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

		namespace Filters
		{
			extern bool legit;
			extern bool visibility_check;
			extern bool enemies;
			extern bool allies;
			extern bool bomb;
			extern bool hostages;
			extern bool defusers;
			extern bool weapons;
			extern bool chickens;
			extern bool fishes;
			extern bool throwables;
		}

		namespace Info
		{
			extern bool name;
			extern bool clan;
			extern bool steam_id;
			extern bool rank;
			extern bool health;
			extern bool weapon;
			extern bool scoped;
			extern bool reloading;
			extern bool flashed;
			extern bool planting;
			extern bool has_defuser;
			extern bool defusing;
			extern bool grabbing_hostage;
			extern bool rescuing;
			extern bool location;
		}

		namespace Skeleton
		{
			extern bool enabled;
			extern ImColor color;
		}

		namespace Boxes
		{
			extern bool enabled;
			extern int type;
		}

		namespace Bars
		{
			extern bool enabled;
			extern int type;
			extern int color_type;
		}

		namespace Tracers
		{
			extern bool enabled;
			extern int type;
		}

		namespace BulletTracers
		{
			extern bool enabled;
		}

		namespace Bomb
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
			extern std::vector<std::string> messages;
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
		extern int animation_speed;
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

	void LoadDefaultsOrSave(std::string path);
	void LoadConfig(std::string path);
	void LoadSettings();
	void DeleteConfig(std::string path);
}
