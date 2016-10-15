#include "settings.h"

char* GetSettingsPath(const char* filename)
{
	char* settingsPath;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	asprintf(&settingsPath, "%s/%s.json", cwd, filename);

	return settingsPath;
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
	settings["Aimbot"]["fov"] = Settings::Aimbot::fov;
	settings["Aimbot"]["bone"] = Settings::Aimbot::bone;
	settings["Aimbot"]["aimkey"] = Settings::Aimbot::aimkey;
	settings["Aimbot"]["Smooth"]["enabled"] = Settings::Aimbot::Smooth::enabled;
	settings["Aimbot"]["Smooth"]["value"] = Settings::Aimbot::Smooth::value;
	settings["Aimbot"]["AutoAim"]["enabled"] = Settings::Aimbot::AutoAim::enabled;
	settings["Aimbot"]["AimStep"]["enabled"] = Settings::Aimbot::AimStep::enabled;
	settings["Aimbot"]["AimStep"]["value"] = Settings::Aimbot::AimStep::value;
	settings["Aimbot"]["RCS"]["enabled"] = Settings::Aimbot::RCS::enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = Settings::Aimbot::AutoShoot::enabled;
	settings["Aimbot"]["AutoShoot"]["autoscope"] = Settings::Aimbot::AutoShoot::autoscope;
	settings["Aimbot"]["AutoCrouch"]["enabled"] = Settings::Aimbot::AutoCrouch::enabled;
	settings["Aimbot"]["AutoStop"]["enabled"] = Settings::Aimbot::AutoStop::enabled;

	settings["Triggerbot"]["enabled"] = Settings::Triggerbot::enabled;
	settings["Triggerbot"]["key"] = Settings::Triggerbot::key;
	settings["Triggerbot"]["Hitchance"]["enabled"] = Settings::Triggerbot::Hitchance::enabled;
	settings["Triggerbot"]["Hitchance"]["value"] = Settings::Triggerbot::Hitchance::value;

	settings["AntiAim"]["enabled_Y"] = Settings::AntiAim::enabled_Y;
	settings["AntiAim"]["enabled_X"] = Settings::AntiAim::enabled_X;
	settings["AntiAim"]["type_Y"] = Settings::AntiAim::type_X;
	settings["AntiAim"]["type_X"] = Settings::AntiAim::type_X;

	settings["ESP"]["enabled"] = Settings::ESP::enabled;
	settings["ESP"]["ally_color"]["r"] = Settings::ESP::ally_color.r;
	settings["ESP"]["ally_color"]["g"] = Settings::ESP::ally_color.g;
	settings["ESP"]["ally_color"]["b"] = Settings::ESP::ally_color.b;
	settings["ESP"]["enemy_color"]["r"] = Settings::ESP::enemy_color.r;
	settings["ESP"]["enemy_color"]["g"] = Settings::ESP::enemy_color.g;
	settings["ESP"]["enemy_color"]["b"] = Settings::ESP::enemy_color.b;
	settings["ESP"]["enemy_visible_color"]["r"] = Settings::ESP::enemy_visible_color.r;
	settings["ESP"]["enemy_visible_color"]["g"] = Settings::ESP::enemy_visible_color.g;
	settings["ESP"]["enemy_visible_color"]["b"] = Settings::ESP::enemy_visible_color.b;
	settings["ESP"]["bones_color"]["r"] = Settings::ESP::bones_color.r;
	settings["ESP"]["bones_color"]["g"] = Settings::ESP::bones_color.g;
	settings["ESP"]["bones_color"]["b"] = Settings::ESP::bones_color.b;
	settings["ESP"]["bomb_color"]["r"] = Settings::ESP::bomb_color.r;
	settings["ESP"]["bomb_color"]["g"] = Settings::ESP::bomb_color.g;
	settings["ESP"]["bomb_color"]["b"] = Settings::ESP::bomb_color.b;
	settings["ESP"]["visibility_check"] = Settings::ESP::visibility_check;
	settings["ESP"]["Walls"]["enabled"] = Settings::ESP::Walls::enabled;
	settings["ESP"]["Walls"]["type"] = Settings::ESP::Walls::type;
	settings["ESP"]["Info"]["showName"] = Settings::ESP::Info::showName;
	settings["ESP"]["Info"]["showHealth"] = Settings::ESP::Info::showHealth;
	settings["ESP"]["Bones"]["enabled"] = Settings::ESP::Bones::enabled;
	settings["ESP"]["Bomb"]["enabled"] = Settings::ESP::Bomb::enabled;
	settings["ESP"]["Weapons"]["enabled"] = Settings::ESP::Weapons::enabled;
	settings["ESP"]["Tracer"]["enabled"] = Settings::ESP::Tracer::enabled;
	settings["ESP"]["Tracer"]["type"] = Settings::ESP::Tracer::type;
	settings["ESP"]["FOVCrosshair"]["enabled"] = Settings::ESP::FOVCrosshair::enabled;
	settings["ESP"]["Chams"]["players"] = Settings::ESP::Chams::players;
	settings["ESP"]["Chams"]["visibility_check"] = Settings::ESP::Chams::visibility_check;
	settings["ESP"]["Chams"]["arms"] = Settings::ESP::Chams::arms;
	settings["ESP"]["Chams"]["rainbow_arms"] = Settings::ESP::Chams::rainbow_arms;
	settings["ESP"]["Chams"]["players_ally_color"]["r"] = Settings::ESP::Chams::players_ally_color.r;
	settings["ESP"]["Chams"]["players_ally_color"]["g"] = Settings::ESP::Chams::players_ally_color.g;
	settings["ESP"]["Chams"]["players_ally_color"]["b"] = Settings::ESP::Chams::players_ally_color.b;
	settings["ESP"]["Chams"]["players_enemy_color"]["r"] = Settings::ESP::Chams::players_enemy_color.r;
	settings["ESP"]["Chams"]["players_enemy_color"]["g"] = Settings::ESP::Chams::players_enemy_color.g;
	settings["ESP"]["Chams"]["players_enemy_color"]["b"] = Settings::ESP::Chams::players_enemy_color.b;
	settings["ESP"]["Chams"]["players_enemy_visible_color"]["r"] = Settings::ESP::Chams::players_enemy_visible_color.r;
	settings["ESP"]["Chams"]["players_enemy_visible_color"]["g"] = Settings::ESP::Chams::players_enemy_visible_color.g;
	settings["ESP"]["Chams"]["players_enemy_visible_color"]["b"] = Settings::ESP::Chams::players_enemy_visible_color.b;
	settings["ESP"]["Chams"]["arms_color"]["r"] = Settings::ESP::Chams::arms_color.r;
	settings["ESP"]["Chams"]["arms_color"]["g"] = Settings::ESP::Chams::arms_color.g;
	settings["ESP"]["Chams"]["arms_color"]["b"] = Settings::ESP::Chams::arms_color.b;
	settings["ESP"]["Chams"]["type"] = Settings::ESP::Chams::type;

	settings["Dlights"]["enabled"] = Settings::Dlights::enabled;
	settings["Dlights"]["radius"] = Settings::Dlights::radius;
	settings["Dlights"]["ally_color"]["r"] = Settings::Dlights::ally_color.r;
	settings["Dlights"]["ally_color"]["g"] = Settings::Dlights::ally_color.g;
	settings["Dlights"]["ally_color"]["b"] = Settings::Dlights::ally_color.b;
	settings["Dlights"]["enemy_color"]["r"] = Settings::Dlights::enemy_color.r;
	settings["Dlights"]["enemy_color"]["g"] = Settings::Dlights::enemy_color.g;
	settings["Dlights"]["enemy_color"]["b"] = Settings::Dlights::enemy_color.b;

	settings["Spammer"]["NormalSpammer"]["enabled"] = Settings::Spammer::NormalSpammer::enabled;
	settings["Spammer"]["KillSpammer"]["enabled"] = Settings::Spammer::KillSpammer::enabled;

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

	std::ofstream(GetSettingsPath(filename)) << styledWriter.write(settings);
}

void Settings::LoadSettings(const char* filename)
{
	if (std::ifstream(GetSettingsPath(filename)).good())
	{
		Json::Value settings;
		std::ifstream config_doc(GetSettingsPath(filename), std::ifstream::binary);
		config_doc >> settings;

		strcpy(Settings::UI::Fonts::Title::family, settings["UI"]["Fonts"]["Title"]["family"].asCString());
		Settings::UI::Fonts::Title::size = settings["UI"]["Fonts"]["Title"]["size"].asInt();
		strcpy(Settings::UI::Fonts::Normal::family, settings["UI"]["Fonts"]["Normal"]["family"].asCString());
		Settings::UI::Fonts::Normal::size = settings["UI"]["Fonts"]["Normal"]["size"].asInt();
		strcpy(Settings::UI::Fonts::ESP::family, settings["UI"]["Fonts"]["ESP"]["family"].asCString());
		Settings::UI::Fonts::ESP::size = settings["UI"]["Fonts"]["ESP"]["size"].asInt();

		title_font = Draw::CreateFont(Settings::UI::Fonts::Title::family, Settings::UI::Fonts::Title::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
		normal_font = Draw::CreateFont(Settings::UI::Fonts::Normal::family, Settings::UI::Fonts::Normal::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
		esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);

		Settings::Aimbot::enabled = settings["Aimbot"]["enabled"].asBool();
		Settings::Aimbot::silent = settings["Aimbot"]["silent"].asBool();
		Settings::Aimbot::fov = settings["Aimbot"]["fov"].asFloat();
		Settings::Aimbot::bone = settings["Aimbot"]["bone"].asInt();
		Settings::Aimbot::aimkey = (ButtonCode_t) settings["Aimbot"]["aimkey"].asInt();
		Settings::Aimbot::Smooth::enabled = settings["Aimbot"]["Smooth"]["enabled"].asBool();
		Settings::Aimbot::Smooth::value = settings["Aimbot"]["Smooth"]["value"].asFloat();
		Settings::Aimbot::AutoAim::enabled = settings["Aimbot"]["AutoAim"]["enabled"].asBool();
		Settings::Aimbot::AimStep::enabled = settings["Aimbot"]["AimStep"]["enabled"].asBool();
		Settings::Aimbot::AimStep::value = settings["Aimbot"]["AimStep"]["value"].asFloat();
		Settings::Aimbot::RCS::enabled = settings["Aimbot"]["RCS"]["enabled"].asBool();
		Settings::Aimbot::AutoShoot::enabled = settings["Aimbot"]["AutoShoot"]["enabled"].asBool();
		Settings::Aimbot::AutoShoot::autoscope = settings["Aimbot"]["AutoShoot"]["autoscope"].asBool();
		Settings::Aimbot::AutoCrouch::enabled = settings["Aimbot"]["AutoCrouch"]["enabled"].asBool();
		Settings::Aimbot::AutoStop::enabled = settings["Aimbot"]["AutoStop"]["enabled"].asBool();

		Settings::Triggerbot::enabled = settings["Triggerbot"]["enabled"].asBool();
		Settings::Triggerbot::key = (ButtonCode_t) settings["Triggerbot"]["key"].asInt();
		Settings::Triggerbot::Hitchance::enabled = settings["Triggerbot"]["Hitchance"]["enabled"].asBool();
		Settings::Triggerbot::Hitchance::value = settings["Triggerbot"]["Hitchance"]["value"].asFloat();

		Settings::AntiAim::enabled_Y = settings["AntiAim"]["enabled_Y"].asBool();
		Settings::AntiAim::enabled_X = settings["AntiAim"]["enabled_X"].asBool();
		Settings::AntiAim::type_Y = (AntiAimType_Y) settings["AntiAim"]["type_Y"].asInt();
		Settings::AntiAim::type_X = (AntiAimType_X) settings["AntiAim"]["type_Y"].asInt();

		Settings::ESP::enabled = settings["ESP"]["enabled"].asBool();
		Settings::ESP::ally_color.r = settings["ESP"]["ally_color"]["r"].asInt();
		Settings::ESP::ally_color.g = settings["ESP"]["ally_color"]["g"].asInt();
		Settings::ESP::ally_color.b = settings["ESP"]["ally_color"]["b"].asInt();
		Settings::ESP::enemy_color.r = settings["ESP"]["enemy_color"]["r"].asInt();
		Settings::ESP::enemy_color.g = settings["ESP"]["enemy_color"]["g"].asInt();
		Settings::ESP::enemy_color.b = settings["ESP"]["enemy_color"]["b"].asInt();
		Settings::ESP::enemy_visible_color.r = settings["ESP"]["enemy_visible_color"]["r"].asInt();
		Settings::ESP::enemy_visible_color.g = settings["ESP"]["enemy_visible_color"]["g"].asInt();
		Settings::ESP::enemy_visible_color.b = settings["ESP"]["enemy_visible_color"]["b"].asInt();
		Settings::ESP::bones_color.r = settings["ESP"]["bones_color"]["r"].asInt();
		Settings::ESP::bones_color.g = settings["ESP"]["bones_color"]["g"].asInt();
		Settings::ESP::bones_color.b = settings["ESP"]["bones_color"]["b"].asInt();
		Settings::ESP::bomb_color.r = settings["ESP"]["bomb_color"]["r"].asInt();
		Settings::ESP::bomb_color.g = settings["ESP"]["bomb_color"]["g"].asInt();
		Settings::ESP::bomb_color.b = settings["ESP"]["bomb_color"]["b"].asInt();
		Settings::ESP::visibility_check = settings["ESP"]["visibility_check"].asBool();
		Settings::ESP::Walls::enabled = settings["ESP"]["Walls"]["enabled"].asBool();
		Settings::ESP::Walls::type = (WallBoxType) settings["ESP"]["Walls"]["type"].asInt();
		Settings::ESP::Info::showName = settings["ESP"]["Info"]["showName"].asBool();
		Settings::ESP::Info::showHealth = settings["ESP"]["Info"]["showHealth"].asBool();
		Settings::ESP::Bones::enabled = settings["ESP"]["Bones"]["enabled"].asBool();
		Settings::ESP::Bomb::enabled = settings["ESP"]["Bomb"]["enabled"].asBool();
		Settings::ESP::Weapons::enabled = settings["ESP"]["Weapons"]["enabled"].asBool();
		Settings::ESP::Tracer::enabled = settings["ESP"]["Tracer"]["enabled"].asBool();
		Settings::ESP::Tracer::type = (TracerType) settings["ESP"]["Tracer"]["type"].asInt();
		Settings::ESP::FOVCrosshair::enabled = settings["ESP"]["FOVCrosshair"]["enabled"].asBool();
		Settings::ESP::Chams::players = settings["ESP"]["Chams"]["players"].asBool();
		Settings::ESP::Chams::visibility_check = settings["ESP"]["Chams"]["visibility_check"].asBool();
		Settings::ESP::Chams::arms = settings["ESP"]["Chams"]["arms"].asBool();
		Settings::ESP::Chams::rainbow_arms = settings["ESP"]["Chams"]["rainbow_arms"].asBool();
		Settings::ESP::Chams::players_ally_color.r = settings["ESP"]["Chams"]["players_ally_color"]["r"].asInt();
		Settings::ESP::Chams::players_ally_color.g = settings["ESP"]["Chams"]["players_ally_color"]["g"].asInt();
		Settings::ESP::Chams::players_ally_color.b = settings["ESP"]["Chams"]["players_ally_color"]["b"].asInt();
		Settings::ESP::Chams::players_enemy_color.r = settings["ESP"]["Chams"]["players_enemy_color"]["r"].asInt();
		Settings::ESP::Chams::players_enemy_color.g = settings["ESP"]["Chams"]["players_enemy_color"]["g"].asInt();
		Settings::ESP::Chams::players_enemy_color.b = settings["ESP"]["Chams"]["players_enemy_color"]["b"].asInt();
		Settings::ESP::Chams::players_enemy_visible_color.r = settings["ESP"]["Chams"]["players_enemy_visible_color"]["r"].asInt();
		Settings::ESP::Chams::players_enemy_visible_color.g = settings["ESP"]["Chams"]["players_enemy_visible_color"]["g"].asInt();
		Settings::ESP::Chams::players_enemy_visible_color.b = settings["ESP"]["Chams"]["players_enemy_visible_color"]["b"].asInt();
		Settings::ESP::Chams::arms_color.r = settings["ESP"]["Chams"]["arms_color"]["r"].asInt();
		Settings::ESP::Chams::arms_color.g = settings["ESP"]["Chams"]["arms_color"]["g"].asInt();
		Settings::ESP::Chams::arms_color.b = settings["ESP"]["Chams"]["arms_color"]["b"].asInt();
		Settings::ESP::Chams::type = (ChamsType) settings["ESP"]["Chams"]["type"].asInt();

		Settings::Dlights::enabled = settings["Dlights"]["enabled"].asBool();
		Settings::Dlights::radius = settings["Dlights"]["radius"].asFloat();
		Settings::Dlights::ally_color.r = settings["Dlights"]["ally_color"]["r"].asInt();
		Settings::Dlights::ally_color.g = settings["Dlights"]["ally_color"]["g"].asInt();
		Settings::Dlights::ally_color.b = settings["Dlights"]["ally_color"]["b"].asInt();
		Settings::Dlights::enemy_color.r = settings["Dlights"]["enemy_color"]["r"].asInt();
		Settings::Dlights::enemy_color.g = settings["Dlights"]["enemy_color"]["g"].asInt();
		Settings::Dlights::enemy_color.b = settings["Dlights"]["enemy_color"]["b"].asInt();

		Settings::Spammer::KillSpammer::enabled = settings["Spammer"]["KillSpammer"]["enabled"].asBool();
		Settings::Spammer::NormalSpammer::enabled = settings["Spammer"]["NormalSpammer"]["enabled"].asBool();

		Settings::BHop::enabled = settings["BHop"]["enabled"].asBool();

		Settings::AutoStrafe::enabled = settings["AutoStrafe"]["enabled"].asBool();

		Settings::Noflash::enabled = settings["Noflash"]["enabled"].asBool();
		Settings::Noflash::value = settings["Noflash"]["value"].asFloat();

		Settings::Recoilcrosshair::enabled = settings["Recoilcrosshair"]["enabled"].asBool();

		Settings::Airstuck::enabled = settings["Airstuck"]["enabled"].asBool();
		Settings::Airstuck::key = (ButtonCode_t) settings["Airstuck"]["key"].asInt();

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

		Settings::Skinchanger::enabled = settings["Skinchanger"]["enabled"].asBool();

		Settings::ShowRanks::enabled = settings["ShowRanks"]["enabled"].asBool();
		Settings::ShowSpectators::enabled = settings["ShowSpectators"]["enabled"].asBool();
	}
	else
	{
		Settings::LoadDefaultsOrSave(filename);
		Settings::LoadSettings(filename);
	}
}