#include "settings.h"

char* GetSettingsPath()
{
	char* settingsPath;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	asprintf(&settingsPath, "%s/aimtux_settings.json", cwd);

	return settingsPath;
}

void Settings::LoadDefaultsOrSave()
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	settings["Aimbot"]["enabled"] = Settings::Aimbot::enabled;
	settings["Aimbot"]["silent"] = Settings::Aimbot::silent;
	settings["Aimbot"]["fov"] = Settings::Aimbot::fov;
	settings["Aimbot"]["bone"] = Settings::Aimbot::bone;
	settings["Aimbot"]["Smooth"]["enabled"] = Settings::Aimbot::Smooth::enabled;
	settings["Aimbot"]["Smooth"]["value"] = Settings::Aimbot::Smooth::value;
	settings["Aimbot"]["AutoAim"]["enabled"] = Settings::Aimbot::AutoAim::enabled;
	settings["Aimbot"]["AimStep"]["enabled"] = Settings::Aimbot::AimStep::enabled;
	settings["Aimbot"]["AimStep"]["value"] = Settings::Aimbot::AimStep::value;
	settings["Aimbot"]["RCS"]["enabled"] = Settings::Aimbot::RCS::enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = Settings::Aimbot::AutoShoot::enabled;
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
	settings["ESP"]["Info"]["showName"] = Settings::ESP::Info::showName;
	settings["ESP"]["Info"]["showHealth"] = Settings::ESP::Info::showHealth;
	settings["ESP"]["Bones"]["enabled"] = Settings::ESP::Bones::enabled;
	settings["ESP"]["Bomb"]["enabled"] = Settings::ESP::Bomb::enabled;
	settings["ESP"]["Tracer"]["enabled"] = Settings::ESP::Tracer::enabled;
	settings["ESP"]["Tracer"]["type"] = Settings::ESP::Tracer::type;
	settings["ESP"]["Chams"]["players"] = Settings::ESP::Chams::players;
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

	settings["Spammer"]["enabled"] = Settings::Spammer::enabled;

	settings["BHop"]["enabled"] = Settings::BHop::enabled;

	settings["AutoStrafe"]["enabled"] = Settings::AutoStrafe::enabled;

	settings["Noflash"]["enabled"] = Settings::Noflash::enabled;
	settings["Noflash"]["value"] = Settings::Noflash::value;

	settings["Recoilcrosshair"]["enabled"] = Settings::Recoilcrosshair::enabled;

	settings["Airstuck"]["enabled"] = Settings::Airstuck::enabled;

	settings["Skinchanger"]["enabled"] = Settings::Skinchanger::enabled;

	std::ofstream(GetSettingsPath()) << styledWriter.write(settings);
}

void Settings::LoadSettings()
{
	if (std::ifstream(GetSettingsPath()).good())
	{
		Json::Value settings;
		std::ifstream config_doc(GetSettingsPath(), std::ifstream::binary);
		config_doc >> settings;

		Settings::Aimbot::enabled = settings["Aimbot"]["enabled"].asBool();
		Settings::Aimbot::silent = settings["Aimbot"]["silent"].asBool();
		Settings::Aimbot::fov = settings["Aimbot"]["fov"].asFloat();
		Settings::Aimbot::bone = settings["Aimbot"]["bone"].asInt();
		Settings::Aimbot::Smooth::enabled = settings["Aimbot"]["Smooth"]["enabled"].asBool();
		Settings::Aimbot::Smooth::value = settings["Aimbot"]["Smooth"]["value"].asFloat();
		Settings::Aimbot::AutoAim::enabled = settings["Aimbot"]["AutoAim"]["enabled"].asBool();
		Settings::Aimbot::AimStep::enabled = settings["Aimbot"]["AimStep"]["enabled"].asBool();
		Settings::Aimbot::AimStep::value = settings["Aimbot"]["AimStep"]["value"].asFloat();
		Settings::Aimbot::RCS::enabled = settings["Aimbot"]["RCS"]["enabled"].asBool();
		Settings::Aimbot::AutoShoot::enabled = settings["Aimbot"]["AutoShoot"]["enabled"].asBool();
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
		Settings::ESP::Info::showName = settings["ESP"]["Info"]["showName"].asBool();
		Settings::ESP::Info::showHealth = settings["ESP"]["Info"]["showHealth"].asBool();
		Settings::ESP::Bones::enabled = settings["ESP"]["Bones"]["enabled"].asBool();
		Settings::ESP::Bomb::enabled = settings["ESP"]["Bomb"]["enabled"].asBool();
		Settings::ESP::Tracer::enabled = settings["ESP"]["Tracer"]["enabled"].asBool();
		Settings::ESP::Tracer::type = (TracerType) settings["ESP"]["Tracer"]["type"].asInt();
		Settings::ESP::Chams::players = settings["ESP"]["Chams"]["players"].asBool();
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

		Settings::Spammer::enabled = settings["Spammer"]["enabled"].asBool();

		Settings::BHop::enabled = settings["BHop"]["enabled"].asBool();

		Settings::AutoStrafe::enabled = settings["AutoStrafe"]["enabled"].asBool();

		Settings::Noflash::enabled = settings["Noflash"]["enabled"].asBool();
		Settings::Noflash::value = settings["Noflash"]["value"].asBool();

		Settings::Recoilcrosshair::enabled = settings["Recoilcrosshair"]["enabled"].asBool();

		Settings::Airstuck::enabled = settings["Airstuck"]["enabled"].asBool();

		Settings::Skinchanger::enabled = settings["Skinchanger"]["enabled"].asBool();
	}
	else
	{
		Settings::LoadDefaultsOrSave();
		Settings::LoadSettings();
	}
}