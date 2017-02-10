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
#include "Utils/draw.h"
#include "Hacks/skinchanger.h"
#include "Utils/util.h"
#include "Utils/util_items.h"
#include "Utils/util_sdk.h"
#include "config.h"
#include "atgui.h"

enum class SmoothType : int
{
	SLOW_END,
	CONSTANT,
	FAST_END
};

enum class  TracerType : int
{
	BOTTOM,
	CURSOR
};

enum class ClanTagType : int
{
	STATIC,
	MARQUEE,
	WORDS,
	LETTERS
};

enum class AutostrafeType : int
{
	AS_FORWARDS,
	AS_BACKWARDS,
	AS_LEFTSIDEWAYS,
	AS_RIGHTSIDEWAYS,
	AS_RAGE
};

enum class AntiAimType_Y : int
{
	SPIN_SLOW,
	SPIN_FAST,
	JITTER,
	SIDE,
	BACKWARDS,
	FORWARDS,
	LEFT,
	RIGHT,
	STATICAA,
	STATICJITTER,
	STATICSMALLJITTER,
	LISP,
	LISP_SIDE,
	LISP_JITTER,
	ANGEL_BACKWARD,
	ANGEL_INVERSE,
	ANGEL_SPIN
};

enum class AntiAimType_X : int
{
	STATIC_UP,
	STATIC_DOWN,
	DANCE,
	FRONT,
	STATIC_UP_FAKE,
	STATIC_DOWN_FAKE,
	LISP_DOWN,
	ANGEL_DOWN,
	ANGEL_UP
};

enum class ChamsType : int
{
	CHAMS,
	CHAMS_XQZ,
	CHAMS_FLAT,
	CHAMS_FLAT_XQZ
};

enum class BoxType : int
{
	FLAT_2D,
	FRAME_2D,
	BOX_3D
};

enum class BarType : int
{
	VERTICAL,
	VERTICAL_RIGHT,
	HORIZONTAL,
	HORIZONTAL_UP,
	INTERWEBZ,
};

enum class BarColorType : int
{
	STATIC_COLOR,
	HEALTH_BASED
};

enum class TeamColorType : int
{
	ABSOLUTE,
	RELATIVE
};

enum class ArmsType : int
{
	DEFAULT,
	RAINBOW,
	WIREFRAME,
	NONE
};

enum class AimTargetType : int
{
	FOV,
	DISTANCE,
	REAL_DISTANCE,
	HP
};

enum class SpammerType : int
{
	SPAMMER_NONE,
	SPAMMER_NORMAL,
	SPAMMER_POSITIONS
};

struct AimbotWeapon_t
{
	bool enabled, silent, friendly;
	Bone bone;
	SmoothType smoothType;
	ButtonCode_t aimkey;
	bool aimkeyOnly, smoothEnabled, smoothSaltEnabled, errorMarginEnabled, autoAimEnabled, aimStepEnabled, rcsEnabled, rcsAlwaysOn;
	float smoothAmount, smoothSaltMultiplier, errorMarginValue, autoAimFov, aimStepValue, rcsAmountX, rcsAmountY, autoWallValue, autoSlowSpeedPercent;
	bool autoPistolEnabled, autoShootEnabled, autoScopeEnabled, noShootEnabled, ignoreJumpEnabled, smokeCheck, flashCheck, autoWallEnabled, autoWallBones[6], autoAimRealDistance, autoSlow;

	AimbotWeapon_t(bool _enabled, bool _silent, bool _friendly, Bone _bone, ButtonCode_t _aimkey, bool _aimkeyOnly,
		   bool _smoothEnabled, float _smoothValue, SmoothType _smoothType, bool _smoothSaltEnabled, float _smoothSaltMultiplier,
		   bool _errorMarginEnabled, float _errorMarginValue,
		   bool _autoAimEnabled, float _autoAimValue, bool _aimStepEnabled, float _aimStepValue,
		   bool _rcsEnabled, bool _rcsAlwaysOn, float _rcsAmountX, float _rcsAmountY,
		   bool _autoPistolEnabled, bool _autoShootEnabled, bool _autoScopeEnabled,
		   bool _noShootEnabled, bool _ignoreJumpEnabled, bool _smokeCheck, bool _flashCheck,
		   bool _autoWallEnabled, float _autoWallValue, bool _autoAimRealDistance, bool _autoSlow,
		   float _autoSlowSpeedPercent, bool _autoWallBones[6] = nullptr)
	{
		this->enabled = _enabled;
		this->silent = _silent;
		this->friendly = _friendly;
		this->bone = _bone;
		this->aimkey = _aimkey;
		this->aimkeyOnly = _aimkeyOnly;
		this->smoothEnabled = _smoothEnabled;
		this->smoothAmount = _smoothValue;
		this->smoothType = _smoothType;
		this->smoothSaltEnabled = _smoothSaltEnabled;
		this->smoothSaltMultiplier = _smoothSaltMultiplier;
		this->errorMarginEnabled = _errorMarginEnabled;
		this->errorMarginValue = _errorMarginValue;
		this->autoAimEnabled = _autoAimEnabled;
		this->autoAimFov = _autoAimValue;
		this->aimStepEnabled = _aimStepEnabled;
		this->aimStepValue = _aimStepValue;
		this->rcsEnabled = _rcsEnabled;
		this->rcsAlwaysOn = _rcsAlwaysOn;
		this->rcsAmountX = _rcsAmountX;
		this->rcsAmountY = _rcsAmountY;
		this->autoPistolEnabled = _autoPistolEnabled;
		this->autoShootEnabled = _autoShootEnabled;
		this->autoScopeEnabled = _autoScopeEnabled;
		this->noShootEnabled = _noShootEnabled;
		this->ignoreJumpEnabled = _ignoreJumpEnabled;
		this->smokeCheck = _smokeCheck;
		this->flashCheck = _flashCheck;
		this->autoWallEnabled = _autoWallEnabled;
		this->autoWallValue = _autoWallValue;
		this->autoSlow = _autoSlow;
		this->autoSlowSpeedPercent = _autoSlowSpeedPercent;

		if(_autoWallBones != nullptr)
			for (int i = (int) Hitbox::HITBOX_HEAD; i <= (int) Hitbox::HITBOX_ARMS; i++)
				this->autoWallBones[i] = _autoWallBones[i];
		else
			for (int i = (int) Hitbox::HITBOX_HEAD; i <= (int) Hitbox::HITBOX_ARMS; i++)
				this->autoWallBones[i] = false;

		this->autoAimRealDistance = _autoAimRealDistance;
	}

	AimbotWeapon_t() {};
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
		extern Bone bone;
		extern ButtonCode_t aimkey;
		extern bool aimkeyOnly;

		namespace Smooth
		{
			extern bool enabled;
			extern float value;
			extern SmoothType type;

			namespace Salting
			{
				extern bool enabled;
				extern float multiplier;
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
			extern bool realDistance;
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
			extern float valueX;
			extern float valueY;
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

		namespace AutoSlow
		{
			extern bool enabled;
			extern float speedPercent;
		}

		namespace NoShoot
		{
			extern bool enabled;
		}

		namespace IgnoreJump
		{
			extern bool enabled;
		}

		namespace SmokeCheck
		{
			extern bool enabled;
		}

		namespace FlashCheck
		{
			extern bool enabled;
		}

		extern std::unordered_map<ItemDefinitionIndex, AimbotWeapon_t, Util::IntHash<ItemDefinitionIndex>> weapons;
	}

	namespace Triggerbot
	{
		extern bool enabled;
		extern ButtonCode_t key;

		namespace Filters
		{
			extern bool enemies;
			extern bool allies;
			extern bool walls;
			extern bool smokeCheck;
			extern bool flashCheck;
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
		namespace AutoDisable
		{
			extern bool noEnemy;
			extern bool knifeHeld;
		}

		namespace Yaw
		{
			extern bool enabled;
			extern AntiAimType_Y type;
			extern AntiAimType_Y typeFake;
		}

		namespace Pitch
		{
			extern bool enabled;
			extern AntiAimType_X type;
		}

		namespace HeadEdge
		{
			extern bool enabled;
			extern float distance;
		}
	}

	namespace Resolver
	{
		extern bool resolveAll;
	}

	namespace ESP
	{
		extern bool enabled;
		extern TeamColorType teamColorType;
		extern ImColor enemyColor;
		extern ImColor allyColor;
		extern ImColor enemyVisibleColor;
		extern ImColor allyVisibleColor;
		extern ImColor ctColor;
		extern ImColor tColor;
		extern ImColor ctVisibleColor;
		extern ImColor tVisibleColor;
		extern ImColor bombColor;
		extern ImColor bombDefusingColor;
		extern ImColor hostageColor;
		extern ImColor defuserColor;
		extern ImColor weaponColor;
		extern ImColor chickenColor;
		extern ImColor fishColor;
		extern ImColor smokeColor;
		extern ImColor decoyColor;
		extern ImColor flashbangColor;
		extern ImColor grenadeColor;
		extern ImColor molotovColor;
		extern ImColor localplayerColor;
		extern bool hpEnemyColor;
		extern bool hpAllyColor;
		extern bool hpEnemyVisibleColor;
		extern bool hpAllyVisibleColor;
		extern bool hpCtColor;
		extern bool hpTColor;
		extern bool hpCtVisibleColor;
		extern bool hpTVisibleColor;
		extern bool hpLocalplayerColor;

		namespace Glow
		{
			extern bool enabled;
			extern ImColor allyColor;
			extern ImColor enemyColor;
			extern ImColor enemyVisibleColor;
			extern ImColor weaponColor;
			extern ImColor grenadeColor;
			extern ImColor defuserColor;
			extern ImColor chickenColor;
			extern ImColor localplayerColor;
			extern bool hpAllyColor;
			extern bool hpEnemyColor;
			extern bool hpEnemyVisibleColor;
			extern bool hpLocalplayerColor;
		}

		namespace Filters
		{
			extern bool legit;
			extern bool visibilityCheck;
			extern bool smokeCheck;
			extern bool flashCheck;
			extern bool enemies;
			extern bool allies;
			extern bool bomb;
			extern bool hostages;
			extern bool defusers;
			extern bool weapons;
			extern bool chickens;
			extern bool fishes;
			extern bool throwables;
			extern bool localplayer;
		}

		namespace Info
		{
			extern bool name;
			extern bool clan;
			extern bool steamId;
			extern bool rank;
			extern bool health;
			extern bool weapon;
			extern bool scoped;
			extern bool reloading;
			extern bool flashed;
			extern bool planting;
			extern bool hasDefuser;
			extern bool defusing;
			extern bool grabbingHostage;
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
			extern BoxType type;
		}

		namespace Bars
		{
			extern bool enabled;
			extern BarType type;
			extern BarColorType colorType;
		}

		namespace Tracers
		{
			extern bool enabled;
			extern TracerType type;
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
			extern bool enabled;
			extern ImColor allyColor;
			extern ImColor allyVisibleColor;
			extern ImColor enemyColor;
			extern ImColor enemyVisibleColor;
			extern ImColor localplayerColor;
			extern ChamsType type;
			extern bool hpAllyColor;
			extern bool hpAllyVisibleColor;
			extern bool hpEnemyColor;
			extern bool hpEnemyVisibleColor;
			extern bool hpLocalplayerColor;

			namespace Arms
			{
				extern bool enabled;
				extern ImColor color;
				extern ArmsType type;
			}

			namespace Weapon
			{
				extern bool enabled;
				extern ImColor color;
			}
		}

		namespace Sounds
		{
			extern bool enabled;
			extern int time;
		}

		namespace Hitmarker
		{
			extern bool enabled;
			extern bool enemies;
			extern bool allies;
			extern ImColor color;
			extern int duration;
			extern int size;
			extern int innerGap;

			namespace Damage
			{
				extern bool enabled;
			}
		}

		namespace HeadDot
		{
			extern bool enabled;
			extern float size;
		}
	}

	namespace Dlights
	{
		extern bool enabled;
		extern float radius;
	}

	namespace Spammer
	{
		extern SpammerType type;
		extern bool say_team;

		namespace KillSpammer
		{
			extern std::vector<std::string> messages;
			extern bool enabled;
			extern bool sayTeam;
		}

		namespace RadioSpammer
		{
			extern bool enabled;
		}

		namespace NormalSpammer
		{
			extern std::vector<std::string> messages;
		}

		namespace PositionSpammer
		{
			extern int team;
			extern bool showName;
			extern bool showWeapon;
			extern bool showRank;
			extern bool showWins;
			extern bool showHealth;
			extern bool showMoney;
			extern bool showLastplace;
		}
	}

	namespace BHop
	{
		extern bool enabled;
	}

	namespace AutoStrafe
	{
		extern bool enabled;
		extern AutostrafeType type;
		extern bool silent;
	}

	namespace Noflash
	{
		extern bool enabled;
		extern float value;
	}

	namespace FOVChanger
	{
		extern bool enabled;
		extern bool viewmodelEnabled;
		extern float value;
		extern float viewmodelValue;
		extern bool ignoreScope;
	}

	namespace Radar
	{
		extern bool enabled;
		extern float zoom;
		extern bool enemies;
		extern bool allies;
		extern bool bomb;
		extern bool defuser;
		extern bool legit;
		extern bool visibilityCheck;
		extern bool smokeCheck;
		extern TeamColorType team_color_type;
		extern ImColor enemyColor;
		extern ImColor enemyVisibleColor;
		extern ImColor allyColor;
		extern ImColor allyVisibleColor;
		extern ImColor tColor;
		extern ImColor tVisibleColor;
		extern ImColor ctColor;
		extern ImColor ctVisibleColor;
		extern ImColor bombColor;
		extern ImColor bombDefusingColor;
		extern ImColor defuser_color;
		extern float iconsScale;
		extern bool hpEnemyColor;
		extern bool hpEnemyVisibleColor;
		extern bool hpAllyColor;
		extern bool hpAllyVisibleColor;
		extern bool hpTColor;
		extern bool hpTVisibleColor;
		extern bool hpCtColor;
		extern bool hpCtVisibleColor;

		namespace InGame
		{
			extern bool enabled;
		}
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

	namespace Autoblock
	{
		extern bool enabled;
		extern ButtonCode_t key;
	}

	namespace Skinchanger
	{
		extern bool enabled;

		namespace Gloves
		{
			extern bool enabled;
		}

		extern std::unordered_map<ItemDefinitionIndex, AttribItem_t, Util::IntHash<ItemDefinitionIndex>> skins;
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
		extern char value[30];
		extern bool animation;
		extern int animationSpeed;
		extern bool enabled;
		extern ClanTagType type;
	}

	namespace View
	{
		namespace NoAimPunch
		{
			extern bool enabled;
		}

		namespace NoViewPunch
		{
			extern bool enabled;
		}
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

	namespace NoSky
	{
		extern bool enabled;
		extern ImColor color;
	}

	namespace ASUSWalls
	{
		extern bool enabled;
		extern ImColor color;
	}

	namespace NoScopeBorder
	{
		extern bool enabled;
	}

	namespace SniperCrosshair
	{
		extern bool enabled;
	}

	namespace AutoDefuse
	{
		extern bool enabled;
	}

	namespace NoSmoke
	{
		extern bool enabled;
	}

	namespace ScreenshotCleaner
	{
		extern bool enabled;
	}

	namespace EdgeJump
	{
		extern bool enabled;
		extern ButtonCode_t key;
	}

	namespace NameStealer
	{
		extern bool enabled;
		extern int team;
	}

	namespace ThirdPerson
	{
		extern bool enabled;
		extern float distance;
	}

	namespace JumpThrow
	{
		extern bool enabled;
		extern ButtonCode_t key;
	}

	void LoadDefaultsOrSave(std::string path);
	void LoadConfig(std::string path);
	void LoadSettings();
	void DeleteConfig(std::string path);
}
