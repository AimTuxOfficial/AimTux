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

void LoadUIColor(Json::Value &config, ImColor color)
{
	config["r"] = color.Value.x;
	config["g"] = color.Value.y;
	config["b"] = color.Value.z;
	config["a"] = color.Value.w;
}

void Settings::LoadDefaultsOrSave(std::string path)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	LoadUIColor(settings["UI"]["mainColor"], Settings::UI::mainColor);
	LoadUIColor(settings["UI"]["bodyColor"], Settings::UI::bodyColor);
	LoadUIColor(settings["UI"]["fontColor"], Settings::UI::fontColor);
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
		weaponSetting["TargetBone"] = i.second.bone;
		weaponSetting["AimKey"] = Util::GetButtonName(i.second.aimkey);
		weaponSetting["AimKeyOnly"] = i.second.aimkey_only;
		weaponSetting["Smooth"]["Enabled"] = i.second.smoothEnabled;
		weaponSetting["Smooth"]["Amount"] = i.second.smoothAmount;
		weaponSetting["Smooth"]["Type"] = i.second.smoothType;
		weaponSetting["Smooth"]["Salting"]["Enabled"] = i.second.smoothSaltEnabled;
		weaponSetting["Smooth"]["Salting"]["Multiplier"] = i.second.smoothSaltMultiplier;
		weaponSetting["ErrorMargin"]["Enabled"] = i.second.errorMarginEnabled;
		weaponSetting["ErrorMargin"]["Value"] = i.second.errorMarginValue;
		weaponSetting["AutoAim"]["Enabled"] = i.second.autoAimEnabled;
		weaponSetting["AutoAim"]["FOV"] = i.second.autoAimFov;
		weaponSetting["AimStep"]["Enabled"] = i.second.aimStepEnabled;
		weaponSetting["AimStep"]["Amount"] = i.second.aimStepValue;
		weaponSetting["RCS"]["Enabled"] = i.second.rcsEnabled;
		weaponSetting["RCS"]["AlwaysOn"] = i.second.rcsAlways_on;
		weaponSetting["RCS"]["Amount"] = i.second.rcsAmount;
		weaponSetting["AutoPistol"]["Enabled"] = i.second.autoPistolEnabled;
		weaponSetting["AutoShoot"]["Enabled"] = i.second.autoShootEnabled;
		weaponSetting["AutoScope"]["Enabled"] = i.second.autoScopeEnabled;
		weaponSetting["NoShoot"]["Enabled"] = i.second.noShootEnabled;
		weaponSetting["IgnoreJump"]["Enabled"] = i.second.ignoreJumpEnabled;
		weaponSetting["SmokeCheck"]["Enabled"] = i.second.smoke_check;
		weaponSetting["AutoWall"]["Enabled"] = i.second.autoWallEnabled;
		weaponSetting["AutoWall"]["Value"] = i.second.autoWallValue;

		for (int bone = HITBOX_HEAD; bone <= HITBOX_ARMS; bone++)
			weaponSetting["AutoWall"]["Bones"][bone] = i.second.autoWallBones[bone];

		weaponSetting["AutoAim"]["RealDistance"] = i.second.autoAimRealDistance;

		#undef weaponSetting
	}

	settings["Aimbot"]["AutoStop"]["enabled"] = Settings::Aimbot::AutoStop::enabled;

	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;

	settings["Resolver"]["resolve_all"] = Settings::Resolver::resolve_all;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Util::GetButtonName(Settings::Triggerbot::key);
	settings["Triggerbot"]["Filters"]["enemies"] = Settings::Triggerbot::Filters::enemies;
	settings["Triggerbot"]["Filters"]["allies"] = Settings::Triggerbot::Filters::allies;
	settings["Triggerbot"]["Filters"]["walls"] = Settings::Triggerbot::Filters::walls;
	settings["Triggerbot"]["Filters"]["smoke_check"] = Settings::Triggerbot::Filters::smoke_check;
	settings["Triggerbot"]["Filters"]["head"] = Settings::Triggerbot::Filters::head;
	settings["Triggerbot"]["Filters"]["chest"] = Settings::Triggerbot::Filters::chest;
	settings["Triggerbot"]["Filters"]["stomach"] = Settings::Triggerbot::Filters::stomach;
	settings["Triggerbot"]["Filters"]["arms"] = Settings::Triggerbot::Filters::arms;
	settings["Triggerbot"]["Filters"]["legs"] = Settings::Triggerbot::Filters::legs;
	settings["Triggerbot"]["Delay"]["enabled"] = Settings::Triggerbot::Delay::enabled;
	settings["Triggerbot"]["Delay"]["value"] = Settings::Triggerbot::Delay::value;

	settings["AntiAim"]["Yaw"]["enabled"] = Settings::AntiAim::Yaw::enabled;
	settings["AntiAim"]["Yaw"]["type"] = Settings::AntiAim::Yaw::type;
	settings["AntiAim"]["Yaw"]["type_fake"] = Settings::AntiAim::Yaw::type_fake;
	settings["AntiAim"]["Pitch"]["enabled"] = Settings::AntiAim::Pitch::enabled;
	settings["AntiAim"]["Pitch"]["type"] = Settings::AntiAim::Pitch::type;
	settings["AntiAim"]["HeadEdge"]["enabled"] = Settings::AntiAim::HeadEdge::enabled;
	settings["AntiAim"]["HeadEdge"]["distance"] = Settings::AntiAim::HeadEdge::distance;
	settings["AntiAim"]["AutoDisable"]["no_enemy"] = Settings::AntiAim::AutoDisable::no_enemy;
	settings["AntiAim"]["AutoDisable"]["knife_held"] = Settings::AntiAim::AutoDisable::knife_held;

	settings["ESP"]["enabled"] = Settings::ESP::enabled;
	LoadUIColor(settings["ESP"]["enemy_color"], Settings::ESP::enemy_color);
	LoadUIColor(settings["ESP"]["enemy_visible_color"], Settings::ESP::enemy_visible_color);
	LoadUIColor(settings["ESP"]["ally_color"], Settings::ESP::ally_color);
	LoadUIColor(settings["ESP"]["ally_visible_color"], Settings::ESP::ally_visible_color);
	LoadUIColor(settings["ESP"]["t_color"], Settings::ESP::t_color);
	LoadUIColor(settings["ESP"]["t_visible_color"], Settings::ESP::t_visible_color);
	LoadUIColor(settings["ESP"]["ct_color"], Settings::ESP::ct_color);
	LoadUIColor(settings["ESP"]["ct_visible_color"], Settings::ESP::ct_visible_color);
	settings["ESP"]["hp_enemy_color"] = Settings::ESP::hp_enemy_color;
	settings["ESP"]["hp_ally_color"] = Settings::ESP::hp_ally_color;
	settings["ESP"]["hp_enemy_visible_color"] = Settings::ESP::hp_enemy_visible_color;
	settings["ESP"]["hp_ally_visible_color"] = Settings::ESP::hp_ally_visible_color;
	settings["ESP"]["hp_ct_color"] = Settings::ESP::hp_ct_color;
	settings["ESP"]["hp_t_color"] = Settings::ESP::hp_t_color;
	settings["ESP"]["hp_ct_visible_color"] = Settings::ESP::hp_ct_visible_color;
	settings["ESP"]["hp_t_visible_color"] = Settings::ESP::hp_t_visible_color;
	LoadUIColor(settings["ESP"]["bomb_color"], Settings::ESP::bomb_color);
	LoadUIColor(settings["ESP"]["bomb_defusing_color"], Settings::ESP::bomb_defusing_color);
	LoadUIColor(settings["ESP"]["hostage_color"], Settings::ESP::hostage_color);
	LoadUIColor(settings["ESP"]["defuser_color"], Settings::ESP::defuser_color);
	LoadUIColor(settings["ESP"]["weapon_color"], Settings::ESP::weapon_color);
	LoadUIColor(settings["ESP"]["chicken_color"], Settings::ESP::chicken_color);
	LoadUIColor(settings["ESP"]["fish_color"], Settings::ESP::fish_color);
	LoadUIColor(settings["ESP"]["smoke_color"], Settings::ESP::smoke_color);
	LoadUIColor(settings["ESP"]["decoy_color"], Settings::ESP::decoy_color);
	LoadUIColor(settings["ESP"]["flashbang_color"], Settings::ESP::flashbang_color);
	LoadUIColor(settings["ESP"]["grenade_color"], Settings::ESP::grenade_color);
	LoadUIColor(settings["ESP"]["molotov_color"], Settings::ESP::molotov_color);
	settings["ESP"]["Glow"]["enabled"] = Settings::ESP::Glow::enabled;
	LoadUIColor(settings["ESP"]["Glow"]["ally_color"], Settings::ESP::Glow::ally_color);
	LoadUIColor(settings["ESP"]["Glow"]["enemy_color"], Settings::ESP::Glow::enemy_color);
	LoadUIColor(settings["ESP"]["Glow"]["enemy_visible_color"], Settings::ESP::Glow::enemy_visible_color);
	settings["ESP"]["Glow"]["hp_ally_color"] = Settings::ESP::Glow::hp_ally_color;
	settings["ESP"]["Glow"]["hp_enemy_color"] = Settings::ESP::Glow::hp_enemy_color;
	settings["ESP"]["Glow"]["hp_enemy_visible_color"] = Settings::ESP::Glow::hp_enemy_visible_color;
	LoadUIColor(settings["ESP"]["Glow"]["weapon_color"], Settings::ESP::Glow::weapon_color);
	LoadUIColor(settings["ESP"]["Glow"]["grenade_color"], Settings::ESP::Glow::grenade_color);
	LoadUIColor(settings["ESP"]["Glow"]["defuser_color"], Settings::ESP::Glow::defuser_color);
	LoadUIColor(settings["ESP"]["Glow"]["chicken_color"], Settings::ESP::Glow::chicken_color);
	settings["ESP"]["Filters"]["legit"] = Settings::ESP::Filters::legit;
	settings["ESP"]["Filters"]["visibility_check"] = Settings::ESP::Filters::visibility_check;
	settings["ESP"]["Filters"]["smoke_check"] = Settings::ESP::Filters::smoke_check;
	settings["ESP"]["Filters"]["enemies"] = Settings::ESP::Filters::enemies;
	settings["ESP"]["Filters"]["allies"] = Settings::ESP::Filters::allies;
	settings["ESP"]["Filters"]["bomb"] = Settings::ESP::Filters::bomb;
	settings["ESP"]["Filters"]["hostages"] = Settings::ESP::Filters::hostages;
	settings["ESP"]["Filters"]["defusers"] = Settings::ESP::Filters::defusers;
	settings["ESP"]["Filters"]["weapons"] = Settings::ESP::Filters::weapons;
	settings["ESP"]["Filters"]["chickens"] = Settings::ESP::Filters::chickens;
	settings["ESP"]["Filters"]["fishes"] = Settings::ESP::Filters::fishes;
	settings["ESP"]["Filters"]["throwables"] = Settings::ESP::Filters::throwables;
	settings["ESP"]["Info"]["name"] = Settings::ESP::Info::name;
	settings["ESP"]["Info"]["clan"] = Settings::ESP::Info::clan;
	settings["ESP"]["Info"]["steam_id"] = Settings::ESP::Info::steam_id;
	settings["ESP"]["Info"]["rank"] = Settings::ESP::Info::rank;
	settings["ESP"]["Info"]["health"] = Settings::ESP::Info::health;
	settings["ESP"]["Info"]["weapon"] = Settings::ESP::Info::weapon;
	settings["ESP"]["Info"]["scoped"] = Settings::ESP::Info::scoped;
	settings["ESP"]["Info"]["reloading"] = Settings::ESP::Info::reloading;
	settings["ESP"]["Info"]["flashed"] = Settings::ESP::Info::flashed;
	settings["ESP"]["Info"]["planting"] = Settings::ESP::Info::planting;
	settings["ESP"]["Info"]["has_defuser"] = Settings::ESP::Info::has_defuser;
	settings["ESP"]["Info"]["defusing"] = Settings::ESP::Info::defusing;
	settings["ESP"]["Info"]["grabbing_hostage"] = Settings::ESP::Info::grabbing_hostage;
	settings["ESP"]["Info"]["rescuing"] = Settings::ESP::Info::rescuing;
	settings["ESP"]["Info"]["location"] = Settings::ESP::Info::location;
	settings["ESP"]["Boxes"]["enabled"] = Settings::ESP::Boxes::enabled;
	settings["ESP"]["Boxes"]["type"] = Settings::ESP::Boxes::type;
	settings["ESP"]["Skeleton"]["enabled"] = Settings::ESP::Skeleton::enabled;
	LoadUIColor(settings["ESP"]["Skeleton"]["color"], Settings::ESP::Skeleton::color);
	settings["ESP"]["Bars"]["enabled"] = Settings::ESP::Bars::enabled;
	settings["ESP"]["Bars"]["color_type"] = Settings::ESP::Bars::color_type;
	settings["ESP"]["Bars"]["type"] = Settings::ESP::Bars::type;
	settings["ESP"]["Tracers"]["enabled"] = Settings::ESP::Tracers::enabled;
	settings["ESP"]["Tracers"]["type"] = Settings::ESP::Tracers::type;
	settings["ESP"]["BulletTracers"]["enabled"] = Settings::ESP::BulletTracers::enabled;
	settings["ESP"]["FOVCrosshair"]["enabled"] = Settings::ESP::FOVCrosshair::enabled;
	LoadUIColor(settings["ESP"]["FOVCrosshair"]["color"], Settings::ESP::FOVCrosshair::color);
	settings["ESP"]["Chams"]["Arms"]["enabled"] = Settings::ESP::Chams::Arms::enabled;
	settings["ESP"]["Chams"]["Arms"]["type"] = Settings::ESP::Chams::Arms::type;
	LoadUIColor(settings["ESP"]["Chams"]["Arms"]["color"], Settings::ESP::Chams::Arms::color);
	LoadUIColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::ally_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_ally_visible_color"], Settings::ESP::Chams::ally_visible_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::enemy_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::enemy_visible_color);
	settings["ESP"]["Chams"]["hp_ally_color"] = Settings::ESP::Chams::hp_ally_color;
	settings["ESP"]["Chams"]["hp_ally_visible_color"] = Settings::ESP::Chams::hp_ally_visible_color;
	settings["ESP"]["Chams"]["hp_enemy_color"] = Settings::ESP::Chams::hp_enemy_color;
	settings["ESP"]["Chams"]["hp_enemy_visible_color"] = Settings::ESP::Chams::hp_enemy_visible_color;
	settings["ESP"]["Chams"]["type"] = Settings::ESP::Chams::type;
	settings["ESP"]["Chams"]["enabled"] = Settings::ESP::Chams::enabled;
	settings["ESP"]["Sounds"]["enabled"] = Settings::ESP::Sounds::enabled;
	settings["ESP"]["Sounds"]["time"] = Settings::ESP::Sounds::time;
	settings["ESP"]["Hitmarker"]["enabled"] = Settings::ESP::Hitmarker::enabled;
	settings["ESP"]["Hitmarker"]["enemies"] = Settings::ESP::Hitmarker::enemies;
	settings["ESP"]["Hitmarker"]["allies"] = Settings::ESP::Hitmarker::allies;
	LoadUIColor(settings["ESP"]["Hitmarker"]["color"], Settings::ESP::Hitmarker::color);
	settings["ESP"]["Hitmarker"]["duration"] = Settings::ESP::Hitmarker::duration;
	settings["ESP"]["Hitmarker"]["size"] = Settings::ESP::Hitmarker::size;
	settings["ESP"]["Hitmarker"]["inner_gap"] = Settings::ESP::Hitmarker::inner_gap;
	settings["ESP"]["Hitmarker"]["Damage"]["enabled"] = Settings::ESP::Hitmarker::Damage::enabled;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;

	settings["Spammer"]["spammer_type"] = Settings::Spammer::type;
	settings["Spammer"]["say_team"] = Settings::Spammer::say_team;
	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["say_team"] = Settings::Spammer::KillSpammer::say_team;
	settings["Spammer"]["KillSpammer"]["message"] = Settings::Spammer::KillSpammer::message;
	Json::Value messages;
	for (auto it : Settings::Spammer::NormalSpammer::messages)
		messages.append(it);
	settings["Spammer"]["NormalSpammer"]["messages"] = messages;
	settings["Spammer"]["PositionSpammer"]["show_name"] = Settings::Spammer::PositionSpammer::show_name;
	settings["Spammer"]["PositionSpammer"]["show_weapon"] = Settings::Spammer::PositionSpammer::show_weapon;
	settings["Spammer"]["PositionSpammer"]["show_rank"] = Settings::Spammer::PositionSpammer::show_rank;
	settings["Spammer"]["PositionSpammer"]["show_wins"] = Settings::Spammer::PositionSpammer::show_wins;
	settings["Spammer"]["PositionSpammer"]["show_health"] = Settings::Spammer::PositionSpammer::show_health;
	settings["Spammer"]["PositionSpammer"]["show_money"] = Settings::Spammer::PositionSpammer::show_money;
	settings["Spammer"]["PositionSpammer"]["show_lastplace"] = Settings::Spammer::PositionSpammer::show_lastplace;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;
	settings["AutoStrafe"]["type"] = Settings::AutoStrafe::type;
	settings["AutoStrafe"]["silent"] = Settings::AutoStrafe::silent;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Radar"]["enabled"] = Settings::Radar::enabled;
	settings["Radar"]["zoom"] = Settings::Radar::zoom;
	settings["Radar"]["enemies"] = Settings::Radar::enemies;
	settings["Radar"]["allies"] = Settings::Radar::allies;
	settings["Radar"]["legit"] = Settings::Radar::legit;
	settings["Radar"]["visibility_check"] = Settings::Radar::visibility_check;
	settings["Radar"]["smoke_check"] = Settings::Radar::smoke_check;
	settings["Radar"]["InGame"]["enabled"] = Settings::Radar::InGame::enabled;
	LoadUIColor(settings["Radar"]["enemy_color"], Settings::Radar::enemy_color);
	LoadUIColor(settings["Radar"]["enemy_visible_color"], Settings::Radar::enemy_visible_color);
	LoadUIColor(settings["Radar"]["ally_color"], Settings::Radar::ally_color);
	LoadUIColor(settings["Radar"]["ally_visible_color"], Settings::Radar::ally_visible_color);
	LoadUIColor(settings["Radar"]["t_color"], Settings::Radar::t_color);
	LoadUIColor(settings["Radar"]["t_visible_color"], Settings::Radar::t_visible_color);
	LoadUIColor(settings["Radar"]["ct_color"], Settings::Radar::ct_color);
	LoadUIColor(settings["Radar"]["ct_visible_color"], Settings::Radar::ct_visible_color);
	LoadUIColor(settings["Radar"]["bomb_color"], Settings::Radar::bomb_color);
	LoadUIColor(settings["Radar"]["bomb_defusing_color"], Settings::Radar::bomb_defusing_color);
	settings["Radar"]["hp_enemy_color"] = Settings::Radar::hp_enemy_color;
	settings["Radar"]["hp_ally_color"] = Settings::Radar::hp_ally_color;
	settings["Radar"]["hp_enemy_visible_color"] = Settings::Radar::hp_enemy_visible_color;
	settings["Radar"]["hp_ally_visible_color"] = Settings::Radar::hp_ally_visible_color;
	settings["Radar"]["hp_ct_color"] = Settings::Radar::hp_ct_color;
	settings["Radar"]["hp_t_color"] = Settings::Radar::hp_t_color;
	settings["Radar"]["hp_ct_visible_color"] = Settings::Radar::hp_ct_visible_color;
	settings["Radar"]["hp_t_visible_color"] = Settings::Radar::hp_t_visible_color;
	settings["Radar"]["icons_scale"] = Settings::Radar::icons_scale;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

	settings["Recoilcrosshair"]["showOnlyWhenShooting"] = Settings::Recoilcrosshair::showOnlyWhenShooting;

	settings["FOVChanger"]["enabled"] = Settings::FOVChanger::enabled;
	settings["FOVChanger"]["value"] = Settings::FOVChanger::value;
	settings["FOVChanger"]["viewmodel_enabled"] = Settings::FOVChanger::viewmodel_enabled;
	settings["FOVChanger"]["viewmodel_value"] = Settings::FOVChanger::viewmodel_value;
	settings["FOVChanger"]["ignore_scope"] = Settings::FOVChanger::ignore_scope;

	settings["Airstuck"]["enabled"] = Settings::Airstuck::enabled;
	settings["Airstuck"]["key"] = Util::GetButtonName(Settings::Airstuck::key);

	settings["Skinchanger"]["enabled"] = Settings::Skinchanger::enabled;
	for (auto i : Settings::Skinchanger::skins)
	{
		// TODO this is kind of a hack and i'm too tired to find a better way to do this
		// yes i tried defining a variable, skinSetting, and giving it the same value but woooooo operator overloading
		// in C++ and weird shit
		#define skinSetting settings["Skinchanger"]["skins"][Util::Items::GetItemName((enum ItemDefinitionIndex) i.first)]
		skinSetting["PaintKit"] = i.second.PaintKit;
		skinSetting["ItemDefinitionIndex"] = Util::Items::GetItemName((enum ItemDefinitionIndex) i.second.ItemDefinitionIndex);
		skinSetting["Seed"] = i.second.Seed;
		skinSetting["Wear"] = i.second.Wear;
		skinSetting["StatTrak"] = i.second.StatTrak;
		skinSetting["CustomName"] = i.second.CustomName;
		skinSetting["Model"] = i.second.Model;
		#undef skinSetting
	}

	settings["ShowRanks"]["enabled"] = Settings::ShowRanks::enabled;

	settings["ShowSpectators"]["enabled"] = Settings::ShowSpectators::enabled;

	settings["ClanTagChanger"]["value"] = Settings::ClanTagChanger::value;
	settings["ClanTagChanger"]["enabled"] = Settings::ClanTagChanger::enabled;
	settings["ClanTagChanger"]["animation"] = Settings::ClanTagChanger::animation;
	settings["ClanTagChanger"]["animation_speed"] = Settings::ClanTagChanger::animation_speed;
	settings["ClanTagChanger"]["type"] = Settings::ClanTagChanger::type;

	settings["View"]["NoViewPunch"]["enabled"] = Settings::View::NoViewPunch::enabled;
	settings["View"]["NoAimPunch"]["enabled"] = Settings::View::NoAimPunch::enabled;

	settings["Teleport"]["enabled"] = Settings::Teleport::enabled;
	settings["Teleport"]["key"] = Settings::Teleport::key;

	settings["FakeLag"]["enabled"] = Settings::FakeLag::enabled;
	settings["FakeLag"]["value"] = Settings::FakeLag::value;

	settings["AutoAccept"]["enabled"] = Settings::AutoAccept::enabled;

	settings["NoSky"]["enabled"] = Settings::NoSky::enabled;
	LoadUIColor(settings["NoSky"]["color"], Settings::NoSky::color);

	settings["ASUSWalls"]["enabled"] = Settings::ASUSWalls::enabled;
	LoadUIColor(settings["ASUSWalls"]["color"], Settings::ASUSWalls::color);

	settings["NoScopeBorder"]["enabled"] = Settings::NoScopeBorder::enabled;

	settings["Autoblock"]["enabled"] = Settings::Autoblock::enabled;
	settings["Autoblock"]["key"] = Settings::Autoblock::key;

	settings["AutoDefuse"]["enabled"] = Settings::AutoDefuse::enabled;

	settings["NoSmoke"]["enabled"] = Settings::NoSmoke::enabled;

	settings["ScreenshotCleaner"]["enabled"] = Settings::ScreenshotCleaner::enabled;

	settings["EdgeJump"]["enabled"] = Settings::EdgeJump::enabled;
	settings["EdgeJump"]["key"] = Util::GetButtonName(Settings::EdgeJump::key);

	settings["NameStealer"]["enabled"] = Settings::NameStealer::enabled;
	settings["NameStealer"]["team"] = Settings::NameStealer::team;

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
	std::ifstream config_doc(path, std::ifstream::binary);
	config_doc >> settings;

	GetVal(settings["UI"]["mainColor"], &Settings::UI::mainColor);
	GetVal(settings["UI"]["bodyColor"], &Settings::UI::bodyColor);
	GetVal(settings["UI"]["fontColor"], &Settings::UI::fontColor);
	GetVal(settings["UI"]["Fonts"]["ESP"]["family"], &Settings::UI::Fonts::ESP::family);
	GetVal(settings["UI"]["Fonts"]["ESP"]["size"], &Settings::UI::Fonts::ESP::size);
	GetVal(settings["UI"]["Fonts"]["ESP"]["flags"], &Settings::UI::Fonts::ESP::flags);

	Fonts::SetupFonts();

	Settings::Aimbot::weapons = {
			{ -1, Settings::Aimbot::Weapon(false, false, false, BONE_HEAD, ButtonCode_t::MOUSE_MIDDLE, false, false, 1.0f, SmoothType::SLOW_END, false, 0.0f, false, 0.0f, true, 180.0f, false, 25.0f, false, false, 2.0f, false, false, false, false, false, false, false, 10.0f, &Settings::Aimbot::AutoWall::bones[0], false) },
	};

	for (Json::ValueIterator itr = settings["Aimbot"]["weapons"].begin(); itr != settings["Aimbot"]["weapons"].end(); itr++)
	{
		std::string weaponDataKey = itr.key().asString();
		auto weaponSetting = settings["Aimbot"]["weapons"][weaponDataKey];

		// XXX Using exception handling to deal with this is stupid, but I don't care to find a better solution
		// XXX We can't use GetOrdinal() since the key type is a string...
		int weaponID;
		try
		{
			weaponID = std::stoi(weaponDataKey);
		}
		catch (std::invalid_argument) // Not a number
		{
			weaponID = Util::Items::GetItemIndex(weaponDataKey);
		}

		Settings::Aimbot::Weapon weapon;
		bool autoWallBones[] = { true, false, false, false, false, false };

		for (int bone = HITBOX_HEAD; bone <= HITBOX_ARMS; bone++)
			autoWallBones[bone] = weaponSetting["AutoWall"]["Bones"][bone].asBool();

		weapon = Settings::Aimbot::Weapon(
			weaponSetting["Enabled"].asBool(),
			weaponSetting["Silent"].asBool(),
			weaponSetting["Friendly"].asBool(),
			weaponSetting["TargetBone"].asInt(),
			Util::GetButtonCode(weaponSetting["AimKey"].asCString()),
			weaponSetting["AimKeyOnly"].asBool(),
			weaponSetting["Smooth"]["Enabled"].asBool(),
			weaponSetting["Smooth"]["Amount"].asFloat(),
			weaponSetting["Smooth"]["Type"].asInt(),
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
			weaponSetting["RCS"]["Amount"].asFloat(),
			weaponSetting["AutoPistol"]["Enabled"].asBool(),
			weaponSetting["AutoShoot"]["Enabled"].asBool(),
			weaponSetting["AutoScope"]["Enabled"].asBool(),
			weaponSetting["NoShoot"]["Enabled"].asBool(),
			weaponSetting["IgnoreJump"]["Enabled"].asBool(),
			weaponSetting["SmokeCheck"]["Enabled"].asBool(),
			weaponSetting["AutoWall"]["Enabled"].asBool(),
			weaponSetting["AutoWall"]["Value"].asFloat(),
			autoWallBones,
			weaponSetting["AutoAim"]["RealDistance"].asBool()
		);

		Settings::Aimbot::weapons[weaponID] = weapon;
	}

	GetVal(settings["Aimbot"]["AutoStop"]["enabled"], &Settings::Aimbot::AutoStop::enabled);

	GetVal(settings["Aimbot"]["AutoCrouch"]["enabled"], &Settings::Aimbot::AutoCrouch::enabled);

	GetVal(settings["Resolver"]["resolve_all"], &Settings::Resolver::resolve_all);

	GetVal(settings["Triggerbot"]["enabled"], &Settings::Triggerbot::enabled);
	GetButtonCode(settings["Triggerbot"]["key"], &Settings::Triggerbot::key);
	GetVal(settings["Triggerbot"]["Filters"]["enemies"], &Settings::Triggerbot::Filters::enemies);
	GetVal(settings["Triggerbot"]["Filters"]["allies"], &Settings::Triggerbot::Filters::allies);
	GetVal(settings["Triggerbot"]["Filters"]["walls"], &Settings::Triggerbot::Filters::walls);
	GetVal(settings["Triggerbot"]["Filters"]["smoke_check"], &Settings::Triggerbot::Filters::smoke_check);
	GetVal(settings["Triggerbot"]["Filters"]["head"], &Settings::Triggerbot::Filters::head);
	GetVal(settings["Triggerbot"]["Filters"]["chest"], &Settings::Triggerbot::Filters::chest);
	GetVal(settings["Triggerbot"]["Filters"]["stomach"], &Settings::Triggerbot::Filters::stomach);
	GetVal(settings["Triggerbot"]["Filters"]["arms"], &Settings::Triggerbot::Filters::arms);
	GetVal(settings["Triggerbot"]["Filters"]["legs"], &Settings::Triggerbot::Filters::legs);
	GetVal(settings["Triggerbot"]["Delay"]["enabled"], &Settings::Triggerbot::Delay::enabled);
	GetVal(settings["Triggerbot"]["Delay"]["value"], &Settings::Triggerbot::Delay::value);

	GetVal(settings["AntiAim"]["Yaw"]["enabled"], &Settings::AntiAim::Yaw::enabled);
	GetVal(settings["AntiAim"]["Yaw"]["type"], &Settings::AntiAim::Yaw::type);
	GetVal(settings["AntiAim"]["Yaw"]["type_fake"], &Settings::AntiAim::Yaw::type_fake);
	GetVal(settings["AntiAim"]["Pitch"]["enabled"], &Settings::AntiAim::Pitch::enabled);
	GetVal(settings["AntiAim"]["Pitch"]["type"], &Settings::AntiAim::Pitch::type);
	GetVal(settings["AntiAim"]["HeadEdge"]["enabled"], &Settings::AntiAim::HeadEdge::enabled);
	GetVal(settings["AntiAim"]["HeadEdge"]["distance"], &Settings::AntiAim::HeadEdge::distance);
	GetVal(settings["AntiAim"]["AutoDisable"]["knife_held"], &Settings::AntiAim::AutoDisable::knife_held);
	GetVal(settings["AntiAim"]["AutoDisable"]["no_enemy"], &Settings::AntiAim::AutoDisable::no_enemy);

	GetVal(settings["ESP"]["enabled"], &Settings::ESP::enabled);
	GetVal(settings["ESP"]["enemy_color"], &Settings::ESP::enemy_color);
	GetVal(settings["ESP"]["enemy_visible_color"], &Settings::ESP::enemy_visible_color);
	GetVal(settings["ESP"]["ally_color"], &Settings::ESP::ally_color);
	GetVal(settings["ESP"]["ally_visible_color"], &Settings::ESP::ally_visible_color);
	GetVal(settings["ESP"]["t_color"], &Settings::ESP::t_color);
	GetVal(settings["ESP"]["t_visible_color"], &Settings::ESP::t_visible_color);
	GetVal(settings["ESP"]["ct_color"], &Settings::ESP::ct_color);
	GetVal(settings["ESP"]["ct_visible_color"], &Settings::ESP::ct_visible_color);
	GetVal(settings["ESP"]["hp_enemy_color"], &Settings::ESP::hp_enemy_color);
	GetVal(settings["ESP"]["hp_enemy_visible_color"], &Settings::ESP::hp_enemy_visible_color);
	GetVal(settings["ESP"]["hp_ally_color"], &Settings::ESP::hp_ally_color);
	GetVal(settings["ESP"]["hp_ally_visible_color"], &Settings::ESP::hp_ally_visible_color);
	GetVal(settings["ESP"]["hp_t_color"], &Settings::ESP::hp_t_color);
	GetVal(settings["ESP"]["hp_t_visible_color"], &Settings::ESP::hp_t_visible_color);
	GetVal(settings["ESP"]["hp_ct_color"], &Settings::ESP::hp_ct_color);
	GetVal(settings["ESP"]["hp_ct_visible_color"], &Settings::ESP::hp_ct_visible_color);
	GetVal(settings["ESP"]["bomb_color"], &Settings::ESP::bomb_color);
	GetVal(settings["ESP"]["bomb_defusing_color"], &Settings::ESP::bomb_defusing_color);
	GetVal(settings["ESP"]["hostage_color"], &Settings::ESP::hostage_color);
	GetVal(settings["ESP"]["defuser_color"], &Settings::ESP::defuser_color);
	GetVal(settings["ESP"]["weapon_color"], &Settings::ESP::weapon_color);
	GetVal(settings["ESP"]["chicken_color"], &Settings::ESP::chicken_color);
	GetVal(settings["ESP"]["fish_color"], &Settings::ESP::fish_color);
	GetVal(settings["ESP"]["smoke_color"], &Settings::ESP::smoke_color);
	GetVal(settings["ESP"]["decoy_color"], &Settings::ESP::decoy_color);
	GetVal(settings["ESP"]["flashbang_color"], &Settings::ESP::flashbang_color);
	GetVal(settings["ESP"]["grenade_color"], &Settings::ESP::grenade_color);
	GetVal(settings["ESP"]["molotov_color"], &Settings::ESP::molotov_color);
	GetVal(settings["ESP"]["Glow"]["enabled"], &Settings::ESP::Glow::enabled);
	GetVal(settings["ESP"]["Glow"]["ally_color"], &Settings::ESP::Glow::ally_color);
	GetVal(settings["ESP"]["Glow"]["enemy_color"], &Settings::ESP::Glow::enemy_color);
	GetVal(settings["ESP"]["Glow"]["enemy_visible_color"], &Settings::ESP::Glow::enemy_visible_color);
	GetVal(settings["ESP"]["Glow"]["hp_ally_color"], &Settings::ESP::Glow::hp_ally_color);
	GetVal(settings["ESP"]["Glow"]["hp_enemy_color"], &Settings::ESP::Glow::hp_enemy_color);
	GetVal(settings["ESP"]["Glow"]["hp_enemy_visible_color"], &Settings::ESP::Glow::hp_enemy_visible_color);
	GetVal(settings["ESP"]["Glow"]["weapon_color"], &Settings::ESP::Glow::weapon_color);
	GetVal(settings["ESP"]["Glow"]["grenade_color"], &Settings::ESP::Glow::grenade_color);
	GetVal(settings["ESP"]["Glow"]["defuser_color"], &Settings::ESP::Glow::defuser_color);
	GetVal(settings["ESP"]["Glow"]["chicken_color"], &Settings::ESP::Glow::chicken_color);
	GetVal(settings["ESP"]["Filters"]["legit"], &Settings::ESP::Filters::legit);
	GetVal(settings["ESP"]["Filters"]["visibility_check"], &Settings::ESP::Filters::visibility_check);
	GetVal(settings["ESP"]["Filters"]["smoke_check"], &Settings::ESP::Filters::smoke_check);
	GetVal(settings["ESP"]["Filters"]["enemies"], &Settings::ESP::Filters::enemies);
	GetVal(settings["ESP"]["Filters"]["allies"], &Settings::ESP::Filters::allies);
	GetVal(settings["ESP"]["Filters"]["bomb"], &Settings::ESP::Filters::bomb);
	GetVal(settings["ESP"]["Filters"]["hostages"], &Settings::ESP::Filters::hostages);
	GetVal(settings["ESP"]["Filters"]["defusers"], &Settings::ESP::Filters::defusers);
	GetVal(settings["ESP"]["Filters"]["weapons"], &Settings::ESP::Filters::weapons);
	GetVal(settings["ESP"]["Filters"]["chickens"], &Settings::ESP::Filters::chickens);
	GetVal(settings["ESP"]["Filters"]["fishes"], &Settings::ESP::Filters::fishes);
	GetVal(settings["ESP"]["Filters"]["throwables"], &Settings::ESP::Filters::throwables);
	GetVal(settings["ESP"]["Info"]["name"], &Settings::ESP::Info::name);
	GetVal(settings["ESP"]["Info"]["clan"], &Settings::ESP::Info::clan);
	GetVal(settings["ESP"]["Info"]["steam_id"], &Settings::ESP::Info::steam_id);
	GetVal(settings["ESP"]["Info"]["rank"], &Settings::ESP::Info::rank);
	GetVal(settings["ESP"]["Info"]["health"], &Settings::ESP::Info::health);
	GetVal(settings["ESP"]["Info"]["weapon"], &Settings::ESP::Info::weapon);
	GetVal(settings["ESP"]["Info"]["scoped"], &Settings::ESP::Info::scoped);
	GetVal(settings["ESP"]["Info"]["reloading"], &Settings::ESP::Info::reloading);
	GetVal(settings["ESP"]["Info"]["flashed"], &Settings::ESP::Info::flashed);
	GetVal(settings["ESP"]["Info"]["planting"], &Settings::ESP::Info::planting);
	GetVal(settings["ESP"]["Info"]["has_defuser"], &Settings::ESP::Info::has_defuser);
	GetVal(settings["ESP"]["Info"]["defusing"], &Settings::ESP::Info::defusing);
	GetVal(settings["ESP"]["Info"]["grabbing_hostage"], &Settings::ESP::Info::grabbing_hostage);
	GetVal(settings["ESP"]["Info"]["rescuing"], &Settings::ESP::Info::rescuing);
	GetVal(settings["ESP"]["Info"]["location"], &Settings::ESP::Info::location);
	GetVal(settings["ESP"]["Boxes"]["enabled"], &Settings::ESP::Boxes::enabled);
	GetVal(settings["ESP"]["Boxes"]["type"], &Settings::ESP::Boxes::type);
	GetVal(settings["ESP"]["Skeleton"]["enabled"], &Settings::ESP::Skeleton::enabled);
	GetVal(settings["ESP"]["Skeleton"]["color"], &Settings::ESP::Skeleton::color);
	GetVal(settings["ESP"]["Bars"]["enabled"], &Settings::ESP::Bars::enabled);
	GetVal(settings["ESP"]["Bars"]["color_type"], &Settings::ESP::Bars::color_type);
	GetVal(settings["ESP"]["Bars"]["type"], &Settings::ESP::Bars::type);
	GetVal(settings["ESP"]["Tracers"]["enabled"], &Settings::ESP::Tracers::enabled);
	GetVal(settings["ESP"]["Tracers"]["type"], &Settings::ESP::Tracers::type);
	GetVal(settings["ESP"]["BulletTracers"]["enabled"], &Settings::ESP::BulletTracers::enabled);
	GetVal(settings["ESP"]["FOVCrosshair"]["enabled"], &Settings::ESP::FOVCrosshair::enabled);
	GetVal(settings["ESP"]["FOVCrosshair"]["color"], &Settings::ESP::FOVCrosshair::color);
	GetVal(settings["ESP"]["Chams"]["Arms"]["enabled"], &Settings::ESP::Chams::Arms::enabled);
	GetVal(settings["ESP"]["Chams"]["Arms"]["type"], &Settings::ESP::Chams::Arms::type);
	GetVal(settings["ESP"]["Chams"]["Arms"]["color"], &Settings::ESP::Chams::Arms::color);
	GetVal(settings["ESP"]["Chams"]["players_ally_color"], &Settings::ESP::Chams::ally_color);
	GetVal(settings["ESP"]["Chams"]["players_ally_visible_color"], &Settings::ESP::Chams::ally_visible_color);
	GetVal(settings["ESP"]["Chams"]["players_enemy_color"], &Settings::ESP::Chams::enemy_color);
	GetVal(settings["ESP"]["Chams"]["players_enemy_visible_color"], &Settings::ESP::Chams::enemy_visible_color);
	GetVal(settings["ESP"]["Chams"]["hp_players_ally_color"], &Settings::ESP::Chams::hp_ally_color);
	GetVal(settings["ESP"]["Chams"]["hp_players_ally_visible_color"], &Settings::ESP::Chams::hp_ally_visible_color);
	GetVal(settings["ESP"]["Chams"]["hp_players_enemy_color"], &Settings::ESP::Chams::hp_enemy_color);
	GetVal(settings["ESP"]["Chams"]["hp_players_enemy_visible_color"], &Settings::ESP::Chams::hp_enemy_visible_color);
	GetVal(settings["ESP"]["Chams"]["type"], &Settings::ESP::Chams::type);
	GetVal(settings["ESP"]["Chams"]["enabled"], &Settings::ESP::Chams::enabled);
	GetVal(settings["ESP"]["Sounds"]["enabled"], &Settings::ESP::Sounds::enabled);
	GetVal(settings["ESP"]["Sounds"]["time"], &Settings::ESP::Sounds::time);
	GetVal(settings["ESP"]["Hitmarker"]["enabled"], &Settings::ESP::Hitmarker::enabled);
	GetVal(settings["ESP"]["Hitmarker"]["enemies"], &Settings::ESP::Hitmarker::enemies);
	GetVal(settings["ESP"]["Hitmarker"]["allies"], &Settings::ESP::Hitmarker::allies);
	GetVal(settings["ESP"]["Hitmarker"]["color"], &Settings::ESP::Hitmarker::color);
	GetVal(settings["ESP"]["Hitmarker"]["duration"], &Settings::ESP::Hitmarker::duration);
	GetVal(settings["ESP"]["Hitmarker"]["size"], &Settings::ESP::Hitmarker::size);
	GetVal(settings["ESP"]["Hitmarker"]["inner_gap"], &Settings::ESP::Hitmarker::inner_gap);
	GetVal(settings["ESP"]["Hitmarker"]["Damage"]["enabled"], &Settings::ESP::Hitmarker::Damage::enabled);

	GetVal(settings["Dlights"]["enabled"], &Settings::Dlights::enabled);
	GetVal(settings["Dlights"]["radius"], &Settings::Dlights::radius);

	GetVal(settings["Spammer"]["spammer_type"], &Settings::Spammer::type);
	GetVal(settings["Spammer"]["say_team"], &Settings::Spammer::say_team);
	GetVal(settings["Spammer"]["KillSpammer"]["enabled"], &Settings::Spammer::KillSpammer::enabled);
	GetVal(settings["Spammer"]["KillSpammer"]["say_team"], &Settings::Spammer::KillSpammer::say_team);
	GetVal(settings["Spammer"]["KillSpammer"]["message"], &Settings::Spammer::KillSpammer::message);
	if (!settings["Spammer"]["NormalSpammer"]["messages"].isNull())
	{
		Settings::Spammer::NormalSpammer::messages.clear();
		for (const Json::Value& message : settings["Spammer"]["NormalSpammer"]["messages"])
			Settings::Spammer::NormalSpammer::messages.push_back(message.asString());
	}
	GetVal(settings["Spammer"]["PositionSpammer"]["show_name"], &Settings::Spammer::PositionSpammer::show_name);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_weapon"], &Settings::Spammer::PositionSpammer::show_weapon);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_rank"], &Settings::Spammer::PositionSpammer::show_rank);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_wins"], &Settings::Spammer::PositionSpammer::show_wins);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_health"], &Settings::Spammer::PositionSpammer::show_health);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_money"], &Settings::Spammer::PositionSpammer::show_money);
	GetVal(settings["Spammer"]["PositionSpammer"]["show_lastplace"], &Settings::Spammer::PositionSpammer::show_lastplace);

	GetVal(settings["BHop"]["enabled"], &Settings::BHop::enabled);

	GetVal(settings["AutoStrafe"]["enabled"], &Settings::AutoStrafe::enabled);
	GetVal(settings["AutoStrafe"]["type"], &Settings::AutoStrafe::type);
	GetVal(settings["AutoStrafe"]["silent"], &Settings::AutoStrafe::silent);

	GetVal(settings["Noflash"]["enabled"], &Settings::Noflash::enabled);
	GetVal(settings["Noflash"]["value"], &Settings::Noflash::value);

	GetVal(settings["Radar"]["enabled"], &Settings::Radar::enabled);
	GetVal(settings["Radar"]["zoom"], &Settings::Radar::zoom);
	GetVal(settings["Radar"]["enemies"], &Settings::Radar::enemies);
	GetVal(settings["Radar"]["allies"], &Settings::Radar::allies);
	GetVal(settings["Radar"]["legit"], &Settings::Radar::legit);
	GetVal(settings["Radar"]["visibility_check"], &Settings::Radar::visibility_check);
	GetVal(settings["Radar"]["smoke_check"], &Settings::Radar::smoke_check);
	GetVal(settings["Radar"]["InGame"]["enabled"], &Settings::Radar::InGame::enabled);
	GetVal(settings["Radar"]["enemy_color"], &Settings::Radar::enemy_color);
	GetVal(settings["Radar"]["enemy_visible_color"], &Settings::Radar::enemy_visible_color);
	GetVal(settings["Radar"]["ally_color"], &Settings::Radar::ally_color);
	GetVal(settings["Radar"]["ally_visible_color"], &Settings::Radar::ally_visible_color);
	GetVal(settings["Radar"]["t_color"], &Settings::Radar::t_color);
	GetVal(settings["Radar"]["t_visible_color"], &Settings::Radar::t_visible_color);
	GetVal(settings["Radar"]["ct_color"], &Settings::Radar::ct_color);
	GetVal(settings["Radar"]["ct_visible_color"], &Settings::Radar::ct_visible_color);
	GetVal(settings["Radar"]["hp_enemy_color"], &Settings::Radar::hp_enemy_color);
	GetVal(settings["Radar"]["hp_enemy_visible_color"], &Settings::Radar::hp_enemy_visible_color);
	GetVal(settings["Radar"]["hp_ally_color"], &Settings::Radar::hp_ally_color);
	GetVal(settings["Radar"]["hp_ally_visible_color"], &Settings::Radar::hp_ally_visible_color);
	GetVal(settings["Radar"]["hp_t_color"], &Settings::Radar::hp_t_color);
	GetVal(settings["Radar"]["hp_t_visible_color"], &Settings::Radar::hp_t_visible_color);
	GetVal(settings["Radar"]["hp_ct_color"], &Settings::Radar::hp_ct_color);
	GetVal(settings["Radar"]["hp_ct_visible_color"], &Settings::Radar::hp_ct_visible_color);
	GetVal(settings["Radar"]["bomb_color"], &Settings::Radar::bomb_color);
	GetVal(settings["Radar"]["bomb_defusing_color"], &Settings::Radar::bomb_defusing_color);
	GetVal(settings["Radar"]["icons_scale"], &Settings::Radar::icons_scale);


	GetVal(settings["Recoilcrosshair"]["enabled"], &Settings::Recoilcrosshair::enabled);
	GetVal(settings["Recoilcrosshair"]["showOnlyWhenShooting"], &Settings::Recoilcrosshair::showOnlyWhenShooting);

	GetVal(settings["FOVChanger"]["enabled"], &Settings::FOVChanger::enabled);
	GetVal(settings["FOVChanger"]["value"], &Settings::FOVChanger::value);
	GetVal(settings["FOVChanger"]["viewmodel_enabled"], &Settings::FOVChanger::viewmodel_enabled);
	GetVal(settings["FOVChanger"]["viewmodel_value"], &Settings::FOVChanger::viewmodel_value);
	GetVal(settings["FOVChanger"]["ignore_scope"], &Settings::FOVChanger::ignore_scope);

	GetVal(settings["Airstuck"]["enabled"], &Settings::Airstuck::enabled);
	GetButtonCode(settings["Airstuck"]["key"], &Settings::Airstuck::key);

	Settings::Skinchanger::enabled = false;
	Settings::Skinchanger::skins.clear();

	for (Json::ValueIterator itr = settings["Skinchanger"]["skins"].begin(); itr != settings["Skinchanger"]["skins"].end(); itr++)
	{
		std::string skinDataKey = itr.key().asString();
		auto skinSetting = settings["Skinchanger"]["skins"][skinDataKey];

		// XXX Using exception handling to deal with this is stupid, but I don't care to find a better solution
		// XXX We can't use GetOrdinal() since the key type is a string...
		int weaponID;
		try
		{
			weaponID = std::stoi(skinDataKey);
		}
		catch (std::invalid_argument) // Not a number
		{
			weaponID = Util::Items::GetItemIndex(skinDataKey);
		}

		enum ItemDefinitionIndex defIndex;
		GetOrdinal<enum ItemDefinitionIndex, Util::Items::GetItemIndex>(skinSetting["ItemDefinitionIndex"], &defIndex);

		Settings::Skinchanger::Skin skin = Settings::Skinchanger::Skin(
				skinSetting["PaintKit"].asInt(),
				defIndex,
				skinSetting["Seed"].asInt(),
				skinSetting["Wear"].asFloat(),
				skinSetting["StatTrak"].asInt(),
				skinSetting["CustomName"].asString(),
				skinSetting["Model"].asString()
		);

		Settings::Skinchanger::skins[weaponID] = skin;
	}

	SkinChanger::ForceFullUpdate = true;

	GetVal(settings["Skinchanger"]["enabled"], &Settings::Skinchanger::enabled);

	GetVal(settings["ShowRanks"]["enabled"], &Settings::ShowRanks::enabled);

	GetVal(settings["ShowSpectators"]["enabled"], &Settings::ShowSpectators::enabled);

	GetVal(settings["ClanTagChanger"]["value"], &Settings::ClanTagChanger::value);
	GetVal(settings["ClanTagChanger"]["enabled"], &Settings::ClanTagChanger::enabled);
	GetVal(settings["ClanTagChanger"]["animation"], &Settings::ClanTagChanger::animation);
	GetVal(settings["ClanTagChanger"]["animation_speed"], &Settings::ClanTagChanger::animation_speed);
	GetVal(settings["ClanTagChanger"]["type"], &Settings::ClanTagChanger::type);
	::ClanTagChanger::UpdateClanTagCallback();

	GetVal(settings["View"]["NoViewPunch"]["enabled"], &Settings::View::NoViewPunch::enabled);
	GetVal(settings["View"]["NoAimPunch"]["enabled"], &Settings::View::NoAimPunch::enabled);

	GetVal(settings["Teleport"]["enabled"], &Settings::Teleport::enabled);
	GetButtonCode(settings["Teleport"]["key"], &Settings::Teleport::key);

	GetVal(settings["FakeLag"]["enabled"], &Settings::FakeLag::enabled);
	GetVal(settings["FakeLag"]["value"], &Settings::FakeLag::value);

	GetVal(settings["AutoAccept"]["enabled"], &Settings::AutoAccept::enabled);

	GetVal(settings["NoSky"]["enabled"], &Settings::NoSky::enabled);
	GetVal(settings["NoSky"]["color"], &Settings::NoSky::color);

	GetVal(settings["ASUSWalls"]["enabled"], &Settings::ASUSWalls::enabled);
	GetVal(settings["ASUSWalls"]["color"], &Settings::ASUSWalls::color);

	GetVal(settings["NoScopeBorder"]["enabled"], &Settings::NoScopeBorder::enabled);

	GetVal(settings["Autoblock"]["enabled"], &Settings::Autoblock::enabled);
	GetButtonCode(settings["Autoblock"]["key"], &Settings::Autoblock::key);

	GetVal(settings["AutoDefuse"]["enabled"], &Settings::AutoDefuse::enabled);

	GetVal(settings["NoSmoke"]["enabled"], &Settings::NoSmoke::enabled);

	GetVal(settings["ScreenshotCleaner"]["enabled"], &Settings::ScreenshotCleaner::enabled);

	GetVal(settings["EdgeJump"]["enabled"], &Settings::EdgeJump::enabled);
	GetButtonCode(settings["EdgeJump"]["key"], &Settings::EdgeJump::key);

	GetVal(settings["NameStealer"]["enabled"], &Settings::NameStealer::enabled);
	GetVal(settings["NameStealer"]["team"], &Settings::NameStealer::team);
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
