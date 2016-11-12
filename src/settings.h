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

struct CSettings
{
	struct
	{
		Color mainColor = Color(230, 75, 100);
		Color bodyColor = Color(25, 25, 35, 200);

		struct
		{
			struct
			{
				char *family;
				int size;
			} Title;

			struct
			{
				char *family;
				int size;
			} Normal;

			struct
			{
				char *family;
				int size;
			} ESP;
		} Fonts;
	} UI;

	struct
	{
		bool enabled;
		bool silent;
		bool friendly;
		float fov;
		float errorMargin;
		unsigned int bone;
		ButtonCode_t aimkey;
		bool aimkey_only;

		struct
		{
			bool enabled;
			float value;
			float max;

			struct
			{
				bool enabled;
				float percentage;
			} Salting;
		} Smooth;

		struct
		{
			bool enabled;
		} AutoAim;

		struct
		{
			bool enabled;
			float value;
			std::vector<Hitbox> bones;
		} AutoWall;

		struct
		{
			bool enabled;
			float value;
		} AimStep;

		struct
		{
			bool enabled;
			float value;
		} RCS;

		struct
		{
			bool enabled;
		} AutoPistol;

		struct
		{
			bool enabled;
			bool autoscope;
		} AutoShoot;

		struct
		{
			bool enabled;
		} AutoCrouch;

		struct
		{
			bool enabled;
		} AutoStop;
	} Aimbot;

	struct
	{
		bool enabled;
		ButtonCode_t key;

		struct
		{
			bool friendly;
			bool head;
			bool chest;
			bool stomach;
			bool arms;
			bool legs;
		} Filter;

		struct
		{
			bool enabled;
			int value;
		} Delay;
	} Triggerbot;

	struct
	{
		bool enabled_Y;
		bool enabled_X;
		AntiAimType_Y type_Y;
		AntiAimType_X type_X;
	} AntiAim;

	struct
	{
		bool enabled;
		bool visibility_check;
		bool friendly;
		Color ally_color;
		Color enemy_color;
		Color enemy_visible_color;
		Color bones_color;
		Color bomb_color;

		struct
		{
			bool enabled;
			Color ally_color;
			Color enemy_color;
			Color enemy_visible_color;
			Color weapon_color;
		} Glow;

		struct
		{
			TracerType type;
			bool enabled;
		} Tracer;

		struct
		{
			bool enabled;
			WallBoxType type;
		} Walls;

		struct
		{
			bool showName;
			bool showHealth;
			Color ally_color;
			Color enemy_visible_color;
			Color enemy_color;
		} Info;

		struct
		{
			bool enabled;
		} Bones;

		struct
		{
			bool enabled;
		} Bomb;

		struct
		{
			bool enabled;
		} Weapons;

		struct
		{
			bool enabled;
		} FOVCrosshair;

		struct
		{
			bool players;
			bool visibility_check;
			Color players_ally_color;
			Color players_ally_visible_color;
			Color players_enemy_color;
			Color players_enemy_visible_color;
			ChamsType type;

			struct
			{
				bool enabled;
				Color color;
				ArmsType type;
			} Arms;
		} Chams;
	} ESP;

	struct
	{
		bool enabled;
		float radius;
		Color ally_color;
		Color enemy_color;
	} Dlights;

	struct
	{
		struct
		{
			bool enabled;
			bool say_team;
			char* message;
		} KillSpammer;

		struct
		{
			bool enabled;
			bool say_team;
		} PositionSpammer;

		struct
		{
			bool enabled;
			bool say_team;
		} NormalSpammer;
	} Spammer;

	struct
	{
		bool enabled;
	} BHop;

	struct
	{
		bool enabled;
	} AutoStrafe;

	struct
	{
		bool enabled;
		float value;
	} Noflash;

	struct
	{
		bool enabled;
		bool viewmodel_enabled;
		float value;
		float viewmodel_value;
	} FOVChanger;

	struct
	{
		bool enabled;
	} Radar;

	struct
	{
		bool enabled;
	} Recoilcrosshair;

	struct
	{
		bool enabled;
		ButtonCode_t key;
	} Airstuck;

	struct {
		bool enabled;
		std::unordered_map<int, Skin> skins;
	} Skinchanger;

	struct
	{
		bool enabled;
	} ShowRanks;

	struct
	{
		bool enabled;
	} ShowSpectators;

	struct
	{
		std::string value;
		bool animation;
		bool enabled;
	} ClanTagChanger;

	struct
	{
		struct
		{
			bool enabled;
		} NoPunch;
	} View;

	struct
	{
		bool enabled;
		bool last_blank;
	} NameChanger;

	struct
	{
		bool enabled;
		ButtonCode_t key;
	} Teleport;

	struct
	{
		bool enabled;
		int value;
	} FakeLag;
};

namespace Settings
{
	void LoadDefaults();
	void LoadDefaultsOrSave(const char* filename);
	void LoadSettings(const char* filename);
}

extern CSettings cSettings;