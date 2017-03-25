#include "settings.h"

void GetVal(Json::Value &config, int* setting)
{
	if (config.isNull())
		return;

	*setting = config.asInt();
}

void GetVal(Json::Value &config, bool* setting)
{
	if (config.isNull())
		return;

	*setting = config.asBool();
}

void GetVal(Json::Value &config, float* setting)
{
	if (config.isNull())
		return;

	*setting = config.asFloat();
}

void GetVal(Json::Value &config, ImColor* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->Value.x);
	GetVal(config["g"], &setting->Value.y);
	GetVal(config["b"], &setting->Value.z);
	GetVal(config["a"], &setting->Value.w);
}

void GetVal(Json::Value &config, char** setting)
{
	if (config.isNull())
		return;

	*setting = strdup(config.asCString());
}

void GetVal(Json::Value &config, char* setting)
{
	if (config.isNull())
		return;

	strcpy(setting, config.asCString());
}

void GetVal(Json::Value &config, ColorVar* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->color.Value.x);
	GetVal(config["g"], &setting->color.Value.y);
	GetVal(config["b"], &setting->color.Value.z);
	GetVal(config["a"], &setting->color.Value.w);
	GetVal(config["rainbow"], &setting->rainbow);
	GetVal(config["rainbowSpeed"], &setting->rainbowSpeed);
}

void GetVal(Json::Value &config, HealthColorVar* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->color.Value.x);
	GetVal(config["g"], &setting->color.Value.y);
	GetVal(config["b"], &setting->color.Value.z);
	GetVal(config["a"], &setting->color.Value.w);
	GetVal(config["rainbow"], &setting->rainbow);
	GetVal(config["rainbowSpeed"], &setting->rainbowSpeed);
	GetVal(config["hp"], &setting->hp);
}

template <typename Ord, Ord (*lookupFunction)(std::string)>
void GetOrdinal(Json::Value& config, Ord* setting)
{
	if (config.isNull())
		return;

	Ord value;
	if (config.isString())
		value = lookupFunction(config.asString());
	else
		value = (Ord) config.asInt();

	*setting = value;
}

void GetButtonCode(Json::Value &config, enum ButtonCode_t* setting)
{
	GetOrdinal<enum ButtonCode_t, Util::GetButtonCode>(config, setting);
}

void LoadColor(Json::Value &config, ImColor color)
{
	config["r"] = color.Value.x;
	config["g"] = color.Value.y;
	config["b"] = color.Value.z;
	config["a"] = color.Value.w;
}

void LoadColor(Json::Value &config, ColorVar color)
{
	config["r"] = color.color.Value.x;
	config["g"] = color.color.Value.y;
	config["b"] = color.color.Value.z;
	config["a"] = color.color.Value.w;
	config["rainbow"] = color.rainbow;
	config["rainbowSpeed"] = color.rainbowSpeed;
}

void LoadColor(Json::Value &config, HealthColorVar color)
{
	config["r"] = color.color.Value.x;
	config["g"] = color.color.Value.y;
	config["b"] = color.color.Value.z;
	config["a"] = color.color.Value.w;
	config["rainbow"] = color.rainbow;
	config["rainbowSpeed"] = color.rainbowSpeed;
	config["hp"] = color.hp;
}

void Settings::LoadDefaultsOrSave(std::string path)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	LoadColor(settings["UI"]["mainColor"], Settings::UI::mainColor);
	LoadColor(settings["UI"]["bodyColor"], Settings::UI::bodyColor);
	LoadColor(settings["UI"]["fontColor"], Settings::UI::fontColor);
	settings["UI"]["Fonts"]["ESP"]["family"] = Settings::UI::Fonts::ESP::family;
	settings["UI"]["Fonts"]["ESP"]["size"] = Settings::UI::Fonts::ESP::size;
	settings["UI"]["Fonts"]["ESP"]["flags"] = Settings::UI::Fonts::ESP::flags;

	for (auto i : Settings::Aimbot::weapons)
	{
		// TODO this is kind of a hack and i'm too tired to find a better way to do this
		// yes i tried defining a variable, skinSetting, and giving it the same value but woooooo operator overloading
		// in C++ and weird shit
		#define weaponSetting settings["Aimbot"]["weapons"][Util::Items::GetItemName((enum ItemDefinitionIndex) i.first)]
		weaponSetting["Enabled"] = i.second.enabled;
		weaponSetting["Silent"] = i.second.silent;
		weaponSetting["Friendly"] = i.second.friendly;
		weaponSetting["TargetBone"] = (int) i.second.bone;
		weaponSetting["AimKey"] = Util::GetButtonName(i.second.aimkey);
		weaponSetting["AimKeyOnly"] = i.second.aimkeyOnly;
		weaponSetting["Smooth"]["Enabled"] = i.second.smoothEnabled;
		weaponSetting["Smooth"]["Amount"] = i.second.smoothAmount;
		weaponSetting["Smooth"]["Type"] = (int) i.second.smoothType;
		weaponSetting["Smooth"]["Salting"]["Enabled"] = i.second.smoothSaltEnabled;
		weaponSetting["Smooth"]["Salting"]["Multiplier"] = i.second.smoothSaltMultiplier;
		weaponSetting["ErrorMargin"]["Enabled"] = i.second.errorMarginEnabled;
		weaponSetting["ErrorMargin"]["Value"] = i.second.errorMarginValue;
		weaponSetting["AutoAim"]["Enabled"] = i.second.autoAimEnabled;
		weaponSetting["AutoAim"]["FOV"] = i.second.autoAimFov;
		weaponSetting["AimStep"]["Enabled"] = i.second.aimStepEnabled;
		weaponSetting["AimStep"]["Amount"] = i.second.aimStepValue;
		weaponSetting["RCS"]["Enabled"] = i.second.rcsEnabled;
		weaponSetting["RCS"]["AlwaysOn"] = i.second.rcsAlwaysOn;
		weaponSetting["RCS"]["AmountX"] = i.second.rcsAmountX;
		weaponSetting["RCS"]["AmountY"] = i.second.rcsAmountY;
		weaponSetting["AutoPistol"]["Enabled"] = i.second.autoPistolEnabled;
		weaponSetting["AutoShoot"]["Enabled"] = i.second.autoShootEnabled;
		weaponSetting["AutoScope"]["Enabled"] = i.second.autoScopeEnabled;
		weaponSetting["NoShoot"]["Enabled"] = i.second.noShootEnabled;
		weaponSetting["IgnoreJump"]["Enabled"] = i.second.ignoreJumpEnabled;
		weaponSetting["SmokeCheck"]["Enabled"] = i.second.smokeCheck;
		weaponSetting["FlashCheck"]["Enabled"] = i.second.flashCheck;
		weaponSetting["AutoWall"]["Enabled"] = i.second.autoWallEnabled;
		weaponSetting["AutoWall"]["Value"] = i.second.autoWallValue;
		weaponSetting["AutoSlow"]["enabled"] = i.second.autoSlow;
		weaponSetting["Prediction"]["enabled"] = i.second.predEnabled;
		weaponSetting["AutoSlow"]["minDamage"] = i.second.autoSlowMinDamage;

		for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
			weaponSetting["AutoWall"]["Bones"][bone] = i.second.autoWallBones[bone];

		weaponSetting["AutoAim"]["RealDistance"] = i.second.autoAimRealDistance;

		#undef weaponSetting
	}

	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;

	settings["Resolver"]["resolve_all"] = Settings::Resolver::resolveAll;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Util::GetButtonName(Settings::Triggerbot::key);
	settings["Triggerbot"]["Filters"]["enemies"] = Settings::Triggerbot::Filters::enemies;
	settings["Triggerbot"]["Filters"]["allies"] = Settings::Triggerbot::Filters::allies;
	settings["Triggerbot"]["Filters"]["walls"] = Settings::Triggerbot::Filters::walls;
	settings["Triggerbot"]["Filters"]["smoke_check"] = Settings::Triggerbot::Filters::smokeCheck;
	settings["Triggerbot"]["Filters"]["flash_check"] = Settings::Triggerbot::Filters::flashCheck;
	settings["Triggerbot"]["Filters"]["head"] = Settings::Triggerbot::Filters::head;
	settings["Triggerbot"]["Filters"]["chest"] = Settings::Triggerbot::Filters::chest;
	settings["Triggerbot"]["Filters"]["stomach"] = Settings::Triggerbot::Filters::stomach;
	settings["Triggerbot"]["Filters"]["arms"] = Settings::Triggerbot::Filters::arms;
	settings["Triggerbot"]["Filters"]["legs"] = Settings::Triggerbot::Filters::legs;
	settings["Triggerbot"]["Delay"]["enabled"] = Settings::Triggerbot::Delay::enabled;
	settings["Triggerbot"]["Delay"]["value"] = Settings::Triggerbot::Delay::value;

	settings["AntiAim"]["Yaw"]["enabled"] = Settings::AntiAim::Yaw::enabled;
	settings["AntiAim"]["Yaw"]["type"] = (int) Settings::AntiAim::Yaw::type;
	settings["AntiAim"]["Yaw"]["type_fake"] = (int) Settings::AntiAim::Yaw::typeFake;
	settings["AntiAim"]["Yaw"]["antiResolver"] = Settings::AntiAim::Yaw::antiResolver;
	settings["AntiAim"]["Pitch"]["enabled"] = Settings::AntiAim::Pitch::enabled;
	settings["AntiAim"]["Pitch"]["type"] = (int) Settings::AntiAim::Pitch::type;
	settings["AntiAim"]["HeadEdge"]["enabled"] = Settings::AntiAim::HeadEdge::enabled;
	settings["AntiAim"]["HeadEdge"]["distance"] = Settings::AntiAim::HeadEdge::distance;
	settings["AntiAim"]["AutoDisable"]["no_enemy"] = Settings::AntiAim::AutoDisable::noEnemy;
	settings["AntiAim"]["AutoDisable"]["knife_held"] = Settings::AntiAim::AutoDisable::knifeHeld;

	settings["ESP"]["enabled"] = Settings::ESP::enabled;
	LoadColor(settings["ESP"]["enemy_color"], Settings::ESP::enemyColor);
	LoadColor(settings["ESP"]["enemy_visible_color"], Settings::ESP::enemyVisibleColor);
	LoadColor(settings["ESP"]["ally_color"], Settings::ESP::allyColor);
	LoadColor(settings["ESP"]["ally_visible_color"], Settings::ESP::allyVisibleColor);
	LoadColor(settings["ESP"]["t_color"], Settings::ESP::tColor);
	LoadColor(settings["ESP"]["t_visible_color"], Settings::ESP::tVisibleColor);
	LoadColor(settings["ESP"]["ct_color"], Settings::ESP::ctColor);
	LoadColor(settings["ESP"]["ct_visible_color"], Settings::ESP::ctVisibleColor);
	LoadColor(settings["ESP"]["localplayer_color"], Settings::ESP::localplayerColor);
	LoadColor(settings["ESP"]["bomb_color"], Settings::ESP::bombColor);
	LoadColor(settings["ESP"]["bomb_defusing_color"], Settings::ESP::bombDefusingColor);
	LoadColor(settings["ESP"]["hostage_color"], Settings::ESP::hostageColor);
	LoadColor(settings["ESP"]["defuser_color"], Settings::ESP::defuserColor);
	LoadColor(settings["ESP"]["weapon_color"], Settings::ESP::weaponColor);
	LoadColor(settings["ESP"]["chicken_color"], Settings::ESP::chickenColor);
	LoadColor(settings["ESP"]["fish_color"], Settings::ESP::fishColor);
	LoadColor(settings["ESP"]["smoke_color"], Settings::ESP::smokeColor);
	LoadColor(settings["ESP"]["decoy_color"], Settings::ESP::decoyColor);
	LoadColor(settings["ESP"]["flashbang_color"], Settings::ESP::flashbangColor);
	LoadColor(settings["ESP"]["grenade_color"], Settings::ESP::grenadeColor);
	LoadColor(settings["ESP"]["molotov_color"], Settings::ESP::molotovColor);
	settings["ESP"]["Glow"]["enabled"] = Settings::ESP::Glow::enabled;
	LoadColor(settings["ESP"]["Glow"]["ally_color"], Settings::ESP::Glow::allyColor);
	LoadColor(settings["ESP"]["Glow"]["enemy_color"], Settings::ESP::Glow::enemyColor);
	LoadColor(settings["ESP"]["Glow"]["enemy_visible_color"], Settings::ESP::Glow::enemyVisibleColor);
	LoadColor(settings["ESP"]["Glow"]["localplayer_color"], Settings::ESP::Glow::localplayerColor);
	LoadColor(settings["ESP"]["Glow"]["weapon_color"], Settings::ESP::Glow::weaponColor);
	LoadColor(settings["ESP"]["Glow"]["grenade_color"], Settings::ESP::Glow::grenadeColor);
	LoadColor(settings["ESP"]["Glow"]["defuser_color"], Settings::ESP::Glow::defuserColor);
	LoadColor(settings["ESP"]["Glow"]["chicken_color"], Settings::ESP::Glow::chickenColor);
	settings["ESP"]["Filters"]["legit"] = Settings::ESP::Filters::legit;
	settings["ESP"]["Filters"]["visibility_check"] = Settings::ESP::Filters::visibilityCheck;
	settings["ESP"]["Filters"]["smoke_check"] = Settings::ESP::Filters::smokeCheck;
	settings["ESP"]["Filters"]["enemies"] = Settings::ESP::Filters::enemies;
	settings["ESP"]["Filters"]["allies"] = Settings::ESP::Filters::allies;
	settings["ESP"]["Filters"]["bomb"] = Settings::ESP::Filters::bomb;
	settings["ESP"]["Filters"]["hostages"] = Settings::ESP::Filters::hostages;
	settings["ESP"]["Filters"]["defusers"] = Settings::ESP::Filters::defusers;
	settings["ESP"]["Filters"]["weapons"] = Settings::ESP::Filters::weapons;
	settings["ESP"]["Filters"]["chickens"] = Settings::ESP::Filters::chickens;
	settings["ESP"]["Filters"]["fishes"] = Settings::ESP::Filters::fishes;
	settings["ESP"]["Filters"]["throwables"] = Settings::ESP::Filters::throwables;
	settings["ESP"]["Filters"]["localplayer"] = Settings::ESP::Filters::localplayer;
	settings["ESP"]["Info"]["name"] = Settings::ESP::Info::name;
	settings["ESP"]["Info"]["clan"] = Settings::ESP::Info::clan;
	settings["ESP"]["Info"]["steam_id"] = Settings::ESP::Info::steamId;
	settings["ESP"]["Info"]["rank"] = Settings::ESP::Info::rank;
	settings["ESP"]["Info"]["health"] = Settings::ESP::Info::health;
	settings["ESP"]["Info"]["weapon"] = Settings::ESP::Info::weapon;
	settings["ESP"]["Info"]["scoped"] = Settings::ESP::Info::scoped;
	settings["ESP"]["Info"]["reloading"] = Settings::ESP::Info::reloading;
	settings["ESP"]["Info"]["flashed"] = Settings::ESP::Info::flashed;
	settings["ESP"]["Info"]["planting"] = Settings::ESP::Info::planting;
	settings["ESP"]["Info"]["has_defuser"] = Settings::ESP::Info::hasDefuser;
	settings["ESP"]["Info"]["defusing"] = Settings::ESP::Info::defusing;
	settings["ESP"]["Info"]["grabbing_hostage"] = Settings::ESP::Info::grabbingHostage;
	settings["ESP"]["Info"]["rescuing"] = Settings::ESP::Info::rescuing;
	settings["ESP"]["Info"]["location"] = Settings::ESP::Info::location;
	settings["ESP"]["Boxes"]["enabled"] = Settings::ESP::Boxes::enabled;
	settings["ESP"]["Boxes"]["type"] = (int) Settings::ESP::Boxes::type;
	settings["ESP"]["Skeleton"]["enabled"] = Settings::ESP::Skeleton::enabled;
	LoadColor(settings["ESP"]["Skeleton"]["color"], Settings::ESP::Skeleton::color);
	settings["ESP"]["Bars"]["enabled"] = Settings::ESP::Bars::enabled;
	settings["ESP"]["Bars"]["color_type"] = (int) Settings::ESP::Bars::colorType;
	settings["ESP"]["Bars"]["type"] = (int) Settings::ESP::Bars::type;
	settings["ESP"]["Tracers"]["enabled"] = Settings::ESP::Tracers::enabled;
	settings["ESP"]["Tracers"]["type"] = (int) Settings::ESP::Tracers::type;
	settings["ESP"]["BulletTracers"]["enabled"] = Settings::ESP::BulletTracers::enabled;
	settings["ESP"]["FOVCrosshair"]["enabled"] = Settings::ESP::FOVCrosshair::enabled;
	settings["ESP"]["FOVCrosshair"]["filled"] = Settings::ESP::FOVCrosshair::filled;
	LoadColor(settings["ESP"]["FOVCrosshair"]["color"], Settings::ESP::FOVCrosshair::color);
	settings["ESP"]["Chams"]["Arms"]["enabled"] = Settings::ESP::Chams::Arms::enabled;
	settings["ESP"]["Chams"]["Arms"]["type"] = (int) Settings::ESP::Chams::Arms::type;
	settings["ESP"]["Chams"]["Weapon"]["enabled"] = Settings::ESP::Chams::Weapon::enabled;
	LoadColor(settings["ESP"]["Chams"]["Weapon"]["color"], Settings::ESP::Chams::Weapon::color);
	LoadColor(settings["ESP"]["Chams"]["Arms"]["color"], Settings::ESP::Chams::Arms::color);
	LoadColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::allyColor);
	LoadColor(settings["ESP"]["Chams"]["players_ally_visible_color"], Settings::ESP::Chams::allyVisibleColor);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::enemyColor);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::enemyVisibleColor);
	LoadColor(settings["ESP"]["Chams"]["localplayer_color"], Settings::ESP::Chams::localplayerColor);
	settings["ESP"]["Chams"]["type"] = (int) Settings::ESP::Chams::type;
	settings["ESP"]["Chams"]["enabled"] = Settings::ESP::Chams::enabled;
	settings["ESP"]["Sounds"]["enabled"] = Settings::ESP::Sounds::enabled;
	settings["ESP"]["Sounds"]["time"] = Settings::ESP::Sounds::time;
	settings["ESP"]["Hitmarker"]["enabled"] = Settings::ESP::Hitmarker::enabled;
	settings["ESP"]["Hitmarker"]["enemies"] = Settings::ESP::Hitmarker::enemies;
	settings["ESP"]["Hitmarker"]["allies"] = Settings::ESP::Hitmarker::allies;
	LoadColor(settings["ESP"]["Hitmarker"]["color"], Settings::ESP::Hitmarker::color);
	settings["ESP"]["Hitmarker"]["duration"] = Settings::ESP::Hitmarker::duration;
	settings["ESP"]["Hitmarker"]["size"] = Settings::ESP::Hitmarker::size;
	settings["ESP"]["Hitmarker"]["inner_gap"] = Settings::ESP::Hitmarker::innerGap;
	settings["ESP"]["Hitmarker"]["Damage"]["enabled"] = Settings::ESP::Hitmarker::Damage::enabled;
	settings["ESP"]["HeadDot"]["enabled"] = Settings::ESP::HeadDot::enabled;
	settings["ESP"]["HeadDot"]["size"] = Settings::ESP::HeadDot::size;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;

	settings["Spammer"]["spammer_type"] = (int) Settings::Spammer::type;
	settings["Spammer"]["say_team"] = Settings::Spammer::say_team;

	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["say_team"] = Settings::Spammer::KillSpammer::sayTeam;
	Json::Value killSpammerMessages;
	for (auto it : Settings::Spammer::KillSpammer::messages)
		killSpammerMessages.append(it);
	settings["Spammer"]["KillSpammer"]["messages"] = killSpammerMessages;

	Json::Value normalSpammerMessages;
	for (auto it : Settings::Spammer::NormalSpammer::messages)
		normalSpammerMessages.append(it);
	settings["Spammer"]["NormalSpammer"]["messages"] = normalSpammerMessages;

	settings["Spammer"]["PositionSpammer"]["show_name"] = Settings::Spammer::PositionSpammer::showName;
	settings["Spammer"]["PositionSpammer"]["show_weapon"] = Settings::Spammer::PositionSpammer::showWeapon;
	settings["Spammer"]["PositionSpammer"]["show_rank"] = Settings::Spammer::PositionSpammer::showRank;
	settings["Spammer"]["PositionSpammer"]["show_wins"] = Settings::Spammer::PositionSpammer::showWins;
	settings["Spammer"]["PositionSpammer"]["show_health"] = Settings::Spammer::PositionSpammer::showHealth;
	settings["Spammer"]["PositionSpammer"]["show_money"] = Settings::Spammer::PositionSpammer::showMoney;
	settings["Spammer"]["PositionSpammer"]["show_lastplace"] = Settings::Spammer::PositionSpammer::showLastplace;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;
	settings["AutoStrafe"]["type"] = (int) Settings::AutoStrafe::type;
	settings["AutoStrafe"]["silent"] = Settings::AutoStrafe::silent;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Radar"]["enabled"] = Settings::Radar::enabled;
	settings["Radar"]["zoom"] = Settings::Radar::zoom;
	settings["Radar"]["enemies"] = Settings::Radar::enemies;
	settings["Radar"]["allies"] = Settings::Radar::allies;
	settings["Radar"]["legit"] = Settings::Radar::legit;
	settings["Radar"]["visibility_check"] = Settings::Radar::visibilityCheck;
	settings["Radar"]["smoke_check"] = Settings::Radar::smokeCheck;
	settings["Radar"]["InGame"]["enabled"] = Settings::Radar::InGame::enabled;
	LoadColor(settings["Radar"]["enemy_color"], Settings::Radar::enemyColor);
	LoadColor(settings["Radar"]["enemy_visible_color"], Settings::Radar::enemyVisibleColor);
	LoadColor(settings["Radar"]["ally_color"], Settings::Radar::allyColor);
	LoadColor(settings["Radar"]["ally_visible_color"], Settings::Radar::allyVisibleColor);
	LoadColor(settings["Radar"]["t_color"], Settings::Radar::tColor);
	LoadColor(settings["Radar"]["t_visible_color"], Settings::Radar::tVisibleColor);
	LoadColor(settings["Radar"]["ct_color"], Settings::Radar::ctColor);
	LoadColor(settings["Radar"]["ct_visible_color"], Settings::Radar::ctVisibleColor);
	LoadColor(settings["Radar"]["bomb_color"], Settings::Radar::bombColor);
	LoadColor(settings["Radar"]["bomb_defusing_color"], Settings::Radar::bombDefusingColor);
	settings["Radar"]["icons_scale"] = Settings::Radar::iconsScale;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

	settings["Recoilcrosshair"]["showOnlyWhenShooting"] = Settings::Recoilcrosshair::showOnlyWhenShooting;

	settings["FOVChanger"]["enabled"] = Settings::FOVChanger::enabled;
	settings["FOVChanger"]["value"] = Settings::FOVChanger::value;
	settings["FOVChanger"]["viewmodel_enabled"] = Settings::FOVChanger::viewmodelEnabled;
	settings["FOVChanger"]["viewmodel_value"] = Settings::FOVChanger::viewmodelValue;
	settings["FOVChanger"]["ignore_scope"] = Settings::FOVChanger::ignoreScope;

	settings["Airstuck"]["enabled"] = Settings::Airstuck::enabled;
	settings["Airstuck"]["key"] = Util::GetButtonName(Settings::Airstuck::key);

	settings["SkinChanger"]["Skins"]["enabled"] = Settings::Skinchanger::Skins::enabled;
	settings["SkinChanger"]["Models"]["enabled"] = Settings::Skinchanger::Models::enabled;
	settings["SkinChanger"]["Skins"]["perTeam"] = Settings::Skinchanger::Skins::perTeam;

	for (const auto& item: Settings::Skinchanger::skinsCT)
	{
		const AttribItem_t& skin = item.second;

		#define skinSetting settings["SkinChanger"]["skinsCT"][Util::Items::GetItemConfigEntityName(item.first)]
		skinSetting["ItemDefinitionIndex"] = Util::Items::GetItemConfigEntityName(skin.itemDefinitionIndex);
		skinSetting["PaintKit"] = skin.fallbackPaintKit;
		skinSetting["Wear"] = skin.fallbackWear;
		skinSetting["Seed"] = skin.fallbackSeed;
		skinSetting["StatTrak"] = skin.fallbackStatTrak;
		skinSetting["CustomName"] = skin.customName;
		#undef skinSetting
	}

	for (const auto& item: Settings::Skinchanger::skinsT)
	{
		const AttribItem_t& skin = item.second;

		#define skinSetting settings["SkinChanger"]["skinsT"][Util::Items::GetItemConfigEntityName(item.first)]
		skinSetting["ItemDefinitionIndex"] = Util::Items::GetItemConfigEntityName(skin.itemDefinitionIndex);
		skinSetting["PaintKit"] = skin.fallbackPaintKit;
		skinSetting["Wear"] = skin.fallbackWear;
		skinSetting["Seed"] = skin.fallbackSeed;
		skinSetting["StatTrak"] = skin.fallbackStatTrak;
		skinSetting["CustomName"] = skin.customName;
		#undef skinSetting
	}

	settings["ShowRanks"]["enabled"] = Settings::ShowRanks::enabled;

	settings["ShowSpectators"]["enabled"] = Settings::ShowSpectators::enabled;

	settings["ClanTagChanger"]["value"] = Settings::ClanTagChanger::value;
	settings["ClanTagChanger"]["enabled"] = Settings::ClanTagChanger::enabled;
	settings["ClanTagChanger"]["animation"] = Settings::ClanTagChanger::animation;
	settings["ClanTagChanger"]["animation_speed"] = Settings::ClanTagChanger::animationSpeed;
	settings["ClanTagChanger"]["type"] = (int) Settings::ClanTagChanger::type;

	settings["View"]["NoViewPunch"]["enabled"] = Settings::View::NoViewPunch::enabled;
	settings["View"]["NoAimPunch"]["enabled"] = Settings::View::NoAimPunch::enabled;

	settings["Teleport"]["enabled"] = Settings::Teleport::enabled;
	settings["Teleport"]["key"] = Settings::Teleport::key;

	settings["FakeLag"]["enabled"] = Settings::FakeLag::enabled;
	settings["FakeLag"]["value"] = Settings::FakeLag::value;
	settings["FakeLag"]["adaptive"] = Settings::FakeLag::adaptive;

	settings["AutoAccept"]["enabled"] = Settings::AutoAccept::enabled;

	settings["NoSky"]["enabled"] = Settings::NoSky::enabled;
	LoadColor(settings["NoSky"]["color"], Settings::NoSky::color);

	settings["ASUSWalls"]["enabled"] = Settings::ASUSWalls::enabled;
	LoadColor(settings["ASUSWalls"]["color"], Settings::ASUSWalls::color);

	settings["NoScopeBorder"]["enabled"] = Settings::NoScopeBorder::enabled;

	settings["SniperCrosshair"]["enabled"] = Settings::SniperCrosshair::enabled;

	settings["Autoblock"]["enabled"] = Settings::Autoblock::enabled;
	settings["Autoblock"]["key"] = Settings::Autoblock::key;

	settings["AutoDefuse"]["enabled"] = Settings::AutoDefuse::enabled;

	settings["NoSmoke"]["enabled"] = Settings::NoSmoke::enabled;

	settings["ScreenshotCleaner"]["enabled"] = Settings::ScreenshotCleaner::enabled;

	settings["EdgeJump"]["enabled"] = Settings::EdgeJump::enabled;
	settings["EdgeJump"]["key"] = Util::GetButtonName(Settings::EdgeJump::key);

	settings["NameStealer"]["enabled"] = Settings::NameStealer::enabled;
	settings["NameStealer"]["team"] = Settings::NameStealer::team;

	settings["ThirdPerson"]["enabled"] = Settings::ThirdPerson::enabled;
	settings["ThirdPerson"]["distance"] = Settings::ThirdPerson::distance;

	settings["JumpThrow"]["enabled"] = Settings::JumpThrow::enabled;
	settings["JumpThrow"]["key"] = Util::GetButtonName(Settings::JumpThrow::key);

	settings["DisablePostProcessing"]["enabled"] = Settings::DisablePostProcessing::enabled;

	settings["GrenadeHelper"]["enabled"] = Settings::GrenadeHelper::enabled;
	settings["GrenadeHelper"]["aimAssist"] = Settings::GrenadeHelper::aimAssist;
	settings["GrenadeHelper"]["OnlyMatching"] = Settings::GrenadeHelper::onlyMatchingInfos;
	settings["GrenadeHelper"]["aimStep"] = Settings::GrenadeHelper::aimStep;
	settings["GrenadeHelper"]["aimDistance"] = Settings::GrenadeHelper::aimDistance;
	settings["GrenadeHelper"]["aimFov"] = Settings::GrenadeHelper::aimFov;
	LoadColor(settings["GrenadeHelper"]["aimDot"], Settings::GrenadeHelper::aimDot);
	LoadColor(settings["GrenadeHelper"]["aimLine"], Settings::GrenadeHelper::aimLine);
	LoadColor(settings["GrenadeHelper"]["infoHe"], Settings::GrenadeHelper::infoHE);
	LoadColor(settings["GrenadeHelper"]["infoSmoke"], Settings::GrenadeHelper::infoSmoke);
	LoadColor(settings["GrenadeHelper"]["infoMolotov"], Settings::GrenadeHelper::infoMolotov);
	LoadColor(settings["GrenadeHelper"]["infoFlash"], Settings::GrenadeHelper::infoFlash);

	std::ofstream(path) << styledWriter.write(settings);
}

void Settings::LoadConfig(std::string path)
{
	if (!std::ifstream(path).good())
	{
		Settings::LoadDefaultsOrSave(path);
		return;
	}

	Json::Value settings;
	std::ifstream configDoc(path, std::ifstream::binary);
	configDoc >> settings;

	GetVal(settings["UI"]["mainColor"], &Settings::UI::mainColor);
	GetVal(settings["UI"]["bodyColor"], &Settings::UI::bodyColor);
	GetVal(settings["UI"]["fontColor"], &Settings::UI::fontColor);
	GetVal(settings["UI"]["Fonts"]["ESP"]["family"], &Settings::UI::Fonts::ESP::family);
	GetVal(settings["UI"]["Fonts"]["ESP"]["size"], &Settings::UI::Fonts::ESP::size);
	GetVal(settings["UI"]["Fonts"]["ESP"]["flags"], &Settings::UI::Fonts::ESP::flags);

	Fonts::SetupFonts();

	Settings::Aimbot::weapons = {
			{ ItemDefinitionIndex::INVALID, { false, false, false, Bone::BONE_HEAD, ButtonCode_t::MOUSE_MIDDLE, false, false, 1.0f, SmoothType::SLOW_END, false, 0.0f, false, 0.0f, true, 180.0f, false, 25.0f, false, false, 2.0f, 2.0f, false, false, false, false, false, false, false, false, 10.0f, false, false, false, 5.0f } },
	};

	for (Json::ValueIterator itr = settings["Aimbot"]["weapons"].begin(); itr != settings["Aimbot"]["weapons"].end(); itr++)
	{
		std::string weaponDataKey = itr.key().asString();
		auto weaponSetting = settings["Aimbot"]["weapons"][weaponDataKey];

		// XXX Using exception handling to deal with this is stupid, but I don't care to find a better solution
		// XXX We can't use GetOrdinal() since the key type is a string...
		ItemDefinitionIndex weaponID;
		try
		{
			weaponID = (ItemDefinitionIndex) std::stoi(weaponDataKey);
		}
		catch (std::invalid_argument) // Not a number
		{
			weaponID = Util::Items::GetItemIndex(weaponDataKey);
		}

		if (Settings::Aimbot::weapons.find(weaponID) == Settings::Aimbot::weapons.end())
			Settings::Aimbot::weapons[weaponID] = AimbotWeapon_t();

		AimbotWeapon_t weapon = {
				weaponSetting["Enabled"].asBool(),
				weaponSetting["Silent"].asBool(),
				weaponSetting["Friendly"].asBool(),
				(Bone) weaponSetting["TargetBone"].asInt(),
				Util::GetButtonCode(weaponSetting["AimKey"].asCString()),
				weaponSetting["AimKeyOnly"].asBool(),
				weaponSetting["Smooth"]["Enabled"].asBool(),
				weaponSetting["Smooth"]["Amount"].asFloat(),
				(SmoothType) weaponSetting["Smooth"]["Type"].asInt(),
				weaponSetting["Smooth"]["Salting"]["Enabled"].asBool(),
				weaponSetting["Smooth"]["Salting"]["Multiplier"].asFloat(),
				weaponSetting["ErrorMargin"]["Enabled"].asBool(),
				weaponSetting["ErrorMargin"]["Value"].asFloat(),
				weaponSetting["AutoAim"]["Enabled"].asBool(),
				weaponSetting["AutoAim"]["FOV"].asFloat(),
				weaponSetting["AimStep"]["Enabled"].asBool(),
				weaponSetting["AimStep"]["Amount"].asFloat(),
				weaponSetting["RCS"]["Enabled"].asBool(),
				weaponSetting["RCS"]["AlwaysOn"].asBool(),
				weaponSetting["RCS"]["AmountX"].asFloat(),
				weaponSetting["RCS"]["AmountY"].asFloat(),
				weaponSetting["AutoPistol"]["Enabled"].asBool(),
				weaponSetting["AutoShoot"]["Enabled"].asBool(),
				weaponSetting["AutoScope"]["Enabled"].asBool(),
				weaponSetting["NoShoot"]["Enabled"].asBool(),
				weaponSetting["IgnoreJump"]["Enabled"].asBool(),
				weaponSetting["SmokeCheck"]["Enabled"].asBool(),
				weaponSetting["FlashCheck"]["Enabled"].asBool(),
				weaponSetting["AutoWall"]["Enabled"].asBool(),
				weaponSetting["AutoWall"]["Value"].asFloat(),
				weaponSetting["AutoAim"]["RealDistance"].asBool(),
				weaponSetting["AutoSlow"]["enabled"].asBool(),
				weaponSetting["AutoSlow"]["minDamage"].asFloat(),
				weaponSetting["Prediction"]["enabled"].asBool()
		};

		for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
			weapon.autoWallBones[bone] = weaponSetting["AutoWall"]["Bones"][bone].asBool();

		Settings::Aimbot::weapons.at(weaponID) = weapon;
	}

	GetVal(settings["Aimbot"]["AutoCrouch"]["enabled"], &Settings::Aimbot::AutoCrouch::enabled);

	GetVal(settings["Resolver"]["resolve_all"], &Settings::Resolver::resolveAll);

	GetVal(settings["Triggerbot"]["enabled"], &Settings::Triggerbot::enabled);
	GetButtonCode(settings["Triggerbot"]["key"], &Settings::Triggerbot::key);
	GetVal(settings["Triggerbot"]["Filters"]["enemies"], &Settings::Triggerbot::Filters::enemies);
	GetVal(settings["Triggerbot"]["Filters"]["allies"], &Settings::Triggerbot::Filters::allies);
	GetVal(settings["Triggerbot"]["Filters"]["walls"], &Settings::Triggerbot::Filters::walls);
	GetVal(settings["Triggerbot"]["Filters"]["smoke_check"], &Settings::Triggerbot::Filters::smokeCheck);
	GetVal(settings["Triggerbot"]["Filters"]["flash_check"], &Settings::Triggerbot::Filters::flashCheck);
	GetVal(settings["Triggerbot"]["Filters"]["head"], &Settings::Triggerbot::Filters::head);
	GetVal(settings["Triggerbot"]["Filters"]["chest"], &Settings::Triggerbot::Filters::chest);
	GetVal(settings["Triggerbot"]["Filters"]["stomach"], &Settings::Triggerbot::Filters::stomach);
	GetVal(settings["Triggerbot"]["Filters"]["arms"], &Settings::Triggerbot::Filters::arms);
	GetVal(settings["Triggerbot"]["Filters"]["legs"], &Settings::Triggerbot::Filters::legs);
	GetVal(settings["Triggerbot"]["Delay"]["enabled"], &Settings::Triggerbot::Delay::enabled);
	GetVal(settings["Triggerbot"]["Delay"]["value"], &Settings::Triggerbot::Delay::value);

	GetVal(settings["AntiAim"]["Yaw"]["enabled"], &Settings::AntiAim::Yaw::enabled);
	GetVal(settings["AntiAim"]["Yaw"]["type"], (int*)& Settings::AntiAim::Yaw::type);
	GetVal(settings["AntiAim"]["Yaw"]["type_fake"], (int*)& Settings::AntiAim::Yaw::typeFake);
	GetVal(settings["AntiAim"]["Yaw"]["antiResolver"], &Settings::AntiAim::Yaw::antiResolver);
	GetVal(settings["AntiAim"]["Pitch"]["enabled"], &Settings::AntiAim::Pitch::enabled);
	GetVal(settings["AntiAim"]["Pitch"]["type"], (int*)& Settings::AntiAim::Pitch::type);
	GetVal(settings["AntiAim"]["HeadEdge"]["enabled"], &Settings::AntiAim::HeadEdge::enabled);
	GetVal(settings["AntiAim"]["HeadEdge"]["distance"], &Settings::AntiAim::HeadEdge::distance);
	GetVal(settings["AntiAim"]["AutoDisable"]["knife_held"], &Settings::AntiAim::AutoDisable::knifeHeld);
	GetVal(settings["AntiAim"]["AutoDisable"]["no_enemy"], &Settings::AntiAim::AutoDisable::noEnemy);

	GetVal(settings["ESP"]["enabled"], &Settings::ESP::enabled);
	GetVal(settings["ESP"]["enemy_color"], &Settings::ESP::enemyColor);
	GetVal(settings["ESP"]["enemy_visible_color"], &Settings::ESP::enemyVisibleColor);
	GetVal(settings["ESP"]["ally_color"], &Settings::ESP::allyColor);
	GetVal(settings["ESP"]["ally_visible_color"], &Settings::ESP::allyVisibleColor);
	GetVal(settings["ESP"]["t_color"], &Settings::ESP::tColor);
	GetVal(settings["ESP"]["t_visible_color"], &Settings::ESP::tVisibleColor);
	GetVal(settings["ESP"]["ct_color"], &Settings::ESP::ctColor);
	GetVal(settings["ESP"]["ct_visible_color"], &Settings::ESP::ctVisibleColor);
	GetVal(settings["ESP"]["localplayer_color"], &Settings::ESP::localplayerColor);
	GetVal(settings["ESP"]["bomb_color"], &Settings::ESP::bombColor);
	GetVal(settings["ESP"]["bomb_defusing_color"], &Settings::ESP::bombDefusingColor);
	GetVal(settings["ESP"]["hostage_color"], &Settings::ESP::hostageColor);
	GetVal(settings["ESP"]["defuser_color"], &Settings::ESP::defuserColor);
	GetVal(settings["ESP"]["weapon_color"], &Settings::ESP::weaponColor);
	GetVal(settings["ESP"]["chicken_color"], &Settings::ESP::chickenColor);
	GetVal(settings["ESP"]["fish_color"], &Settings::ESP::fishColor);
	GetVal(settings["ESP"]["smoke_color"], &Settings::ESP::smokeColor);
	GetVal(settings["ESP"]["decoy_color"], &Settings::ESP::decoyColor);
	GetVal(settings["ESP"]["flashbang_color"], &Settings::ESP::flashbangColor);
	GetVal(settings["ESP"]["grenade_color"], &Settings::ESP::grenadeColor);
	GetVal(settings["ESP"]["molotov_color"], &Settings::ESP::molotovColor);
	GetVal(settings["ESP"]["Glow"]["enabled"], &Settings::ESP::Glow::enabled);
	GetVal(settings["ESP"]["Glow"]["ally_color"], &Settings::ESP::Glow::allyColor);
	GetVal(settings["ESP"]["Glow"]["enemy_color"], &Settings::ESP::Glow::enemyColor);
	GetVal(settings["ESP"]["Glow"]["enemy_visible_color"], &Settings::ESP::Glow::enemyVisibleColor);
	GetVal(settings["ESP"]["Glow"]["localplayer_color"], &Settings::ESP::Glow::localplayerColor);
	GetVal(settings["ESP"]["Glow"]["weapon_color"], &Settings::ESP::Glow::weaponColor);
	GetVal(settings["ESP"]["Glow"]["grenade_color"], &Settings::ESP::Glow::grenadeColor);
	GetVal(settings["ESP"]["Glow"]["defuser_color"], &Settings::ESP::Glow::defuserColor);
	GetVal(settings["ESP"]["Glow"]["chicken_color"], &Settings::ESP::Glow::chickenColor);
	GetVal(settings["ESP"]["Filters"]["legit"], &Settings::ESP::Filters::legit);
	GetVal(settings["ESP"]["Filters"]["visibility_check"], &Settings::ESP::Filters::visibilityCheck);
	GetVal(settings["ESP"]["Filters"]["smoke_check"], &Settings::ESP::Filters::smokeCheck);
	GetVal(settings["ESP"]["Filters"]["enemies"], &Settings::ESP::Filters::enemies);
	GetVal(settings["ESP"]["Filters"]["allies"], &Settings::ESP::Filters::allies);
	GetVal(settings["ESP"]["Filters"]["bomb"], &Settings::ESP::Filters::bomb);
	GetVal(settings["ESP"]["Filters"]["hostages"], &Settings::ESP::Filters::hostages);
	GetVal(settings["ESP"]["Filters"]["defusers"], &Settings::ESP::Filters::defusers);
	GetVal(settings["ESP"]["Filters"]["weapons"], &Settings::ESP::Filters::weapons);
	GetVal(settings["ESP"]["Filters"]["chickens"], &Settings::ESP::Filters::chickens);
	GetVal(settings["ESP"]["Filters"]["fishes"], &Settings::ESP::Filters::fishes);
	GetVal(settings["ESP"]["Filters"]["throwables"], &Settings::ESP::Filters::throwables);
	GetVal(settings["ESP"]["Filters"]["localplayer"], &Settings::ESP::Filters::localplayer);
	GetVal(settings["ESP"]["Info"]["name"], &Settings::ESP::Info::name);
	GetVal(settings["ESP"]["Info"]["clan"], &Settings::ESP::Info::clan);
	GetVal(settings["ESP"]["Info"]["steam_id"], &Settings::ESP::Info::steamId);
	GetVal(settings["ESP"]["Info"]["rank"], &Settings::ESP::Info::rank);
	GetVal(settings["ESP"]["Info"]["health"], &Settings::ESP::Info::health);
	GetVal(settings["ESP"]["Info"]["weapon"], &Settings::ESP::Info::weapon);
	GetVal(settings["ESP"]["Info"]["scoped"], &Settings::ESP::Info::scoped);
	GetVal(settings["ESP"]["Info"]["reloading"], &Settings::ESP::Info::reloading);
	GetVal(settings["ESP"]["Info"]["flashed"], &Settings::ESP::Info::flashed);
	GetVal(settings["ESP"]["Info"]["planting"], &Settings::ESP::Info::planting);
	GetVal(settings["ESP"]["Info"]["has_defuser"], &Settings::ESP::Info::hasDefuser);
	GetVal(settings["ESP"]["Info"]["defusing"], &Settings::ESP::Info::defusing);
	GetVal(settings["ESP"]["Info"]["grabbing_hostage"], &Settings::ESP::Info::grabbingHostage);
	GetVal(settings["ESP"]["Info"]["rescuing"], &Settings::ESP::Info::rescuing);
	GetVal(settings["ESP"]["Info"]["location"], &Settings::ESP::Info::location);
	GetVal(settings["ESP"]["Boxes"]["enabled"], &Settings::ESP::Boxes::enabled);
	GetVal(settings["ESP"]["Boxes"]["type"], (int*)& Settings::ESP::Boxes::type);
	GetVal(settings["ESP"]["Skeleton"]["enabled"], &Settings::ESP::Skeleton::enabled);
	GetVal(settings["ESP"]["Skeleton"]["color"], &Settings::ESP::Skeleton::color);
	GetVal(settings["ESP"]["Bars"]["enabled"], &Settings::ESP::Bars::enabled);
	GetVal(settings["ESP"]["Bars"]["color_type"], (int*)& Settings::ESP::Bars::colorType);
	GetVal(settings["ESP"]["Bars"]["type"], (int*)& Settings::ESP::Bars::type);
	GetVal(settings["ESP"]["Tracers"]["enabled"], &Settings::ESP::Tracers::enabled);
	GetVal(settings["ESP"]["Tracers"]["type"], (int*)& Settings::ESP::Tracers::type);
	GetVal(settings["ESP"]["BulletTracers"]["enabled"], &Settings::ESP::BulletTracers::enabled);
	GetVal(settings["ESP"]["FOVCrosshair"]["enabled"], &Settings::ESP::FOVCrosshair::enabled);
	GetVal(settings["ESP"]["FOVCrosshair"]["filled"], &Settings::ESP::FOVCrosshair::filled);
	GetVal(settings["ESP"]["FOVCrosshair"]["color"], &Settings::ESP::FOVCrosshair::color);
	GetVal(settings["ESP"]["Chams"]["Arms"]["enabled"], &Settings::ESP::Chams::Arms::enabled);
	GetVal(settings["ESP"]["Chams"]["Arms"]["type"], (int*)& Settings::ESP::Chams::Arms::type);
	GetVal(settings["ESP"]["Chams"]["Arms"]["color"], &Settings::ESP::Chams::Arms::color);
	GetVal(settings["ESP"]["Chams"]["Weapon"]["enabled"], &Settings::ESP::Chams::Weapon::enabled);
	GetVal(settings["ESP"]["Chams"]["Weapon"]["color"], &Settings::ESP::Chams::Weapon::color);
	GetVal(settings["ESP"]["Chams"]["players_ally_color"], &Settings::ESP::Chams::allyColor);
	GetVal(settings["ESP"]["Chams"]["players_ally_visible_color"], &Settings::ESP::Chams::allyVisibleColor);
	GetVal(settings["ESP"]["Chams"]["players_enemy_color"], &Settings::ESP::Chams::enemyColor);
	GetVal(settings["ESP"]["Chams"]["players_enemy_visible_color"], &Settings::ESP::Chams::enemyVisibleColor);
	GetVal(settings["ESP"]["Chams"]["localplayer_color"], &Settings::ESP::Chams::localplayerColor);
	GetVal(settings["ESP"]["Chams"]["type"], (int*)& Settings::ESP::Chams::type);
	GetVal(settings["ESP"]["Chams"]["enabled"], &Settings::ESP::Chams::enabled);
	GetVal(settings["ESP"]["Sounds"]["enabled"], &Settings::ESP::Sounds::enabled);
	GetVal(settings["ESP"]["Sounds"]["time"], &Settings::ESP::Sounds::time);
	GetVal(settings["ESP"]["Hitmarker"]["enabled"], &Settings::ESP::Hitmarker::enabled);
	GetVal(settings["ESP"]["Hitmarker"]["enemies"], &Settings::ESP::Hitmarker::enemies);
	GetVal(settings["ESP"]["Hitmarker"]["allies"], &Settings::ESP::Hitmarker::allies);
	GetVal(settings["ESP"]["Hitmarker"]["color"], &Settings::ESP::Hitmarker::color);
	GetVal(settings["ESP"]["Hitmarker"]["duration"], &Settings::ESP::Hitmarker::duration);
	GetVal(settings["ESP"]["Hitmarker"]["size"], &Settings::ESP::Hitmarker::size);
	GetVal(settings["ESP"]["Hitmarker"]["inner_gap"], &Settings::ESP::Hitmarker::innerGap);
	GetVal(settings["ESP"]["Hitmarker"]["Damage"]["enabled"], &Settings::ESP::Hitmarker::Damage::enabled);
	GetVal(settings["ESP"]["HeadDot"]["enabled"], &Settings::ESP::HeadDot::enabled);
	GetVal(settings["ESP"]["HeadDot"]["size"], &Settings::ESP::HeadDot::size);

	GetVal(settings["Dlights"]["enabled"], &Settings::Dlights::enabled);
	GetVal(settings["Dlights"]["radius"], &Settings::Dlights::radius);

	GetVal(settings["Spammer"]["spammer_type"], (int*)& Settings::Spammer::type);
	GetVal(settings["Spammer"]["say_team"], &Settings::Spammer::say_team);
	GetVal(settings["Spammer"]["KillSpammer"]["enabled"], &Settings::Spammer::KillSpammer::enabled);
	GetVal(settings["Spammer"]["KillSpammer"]["say_team"], &Settings::Spammer::KillSpammer::sayTeam);
	if (!settings["Spammer"]["KillSpammer"]["messages"].isNull())
	{
		Settings::Spammer::KillSpammer::messages.clear();
		for (const Json::Value& message : settings["Spammer"]["KillSpammer"]["messages"])
			Settings::Spammer::KillSpammer::messages.push_back(message.asString());
	}
	if (!settings["Spammer"]["NormalSpammer"]["messages"].isNull())
	{
		Settings::Spammer::NormalSpammer::messages.clear();
		for (const Json::Value& message : settings["Spammer"]["NormalSpammer"]["messages"])
			Settings::Spammer::NormalSpammer::messages.push_back(message.asString());
	}
	GetVal(settings["Spammer"]["PositionSpammer"]["show_name"], &Settings::Spammer::PositionSpammer::showName);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_weapon"], &Settings::Spammer::PositionSpammer::showWeapon);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_rank"], &Settings::Spammer::PositionSpammer::showRank);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_wins"], &Settings::Spammer::PositionSpammer::showWins);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_health"], &Settings::Spammer::PositionSpammer::showHealth);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_money"], &Settings::Spammer::PositionSpammer::showMoney);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_lastplace"], &Settings::Spammer::PositionSpammer::showLastplace);

	GetVal(settings["BHop"]["enabled"], &Settings::BHop::enabled);

	GetVal(settings["AutoStrafe"]["enabled"], &Settings::AutoStrafe::enabled);
	GetVal(settings["AutoStrafe"]["type"], (int*)& Settings::AutoStrafe::type);
	GetVal(settings["AutoStrafe"]["silent"], &Settings::AutoStrafe::silent);

	GetVal(settings["Noflash"]["enabled"], &Settings::Noflash::enabled);
	GetVal(settings["Noflash"]["value"], &Settings::Noflash::value);

	GetVal(settings["Radar"]["enabled"], &Settings::Radar::enabled);
	GetVal(settings["Radar"]["zoom"], &Settings::Radar::zoom);
	GetVal(settings["Radar"]["enemies"], &Settings::Radar::enemies);
	GetVal(settings["Radar"]["allies"], &Settings::Radar::allies);
	GetVal(settings["Radar"]["legit"], &Settings::Radar::legit);
	GetVal(settings["Radar"]["visibility_check"], &Settings::Radar::visibilityCheck);
	GetVal(settings["Radar"]["smoke_check"], &Settings::Radar::smokeCheck);
	GetVal(settings["Radar"]["InGame"]["enabled"], &Settings::Radar::InGame::enabled);
	GetVal(settings["Radar"]["enemy_color"], &Settings::Radar::enemyColor);
	GetVal(settings["Radar"]["enemy_visible_color"], &Settings::Radar::enemyVisibleColor);
	GetVal(settings["Radar"]["ally_color"], &Settings::Radar::allyColor);
	GetVal(settings["Radar"]["ally_visible_color"], &Settings::Radar::allyVisibleColor);
	GetVal(settings["Radar"]["t_color"], &Settings::Radar::tColor);
	GetVal(settings["Radar"]["t_visible_color"], &Settings::Radar::tVisibleColor);
	GetVal(settings["Radar"]["ct_color"], &Settings::Radar::ctColor);
	GetVal(settings["Radar"]["ct_visible_color"], &Settings::Radar::ctVisibleColor);
	GetVal(settings["Radar"]["bomb_color"], &Settings::Radar::bombColor);
	GetVal(settings["Radar"]["bomb_defusing_color"], &Settings::Radar::bombDefusingColor);
	GetVal(settings["Radar"]["icons_scale"], &Settings::Radar::iconsScale);


	GetVal(settings["Recoilcrosshair"]["enabled"], &Settings::Recoilcrosshair::enabled);
	GetVal(settings["Recoilcrosshair"]["showOnlyWhenShooting"], &Settings::Recoilcrosshair::showOnlyWhenShooting);

	GetVal(settings["FOVChanger"]["enabled"], &Settings::FOVChanger::enabled);
	GetVal(settings["FOVChanger"]["value"], &Settings::FOVChanger::value);
	GetVal(settings["FOVChanger"]["viewmodel_enabled"], &Settings::FOVChanger::viewmodelEnabled);
	GetVal(settings["FOVChanger"]["viewmodel_value"], &Settings::FOVChanger::viewmodelValue);
	GetVal(settings["FOVChanger"]["ignore_scope"], &Settings::FOVChanger::ignoreScope);

	GetVal(settings["Airstuck"]["enabled"], &Settings::Airstuck::enabled);
	GetButtonCode(settings["Airstuck"]["key"], &Settings::Airstuck::key);

	Settings::Skinchanger::Skins::enabled = false;
	Settings::Skinchanger::skinsCT.clear();
	Settings::Skinchanger::skinsT.clear();

	for (Json::ValueIterator itr = settings["SkinChanger"]["skinsCT"].begin(); itr != settings["SkinChanger"]["skinsCT"].end(); itr++)
	{
		std::string skinDataKey = itr.key().asString();
		auto skinSetting = settings["SkinChanger"]["skinsCT"][skinDataKey];

		// XXX Using exception handling to deal with this is stupid, but I don't care to find a better solution
		// XXX We can't use GetOrdinal() since the key type is a string...
		unsigned int weaponID;

		try
		{
			weaponID = std::stoi(skinDataKey);
		}
		catch(std::invalid_argument)
		{
			weaponID = (int) Util::Items::GetItemIndex(skinDataKey);
		}

		ItemDefinitionIndex defIndex;
		GetOrdinal<ItemDefinitionIndex, Util::Items::GetItemIndex>(skinSetting["ItemDefinitionIndex"], &defIndex);

		if (Settings::Skinchanger::skinsCT.find((ItemDefinitionIndex) weaponID) == Settings::Skinchanger::skinsCT.end())
			Settings::Skinchanger::skinsCT[(ItemDefinitionIndex) weaponID] = AttribItem_t();

		AttribItem_t skin = {
				defIndex,
				skinSetting["PaintKit"].asInt(),
				skinSetting["Wear"].asFloat(),
				skinSetting["Seed"].asInt(),
				skinSetting["StatTrak"].asInt(),
				-1,
				skinSetting["CustomName"].asString(),
		};

		Settings::Skinchanger::skinsCT.at((ItemDefinitionIndex) weaponID) = skin;
	}

	for (Json::ValueIterator itr = settings["SkinChanger"]["skinsT"].begin(); itr != settings["SkinChanger"]["skinsT"].end(); itr++)
	{
		std::string skinDataKey = itr.key().asString();
		auto skinSetting = settings["SkinChanger"]["skinsT"][skinDataKey];

		// XXX Using exception handling to deal with this is stupid, but I don't care to find a better solution
		// XXX We can't use GetOrdinal() since the key type is a string...
		unsigned int weaponID;

		try
		{
			weaponID = std::stoi(skinDataKey);
		}
		catch(std::invalid_argument)
		{
			weaponID = (int) Util::Items::GetItemIndex(skinDataKey);
		}

		ItemDefinitionIndex defIndex;
		GetOrdinal<ItemDefinitionIndex, Util::Items::GetItemIndex>(skinSetting["ItemDefinitionIndex"], &defIndex);

		if (Settings::Skinchanger::skinsT.find((ItemDefinitionIndex) weaponID) == Settings::Skinchanger::skinsT.end())
			Settings::Skinchanger::skinsT[(ItemDefinitionIndex) weaponID] = AttribItem_t();

		AttribItem_t skin = {
				defIndex,
				skinSetting["PaintKit"].asInt(),
				skinSetting["Wear"].asFloat(),
				skinSetting["Seed"].asInt(),
				skinSetting["StatTrak"].asInt(),
				-1,
				skinSetting["CustomName"].asString(),
		};

		Settings::Skinchanger::skinsT.at((ItemDefinitionIndex) weaponID) = skin;
	}

	SkinChanger::forceFullUpdate = true;

	GetVal(settings["SkinChanger"]["Skins"]["enabled"], &Settings::Skinchanger::Skins::enabled);
	GetVal(settings["SkinChanger"]["Models"]["enabled"], &Settings::Skinchanger::Models::enabled);
	GetVal(settings["SkinChanger"]["Skins"]["perTeam"], &Settings::Skinchanger::Skins::perTeam);

	GetVal(settings["ShowRanks"]["enabled"], &Settings::ShowRanks::enabled);

	GetVal(settings["ShowSpectators"]["enabled"], &Settings::ShowSpectators::enabled);

	GetVal(settings["ClanTagChanger"]["value"], (char *)& Settings::ClanTagChanger::value);
	GetVal(settings["ClanTagChanger"]["enabled"], &Settings::ClanTagChanger::enabled);
	GetVal(settings["ClanTagChanger"]["animation"], &Settings::ClanTagChanger::animation);
	GetVal(settings["ClanTagChanger"]["animation_speed"], &Settings::ClanTagChanger::animationSpeed);
	GetVal(settings["ClanTagChanger"]["type"], (int*)& Settings::ClanTagChanger::type);
	::ClanTagChanger::UpdateClanTagCallback();

	GetVal(settings["View"]["NoViewPunch"]["enabled"], &Settings::View::NoViewPunch::enabled);
	GetVal(settings["View"]["NoAimPunch"]["enabled"], &Settings::View::NoAimPunch::enabled);

	GetVal(settings["Teleport"]["enabled"], &Settings::Teleport::enabled);
	GetButtonCode(settings["Teleport"]["key"], &Settings::Teleport::key);

	GetVal(settings["FakeLag"]["enabled"], &Settings::FakeLag::enabled);
	GetVal(settings["FakeLag"]["value"], &Settings::FakeLag::value);
	GetVal(settings["FakeLag"]["adaptive"], &Settings::FakeLag::adaptive);

	GetVal(settings["AutoAccept"]["enabled"], &Settings::AutoAccept::enabled);

	GetVal(settings["NoSky"]["enabled"], &Settings::NoSky::enabled);
	GetVal(settings["NoSky"]["color"], &Settings::NoSky::color);

	GetVal(settings["ASUSWalls"]["enabled"], &Settings::ASUSWalls::enabled);
	GetVal(settings["ASUSWalls"]["color"], &Settings::ASUSWalls::color);

	GetVal(settings["NoScopeBorder"]["enabled"], &Settings::NoScopeBorder::enabled);

	GetVal(settings["SniperCrosshair"]["enabled"], &Settings::SniperCrosshair::enabled);

	GetVal(settings["Autoblock"]["enabled"], &Settings::Autoblock::enabled);
	GetButtonCode(settings["Autoblock"]["key"], &Settings::Autoblock::key);

	GetVal(settings["AutoDefuse"]["enabled"], &Settings::AutoDefuse::enabled);

	GetVal(settings["NoSmoke"]["enabled"], &Settings::NoSmoke::enabled);

	GetVal(settings["ScreenshotCleaner"]["enabled"], &Settings::ScreenshotCleaner::enabled);

	GetVal(settings["EdgeJump"]["enabled"], &Settings::EdgeJump::enabled);
	GetButtonCode(settings["EdgeJump"]["key"], &Settings::EdgeJump::key);

	GetVal(settings["NameStealer"]["enabled"], &Settings::NameStealer::enabled);
	GetVal(settings["NameStealer"]["team"], &Settings::NameStealer::team);

	GetVal(settings["ThirdPerson"]["enabled"], &Settings::ThirdPerson::enabled);
	GetVal(settings["ThirdPerson"]["distance"], &Settings::ThirdPerson::distance);

	GetVal(settings["JumpThrow"]["enabled"], &Settings::JumpThrow::enabled);
	GetButtonCode(settings["JumpThrow"]["key"], &Settings::JumpThrow::key);

	GetVal(settings["DisablePostProcessing"]["enabled"], &Settings::DisablePostProcessing::enabled);

	GetVal(settings["GrenadeHelper"]["enabled"], &Settings::GrenadeHelper::enabled);
	GetVal(settings["GrenadeHelper"]["aimAssist"], &Settings::GrenadeHelper::aimAssist);
	GetVal(settings["GrenadeHelper"]["OnlyMatching"], &Settings::GrenadeHelper::onlyMatchingInfos);
	GetVal(settings["GrenadeHelper"]["aimStep"], &Settings::GrenadeHelper::aimStep);
	GetVal(settings["GrenadeHelper"]["aimDistance"], &Settings::GrenadeHelper::aimDistance);
	GetVal(settings["GrenadeHelper"]["aimFov"], &Settings::GrenadeHelper::aimFov);

	GetVal(settings["GrenadeHelper"]["aimDot"], &Settings::GrenadeHelper::aimDot);
	GetVal(settings["GrenadeHelper"]["aimLine"], &Settings::GrenadeHelper::aimLine);
	GetVal(settings["GrenadeHelper"]["infoHE"], &Settings::GrenadeHelper::infoHE);
	GetVal(settings["GrenadeHelper"]["infoSmoke"], &Settings::GrenadeHelper::infoSmoke);
	GetVal(settings["GrenadeHelper"]["infoFlash"], &Settings::GrenadeHelper::infoFlash);
	GetVal(settings["GrenadeHelper"]["infoMolotov"], &Settings::GrenadeHelper::infoMolotov);


}

void Settings::LoadSettings()
{
	pstring directory = getenv("HOME");
	directory << "/.config";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	directory << "/AimTux/";

	if (!DoesDirectoryExist(directory.c_str()))
		mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}


void Settings::SaveGrenadeInfo(std::string path)
{
	Json::Value grenadeInfos;
	for (auto grenadeInfo = GrenadeHelper::grenadeInfos.begin(); grenadeInfo != GrenadeHelper::grenadeInfos.end(); grenadeInfo++)
	{
		Json::Value act;
		act["name"] = grenadeInfo->name.c_str();
		act["gType"] = grenadeInfo->gType;
		act["tType"] = grenadeInfo->tType;
		act["pos"]["x"] = grenadeInfo->pos.x;
		act["pos"]["y"] = grenadeInfo->pos.y;
		act["pos"]["z"] = grenadeInfo->pos.z;

		act["angle"]["x"] = grenadeInfo->angle.x;
		act["angle"]["y"] = grenadeInfo->angle.y;

		grenadeInfos.append(act);
	}

	Json::Value data;
	Json::StyledWriter styledWriter;

	data["smokeinfos"] = grenadeInfos;

	std::ofstream(path) << styledWriter.write(data);
}

void Settings::LoadGrenadeInfo(std::string path)
{
	if (!std::ifstream(path).good() || !DoesFileExist(path.c_str()))
		return;
	Json::Value data;
	std::ifstream configDoc(path, std::ifstream::binary);
	try {
		configDoc >> data;
	}
	catch (...)
	{
		cvar->ConsoleDPrintf("Error parsing the config file.\n");
		return;
	}

	Json::Value array = data["smokeinfos"];
	Settings::GrenadeHelper::grenadeInfos = {};

	for(Json::Value::iterator it = array.begin(); it!=array.end(); ++it)
	{
		Json::Value act = *it;
		const char* name = act["name"].asCString();
		GrenadeType gType = (GrenadeType)act["gType"].asInt();
		ThrowType tType = (ThrowType)act["tType"].asInt();
		Json::Value pos = act["pos"];
		Vector posVec = Vector(pos["x"].asFloat(), pos["y"].asFloat(), pos["z"].asFloat());
		Json::Value angle = act["angle"];
		QAngle vAngle = QAngle(angle["x"].asFloat(), angle["y"].asFloat(), 0);
		Settings::GrenadeHelper::grenadeInfos.push_back(GrenadeInfo(gType, posVec, vAngle, tType, pstring(name)));
	}
}

void remove_directory(const char* path)
{
	DIR* dir;
	dirent* pdir;

	dir = opendir(path);

	while ((pdir = readdir(dir)))
	{
		if (strcmp(pdir->d_name, ".") == 0 || strcmp(pdir->d_name, "..") == 0)
			continue;

		if (pdir->d_type == DT_DIR)
		{
			pstring _dir;
			_dir << path << "/" << pdir->d_name;

			remove_directory(_dir.c_str());
		}
		else if (pdir->d_type == DT_REG)
		{
			pstring file;
			file << path << "/" << pdir->d_name;

			unlink(file.c_str());
		}
	}

	rmdir(path);
}

void Settings::DeleteConfig(std::string path)
{
	remove_directory(path.c_str());
}
