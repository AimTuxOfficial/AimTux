#include "settings.h"
#include "interfaces.h"

char* GetSettingsPath(const char* filename)
{
	char* settingsPath;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	asprintf(&settingsPath, "%s/%s.json", cwd, filename);

	return settingsPath;
}

void GetBool(Json::Value &config, bool &setting)
{
	if (config.isNull())
		return;

	setting = config.asBool();
}

void GetCString(Json::Value &config, char* &setting)
{
	if (config.isNull())
		return;

	setting = strdup(config.asCString());
}

void GetString(Json::Value &config, std::string* /* references are for pussies */ setting)
{
	if (config.isNull())
		return;

	*setting = config.asString();
}

template <typename Type>
void GetInt(Json::Value &config, Type &setting)
{
	if (config.isNull())
		return;

	setting = (Type) config.asInt();
}

void GetFloat(Json::Value &config, float &setting)
{
	if (config.isNull())
		return;

	setting = config.asFloat();
}

template <typename Type>
void GetColor(Json::Value &config, Type &setting)
{
	GetInt(config["r"], setting.r);
	GetInt(config["g"], setting.g);
	GetInt(config["b"], setting.b);
	GetInt(config["a"], setting.a);
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

	settings["UI"]["Fonts"]["Title"]["family"] = Settings::UI::Fonts::Title::family;
	settings["UI"]["Fonts"]["Title"]["size"] = Settings::UI::Fonts::Title::size;
	settings["UI"]["Fonts"]["Normal"]["family"] = Settings::UI::Fonts::Normal::family;
	settings["UI"]["Fonts"]["Normal"]["size"] = Settings::UI::Fonts::Normal::size;
	settings["UI"]["Fonts"]["ESP"]["family"] = Settings::UI::Fonts::ESP::family;
	settings["UI"]["Fonts"]["ESP"]["size"] = Settings::UI::Fonts::ESP::size;

	settings["Aimbot"]["enabled"] = Settings::Aimbot::enabled;
	settings["Aimbot"]["silent"] = Settings::Aimbot::silent;
	settings["Aimbot"]["friendly"] = Settings::Aimbot::friendly;
	settings["Aimbot"]["fov"] = Settings::Aimbot::fov;
	settings["Aimbot"]["errorMargin"] = Settings::Aimbot::errorMargin;
	settings["Aimbot"]["bone"] = Settings::Aimbot::bone;
	settings["Aimbot"]["aimkey"] = Settings::Aimbot::aimkey;
	settings["Aimbot"]["Smooth"]["enabled"] = Settings::Aimbot::Smooth::enabled;
	settings["Aimbot"]["Smooth"]["value"] = Settings::Aimbot::Smooth::value;
	settings["Aimbot"]["AutoAim"]["enabled"] = Settings::Aimbot::AutoAim::enabled;
	settings["Aimbot"]["AutoWall"]["enabled"] = Settings::Aimbot::AutoWall::enabled;
	settings["Aimbot"]["AutoWall"]["value"] = Settings::Aimbot::AutoWall::value;
	settings["Aimbot"]["AimStep"]["enabled"] = Settings::Aimbot::AimStep::enabled;
	settings["Aimbot"]["AimStep"]["value"] = Settings::Aimbot::AimStep::value;
	settings["Aimbot"]["RCS"]["enabled"] = Settings::Aimbot::RCS::enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = Settings::Aimbot::AutoShoot::enabled;
	settings["Aimbot"]["AutoShoot"]["autoscope"] = Settings::Aimbot::AutoShoot::autoscope;
	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;
	settings["Aimbot"]["AutoStop"]["enabled"] = Settings::Aimbot::AutoStop::enabled;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Settings::Triggerbot::key;
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
	settings["ESP"]["Bones"]["enabled"] = Settings::ESP::Bones::enabled;
	settings["ESP"]["Bomb"]["enabled"] = Settings::ESP::Bomb::enabled;
	settings["ESP"]["Weapons"]["enabled"] = Settings::ESP::Weapons::enabled;
	settings["ESP"]["FOVCrosshair"]["enabled"] = Settings::ESP::FOVCrosshair::enabled;
	settings["ESP"]["Chams"]["players"] = Settings::ESP::Chams::players;
	settings["ESP"]["Chams"]["visibility_check"] = Settings::ESP::Chams::visibility_check;
	settings["ESP"]["Chams"]["arms"] = Settings::ESP::Chams::arms;
	settings["ESP"]["Chams"]["rainbow_arms"] = Settings::ESP::Chams::rainbow_arms;
	LoadColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::players_ally_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::players_enemy_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::players_enemy_visible_color);
	LoadColor(settings["ESP"]["Chams"]["arms_color"], Settings::ESP::Chams::arms_color);
	settings["ESP"]["Chams"]["type"] = Settings::ESP::Chams::type;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;
	LoadColor(settings["Dlights"]["ally_color"], Settings::Dlights::ally_color);
	LoadColor(settings["Dlights"]["enemy_color"], Settings::Dlights::enemy_color);

	settings["Spammer"]["NormalSpammer"]["enabled"] = Settings::Spammer::NormalSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["message"] = Settings::Spammer::KillSpammer::message;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

	settings["Airstuck"]["enabled"] = Settings::Airstuck::enabled;
	settings["Airstuck"]["key"] = Settings::Airstuck::key;

	settings["Skinchanger"]["enabled"] = Settings::Skinchanger::enabled;
	for (auto i : Settings::Skinchanger::skins)
	{
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["PaintKit"] = i.second.PaintKit;
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["ItemDefinitionIndex"] = i.second.ItemDefinitionIndex;
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["Wear"] = i.second.Wear;
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["StatTrak"] = i.second.StatTrak;
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["CustomName"] = i.second.CustomName;
		settings["Skinchanger"]["skins"][std::to_string(i.first)]["Model"] = i.second.Model;
	}

	settings["ShowRanks"]["enabled"] = Settings::ShowRanks::enabled;

	settings["ShowSpectators"]["enabled"] = Settings::ShowSpectators::enabled;

	settings["ClanTagChanger"]["value"] = Settings::ClanTagChanger::value;
	settings["ClanTagChanger"]["enabled"] = Settings::ClanTagChanger::enabled;
	settings["ClanTagChanger"]["animation"] = Settings::ClanTagChanger::animation;

	std::ofstream(GetSettingsPath(filename)) << styledWriter.write(settings);
}

void Settings::LoadSettings(const char* filename)
{
	if (std::ifstream(GetSettingsPath(filename)).good())
	{
		Json::Value settings;
		std::ifstream config_doc(GetSettingsPath(filename), std::ifstream::binary);
		config_doc >> settings;

		GetCString(settings["UI"]["Fonts"]["Title"]["family"], Settings::UI::Fonts::Title::family);
		GetInt(settings["UI"]["Fonts"]["Title"]["size"], Settings::UI::Fonts::Title::size);
		GetCString(settings["UI"]["Fonts"]["Normal"]["family"], Settings::UI::Fonts::Normal::family);
		GetInt(settings["UI"]["Fonts"]["Normal"]["size"], Settings::UI::Fonts::Normal::size);
		GetCString(settings["UI"]["Fonts"]["ESP"]["family"], Settings::UI::Fonts::ESP::family);
		GetInt(settings["UI"]["Fonts"]["ESP"]["size"], Settings::UI::Fonts::ESP::size);

		title_font = Draw::CreateFont(Settings::UI::Fonts::Title::family, Settings::UI::Fonts::Title::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
		normal_font = Draw::CreateFont(Settings::UI::Fonts::Normal::family, Settings::UI::Fonts::Normal::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
		esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);

		GetBool(settings["Aimbot"]["enabled"], Settings::Aimbot::enabled);
		GetBool(settings["Aimbot"]["silent"], Settings::Aimbot::silent);
		GetBool(settings["Aimbot"]["friendly"], Settings::Aimbot::friendly);
		GetFloat(settings["Aimbot"]["fov"], Settings::Aimbot::fov);
		GetFloat(settings["Aimbot"]["errorMargin"], Settings::Aimbot::errorMargin);
		GetInt(settings["Aimbot"]["bone"], Settings::Aimbot::bone);
		GetInt(settings["Aimbot"]["aimkey"], Settings::Aimbot::aimkey);
		GetBool(settings["Aimbot"]["Smooth"]["enabled"], Settings::Aimbot::Smooth::enabled);
		GetFloat(settings["Aimbot"]["Smooth"]["value"], Settings::Aimbot::Smooth::value);
		GetBool(settings["Aimbot"]["AutoAim"]["enabled"], Settings::Aimbot::AutoAim::enabled);
		GetBool(settings["Aimbot"]["AutoWall"]["enabled"], Settings::Aimbot::AutoWall::enabled);
		GetFloat(settings["Aimbot"]["AutoWall"]["value"], Settings::Aimbot::AutoWall::value);
		GetBool(settings["Aimbot"]["AimStep"]["enabled"], Settings::Aimbot::AimStep::enabled);
		GetFloat(settings["Aimbot"]["AimStep"]["value"], Settings::Aimbot::AimStep::value);
		GetBool(settings["Aimbot"]["RCS"]["enabled"], Settings::Aimbot::RCS::enabled);
		GetBool(settings["Aimbot"]["AutoShoot"]["enabled"], Settings::Aimbot::AutoShoot::enabled);
		GetBool(settings["Aimbot"]["AutoShoot"]["autoscope"], Settings::Aimbot::AutoShoot::autoscope);
		GetBool(settings["Aimbot"]["AutoCrouch"]["enabled"], Settings::Aimbot::AutoCrouch::enabled);
		GetBool(settings["Aimbot"]["AutoStop"]["enabled"], Settings::Aimbot::AutoStop::enabled);

		GetBool(settings["Triggerbot"]["enabled"], Settings::Triggerbot::enabled);
		GetInt(settings["Triggerbot"]["key"], Settings::Triggerbot::key);
		GetBool(settings["Triggerbot"]["Filter"]["friendly"], Settings::Triggerbot::Filter::friendly);
		GetBool(settings["Triggerbot"]["Filter"]["head"], Settings::Triggerbot::Filter::head);
		GetBool(settings["Triggerbot"]["Filter"]["chest"], Settings::Triggerbot::Filter::chest);
		GetBool(settings["Triggerbot"]["Filter"]["stomach"], Settings::Triggerbot::Filter::stomach);
		GetBool(settings["Triggerbot"]["Filter"]["arms"], Settings::Triggerbot::Filter::arms);
		GetBool(settings["Triggerbot"]["Filter"]["legs"], Settings::Triggerbot::Filter::legs);
		GetBool(settings["Triggerbot"]["Delay"]["enabled"], Settings::Triggerbot::Delay::enabled);
		GetFloat(settings["Triggerbot"]["Delay"]["value"], Settings::Triggerbot::Delay::value);

		GetBool(settings["AntiAim"]["enabled_Y"], Settings::AntiAim::enabled_Y);
		GetBool(settings["AntiAim"]["enabled_X"], Settings::AntiAim::enabled_X);
		GetInt(settings["AntiAim"]["type_Y"], Settings::AntiAim::type_Y);
		GetInt(settings["AntiAim"]["type_X"], Settings::AntiAim::type_X);

		GetBool(settings["ESP"]["enabled"], Settings::ESP::enabled);
		GetColor(settings["ESP"]["ally_color"], Settings::ESP::ally_color);
		GetColor(settings["ESP"]["enemy_color"], Settings::ESP::enemy_color);
		GetColor(settings["ESP"]["enemy_visible_color"], Settings::ESP::enemy_visible_color);
		GetColor(settings["ESP"]["bones_color"], Settings::ESP::bones_color);
		GetColor(settings["ESP"]["bomb_color"], Settings::ESP::bomb_color);
		GetBool(settings["ESP"]["visibility_check"], Settings::ESP::visibility_check);
		GetBool(settings["ESP"]["Glow"]["enabled"], Settings::ESP::Glow::enabled);
		GetColor(settings["ESP"]["Glow"]["ally_color"], Settings::ESP::Glow::ally_color);
		GetColor(settings["ESP"]["Glow"]["enemy_color"], Settings::ESP::Glow::enemy_color);
		GetColor(settings["ESP"]["Glow"]["enemy_visible_color"], Settings::ESP::Glow::enemy_visible_color);
		GetColor(settings["ESP"]["Glow"]["weapon_color"], Settings::ESP::Glow::weapon_color);
		GetBool(settings["ESP"]["Tracer"]["enabled"], Settings::ESP::Tracer::enabled);
		GetInt(settings["ESP"]["Tracer"]["type"], Settings::ESP::Tracer::type);
		GetBool(settings["ESP"]["Walls"]["enabled"], Settings::ESP::Walls::enabled);
		GetInt(settings["ESP"]["Walls"]["type"], Settings::ESP::Walls::type);
		GetBool(settings["ESP"]["Info"]["showName"], Settings::ESP::Info::showName);
		GetBool(settings["ESP"]["Info"]["showHealth"], Settings::ESP::Info::showHealth);
		GetBool(settings["ESP"]["Bones"]["enabled"], Settings::ESP::Bones::enabled);
		GetBool(settings["ESP"]["Bomb"]["enabled"], Settings::ESP::Bomb::enabled);
		GetBool(settings["ESP"]["Weapons"]["enabled"], Settings::ESP::Weapons::enabled);
		GetBool(settings["ESP"]["FOVCrosshair"]["enabled"], Settings::ESP::FOVCrosshair::enabled);
		GetBool(settings["ESP"]["Chams"]["players"], Settings::ESP::Chams::players);
		GetBool(settings["ESP"]["Chams"]["visibility_check"], Settings::ESP::Chams::visibility_check);
		GetBool(settings["ESP"]["Chams"]["arms"], Settings::ESP::Chams::arms);
		GetBool(settings["ESP"]["Chams"]["rainbow_arms"], Settings::ESP::Chams::rainbow_arms);
		GetColor(settings["ESP"]["Chams"]["players_ally_color"], Settings::ESP::Chams::players_ally_color);
		GetColor(settings["ESP"]["Chams"]["players_enemy_color"], Settings::ESP::Chams::players_enemy_color);
		GetColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], Settings::ESP::Chams::players_enemy_visible_color);
		GetColor(settings["ESP"]["Chams"]["arms_color"], Settings::ESP::Chams::arms_color);
		GetInt(settings["ESP"]["Chams"]["type"], Settings::ESP::Chams::type);

		GetBool(settings["Dlights"]["enabled"], Settings::Dlights::enabled);
		GetFloat(settings["Dlights"]["radius"], Settings::Dlights::radius);
		GetColor(settings["Dlights"]["ally_color"], Settings::Dlights::ally_color);
		GetColor(settings["Dlights"]["enemy_color"], Settings::Dlights::enemy_color);

		GetBool(settings["Spammer"]["KillSpammer"]["enabled"], Settings::Spammer::KillSpammer::enabled);
		GetCString(settings["Spammer"]["KillSpammer"]["message"], Settings::Spammer::KillSpammer::message);
		GetBool(settings["Spammer"]["NormalSpammer"]["enabled"], Settings::Spammer::NormalSpammer::enabled);

		GetBool(settings["BHop"]["enabled"], Settings::BHop::enabled);

		GetBool(settings["AutoStrafe"]["enabled"], Settings::AutoStrafe::enabled);

		GetBool(settings["Noflash"]["enabled"], Settings::Noflash::enabled);
		GetFloat(settings["Noflash"]["value"], Settings::Noflash::value);

		GetBool(settings["Recoilcrosshair"]["enabled"], Settings::Recoilcrosshair::enabled);

		GetBool(settings["Airstuck"]["enabled"], Settings::Airstuck::enabled);
		GetInt(settings["Airstuck"]["key"], Settings::Airstuck::key);

		Settings::Skinchanger::enabled = false;
		Settings::Skinchanger::skins.clear();

		for (Json::ValueIterator itr = settings["Skinchanger"]["skins"].begin(); itr != settings["Skinchanger"]["skins"].end(); itr++)
		{
			int weaponID = std::stoi(itr.key().asString());
			Settings::Skinchanger::Skin skin = Settings::Skinchanger::Skin(
					settings["Skinchanger"]["skins"][itr.key().asString()]["PaintKit"].asInt(),
					settings["Skinchanger"]["skins"][itr.key().asString()]["ItemDefinitionIndex"].asInt(),
					settings["Skinchanger"]["skins"][itr.key().asString()]["Wear"].asFloat(),
					settings["Skinchanger"]["skins"][itr.key().asString()]["StatTrak"].asInt(),
					settings["Skinchanger"]["skins"][itr.key().asString()]["CustomName"].asString(),
					settings["Skinchanger"]["skins"][itr.key().asString()]["Model"].asString()
			);

			Settings::Skinchanger::skins[weaponID] = skin;
		}

		GetBool(settings["Skinchanger"]["enabled"], Settings::Skinchanger::enabled);

		GetBool(settings["ShowRanks"]["enabled"], Settings::ShowRanks::enabled);

		GetBool(settings["ShowSpectators"]["enabled"], Settings::ShowSpectators::enabled);

		GetString(settings["ClanTagChanger"]["value"], &Settings::ClanTagChanger::value);
		GetBool(settings["ClanTagChanger"]["enabled"], Settings::ClanTagChanger::enabled);
		GetBool(settings["ClanTagChanger"]["animation"], Settings::ClanTagChanger::animation);
	}
	else
	{
		Settings::LoadDefaultsOrSave(filename);
		Settings::LoadSettings(filename);
	}
}
