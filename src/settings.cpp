#include "settings.h"

char* GetSettingsPath(const char* filename)
{
	char* settingsPath;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	asprintf(&settingsPath, "%s/%s.json", cwd, filename);

	return settingsPath;
}

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

void LoadColor(Json::Value &config, Color color)
{
	config["r"] = color.r;
	config["g"] = color.g;
	config["b"] = color.b;
	config["a"] = color.a;
}

void Settings::LoadDefaultsOrSave(const char* filename)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	LoadColor(settings["UI"]["mainColor"], Settings::UI::mainColor);
	settings["UI"]["Fonts"]["Title"]["family"] = Settings::UI::Fonts::Title::family;
	settings["UI"]["Fonts"]["Title"]["size"] = Settings::UI::Fonts::Title::size;
	settings["UI"]["Fonts"]["Title"]["flags"] = Settings::UI::Fonts::Title::flags;
	settings["UI"]["Fonts"]["Normal"]["family"] = Settings::UI::Fonts::Normal::family;
	settings["UI"]["Fonts"]["Normal"]["size"] = Settings::UI::Fonts::Normal::size;
	settings["UI"]["Fonts"]["Normal"]["flags"] = Settings::UI::Fonts::Normal::flags;
	settings["UI"]["Fonts"]["ESP"]["family"] = Settings::UI::Fonts::ESP::family;
	settings["UI"]["Fonts"]["ESP"]["size"] = Settings::UI::Fonts::ESP::size;
	settings["UI"]["Fonts"]["ESP"]["flags"] = Settings::UI::Fonts::ESP::flags;
	settings["UI"]["Fonts"]["Mono"]["family"] = Settings::UI::Fonts::Mono::family;
	settings["UI"]["Fonts"]["Mono"]["size"] = Settings::UI::Fonts::Mono::size;
	settings["UI"]["Fonts"]["Mono"]["flags"] = Settings::UI::Fonts::Mono::flags;

	settings["Aimbot"]["enabled"] = Settings::Aimbot::enabled;
	settings["Aimbot"]["silent"] = Settings::Aimbot::silent;
	settings["Aimbot"]["friendly"] = Settings::Aimbot::friendly;
	settings["Aimbot"]["fov"] = Settings::Aimbot::fov;
	settings["Aimbot"]["errorMargin"] = Settings::Aimbot::errorMargin;
	settings["Aimbot"]["bone"] = Settings::Aimbot::bone;
	settings["Aimbot"]["aimkey"] = Util::GetButtonName(Settings::Aimbot::aimkey);
	settings["Aimbot"]["aimkey_only"] = Settings::Aimbot::aimkey_only;
	settings["Aimbot"]["Smooth"]["enabled"] = Settings::Aimbot::Smooth::enabled;
	settings["Aimbot"]["Smooth"]["value"] = Settings::Aimbot::Smooth::value;
	settings["Aimbot"]["Smooth"]["Salting"]["enabled"] = Settings::Aimbot::Smooth::Salting::enabled;
	settings["Aimbot"]["Smooth"]["Salting"]["percentage"] = Settings::Aimbot::Smooth::Salting::percentage;
	settings["Aimbot"]["AutoAim"]["enabled"] = Settings::Aimbot::AutoAim::enabled;
	settings["Aimbot"]["AutoWall"]["enabled"] = Settings::Aimbot::AutoWall::enabled;
	settings["Aimbot"]["AutoWall"]["value"] = Settings::Aimbot::AutoWall::value;
	settings["Aimbot"]["AutoWall"]["bones"] = Json::Value(Json::arrayValue);
	for (auto bone : Settings::Aimbot::AutoWall::bones)
		settings["Aimbot"]["AutoWall"]["bones"].append(bone);
	settings["Aimbot"]["AimStep"]["enabled"] = Settings::Aimbot::AimStep::enabled;
	settings["Aimbot"]["AimStep"]["value"] = Settings::Aimbot::AimStep::value;
	settings["Aimbot"]["RCS"]["enabled"] = Settings::Aimbot::RCS::enabled;
	settings["Aimbot"]["RCS"]["value"] = Settings::Aimbot::RCS::value;
	settings["Aimbot"]["AutoPistol"]["enabled"] = Settings::Aimbot::AutoPistol::enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = Settings::Aimbot::AutoShoot::enabled;
	settings["Aimbot"]["AutoShoot"]["autoscope"] = Settings::Aimbot::AutoShoot::autoscope;
	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;
	settings["Aimbot"]["AutoStop"]["enabled"] = Settings::Aimbot::AutoStop::enabled;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Util::GetButtonName(Settings::Triggerbot::key);
	settings["Triggerbot"]["Filter"]["friendly"] = Settings::Triggerbot::Filter::friendly;
	settings["Triggerbot"]["Filter"]["head"] = Settings::Triggerbot::Filter::head;
	settings["Triggerbot"]["Filter"]["chest"] = Settings::Triggerbot::Filter::chest;
	settings["Triggerbot"]["Filter"]["stomach"] = Settings::Triggerbot::Filter::stomach;
	settings["Triggerbot"]["Filter"]["arms"] = Settings::Triggerbot::Filter::arms;
	settings["Triggerbot"]["Filter"]["legs"] = Settings::Triggerbot::Filter::legs;
	settings["Triggerbot"]["Delay"]["enabled"] = Settings::Triggerbot::Delay::enabled;
	settings["Triggerbot"]["Delay"]["value"] = Settings::Triggerbot::Delay::value;

	settings["AntiAim"]["enabled_Y"] = Settings::AntiAim::enabled_Y;
	settings["AntiAim"]["enabled_X"] = Settings::AntiAim::enabled_X;
	settings["AntiAim"]["type_Y"] = Settings::AntiAim::type_Y;
	settings["AntiAim"]["type_X"] = Settings::AntiAim::type_X;

	settings["ESP"]["enabled"] = Settings::ESP::enabled;

	LoadColor(settings["ESP"]["ally_color"], Settings::ESP::ally_color);
	LoadColor(settings["ESP"]["enemy_color"], Settings::ESP::enemy_color);
	LoadColor(settings["ESP"]["enemy_visible_color"], Settings::ESP::enemy_visible_color);
	LoadColor(settings["ESP"]["bones_color"], Settings::ESP::bones_color);
	LoadColor(settings["ESP"]["bomb_color"], Settings::ESP::bomb_color);
	settings["ESP"]["visibility_check"] = Settings::ESP::visibility_check;
	settings["ESP"]["friendly"] = Settings::ESP::friendly;
	settings["ESP"]["Glow"]["enabled"] = Settings::ESP::Glow::enabled;
	LoadColor(settings["ESP"]["Glow"]["ally_color"], Settings::ESP::Glow::ally_color);
	LoadColor(settings["ESP"]["Glow"]["enemy_color"], Settings::ESP::Glow::enemy_color);
	LoadColor(settings["ESP"]["Glow"]["enemy_visible_color"], Settings::ESP::Glow::enemy_visible_color);
	LoadColor(settings["ESP"]["Glow"]["weapon_color"], Settings::ESP::Glow::weapon_color);
	settings["ESP"]["Tracer"]["enabled"] = Settings::ESP::Tracer::enabled;
	settings["ESP"]["Tracer"]["type"] = Settings::ESP::Tracer::type;
	settings["ESP"]["Walls"]["enabled"] = Settings::ESP::Walls::enabled;
	settings["ESP"]["Walls"]["type"] = Settings::ESP::Walls::type;
	settings["ESP"]["Info"]["showName"] = Settings::ESP::Info::showName;
	settings["ESP"]["Info"]["showHealth"] = Settings::ESP::Info::showHealth;
	settings["ESP"]["Info"]["showWeapon"] = Settings::ESP::Info::showWeapon;
	settings["ESP"]["Info"]["colorCode"] = Settings::ESP::Info::colorCode;
	LoadColor(settings["ESP"]["Info"]["ally_color"], Settings::ESP::Info::ally_color);
	LoadColor(settings["ESP"]["Info"]["enemy_color"], Settings::ESP::Info::enemy_color);
	LoadColor(settings["ESP"]["Info"]["enemy_visible_color"], Settings::ESP::Info::enemy_visible_color);
	settings["ESP"]["Bones"]["enabled"] = Settings::ESP::Bones::enabled;
	settings["ESP"]["Bomb"]["enabled"] = Settings::ESP::Bomb::enabled;
	settings["ESP"]["Weapons"]["enabled"] = Settings::ESP::Weapons::enabled;
	settings["ESP"]["FOVCrosshair"]["enabled"] = Settings::ESP::FOVCrosshair::enabled;
	settings["ESP"]["Chams"]["players"] = Settings::ESP::Chams::players;
	settings["ESP"]["Chams"]["visibility_check"] = Settings::ESP::Chams::visibility_check;
	settings["ESP"]["Chams"]["Arms"]["enabled"] = Settings::ESP::Chams::Arms::enabled;
	settings["ESP"]["Chams"]["Arms"]["type"] = Settings::ESP::Chams::Arms::type;
	LoadColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::players_ally_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::players_enemy_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::players_enemy_visible_color);
	LoadColor(settings["ESP"]["Chams"]["Arms"]["color"], Settings::ESP::Chams::Arms::color);
	settings["ESP"]["Chams"]["type"] = Settings::ESP::Chams::type;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;
	LoadColor(settings["Dlights"]["ally_color"], Settings::Dlights::ally_color);
	LoadColor(settings["Dlights"]["enemy_color"], Settings::Dlights::enemy_color);

	settings["Spammer"]["PositionSpammer"]["enabled"] = Settings::Spammer::PositionSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["message"] = Settings::Spammer::KillSpammer::message;
	settings["Spammer"]["NormalSpammer"]["enabled"] = Settings::Spammer::NormalSpammer::enabled;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Radar"]["enabled"] = Settings::Radar::enabled;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

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

	settings["View"]["NoPunch"]["enabled"] = Settings::View::NoPunch::enabled;

	settings["NameChanger"]["enabled"] = Settings::NameChanger::enabled;
	settings["NameChanger"]["last_blank"] = Settings::NameChanger::last_blank;

	settings["Teleport"]["enabled"] = Settings::Teleport::enabled;
	settings["Teleport"]["key"] = Settings::Teleport::key;

	settings["FakeLag"]["enabled"] = Settings::FakeLag::enabled;

	std::ofstream(GetSettingsPath(filename)) << styledWriter.write(settings);
}

void Settings::LoadSettings(const char* filename)
{
	if (!std::ifstream(GetSettingsPath(filename)).good())
	{
		Settings::LoadDefaultsOrSave(filename);
		return;
	}

	Json::Value settings;
	std::ifstream config_doc(GetSettingsPath(filename), std::ifstream::binary);
	config_doc >> settings;

	GetColor(settings["UI"]["mainColor"], &Settings::UI::mainColor);
	GetCString(settings["UI"]["Fonts"]["Title"]["family"], &Settings::UI::Fonts::Title::family);
	GetInt(settings["UI"]["Fonts"]["Title"]["size"], &Settings::UI::Fonts::Title::size);
	GetInt(settings["UI"]["Fonts"]["Title"]["flags"], &Settings::UI::Fonts::Title::flags);
	GetCString(settings["UI"]["Fonts"]["Normal"]["family"], &Settings::UI::Fonts::Normal::family);
	GetInt(settings["UI"]["Fonts"]["Normal"]["size"], &Settings::UI::Fonts::Normal::size);
	GetInt(settings["UI"]["Fonts"]["Normal"]["flags"], &Settings::UI::Fonts::Normal::flags);
	GetCString(settings["UI"]["Fonts"]["ESP"]["family"], &Settings::UI::Fonts::ESP::family);
	GetInt(settings["UI"]["Fonts"]["ESP"]["size"], &Settings::UI::Fonts::ESP::size);
	GetInt(settings["UI"]["Fonts"]["ESP"]["flags"], &Settings::UI::Fonts::ESP::flags);
	GetCString(settings["UI"]["Fonts"]["Mono"]["family"], &Settings::UI::Fonts::Mono::family);
	GetInt(settings["UI"]["Fonts"]["Mono"]["size"], &Settings::UI::Fonts::Mono::size);
	GetInt(settings["UI"]["Fonts"]["Mono"]["flags"], &Settings::UI::Fonts::Mono::flags);

	Fonts::SetupFonts();

	GetBool(settings["Aimbot"]["enabled"], &Settings::Aimbot::enabled);
	GetBool(settings["Aimbot"]["silent"], &Settings::Aimbot::silent);
	GetBool(settings["Aimbot"]["friendly"], &Settings::Aimbot::friendly);
	GetFloat(settings["Aimbot"]["fov"], &Settings::Aimbot::fov);
	GetFloat(settings["Aimbot"]["errorMargin"], &Settings::Aimbot::errorMargin);
	GetInt(settings["Aimbot"]["bone"], &Settings::Aimbot::bone);
	GetButtonCode(settings["Aimbot"]["aimkey"], &Settings::Aimbot::aimkey);
	GetBool(settings["Aimbot"]["aimkey_only"], &Settings::Aimbot::aimkey_only);
	GetBool(settings["Aimbot"]["Smooth"]["enabled"], &Settings::Aimbot::Smooth::enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["value"], &Settings::Aimbot::Smooth::value);
	GetBool(settings["Aimbot"]["Smooth"]["Salting"]["enabled"], &Settings::Aimbot::Smooth::Salting::enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["Salting"]["percentage"], &Settings::Aimbot::Smooth::Salting::percentage);
	GetBool(settings["Aimbot"]["AutoAim"]["enabled"], &Settings::Aimbot::AutoAim::enabled);
	GetBool(settings["Aimbot"]["AutoWall"]["enabled"], &Settings::Aimbot::AutoWall::enabled);
	GetFloat(settings["Aimbot"]["AutoWall"]["value"], &Settings::Aimbot::AutoWall::value);
	Settings::Aimbot::AutoWall::bones.clear();
	for (Json::ValueIterator itr = settings["Aimbot"]["AutoWall"]["bones"].begin(); itr != settings["Aimbot"]["AutoWall"]["bones"].end(); itr++)
		Settings::Aimbot::AutoWall::bones.push_back((Hitbox) settings["Aimbot"]["AutoWall"]["bones"][itr.index()].asInt());
	GetBool(settings["Aimbot"]["AimStep"]["enabled"], &Settings::Aimbot::AimStep::enabled);
	GetFloat(settings["Aimbot"]["AimStep"]["value"], &Settings::Aimbot::AimStep::value);
	GetBool(settings["Aimbot"]["RCS"]["enabled"], &Settings::Aimbot::RCS::enabled);
	GetFloat(settings["Aimbot"]["RCS"]["value"], &Settings::Aimbot::RCS::value);
	GetBool(settings["Aimbot"]["AutoPistol"]["enabled"], &Settings::Aimbot::AutoPistol::enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["enabled"], &Settings::Aimbot::AutoShoot::enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["autoscope"], &Settings::Aimbot::AutoShoot::autoscope);
	GetBool(settings["Aimbot"]["AutoCrouch"]["enabled"], &Settings::Aimbot::AutoCrouch::enabled);
	GetBool(settings["Aimbot"]["AutoStop"]["enabled"], &Settings::Aimbot::AutoStop::enabled);

	GetBool(settings["Triggerbot"]["enabled"], &Settings::Triggerbot::enabled);
	GetButtonCode(settings["Triggerbot"]["key"], &Settings::Triggerbot::key);
	GetBool(settings["Triggerbot"]["Filter"]["friendly"], &Settings::Triggerbot::Filter::friendly);
	GetBool(settings["Triggerbot"]["Filter"]["head"], &Settings::Triggerbot::Filter::head);
	GetBool(settings["Triggerbot"]["Filter"]["chest"], &Settings::Triggerbot::Filter::chest);
	GetBool(settings["Triggerbot"]["Filter"]["stomach"], &Settings::Triggerbot::Filter::stomach);
	GetBool(settings["Triggerbot"]["Filter"]["arms"], &Settings::Triggerbot::Filter::arms);
	GetBool(settings["Triggerbot"]["Filter"]["legs"], &Settings::Triggerbot::Filter::legs);
	GetBool(settings["Triggerbot"]["Delay"]["enabled"], &Settings::Triggerbot::Delay::enabled);
	GetInt(settings["Triggerbot"]["Delay"]["value"], &Settings::Triggerbot::Delay::value);

	GetBool(settings["AntiAim"]["enabled_Y"], &Settings::AntiAim::enabled_Y);
	GetBool(settings["AntiAim"]["enabled_X"], &Settings::AntiAim::enabled_X);
	GetInt(settings["AntiAim"]["type_Y"], &Settings::AntiAim::type_Y);
	GetInt(settings["AntiAim"]["type_X"], &Settings::AntiAim::type_X);

	GetBool(settings["ESP"]["enabled"], &Settings::ESP::enabled);
	GetColor(settings["ESP"]["ally_color"], &Settings::ESP::ally_color);
	GetColor(settings["ESP"]["enemy_color"], &Settings::ESP::enemy_color);
	GetColor(settings["ESP"]["enemy_visible_color"], &Settings::ESP::enemy_visible_color);
	GetColor(settings["ESP"]["bones_color"], &Settings::ESP::bones_color);
	GetColor(settings["ESP"]["bomb_color"], &Settings::ESP::bomb_color);
	GetBool(settings["ESP"]["visibility_check"], &Settings::ESP::visibility_check);
	GetBool(settings["ESP"]["friendly"], &Settings::ESP::friendly);
	GetBool(settings["ESP"]["Glow"]["enabled"], &Settings::ESP::Glow::enabled);
	GetColor(settings["ESP"]["Glow"]["ally_color"], &Settings::ESP::Glow::ally_color);
	GetColor(settings["ESP"]["Glow"]["enemy_color"], &Settings::ESP::Glow::enemy_color);
	GetColor(settings["ESP"]["Glow"]["enemy_visible_color"], &Settings::ESP::Glow::enemy_visible_color);
	GetColor(settings["ESP"]["Glow"]["weapon_color"], &Settings::ESP::Glow::weapon_color);
	GetBool(settings["ESP"]["Tracer"]["enabled"], &Settings::ESP::Tracer::enabled);
	GetInt(settings["ESP"]["Tracer"]["type"], &Settings::ESP::Tracer::type);
	GetBool(settings["ESP"]["Walls"]["enabled"], &Settings::ESP::Walls::enabled);
	GetInt(settings["ESP"]["Walls"]["type"], &Settings::ESP::Walls::type);
	GetBool(settings["ESP"]["Info"]["showName"], &Settings::ESP::Info::showName);
	GetBool(settings["ESP"]["Info"]["showHealth"], &Settings::ESP::Info::showHealth);
	GetBool(settings["ESP"]["Info"]["showWeapon"], &Settings::ESP::Info::showWeapon);
	GetBool(settings["ESP"]["Info"]["colorCode"], &Settings::ESP::Info::colorCode);
	GetColor(settings["ESP"]["Info"]["ally_color"], &Settings::ESP::Info::ally_color);
	GetColor(settings["ESP"]["Info"]["enemy_color"], &Settings::ESP::Info::enemy_color);
	GetColor(settings["ESP"]["Info"]["enemy_visible_color"], &Settings::ESP::Info::enemy_visible_color);
	GetBool(settings["ESP"]["Bones"]["enabled"], &Settings::ESP::Bones::enabled);
	GetBool(settings["ESP"]["Bomb"]["enabled"], &Settings::ESP::Bomb::enabled);
	GetBool(settings["ESP"]["Weapons"]["enabled"], &Settings::ESP::Weapons::enabled);
	GetBool(settings["ESP"]["FOVCrosshair"]["enabled"], &Settings::ESP::FOVCrosshair::enabled);
	GetBool(settings["ESP"]["Chams"]["players"], &Settings::ESP::Chams::players);
	GetBool(settings["ESP"]["Chams"]["visibility_check"], &Settings::ESP::Chams::visibility_check);
	GetBool(settings["ESP"]["Chams"]["Arms"]["enabled"], &Settings::ESP::Chams::Arms::enabled);
	GetInt(settings["ESP"]["Chams"]["Arms"]["type"], &Settings::ESP::Chams::Arms::type);
	GetColor(settings["ESP"]["Chams"]["players_ally_color"], &Settings::ESP::Chams::players_ally_color);
	GetColor(settings["ESP"]["Chams"]["players_enemy_color"], &Settings::ESP::Chams::players_enemy_color);
	GetColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], &Settings::ESP::Chams::players_enemy_visible_color);
	GetColor(settings["ESP"]["Chams"]["Arms"]["color"], &Settings::ESP::Chams::Arms::color);
	GetInt(settings["ESP"]["Chams"]["type"], &Settings::ESP::Chams::type);

	GetBool(settings["Dlights"]["enabled"], &Settings::Dlights::enabled);
	GetFloat(settings["Dlights"]["radius"], &Settings::Dlights::radius);
	GetColor(settings["Dlights"]["ally_color"], &Settings::Dlights::ally_color);
	GetColor(settings["Dlights"]["enemy_color"], &Settings::Dlights::enemy_color);

	GetBool(settings["Spammer"]["PositionSpammer"]["enabled"], &Settings::Spammer::PositionSpammer::enabled);
	GetBool(settings["Spammer"]["KillSpammer"]["enabled"], &Settings::Spammer::KillSpammer::enabled);
	GetCString(settings["Spammer"]["KillSpammer"]["message"], &Settings::Spammer::KillSpammer::message);
	GetBool(settings["Spammer"]["NormalSpammer"]["enabled"], &Settings::Spammer::NormalSpammer::enabled);

	GetBool(settings["BHop"]["enabled"], &Settings::BHop::enabled);

	GetBool(settings["AutoStrafe"]["enabled"], &Settings::AutoStrafe::enabled);

	GetBool(settings["Noflash"]["enabled"], &Settings::Noflash::enabled);
	GetFloat(settings["Noflash"]["value"], &Settings::Noflash::value);

	GetBool(settings["Radar"]["enabled"], &Settings::Radar::enabled);

	GetBool(settings["Recoilcrosshair"]["enabled"], &Settings::Recoilcrosshair::enabled);

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

	GetString(settings["ClanTagChanger"]["value"], &Settings::ClanTagChanger::value);
	GetBool(settings["ClanTagChanger"]["enabled"], &Settings::ClanTagChanger::enabled);
	GetBool(settings["ClanTagChanger"]["animation"], &Settings::ClanTagChanger::animation);

	GetBool(settings["View"]["NoPunch"]["enabled"], &Settings::View::NoPunch::enabled);

	GetBool(settings["NameChanger"]["enabled"], &Settings::NameChanger::enabled);
	GetBool(settings["NameChanger"]["last_blank"], &Settings::NameChanger::last_blank);

	GetBool(settings["Teleport"]["enabled"], &Settings::Teleport::enabled);
	GetButtonCode(settings["Teleport"]["key"], &Settings::Teleport::key);

	GetBool(settings["FakeLag"]["enabled"], &Settings::FakeLag::enabled);
}
