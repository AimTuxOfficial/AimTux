#include "settings.h"

void GetBool(Json::Value &config, bool* setting)
{
	if (config.isNull())
		return;

	*setting = config.asBool();
}

void GetCString(Json::Value &config, char** setting)
{
	if (config.isNull())
		return;

	*setting = strdup(config.asCString());
}

void GetString(Json::Value &config, std::string* setting)
{
	if (config.isNull())
		return;

	*setting = config.asString();
}

template <typename Type>
void GetInt(Json::Value &config, Type* setting)
{
	if (config.isNull())
		return;

	*setting = (Type) config.asInt();
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

void GetFloat(Json::Value &config, float* setting)
{
	if (config.isNull())
		return;

	*setting = config.asFloat();
}

template <typename T>
void GetColor(Json::Value &config, T setting)
{
	GetInt(config["r"], &setting->r);
	GetInt(config["g"], &setting->g);
	GetInt(config["b"], &setting->b);
	GetInt(config["a"], &setting->a);
}

template <typename T>
void GetUIColor(Json::Value &config, T setting)
{
	GetFloat(config["r"], &setting->Value.x);
	GetFloat(config["g"], &setting->Value.y);
	GetFloat(config["b"], &setting->Value.z);
	GetFloat(config["a"], &setting->Value.w);
}

void LoadColor(Json::Value &config, Color color)
{
	config["r"] = color.r;
	config["g"] = color.g;
	config["b"] = color.b;
	config["a"] = color.a;
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

	settings["Aimbot"]["enabled"] = Settings::Aimbot::enabled;
	settings["Aimbot"]["silent"] = Settings::Aimbot::silent;
	settings["Aimbot"]["friendly"] = Settings::Aimbot::friendly;
	settings["Aimbot"]["NoShoot"]["enabled"] = Settings::Aimbot::NoShoot::enabled;
	settings["Aimbot"]["ErrorMargin"]["enabled"] = Settings::Aimbot::ErrorMargin::enabled;
	settings["Aimbot"]["ErrorMargin"]["value"] = Settings::Aimbot::ErrorMargin::value;
	settings["Aimbot"]["bone"] = Settings::Aimbot::bone;
	settings["Aimbot"]["aimkey"] = Util::GetButtonName(Settings::Aimbot::aimkey);
	settings["Aimbot"]["aimkey_only"] = Settings::Aimbot::aimkey_only;
	settings["Aimbot"]["Smooth"]["enabled"] = Settings::Aimbot::Smooth::enabled;
	settings["Aimbot"]["Smooth"]["value"] = Settings::Aimbot::Smooth::value;
	settings["Aimbot"]["Smooth"]["Salting"]["enabled"] = Settings::Aimbot::Smooth::Salting::enabled;
	settings["Aimbot"]["Smooth"]["Salting"]["percentage"] = Settings::Aimbot::Smooth::Salting::percentage;
	settings["Aimbot"]["AutoAim"]["enabled"] = Settings::Aimbot::AutoAim::enabled;
	settings["Aimbot"]["AutoAim"]["fov"] = Settings::Aimbot::AutoAim::fov;
	settings["Aimbot"]["AutoWall"]["enabled"] = Settings::Aimbot::AutoWall::enabled;
	settings["Aimbot"]["AutoWall"]["value"] = Settings::Aimbot::AutoWall::value;
	settings["Aimbot"]["AutoWall"]["bones"] = Json::Value(Json::arrayValue);
	for (int i = HITBOX_HEAD; i <= HITBOX_ARMS; i++)
		settings["Aimbot"]["AutoWall"]["bones"][i] = Settings::Aimbot::AutoWall::bones[i];
	settings["Aimbot"]["AimStep"]["enabled"] = Settings::Aimbot::AimStep::enabled;
	settings["Aimbot"]["AimStep"]["value"] = Settings::Aimbot::AimStep::value;
	settings["Aimbot"]["RCS"]["enabled"] = Settings::Aimbot::RCS::enabled;
	settings["Aimbot"]["RCS"]["always_on"] = Settings::Aimbot::RCS::always_on;
	settings["Aimbot"]["RCS"]["value"] = Settings::Aimbot::RCS::value;
	settings["Aimbot"]["AutoPistol"]["enabled"] = Settings::Aimbot::AutoPistol::enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = Settings::Aimbot::AutoShoot::enabled;
	settings["Aimbot"]["AutoShoot"]["autoscope"] = Settings::Aimbot::AutoShoot::autoscope;
	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;
	settings["Aimbot"]["AutoStop"]["enabled"] = Settings::Aimbot::AutoStop::enabled;
	settings["Aimbot"]["IgnoreJump"]["enabled"] = Settings::Aimbot::IgnoreJump::enabled;

	settings["Resolver"]["resolve_all"] = Settings::Resolver::resolve_all;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Util::GetButtonName(Settings::Triggerbot::key);
	settings["Triggerbot"]["Filter"]["friendly"] = Settings::Triggerbot::Filter::friendly;
	settings["Triggerbot"]["Filter"]["walls"] = Settings::Triggerbot::Filter::walls;
	settings["Triggerbot"]["Filter"]["head"] = Settings::Triggerbot::Filter::head;
	settings["Triggerbot"]["Filter"]["chest"] = Settings::Triggerbot::Filter::chest;
	settings["Triggerbot"]["Filter"]["stomach"] = Settings::Triggerbot::Filter::stomach;
	settings["Triggerbot"]["Filter"]["arms"] = Settings::Triggerbot::Filter::arms;
	settings["Triggerbot"]["Filter"]["legs"] = Settings::Triggerbot::Filter::legs;
	settings["Triggerbot"]["Delay"]["enabled"] = Settings::Triggerbot::Delay::enabled;
	settings["Triggerbot"]["Delay"]["value"] = Settings::Triggerbot::Delay::value;

	settings["AntiAim"]["Yaw"]["enabled"] = Settings::AntiAim::Yaw::enabled;
	settings["AntiAim"]["Yaw"]["type"] = Settings::AntiAim::Yaw::type;
	settings["AntiAim"]["Yaw"]["type_fake"] = Settings::AntiAim::Yaw::type_fake;
	settings["AntiAim"]["Pitch"]["enabled"] = Settings::AntiAim::Pitch::enabled;
	settings["AntiAim"]["Pitch"]["type"] = Settings::AntiAim::Pitch::type;
	settings["AntiAim"]["HeadEdge"]["enabled"] = Settings::AntiAim::HeadEdge::enabled;
	settings["AntiAim"]["HeadEdge"]["distance"] = Settings::AntiAim::HeadEdge::distance;
	settings["AntiAim"]["FakeOut"]["enabled"] = Settings::AntiAim::FakeOut::enabled;

	settings["ESP"]["enabled"], Settings::ESP::enabled;
	LoadUIColor(settings["ESP"]["enemy_color"], Settings::ESP::enemy_color);
	LoadUIColor(settings["ESP"]["enemy_visible_color"], Settings::ESP::enemy_visible_color);
	LoadUIColor(settings["ESP"]["ally_color"], Settings::ESP::ally_color);
	LoadUIColor(settings["ESP"]["ally_visible_color"], Settings::ESP::ally_visible_color);
	LoadUIColor(settings["ESP"]["t_color"], Settings::ESP::t_color);
	LoadUIColor(settings["ESP"]["t_visible_color"], Settings::ESP::t_visible_color);
	LoadUIColor(settings["ESP"]["ct_color"], Settings::ESP::ct_color);
	LoadUIColor(settings["ESP"]["ct_visible_color"], Settings::ESP::ct_visible_color);
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
	LoadUIColor(settings["ESP"]["Glow"]["weapon_color"], Settings::ESP::Glow::weapon_color);
	LoadUIColor(settings["ESP"]["Glow"]["grenade_color"], Settings::ESP::Glow::grenade_color);
	LoadUIColor(settings["ESP"]["Glow"]["defuser_color"], Settings::ESP::Glow::defuser_color);
	LoadUIColor(settings["ESP"]["Glow"]["chicken_color"], Settings::ESP::Glow::chicken_color);
	settings["ESP"]["Filters"]["legit"] = Settings::ESP::Filters::legit;
	settings["ESP"]["Filters"]["visibility_check"] = Settings::ESP::Filters::visibility_check;
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
	settings["ESP"]["Chams"]["players"] = Settings::ESP::Chams::players;
	settings["ESP"]["Chams"]["visibility_check"] = Settings::ESP::Chams::visibility_check;
	settings["ESP"]["Chams"]["Arms"]["enabled"] = Settings::ESP::Chams::Arms::enabled;
	settings["ESP"]["Chams"]["Arms"]["type"] = Settings::ESP::Chams::Arms::type;
	LoadUIColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::players_ally_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_ally_visible_color"], Settings::ESP::Chams::players_ally_visible_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::players_enemy_color);
	LoadUIColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::players_enemy_visible_color);
	LoadUIColor(settings["ESP"]["Chams"]["Arms"]["color"], Settings::ESP::Chams::Arms::color);
	settings["ESP"]["Chams"]["type"] = Settings::ESP::Chams::type;
	settings["ESP"]["Sounds"]["enabled"] = Settings::ESP::Sounds::enabled;
	settings["ESP"]["Sounds"]["time"] = Settings::ESP::Sounds::time;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;
	LoadUIColor(settings["Dlights"]["ally_color"], Settings::Dlights::ally_color);
	LoadUIColor(settings["Dlights"]["enemy_color"], Settings::Dlights::enemy_color);

	settings["Spammer"]["PositionSpammer"]["enabled"] = Settings::Spammer::PositionSpammer::enabled;
	settings["Spammer"]["PositionSpammer"]["say_team"] = Settings::Spammer::PositionSpammer::say_team;
	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["say_team"] = Settings::Spammer::KillSpammer::say_team;
	settings["Spammer"]["KillSpammer"]["message"] = Settings::Spammer::KillSpammer::message;
	settings["Spammer"]["NormalSpammer"]["enabled"] = Settings::Spammer::NormalSpammer::enabled;
	settings["Spammer"]["NormalSpammer"]["say_team"] = Settings::Spammer::NormalSpammer::say_team;
	Json::Value messages;
	for (auto it : Settings::Spammer::NormalSpammer::messages)
		messages.append(it);
	settings["Spammer"]["NormalSpammer"]["messages"] = messages;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;
	settings["AutoStrafe"]["type"] = Settings::AutoStrafe::type;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Radar"]["enabled"] = Settings::Radar::enabled;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

	settings["Recoilcrosshair"]["showOnlyWhenShooting"] = Settings::Recoilcrosshair::showOnlyWhenShooting;

	settings["FOVChanger"]["enabled"] = Settings::FOVChanger::enabled;
	settings["FOVChanger"]["value"] = Settings::FOVChanger::value;
	settings["FOVChanger"]["viewmodel_enabled"] = Settings::FOVChanger::viewmodel_enabled;
	settings["FOVChanger"]["viewmodel_value"] = Settings::FOVChanger::viewmodel_value;

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

	settings["View"]["NoPunch"]["enabled"] = Settings::View::NoPunch::enabled;

	settings["NameChanger"]["enabled"] = Settings::NameChanger::enabled;
	settings["NameChanger"]["last_blank"] = Settings::NameChanger::last_blank;

	settings["Teleport"]["enabled"] = Settings::Teleport::enabled;
	settings["Teleport"]["key"] = Settings::Teleport::key;

	settings["FakeLag"]["enabled"] = Settings::FakeLag::enabled;

	settings["AutoAccept"]["enabled"] = Settings::AutoAccept::enabled;

	settings["NoSky"]["enabled"] = Settings::NoSky::enabled;
	LoadUIColor(settings["NoSky"]["color"], Settings::NoSky::color);

	settings["ASUSWalls"]["enabled"] = Settings::ASUSWalls::enabled;
	LoadUIColor(settings["ASUSWalls"]["color"], Settings::ASUSWalls::color);

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

	GetUIColor(settings["UI"]["mainColor"], &Settings::UI::mainColor);
	GetUIColor(settings["UI"]["bodyColor"], &Settings::UI::bodyColor);
	GetUIColor(settings["UI"]["fontColor"], &Settings::UI::fontColor);
	GetCString(settings["UI"]["Fonts"]["ESP"]["family"], &Settings::UI::Fonts::ESP::family);
	GetInt(settings["UI"]["Fonts"]["ESP"]["size"], &Settings::UI::Fonts::ESP::size);
	GetInt(settings["UI"]["Fonts"]["ESP"]["flags"], &Settings::UI::Fonts::ESP::flags);

	Fonts::SetupFonts();

	GetBool(settings["Aimbot"]["enabled"], &Settings::Aimbot::enabled);
	GetBool(settings["Aimbot"]["silent"], &Settings::Aimbot::silent);
	GetBool(settings["Aimbot"]["friendly"], &Settings::Aimbot::friendly);
	GetBool(settings["Aimbot"]["ErrorMargin"]["enabled"], &Settings::Aimbot::ErrorMargin::enabled);
	GetFloat(settings["Aimbot"]["ErrorMargin"]["value"], &Settings::Aimbot::ErrorMargin::value);
	GetBool(settings["Aimbot"]["NoShoot"]["enabled"], &Settings::Aimbot::NoShoot::enabled);
	GetInt(settings["Aimbot"]["bone"], &Settings::Aimbot::bone);
	GetButtonCode(settings["Aimbot"]["aimkey"], &Settings::Aimbot::aimkey);
	GetBool(settings["Aimbot"]["aimkey_only"], &Settings::Aimbot::aimkey_only);
	GetBool(settings["Aimbot"]["Smooth"]["enabled"], &Settings::Aimbot::Smooth::enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["value"], &Settings::Aimbot::Smooth::value);
	GetBool(settings["Aimbot"]["Smooth"]["Salting"]["enabled"], &Settings::Aimbot::Smooth::Salting::enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["Salting"]["percentage"], &Settings::Aimbot::Smooth::Salting::percentage);
	GetBool(settings["Aimbot"]["AutoAim"]["enabled"], &Settings::Aimbot::AutoAim::enabled);
	GetFloat(settings["Aimbot"]["AutoAim"]["fov"], &Settings::Aimbot::AutoAim::fov);
	GetBool(settings["Aimbot"]["AutoWall"]["enabled"], &Settings::Aimbot::AutoWall::enabled);
	GetFloat(settings["Aimbot"]["AutoWall"]["value"], &Settings::Aimbot::AutoWall::value);
	for (int i = HITBOX_HEAD; i <= HITBOX_ARMS; i++)
		GetBool(settings["Aimbot"]["AutoWall"]["bones"][i], &Settings::Aimbot::AutoWall::bones[i]);
	GetBool(settings["Aimbot"]["AimStep"]["enabled"], &Settings::Aimbot::AimStep::enabled);
	GetFloat(settings["Aimbot"]["AimStep"]["value"], &Settings::Aimbot::AimStep::value);
	GetBool(settings["Aimbot"]["RCS"]["enabled"], &Settings::Aimbot::RCS::enabled);
	GetBool(settings["Aimbot"]["RCS"]["always_on"], &Settings::Aimbot::RCS::always_on);
	GetFloat(settings["Aimbot"]["RCS"]["value"], &Settings::Aimbot::RCS::value);
	GetBool(settings["Aimbot"]["AutoPistol"]["enabled"], &Settings::Aimbot::AutoPistol::enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["enabled"], &Settings::Aimbot::AutoShoot::enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["autoscope"], &Settings::Aimbot::AutoShoot::autoscope);
	GetBool(settings["Aimbot"]["AutoCrouch"]["enabled"], &Settings::Aimbot::AutoCrouch::enabled);
	GetBool(settings["Aimbot"]["AutoStop"]["enabled"], &Settings::Aimbot::AutoStop::enabled);
	GetBool(settings["Aimbot"]["IgnoreJump"]["enabled"], &Settings::Aimbot::IgnoreJump::enabled);

	GetBool(settings["Resolver"]["resolve_all"], &Settings::Resolver::resolve_all);

	GetBool(settings["Triggerbot"]["enabled"], &Settings::Triggerbot::enabled);
	GetButtonCode(settings["Triggerbot"]["key"], &Settings::Triggerbot::key);
	GetBool(settings["Triggerbot"]["Filter"]["friendly"], &Settings::Triggerbot::Filter::friendly);
	GetBool(settings["Triggerbot"]["Filter"]["walls"], &Settings::Triggerbot::Filter::walls);
	GetBool(settings["Triggerbot"]["Filter"]["head"], &Settings::Triggerbot::Filter::head);
	GetBool(settings["Triggerbot"]["Filter"]["chest"], &Settings::Triggerbot::Filter::chest);
	GetBool(settings["Triggerbot"]["Filter"]["stomach"], &Settings::Triggerbot::Filter::stomach);
	GetBool(settings["Triggerbot"]["Filter"]["arms"], &Settings::Triggerbot::Filter::arms);
	GetBool(settings["Triggerbot"]["Filter"]["legs"], &Settings::Triggerbot::Filter::legs);
	GetBool(settings["Triggerbot"]["Delay"]["enabled"], &Settings::Triggerbot::Delay::enabled);
	GetInt(settings["Triggerbot"]["Delay"]["value"], &Settings::Triggerbot::Delay::value);

	GetBool(settings["AntiAim"]["Yaw"]["enabled"], &Settings::AntiAim::Yaw::enabled);
	GetInt(settings["AntiAim"]["Yaw"]["type"], &Settings::AntiAim::Yaw::type);
	GetInt(settings["AntiAim"]["Yaw"]["type_fake"], &Settings::AntiAim::Yaw::type_fake);
	GetBool(settings["AntiAim"]["Pitch"]["enabled"], &Settings::AntiAim::Pitch::enabled);
	GetInt(settings["AntiAim"]["Pitch"]["type"], &Settings::AntiAim::Pitch::type);
	GetBool(settings["AntiAim"]["HeadEdge"]["enabled"], &Settings::AntiAim::HeadEdge::enabled);
	GetFloat(settings["AntiAim"]["HeadEdge"]["distance"], &Settings::AntiAim::HeadEdge::distance);
	GetBool(settings["AntiAim"]["FakeOut"]["enabled"], &Settings::AntiAim::FakeOut::enabled);

	GetBool(settings["ESP"]["enabled"], &Settings::ESP::enabled);
	GetUIColor(settings["ESP"]["enemy_color"], &Settings::ESP::enemy_color);
	GetUIColor(settings["ESP"]["enemy_visible_color"], &Settings::ESP::enemy_visible_color);
	GetUIColor(settings["ESP"]["ally_color"], &Settings::ESP::ally_color);
	GetUIColor(settings["ESP"]["ally_visible_color"], &Settings::ESP::ally_visible_color);
	GetUIColor(settings["ESP"]["t_color"], &Settings::ESP::t_color);
	GetUIColor(settings["ESP"]["t_visible_color"], &Settings::ESP::t_visible_color);
	GetUIColor(settings["ESP"]["ct_color"], &Settings::ESP::ct_color);
	GetUIColor(settings["ESP"]["ct_visible_color"], &Settings::ESP::ct_visible_color);
	GetUIColor(settings["ESP"]["bomb_color"], &Settings::ESP::bomb_color);
	GetUIColor(settings["ESP"]["bomb_defusing_color"], &Settings::ESP::bomb_defusing_color);
	GetUIColor(settings["ESP"]["hostage_color"], &Settings::ESP::hostage_color);
	GetUIColor(settings["ESP"]["defuser_color"], &Settings::ESP::defuser_color);
	GetUIColor(settings["ESP"]["weapon_color"], &Settings::ESP::weapon_color);
	GetUIColor(settings["ESP"]["chicken_color"], &Settings::ESP::chicken_color);
	GetUIColor(settings["ESP"]["fish_color"], &Settings::ESP::fish_color);
	GetUIColor(settings["ESP"]["smoke_color"], &Settings::ESP::smoke_color);
	GetUIColor(settings["ESP"]["decoy_color"], &Settings::ESP::decoy_color);
	GetUIColor(settings["ESP"]["flashbang_color"], &Settings::ESP::flashbang_color);
	GetUIColor(settings["ESP"]["grenade_color"], &Settings::ESP::grenade_color);
	GetUIColor(settings["ESP"]["molotov_color"], &Settings::ESP::molotov_color);
	GetBool(settings["ESP"]["Glow"]["enabled"], &Settings::ESP::Glow::enabled);
	GetUIColor(settings["ESP"]["Glow"]["ally_color"], &Settings::ESP::Glow::ally_color);
	GetUIColor(settings["ESP"]["Glow"]["enemy_color"], &Settings::ESP::Glow::enemy_color);
	GetUIColor(settings["ESP"]["Glow"]["enemy_visible_color"], &Settings::ESP::Glow::enemy_visible_color);
	GetUIColor(settings["ESP"]["Glow"]["weapon_color"], &Settings::ESP::Glow::weapon_color);
	GetUIColor(settings["ESP"]["Glow"]["grenade_color"], &Settings::ESP::Glow::grenade_color);
	GetUIColor(settings["ESP"]["Glow"]["defuser_color"], &Settings::ESP::Glow::defuser_color);
	GetUIColor(settings["ESP"]["Glow"]["chicken_color"], &Settings::ESP::Glow::chicken_color);
	GetBool(settings["ESP"]["Filters"]["legit"], &Settings::ESP::Filters::legit);
	GetBool(settings["ESP"]["Filters"]["visibility_check"], &Settings::ESP::Filters::visibility_check);
	GetBool(settings["ESP"]["Filters"]["enemies"], &Settings::ESP::Filters::enemies);
	GetBool(settings["ESP"]["Filters"]["allies"], &Settings::ESP::Filters::allies);
	GetBool(settings["ESP"]["Filters"]["bomb"], &Settings::ESP::Filters::bomb);
	GetBool(settings["ESP"]["Filters"]["hostages"], &Settings::ESP::Filters::hostages);
	GetBool(settings["ESP"]["Filters"]["defusers"], &Settings::ESP::Filters::defusers);
	GetBool(settings["ESP"]["Filters"]["weapons"], &Settings::ESP::Filters::weapons);
	GetBool(settings["ESP"]["Filters"]["chickens"], &Settings::ESP::Filters::chickens);
	GetBool(settings["ESP"]["Filters"]["fishes"], &Settings::ESP::Filters::fishes);
	GetBool(settings["ESP"]["Filters"]["throwables"], &Settings::ESP::Filters::throwables);
	GetBool(settings["ESP"]["Info"]["name"], &Settings::ESP::Info::name);
	GetBool(settings["ESP"]["Info"]["clan"], &Settings::ESP::Info::clan);
	GetBool(settings["ESP"]["Info"]["steam_id"], &Settings::ESP::Info::steam_id);
	GetBool(settings["ESP"]["Info"]["rank"], &Settings::ESP::Info::rank);
	GetBool(settings["ESP"]["Info"]["health"], &Settings::ESP::Info::health);
	GetBool(settings["ESP"]["Info"]["weapon"], &Settings::ESP::Info::weapon);
	GetBool(settings["ESP"]["Info"]["scoped"], &Settings::ESP::Info::scoped);
	GetBool(settings["ESP"]["Info"]["reloading"], &Settings::ESP::Info::reloading);
	GetBool(settings["ESP"]["Info"]["flashed"], &Settings::ESP::Info::flashed);
	GetBool(settings["ESP"]["Info"]["planting"], &Settings::ESP::Info::planting);
	GetBool(settings["ESP"]["Info"]["has_defuser"], &Settings::ESP::Info::has_defuser);
	GetBool(settings["ESP"]["Info"]["defusing"], &Settings::ESP::Info::defusing);
	GetBool(settings["ESP"]["Info"]["grabbing_hostage"], &Settings::ESP::Info::grabbing_hostage);
	GetBool(settings["ESP"]["Info"]["rescuing"], &Settings::ESP::Info::rescuing);
	GetBool(settings["ESP"]["Info"]["location"], &Settings::ESP::Info::location);
	GetBool(settings["ESP"]["Boxes"]["enabled"], &Settings::ESP::Boxes::enabled);
	GetInt(settings["ESP"]["Boxes"]["type"], &Settings::ESP::Boxes::type);
	GetBool(settings["ESP"]["Skeleton"]["enabled"], &Settings::ESP::Skeleton::enabled);
	GetUIColor(settings["ESP"]["Skeleton"]["color"], &Settings::ESP::Skeleton::color);
	GetBool(settings["ESP"]["Bars"]["enabled"], &Settings::ESP::Bars::enabled);
	GetInt(settings["ESP"]["Bars"]["color_type"], &Settings::ESP::Bars::color_type);
	GetInt(settings["ESP"]["Bars"]["type"], &Settings::ESP::Bars::type);
	GetBool(settings["ESP"]["Tracers"]["enabled"], &Settings::ESP::Tracers::enabled);
	GetInt(settings["ESP"]["Tracers"]["type"], &Settings::ESP::Tracers::type);
	GetBool(settings["ESP"]["BulletTracers"]["enabled"], &Settings::ESP::BulletTracers::enabled);
	GetBool(settings["ESP"]["FOVCrosshair"]["enabled"], &Settings::ESP::FOVCrosshair::enabled);
	GetUIColor(settings["ESP"]["FOVCrosshair"]["color"], &Settings::ESP::FOVCrosshair::color);
	GetBool(settings["ESP"]["Chams"]["players"], &Settings::ESP::Chams::players);
	GetBool(settings["ESP"]["Chams"]["visibility_check"], &Settings::ESP::Chams::visibility_check);
	GetBool(settings["ESP"]["Chams"]["Arms"]["enabled"], &Settings::ESP::Chams::Arms::enabled);
	GetInt(settings["ESP"]["Chams"]["Arms"]["type"], &Settings::ESP::Chams::Arms::type);
	GetUIColor(settings["ESP"]["Chams"]["players_ally_color"], &Settings::ESP::Chams::players_ally_color);
	GetUIColor(settings["ESP"]["Chams"]["players_ally_visible_color"], &Settings::ESP::Chams::players_ally_visible_color);
	GetUIColor(settings["ESP"]["Chams"]["players_enemy_color"], &Settings::ESP::Chams::players_enemy_color);
	GetUIColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], &Settings::ESP::Chams::players_enemy_visible_color);
	GetUIColor(settings["ESP"]["Chams"]["Arms"]["color"], &Settings::ESP::Chams::Arms::color);
	GetInt(settings["ESP"]["Chams"]["type"], &Settings::ESP::Chams::type);
	GetBool(settings["ESP"]["Sounds"]["enabled"], &Settings::ESP::Sounds::enabled);
	GetInt(settings["ESP"]["Sounds"]["time"], &Settings::ESP::Sounds::time);

	GetBool(settings["Dlights"]["enabled"], &Settings::Dlights::enabled);
	GetFloat(settings["Dlights"]["radius"], &Settings::Dlights::radius);
	GetUIColor(settings["Dlights"]["ally_color"], &Settings::Dlights::ally_color);
	GetUIColor(settings["Dlights"]["enemy_color"], &Settings::Dlights::enemy_color);

	GetBool(settings["Spammer"]["PositionSpammer"]["enabled"], &Settings::Spammer::PositionSpammer::enabled);
	GetBool(settings["Spammer"]["PositionSpammer"]["say_team"], &Settings::Spammer::PositionSpammer::say_team);
	GetBool(settings["Spammer"]["KillSpammer"]["enabled"], &Settings::Spammer::KillSpammer::enabled);
	GetBool(settings["Spammer"]["KillSpammer"]["say_team"], &Settings::Spammer::KillSpammer::say_team);
	GetCString(settings["Spammer"]["KillSpammer"]["message"], &Settings::Spammer::KillSpammer::message);
	GetBool(settings["Spammer"]["NormalSpammer"]["enabled"], &Settings::Spammer::NormalSpammer::enabled);
	GetBool(settings["Spammer"]["NormalSpammer"]["say_team"], &Settings::Spammer::NormalSpammer::say_team);
	if (!settings["Spammer"]["NormalSpammer"]["messages"].isNull())
	{
		Settings::Spammer::NormalSpammer::messages.clear();
		for (const Json::Value& message : settings["Spammer"]["NormalSpammer"]["messages"])
			Settings::Spammer::NormalSpammer::messages.push_back(message.asString());
	}

	GetBool(settings["BHop"]["enabled"], &Settings::BHop::enabled);

	GetBool(settings["AutoStrafe"]["enabled"], &Settings::AutoStrafe::enabled);
	GetInt(settings["AutoStrafe"]["type"], &Settings::AutoStrafe::type);

	GetBool(settings["Noflash"]["enabled"], &Settings::Noflash::enabled);
	GetFloat(settings["Noflash"]["value"], &Settings::Noflash::value);

	GetBool(settings["Radar"]["enabled"], &Settings::Radar::enabled);

	GetBool(settings["Recoilcrosshair"]["enabled"], &Settings::Recoilcrosshair::enabled);
	GetBool(settings["Recoilcrosshair"]["showOnlyWhenShooting"], &Settings::Recoilcrosshair::showOnlyWhenShooting);

	GetBool(settings["FOVChanger"]["enabled"], &Settings::FOVChanger::enabled);
	GetFloat(settings["FOVChanger"]["value"], &Settings::FOVChanger::value);
	GetBool(settings["FOVChanger"]["viewmodel_enabled"], &Settings::FOVChanger::viewmodel_enabled);
	GetFloat(settings["FOVChanger"]["viewmodel_value"], &Settings::FOVChanger::viewmodel_value);

	GetBool(settings["Airstuck"]["enabled"], &Settings::Airstuck::enabled);
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

	GetBool(settings["Skinchanger"]["enabled"], &Settings::Skinchanger::enabled);

	GetBool(settings["ShowRanks"]["enabled"], &Settings::ShowRanks::enabled);

	GetBool(settings["ShowSpectators"]["enabled"], &Settings::ShowSpectators::enabled);

	GetCString(settings["ClanTagChanger"]["value"], &Settings::ClanTagChanger::value);
	GetBool(settings["ClanTagChanger"]["enabled"], &Settings::ClanTagChanger::enabled);
	GetBool(settings["ClanTagChanger"]["animation"], &Settings::ClanTagChanger::animation);
	GetInt(settings["ClanTagChanger"]["animation_speed"], &Settings::ClanTagChanger::animation_speed);
	GetInt(settings["ClanTagChanger"]["type"], &Settings::ClanTagChanger::type);
	::ClanTagChanger::UpdateClanTagCallback();

	GetBool(settings["View"]["NoPunch"]["enabled"], &Settings::View::NoPunch::enabled);

	GetBool(settings["NameChanger"]["enabled"], &Settings::NameChanger::enabled);
	GetBool(settings["NameChanger"]["last_blank"], &Settings::NameChanger::last_blank);

	GetBool(settings["Teleport"]["enabled"], &Settings::Teleport::enabled);
	GetButtonCode(settings["Teleport"]["key"], &Settings::Teleport::key);

	GetBool(settings["FakeLag"]["enabled"], &Settings::FakeLag::enabled);

	GetBool(settings["AutoAccept"]["enabled"], &Settings::AutoAccept::enabled);

	GetBool(settings["NoSky"]["enabled"], &Settings::NoSky::enabled);
	GetUIColor(settings["NoSky"]["color"], &Settings::NoSky::color);

	GetBool(settings["ASUSWalls"]["enabled"], &Settings::ASUSWalls::enabled);
	GetUIColor(settings["ASUSWalls"]["color"], &Settings::ASUSWalls::color);
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
