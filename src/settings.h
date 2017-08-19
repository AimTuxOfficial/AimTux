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
#include "ATGUI/atgui.h"
#include "Hacks/esp.h"

enum class SmoothType : int
{
	SLOW_END,
	CONSTANT,
	FAST_END,
};

enum class  TracerType : int
{
	BOTTOM,
	CURSOR,
};

enum class ClanTagType : int
{
	STATIC,
	MARQUEE,
	WORDS,
	LETTERS,
};

enum class AutostrafeType : int
{
	AS_FORWARDS,
	AS_BACKWARDS,
	AS_LEFTSIDEWAYS,
	AS_RIGHTSIDEWAYS,
	AS_RAGE,
};

enum class AntiAimType_Y : int
{
	SPIN_SLOW,
	SPIN_FAST,
	JITTER,
	BACKJITTER,
	SIDE,
	BACKWARDS,
	FORWARDS,
	LEFT,
	RIGHT,
	STATICAA,
	STATICJITTER,
	STATICSMALLJITTER,
	LUA1, // ImGui stole the name of LUA
	LUA2, // Alternate LUA if you want a separate one for Fake.
	CASUAL,
	LISP,
	LISP_SIDE,
	LISP_JITTER,
	ANGEL_BACKWARD,
	ANGEL_INVERSE,
	ANGEL_SPIN,
	LOWERBODY,
	LBYONGROUND,
	LUA_UNCLAMPED,
	LUA_UNCLAMPED2
};

enum class AntiAimType_X : int
{
	STATIC_UP,
	STATIC_DOWN,
	DANCE,
	FRONT,
	LUA1,
	STATIC_UP_FAKE,
	STATIC_DOWN_FAKE,
	LISP_DOWN,
	ANGEL_DOWN,
	ANGEL_UP,
	LUA_UNCLAMPED,
};

enum class ChamsType : int
{
	CHAMS,
	CHAMS_XQZ,
	CHAMS_FLAT,
	CHAMS_FLAT_XQZ,
};

enum class BoxType : int
{
	FLAT_2D,
	FRAME_2D,
	BOX_3D,
	HITBOXES,
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
	HEALTH_BASED,
};

enum class TeamColorType : int
{
	ABSOLUTE,
	RELATIVE,
};

enum class ArmsType : int
{
	DEFAULT,
	WIREFRAME,
	NONE,
};

enum class AimTargetType : int
{
	FOV,
	DISTANCE,
	REAL_DISTANCE,
	HP,
};

enum class SpammerType : int
{
	SPAMMER_NONE,
	SPAMMER_NORMAL,
	SPAMMER_POSITIONS,
};

struct AimbotWeapon_t
{
	bool enabled, silent, friendly, closestBone, desiredBones[31], engageLock, engageLockTR;
	int engageLockTTR;
	Bone bone;
	SmoothType smoothType;
	ButtonCode_t aimkey;
	bool aimkeyOnly, smoothEnabled, smoothSaltEnabled, errorMarginEnabled, autoAimEnabled, aimStepEnabled, rcsEnabled, rcsAlwaysOn, spreadLimitEnabled;
	float smoothAmount, smoothSaltMultiplier, errorMarginValue, autoAimFov, aimStepMin, aimStepMax, rcsAmountX, rcsAmountY, autoWallValue, spreadLimit;
	bool autoPistolEnabled, autoShootEnabled, autoScopeEnabled, noShootEnabled, ignoreJumpEnabled, smokeCheck, flashCheck, autoWallEnabled, autoAimRealDistance, autoSlow, predEnabled, moveMouse;

	AimbotWeapon_t(bool enabled, bool silent, bool friendly, bool closestBone, bool engageLock, bool engageLockTR, int engageLockTTR, Bone bone, ButtonCode_t aimkey, bool aimkeyOnly,
		   bool smoothEnabled, float smoothValue, SmoothType smoothType, bool smoothSaltEnabled, float smoothSaltMultiplier,
		   bool errorMarginEnabled, float errorMarginValue,
		   bool autoAimEnabled, float autoAimValue, bool aimStepEnabled, float aimStepMin, float aimStepMax,
		   bool rcsEnabled, bool rcsAlwaysOn, float rcsAmountX, float rcsAmountY,
		   bool autoPistolEnabled, bool autoShootEnabled, bool autoScopeEnabled,
		   bool noShootEnabled, bool ignoreJumpEnabled, bool smokeCheck, bool flashCheck,
		   bool spreadLimitEnabled, float spreadLimit,
		   bool autoWallEnabled, float autoWallValue, bool autoAimRealDistance, bool autoSlow,
		   bool predEnabled, bool moveMouse)
	{
		this->enabled = enabled;
		this->silent = silent;
		this->friendly = friendly;
		this->closestBone = closestBone;
		this->engageLock = engageLock;
		this->engageLockTR = engageLockTR;
		this->engageLockTTR = engageLockTTR;
		this->bone = bone;
		this->aimkey = aimkey;
		this->aimkeyOnly = aimkeyOnly;
		this->smoothEnabled = smoothEnabled;
		this->smoothAmount = smoothValue;
		this->smoothType = smoothType;
		this->smoothSaltEnabled = smoothSaltEnabled;
		this->smoothSaltMultiplier = smoothSaltMultiplier;
		this->errorMarginEnabled = errorMarginEnabled;
		this->errorMarginValue = errorMarginValue;
		this->autoAimEnabled = autoAimEnabled;
		this->autoAimFov = autoAimValue;
		this->aimStepEnabled = aimStepEnabled;
		this->aimStepMin = aimStepMin;
		this->aimStepMax = aimStepMax;
		this->rcsEnabled = rcsEnabled;
		this->rcsAlwaysOn = rcsAlwaysOn;
		this->rcsAmountX = rcsAmountX;
		this->rcsAmountY = rcsAmountY;
		this->autoPistolEnabled = autoPistolEnabled;
		this->autoShootEnabled = autoShootEnabled;
		this->autoScopeEnabled = autoScopeEnabled;
		this->noShootEnabled = noShootEnabled;
		this->ignoreJumpEnabled = ignoreJumpEnabled;
		this->smokeCheck = smokeCheck;
		this->flashCheck = flashCheck;
		this->spreadLimitEnabled = spreadLimitEnabled;
		this->spreadLimit = spreadLimit;
		this->autoWallEnabled = autoWallEnabled;
		this->autoWallValue = autoWallValue;
		this->autoSlow = autoSlow;
		this->predEnabled = predEnabled;
		this->moveMouse = moveMouse;

		for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
			this->desiredBones[bone] = (desiredBones != nullptr ) ? desiredBones[bone] : false;

		this->autoAimRealDistance = autoAimRealDistance;
	}

	AimbotWeapon_t() {};

	bool operator == (const AimbotWeapon_t& another) const
	{
		for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
		{
			if( this->desiredBones[bone] != another.desiredBones[bone] )
				return false;
		}

		return this->enabled == another.enabled &&
			this->silent == another.silent &&
			this->friendly == another.friendly &&
			this->closestBone == another.closestBone &&
			this->engageLock == another.engageLock &&
			this->engageLockTR == another.engageLockTR &&
			this->engageLockTTR == another.engageLockTTR &&
			this->bone == another.bone &&
			this->aimkey == another.aimkey &&
			this->aimkeyOnly == another.aimkeyOnly &&
			this->smoothEnabled == another.smoothEnabled &&
			this->smoothAmount == another.smoothAmount &&
			this->smoothType == another.smoothType &&
			this->smoothSaltEnabled == another.smoothSaltEnabled &&
			this->smoothSaltMultiplier == another.smoothSaltMultiplier &&
			this->errorMarginEnabled == another.errorMarginEnabled &&
			this->errorMarginValue == another.errorMarginValue &&
			this->autoAimEnabled == another.autoAimEnabled &&
			this->autoAimFov == another.autoAimFov &&
			this->aimStepEnabled == another.aimStepEnabled &&
			this->aimStepMin == another.aimStepMin &&
			this->aimStepMax == another.aimStepMax &&
			this->rcsEnabled == another.rcsEnabled &&
			this->rcsAlwaysOn == another.rcsAlwaysOn &&
			this->rcsAmountX == another.rcsAmountX &&
			this->rcsAmountY == another.rcsAmountY &&
			this->autoPistolEnabled == another.autoPistolEnabled &&
			this->autoShootEnabled == another.autoShootEnabled &&
			this->autoScopeEnabled == another.autoScopeEnabled &&
			this->noShootEnabled == another.noShootEnabled &&
			this->ignoreJumpEnabled == another.ignoreJumpEnabled &&
			this->smokeCheck == another.smokeCheck &&
			this->flashCheck == another.flashCheck &&
			this->spreadLimitEnabled == another.spreadLimitEnabled &&
			this->spreadLimit == another.spreadLimit &&
			this->autoWallEnabled == another.autoWallEnabled &&
			this->autoWallValue == another.autoWallValue &&
			this->autoSlow == another.autoSlow &&
			this->predEnabled == another.predEnabled &&
			this->autoAimRealDistance == another.autoAimRealDistance &&
			this->moveMouse == another.moveMouse;
	}
};

class ColorVar
{
public:
	ImColor color;
	bool rainbow;
	float rainbowSpeed;

	ColorVar() {}

	ColorVar(ImColor color)
	{
		this->color = color;
		this->rainbow = false;
		this->rainbowSpeed = 0.5f;
	}

	ImColor Color()
	{
		ImColor result = this->rainbow ? Util::GetRainbowColor(this->rainbowSpeed) : this->color;
		result.Value.w = this->color.Value.w;
		return result;
	}
};

class HealthColorVar : public ColorVar
{
public:
	bool hp;

	HealthColorVar(ImColor color)
	{
		this->color = color;
		this->rainbow = false;
		this->rainbowSpeed = 0.5f;
		this->hp = false;
	}

	ImColor Color(C_BasePlayer* player)
	{
		ImColor result = this->rainbow ? Util::GetRainbowColor(this->rainbowSpeed) : (this->hp ? Color::ToImColor(Util::GetHealthColor(player)) : this->color);
		result.Value.w = this->color.Value.w;
		return result;
	}
};

namespace Settings
{
	namespace UI
	{
		extern ColorVar mainColor;
		extern ColorVar bodyColor;
		extern ColorVar fontColor;
		extern ColorVar accentColor;

		namespace Windows
		{
			namespace Colors
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Config
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Main
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Playerlist
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Skinmodel
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Spectators
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool reload; // True on config load, used to change Window Position.
			}
			namespace Walkbot
			{
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
		}
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
		extern bool moveMouse;

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
			extern bool closestBone;
			extern bool desiredBones[];
			extern bool engageLock;
			extern bool engageLockTR;
			extern int engageLockTTR;
		}

		namespace AutoWall
		{
			extern bool enabled;
			extern float value;
		}

		namespace AimStep
		{
			extern bool enabled;
			extern float min;
			extern float max;
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
			extern bool velocityCheck;
			extern bool autoscope;
		}

		namespace AutoCrouch
		{
			extern bool enabled;
		}

		namespace AutoSlow
		{
			extern bool enabled;
			extern bool goingToSlow;
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

		namespace SpreadLimit
		{
			extern bool enabled;
			extern float value;
		}

		namespace Prediction
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

		namespace RandomDelay
		{
			extern bool enabled;
			extern int lowBound; // in ms
			extern int highBound;// in ms
			extern int lastRoll;
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
			extern bool antiResolver;
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

		namespace Lua
		{
			extern bool debugMode; // turns on/off error checking. Can be turned off after your script is working for speed.
			extern char scriptX[512];
			extern char scriptY[512];
			extern char scriptY2[512];
		}
	}

	namespace Resolver
	{
		extern bool resolveAll;
	}

	namespace ESP
	{
		extern bool enabled;
		extern ButtonCode_t key;
		extern TeamColorType teamColorType;
		extern HealthColorVar enemyColor;
		extern HealthColorVar allyColor;
		extern HealthColorVar enemyVisibleColor;
		extern HealthColorVar allyVisibleColor;
		extern HealthColorVar ctColor;
		extern HealthColorVar tColor;
		extern HealthColorVar ctVisibleColor;
		extern HealthColorVar tVisibleColor;
		extern ColorVar bombColor;
		extern ColorVar bombDefusingColor;
		extern ColorVar hostageColor;
		extern ColorVar defuserColor;
		extern ColorVar weaponColor;
		extern ColorVar chickenColor;
		extern ColorVar fishColor;
		extern ColorVar smokeColor;
		extern ColorVar decoyColor;
		extern ColorVar flashbangColor;
		extern ColorVar grenadeColor;
		extern ColorVar molotovColor;
		extern HealthColorVar localplayerColor;

		namespace AutoWall
		{
			extern bool debugView;
		}
		namespace Glow
		{
			extern bool enabled;
			extern HealthColorVar allyColor;
			extern HealthColorVar enemyColor;
			extern HealthColorVar enemyVisibleColor;
			extern ColorVar weaponColor;
			extern ColorVar grenadeColor;
			extern ColorVar defuserColor;
			extern ColorVar chickenColor;
			extern HealthColorVar localplayerColor;
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
			extern ColorVar color;
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
			extern bool filled;
			extern ColorVar color;
		}

		namespace Chams
		{
			extern bool enabled;
			extern HealthColorVar allyColor;
			extern HealthColorVar allyVisibleColor;
			extern HealthColorVar enemyColor;
			extern HealthColorVar enemyVisibleColor;
			extern HealthColorVar localplayerColor;
			extern ChamsType type;

			namespace Arms
			{
				extern bool enabled;
				extern ColorVar color;
				extern ArmsType type;
			}

			namespace Weapon
			{
				extern bool enabled;
				extern ColorVar color;
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
			extern ColorVar color;
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

		namespace Spread
		{
			extern bool enabled; // show current spread
			extern bool spreadLimit; // show spreadLimit value
			extern ColorVar color;
			extern ColorVar spreadLimitColor;
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
			extern bool enabled;
			extern bool sayTeam;
			extern std::vector<std::string> messages;
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

		namespace Chance
		{
			extern bool enabled;
			extern int value;
		}

		namespace Hops
		{
			extern bool enabledMax;
			extern int Max;
			extern bool enabledMin;
			extern int Min;
		}
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
		extern TeamColorType teamColorType;
		extern HealthColorVar enemyColor;
		extern HealthColorVar enemyVisibleColor;
		extern HealthColorVar allyColor;
		extern HealthColorVar allyVisibleColor;
		extern HealthColorVar tColor;
		extern HealthColorVar tVisibleColor;
		extern HealthColorVar ctColor;
		extern HealthColorVar ctVisibleColor;
		extern ColorVar bombColor;
		extern ColorVar bombDefusingColor;
		extern ColorVar defuserColor;
		extern float iconsScale;

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
		namespace Skins
		{
			extern bool enabled;
			extern bool perTeam;
		}

		namespace Models
		{
			extern bool enabled;
		}

		extern std::unordered_map<ItemDefinitionIndex, AttribItem_t, Util::IntHash<ItemDefinitionIndex>> skinsCT;
		extern std::unordered_map<ItemDefinitionIndex, AttribItem_t, Util::IntHash<ItemDefinitionIndex>> skinsT;
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

	namespace FakeLag
	{
		extern bool enabled;
		extern int value;
		extern bool adaptive;
	}

	namespace AutoAccept
	{
		extern bool enabled;
	}

	namespace NoSky
	{
		extern bool enabled;
		extern ColorVar color;
	}

	namespace SkyBox
	{
		extern bool enabled;
		extern int skyBoxNumber; // number in skyBoxNames
	}

	namespace ASUSWalls
	{
		extern bool enabled;
		extern ColorVar color;
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
		extern bool silent;
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

	namespace DisablePostProcessing
	{
		extern bool enabled;
	}

	namespace GrenadeHelper
	{
		extern std::vector<GrenadeInfo> grenadeInfos;
		extern bool enabled;
		extern bool onlyMatchingInfos;
		extern bool aimAssist;
		extern float aimStep;
		extern float aimDistance;
		extern float aimFov;
		extern ColorVar aimDot;
		extern ColorVar aimLine;
		extern ColorVar infoHE;
		extern ColorVar infoSmoke;
		extern ColorVar infoFlash;
		extern ColorVar infoMolotov;
		extern pstring actMapName;
	}

	namespace WalkBot
	{
		extern bool enabled;
		extern bool forceReset;
		extern bool autobuy;
		extern int autobuyAt;
	}

	namespace AutoKnife
 	{
 		extern bool enabled;
 		extern bool onKey;
 
 		namespace Filters
 		{
 			extern bool enemies;
 			extern bool allies;
 		}
 	}

	void LoadDefaultsOrSave(std::string path);
	void LoadConfig(std::string path);
	void LoadSettings();
	void DeleteConfig(std::string path);
	void SaveGrenadeInfo(std::string path);
	void LoadGrenadeInfo(std::string path);
}
