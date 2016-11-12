#include "settings.h"

CSettings cSettings;

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

void Settings::LoadDefaults()
{
	cSettings.UI.mainColor = Color (230, 75, 100);
	cSettings.UI.Fonts.Title.family = (char *) "Arial";
	cSettings.UI.Fonts.Title.size = 20;
	cSettings.UI.Fonts.Normal.family = (char *) "Arial";
	cSettings.UI.Fonts.Normal.size = 17;
	cSettings.UI.Fonts.ESP.family = (char *) "Andale Mono";
	cSettings.UI.Fonts.ESP.size = 20;

	cSettings.Aimbot.enabled = true;
	cSettings.Aimbot.silent = false;
	cSettings.Aimbot.friendly = false;
	cSettings.Aimbot.fov = 180.0f;
	cSettings.Aimbot.errorMargin = 0.0F;
	cSettings.Aimbot.bone = BONE_HEAD;
	cSettings.Aimbot.aimkey = ButtonCode_t::MOUSE_MIDDLE;
	cSettings.Aimbot.aimkey_only = false;
	cSettings.Aimbot.Smooth.enabled = false;
	cSettings.Aimbot.Smooth.value = 1.0f;
	cSettings.Aimbot.Smooth.max = 15.0f;
	cSettings.Aimbot.AutoAim.enabled = false;
	cSettings.Aimbot.AutoWall.enabled = false;
	cSettings.Aimbot.AutoWall.value = 10.0f;
	cSettings.Aimbot.AutoWall.bones = { HITBOX_HEAD };
	cSettings.Aimbot.AimStep.enabled = false;
	cSettings.Aimbot.AimStep.value = 25.0f;
	cSettings.Aimbot.AutoPistol.enabled = false;
	cSettings.Aimbot.AutoShoot.enabled = false;
	cSettings.Aimbot.AutoShoot.autoscope = false;
	cSettings.Aimbot.RCS.enabled = false;
	cSettings.Aimbot.RCS.value = 2.0f;
	cSettings.Aimbot.AutoCrouch.enabled = false;
	cSettings.Aimbot.AutoStop.enabled = false;
	cSettings.Aimbot.Smooth.Salting.enabled = false;
	cSettings.Aimbot.Smooth.Salting.percentage = 0.0f;

	cSettings.Triggerbot.enabled = true;
	cSettings.Triggerbot.Filter.friendly = false;
	cSettings.Triggerbot.Filter.head = true;
	cSettings.Triggerbot.Filter.chest = true;
	cSettings.Triggerbot.Filter.stomach = true;
	cSettings.Triggerbot.Filter.arms = true;
	cSettings.Triggerbot.Filter.legs = true;
	cSettings.Triggerbot.Delay.enabled = false;
	cSettings.Triggerbot.Delay.value = 250;
	cSettings.Triggerbot.key = ButtonCode_t::KEY_LALT;

	cSettings.AntiAim.enabled_Y = false;
	cSettings.AntiAim.enabled_X = false;
	cSettings.AntiAim.type_Y = AntiAimType_Y::SPIN_FAST;
	cSettings.AntiAim.type_X = AntiAimType_X::STATIC_DOWN;
	
	cSettings.ESP.enabled = true;
	cSettings.ESP.ally_color = Color(0, 50, 200);
	cSettings.ESP.enemy_color = Color(200, 0, 50);
	cSettings.ESP.enemy_visible_color = Color(200, 200, 50);
	cSettings.ESP.bones_color = Color(255, 255, 255);
	cSettings.ESP.bomb_color = Color(200, 0, 50);
	cSettings.ESP.Glow.enabled = false;
	cSettings.ESP.friendly = true;
	cSettings.ESP.Glow.ally_color = Color(0, 50, 200, 0);
	cSettings.ESP.Glow.enemy_color = Color(200, 0, 50, 0);
	cSettings.ESP.Glow.enemy_visible_color = Color(200, 200, 50, 0);
	cSettings.ESP.Glow.weapon_color = Color(200, 0, 50, 200);
	cSettings.ESP.visibility_check = false;
	cSettings.ESP.Walls.enabled = false;
	cSettings.ESP.Walls.type = WallBoxType::FLAT_2D;
	cSettings.ESP.Info.showName = true;
	cSettings.ESP.Info.showHealth = false;
	cSettings.ESP.Info.ally_color = Color(0, 50, 200);
	cSettings.ESP.Info.enemy_color = Color(200, 0, 50);
	cSettings.ESP.Info.enemy_visible_color = Color(200, 200, 50);
	cSettings.ESP.Bones.enabled = false;
	cSettings.ESP.Bomb.enabled = true;
	cSettings.ESP.Weapons.enabled = false;
	cSettings.ESP.Tracer.enabled = false;
	cSettings.ESP.Tracer.type = TracerType::BOTTOM;
	cSettings.ESP.FOVCrosshair.enabled = false;
	cSettings.ESP.Chams.players = false;
	cSettings.ESP.Chams.visibility_check = false;
	cSettings.ESP.Chams.Arms.enabled = false;
	cSettings.ESP.Chams.Arms.type = ArmsType::RAINBOW;
	cSettings.ESP.Chams.players_ally_color = Color(7, 98, 168);
	cSettings.ESP.Chams.players_ally_visible_color = Color(40, 52, 138);
	cSettings.ESP.Chams.players_enemy_color = Color(243, 24, 28);
	cSettings.ESP.Chams.players_enemy_visible_color = Color(243, 159, 20);
	cSettings.ESP.Chams.Arms.color = Color(117, 43, 73);
	cSettings.ESP.Chams.type = ChamsType::CHAMS_FLAT;

	cSettings.Dlights.enabled = false;
	cSettings.Dlights.radius = 500.0f;
	cSettings.Dlights.ally_color = Color(0, 50, 200);
	cSettings.Dlights.enemy_color = Color(200, 0, 50);

	cSettings.Spammer.PositionSpammer.enabled = false;
	cSettings.Spammer.PositionSpammer.say_team = false;
	cSettings.Spammer.KillSpammer.enabled = false;
	cSettings.Spammer.KillSpammer.say_team = false;
	cSettings.Spammer.KillSpammer.message = (char*) "$nick just got OWNED by AimTux!!";
	cSettings.Spammer.NormalSpammer.enabled = false;
	cSettings.Spammer.NormalSpammer.say_team = false;

	cSettings.BHop.enabled = true;

	cSettings.AutoStrafe.enabled = true;

	cSettings.Noflash.enabled = true;
	cSettings.Noflash.value = 160.0f;

	cSettings.FOVChanger.enabled = false;
	cSettings.FOVChanger.value = 100.f;
	cSettings.FOVChanger.viewmodel_enabled = false;
	cSettings.FOVChanger.viewmodel_value = 90.f;

	cSettings.Radar.enabled = false;

	cSettings.Recoilcrosshair.enabled = true;

	cSettings.Airstuck.enabled = false;
	cSettings.Airstuck.key = ButtonCode_t::KEY_F;

	cSettings.Skinchanger.enabled = true;
	cSettings.Skinchanger.skins = {
			{ WEAPON_AWP, Skin(344, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_AK47, Skin(524, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_M4A1, Skin(512, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_M4A1_SILENCER, Skin(548, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_DEAGLE, Skin(277, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_GLOCK, Skin(38, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_USP_SILENCER, Skin(332, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_FIVESEVEN, Skin(252, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_SCAR20, Skin(391, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_ELITE, Skin(249, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_SSG08, Skin(319, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_TEC9, Skin(179, -1, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_KNIFE, Skin(417, WEAPON_KNIFE_M9_BAYONET, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_KNIFE_T, Skin(417, WEAPON_KNIFE_KARAMBIT, 0, 0.0005f, 1337, "AimTux", "") },
			{ WEAPON_KNIFE_GUT, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_gut.mdl") },
			{ WEAPON_KNIFE_FLIP, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_flip.mdl") },
			{ WEAPON_KNIFE_BAYONET, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_bayonet.mdl") },
			{ WEAPON_KNIFE_M9_BAYONET, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_m9_bay.mdl") },
			{ WEAPON_KNIFE_KARAMBIT, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_karam.mdl") },
			{ WEAPON_KNIFE_TACTICAL, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_tactical.mdl") },
			{ WEAPON_KNIFE_BUTTERFLY, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_butterfly.mdl") },
			{ WEAPON_KNIFE_SURVIVAL_BOWIE, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_survival_bowie.mdl") },
			{ WEAPON_KNIFE_FALCHION, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_falchion_advanced.mdl") },
			{ WEAPON_KNIFE_PUSH, Skin(-1, -1, -1, -1, -1, "", "models/weapons/v_knife_push.mdl") }
	};

	cSettings.ShowRanks.enabled = true;

	cSettings.ClanTagChanger.value = "AimTux";
	cSettings.ClanTagChanger.animation = false;
	cSettings.ClanTagChanger.enabled = false;

	cSettings.View.NoPunch.enabled = false;

	cSettings.NameChanger.enabled = false;
	cSettings.NameChanger.last_blank = false;

	cSettings.Teleport.enabled = false;
	cSettings.Teleport.key = ButtonCode_t::KEY_RALT;

	cSettings.FakeLag.enabled = false;
	cSettings.FakeLag.value = 5;
}

void Settings::LoadDefaultsOrSave(const char* filename)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	Settings::LoadDefaults();

	LoadColor(settings["UI"]["mainColor"], cSettings.UI.mainColor);
	settings["UI"]["Fonts"]["Title"]["family"] = cSettings.UI.Fonts.Title.family;
	settings["UI"]["Fonts"]["Title"]["size"] = cSettings.UI.Fonts.Title.size;
	settings["UI"]["Fonts"]["Normal"]["family"] = cSettings.UI.Fonts.Normal.family;
	settings["UI"]["Fonts"]["Normal"]["size"] = cSettings.UI.Fonts.Normal.size;
	settings["UI"]["Fonts"]["ESP"]["family"] = cSettings.UI.Fonts.ESP.family;
	settings["UI"]["Fonts"]["ESP"]["size"] = cSettings.UI.Fonts.ESP.size;

	settings["Aimbot"]["enabled"] = cSettings.Aimbot.enabled;
	settings["Aimbot"]["silent"] = cSettings.Aimbot.silent;
	settings["Aimbot"]["friendly"] = cSettings.Aimbot.friendly;
	settings["Aimbot"]["fov"] = cSettings.Aimbot.fov;
	settings["Aimbot"]["errorMargin"] = cSettings.Aimbot.errorMargin;
	settings["Aimbot"]["bone"] = cSettings.Aimbot.bone;
	settings["Aimbot"]["aimkey"] = Util::GetButtonName(cSettings.Aimbot.aimkey);
	settings["Aimbot"]["aimkey_only"] = cSettings.Aimbot.aimkey_only;
	settings["Aimbot"]["Smooth"]["enabled"] = cSettings.Aimbot.Smooth.enabled;
	settings["Aimbot"]["Smooth"]["value"] = cSettings.Aimbot.Smooth.value;
	settings["Aimbot"]["Smooth"]["Salting"]["enabled"] = cSettings.Aimbot.Smooth.Salting.enabled;
	settings["Aimbot"]["Smooth"]["Salting"]["percentage"] = cSettings.Aimbot.Smooth.Salting.percentage;
	settings["Aimbot"]["AutoAim"]["enabled"] = cSettings.Aimbot.AutoAim.enabled;
	settings["Aimbot"]["AutoWall"]["enabled"] = cSettings.Aimbot.AutoWall.enabled;
	settings["Aimbot"]["AutoWall"]["value"] = cSettings.Aimbot.AutoWall.value;
	settings["Aimbot"]["AutoWall"]["bones"] = Json::Value(Json::arrayValue);
	for (auto bone : cSettings.Aimbot.AutoWall.bones)
		settings["Aimbot"]["AutoWall"]["bones"].append(bone);
	settings["Aimbot"]["AimStep"]["enabled"] = cSettings.Aimbot.AimStep.enabled;
	settings["Aimbot"]["AimStep"]["value"] = cSettings.Aimbot.AimStep.value;
	settings["Aimbot"]["RCS"]["enabled"] = cSettings.Aimbot.RCS.enabled;
	settings["Aimbot"]["RCS"]["value"] = cSettings.Aimbot.RCS.value;
	settings["Aimbot"]["AutoPistol"]["enabled"] = cSettings.Aimbot.AutoPistol.enabled;
	settings["Aimbot"]["AutoShoot"]["enabled"] = cSettings.Aimbot.AutoShoot.enabled;
	settings["Aimbot"]["AutoShoot"]["autoscope"] = cSettings.Aimbot.AutoShoot.autoscope;
	settings["Aimbot"]["AutoCrouch"]["enabled"] = cSettings.Aimbot.AutoCrouch.enabled;
	settings["Aimbot"]["AutoStop"]["enabled"] = cSettings.Aimbot.AutoStop.enabled;

	settings["Triggerbot"]["enabled"] = cSettings.Triggerbot.enabled;
	settings["Triggerbot"]["key"] = Util::GetButtonName(cSettings.Triggerbot.key);
	settings["Triggerbot"]["Filter"]["friendly"] = cSettings.Triggerbot.Filter.friendly;
	settings["Triggerbot"]["Filter"]["head"] = cSettings.Triggerbot.Filter.head;
	settings["Triggerbot"]["Filter"]["chest"] = cSettings.Triggerbot.Filter.chest;
	settings["Triggerbot"]["Filter"]["stomach"] = cSettings.Triggerbot.Filter.stomach;
	settings["Triggerbot"]["Filter"]["arms"] = cSettings.Triggerbot.Filter.arms;
	settings["Triggerbot"]["Filter"]["legs"] = cSettings.Triggerbot.Filter.legs;
	settings["Triggerbot"]["Delay"]["enabled"] = cSettings.Triggerbot.Delay.enabled;
	settings["Triggerbot"]["Delay"]["value"] = cSettings.Triggerbot.Delay.value;

	settings["AntiAim"]["enabled_Y"] = cSettings.AntiAim.enabled_Y;
	settings["AntiAim"]["enabled_X"] = cSettings.AntiAim.enabled_X;
	settings["AntiAim"]["type_Y"] = cSettings.AntiAim.type_Y;
	settings["AntiAim"]["type_X"] = cSettings.AntiAim.type_X;

	settings["ESP"]["enabled"] = cSettings.ESP.enabled;

	LoadColor(settings["ESP"]["ally_color"], cSettings.ESP.ally_color);
	LoadColor(settings["ESP"]["enemy_color"], cSettings.ESP.enemy_color);
	LoadColor(settings["ESP"]["enemy_visible_color"], cSettings.ESP.enemy_visible_color);
	LoadColor(settings["ESP"]["bones_color"], cSettings.ESP.bones_color);
	LoadColor(settings["ESP"]["bomb_color"], cSettings.ESP.bomb_color);
	settings["ESP"]["visibility_check"] = cSettings.ESP.visibility_check;
	settings["ESP"]["friendly"] = cSettings.ESP.friendly;
	settings["ESP"]["Glow"]["enabled"] = cSettings.ESP.Glow.enabled;
	LoadColor(settings["ESP"]["Glow"]["ally_color"], cSettings.ESP.Glow.ally_color);
	LoadColor(settings["ESP"]["Glow"]["enemy_color"], cSettings.ESP.Glow.enemy_color);
	LoadColor(settings["ESP"]["Glow"]["enemy_visible_color"], cSettings.ESP.Glow.enemy_visible_color);
	LoadColor(settings["ESP"]["Glow"]["weapon_color"], cSettings.ESP.Glow.weapon_color);
	settings["ESP"]["Tracer"]["enabled"] = cSettings.ESP.Tracer.enabled;
	settings["ESP"]["Tracer"]["type"] = cSettings.ESP.Tracer.type;
	settings["ESP"]["Walls"]["enabled"] = cSettings.ESP.Walls.enabled;
	settings["ESP"]["Walls"]["type"] = cSettings.ESP.Walls.type;
	settings["ESP"]["Info"]["showName"] = cSettings.ESP.Info.showName;
	settings["ESP"]["Info"]["showHealth"] = cSettings.ESP.Info.showHealth;
	LoadColor(settings["ESP"]["Info"]["ally_color"], cSettings.ESP.Info.ally_color);
	LoadColor(settings["ESP"]["Info"]["enemy_color"], cSettings.ESP.Info.enemy_color);
	LoadColor(settings["ESP"]["Info"]["enemy_visible_color"], cSettings.ESP.Info.enemy_visible_color);
	settings["ESP"]["Bones"]["enabled"] = cSettings.ESP.Bones.enabled;
	settings["ESP"]["Bomb"]["enabled"] = cSettings.ESP.Bomb.enabled;
	settings["ESP"]["Weapons"]["enabled"] = cSettings.ESP.Weapons.enabled;
	settings["ESP"]["FOVCrosshair"]["enabled"] = cSettings.ESP.FOVCrosshair.enabled;
	settings["ESP"]["Chams"]["players"] = cSettings.ESP.Chams.players;
	settings["ESP"]["Chams"]["visibility_check"] = cSettings.ESP.Chams.visibility_check;
	settings["ESP"]["Chams"]["Arms"]["enabled"] = cSettings.ESP.Chams.Arms.enabled;
	settings["ESP"]["Chams"]["Arms"]["type"] = cSettings.ESP.Chams.Arms.type;
	LoadColor(settings["ESP"]["Chams"]["players_ally_color"], cSettings.ESP.Chams.players_ally_color);
	LoadColor(settings["ESP"]["Chams"]["players_ally_visible_color"], cSettings.ESP.Chams.players_ally_visible_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_color"], cSettings.ESP.Chams.players_enemy_color);
	LoadColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], cSettings.ESP.Chams.players_enemy_visible_color);
	LoadColor(settings["ESP"]["Chams"]["Arms"]["color"], cSettings.ESP.Chams.Arms.color);
	settings["ESP"]["Chams"]["type"] = cSettings.ESP.Chams.type;

	settings["Dlights"]["enabled"] = cSettings.Dlights.enabled;
	settings["Dlights"]["radius"] = cSettings.Dlights.radius;
	LoadColor(settings["Dlights"]["ally_color"], cSettings.Dlights.ally_color);
	LoadColor(settings["Dlights"]["enemy_color"], cSettings.Dlights.enemy_color);

	settings["Spammer"]["PositionSpammer"]["enabled"] = cSettings.Spammer.PositionSpammer.enabled;
	settings["Spammer"]["KillSpammer"]["enabled"] = cSettings.Spammer.KillSpammer.enabled;
	settings["Spammer"]["KillSpammer"]["message"] = cSettings.Spammer.KillSpammer.message;
	settings["Spammer"]["NormalSpammer"]["enabled"] = cSettings.Spammer.NormalSpammer.enabled;

	settings["BHop"]["enabled"] = cSettings.BHop.enabled;

	settings["AutoStrafe"]["enabled"] = cSettings.AutoStrafe.enabled;

	settings["Noflash"]["enabled"] = cSettings.Noflash.enabled;
	settings["Noflash"]["value"] = cSettings.Noflash.value;

	settings["Radar"]["enabled"] = cSettings.Radar.enabled;

	settings["Recoilcrosshair"]["enabled"] = cSettings.Recoilcrosshair.enabled;

	settings["FOVChanger"]["enabled"] = cSettings.FOVChanger.enabled;
	settings["FOVChanger"]["value"] = cSettings.FOVChanger.value;
	settings["FOVChanger"]["viewmodel_enabled"] = cSettings.FOVChanger.viewmodel_enabled;
	settings["FOVChanger"]["viewmodel_value"] = cSettings.FOVChanger.viewmodel_value;

	settings["Airstuck"]["enabled"] = cSettings.Airstuck.enabled;
	settings["Airstuck"]["key"] = Util::GetButtonName(cSettings.Airstuck.key);

	settings["Skinchanger"]["enabled"] = cSettings.Skinchanger.enabled;
	for (auto i : cSettings.Skinchanger.skins)
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

	settings["ShowRanks"]["enabled"] = cSettings.ShowRanks.enabled;

	settings["ShowSpectators"]["enabled"] = cSettings.ShowSpectators.enabled;

	settings["ClanTagChanger"]["value"] = cSettings.ClanTagChanger.value;
	settings["ClanTagChanger"]["enabled"] = cSettings.ClanTagChanger.enabled;
	settings["ClanTagChanger"]["animation"] = cSettings.ClanTagChanger.animation;

	settings["View"]["NoPunch"]["enabled"] = cSettings.View.NoPunch.enabled;

	settings["NameChanger"]["enabled"] = cSettings.NameChanger.enabled;
	settings["NameChanger"]["last_blank"] = cSettings.NameChanger.last_blank;

	settings["Teleport"]["enabled"] = cSettings.Teleport.enabled;
	settings["Teleport"]["key"] = cSettings.Teleport.key;

	settings["FakeLag"]["enabled"] = cSettings.FakeLag.enabled;

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

	GetColor(settings["UI"]["mainColor"], &cSettings.UI.mainColor);
	GetCString(settings["UI"]["Fonts"]["Title"]["family"], &cSettings.UI.Fonts.Title.family);
	GetInt(settings["UI"]["Fonts"]["Title"]["size"], &cSettings.UI.Fonts.Title.size);
	GetCString(settings["UI"]["Fonts"]["Normal"]["family"], &cSettings.UI.Fonts.Normal.family);
	GetInt(settings["UI"]["Fonts"]["Normal"]["size"], &cSettings.UI.Fonts.Normal.size);
	GetCString(settings["UI"]["Fonts"]["ESP"]["family"], &cSettings.UI.Fonts.ESP.family);
	GetInt(settings["UI"]["Fonts"]["ESP"]["size"], &cSettings.UI.Fonts.ESP.size);

	title_font = Draw::CreateFont(cSettings.UI.Fonts.Title.family, cSettings.UI.Fonts.Title.size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	normal_font = Draw::CreateFont(cSettings.UI.Fonts.Normal.family, cSettings.UI.Fonts.Normal.size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	esp_font = Draw::CreateFont(cSettings.UI.Fonts.ESP.family, cSettings.UI.Fonts.ESP.size, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);

	GetBool(settings["Aimbot"]["enabled"], &cSettings.Aimbot.enabled);
	GetBool(settings["Aimbot"]["silent"], &cSettings.Aimbot.silent);
	GetBool(settings["Aimbot"]["friendly"], &cSettings.Aimbot.friendly);
	GetFloat(settings["Aimbot"]["fov"], &cSettings.Aimbot.fov);
	GetFloat(settings["Aimbot"]["errorMargin"], &cSettings.Aimbot.errorMargin);
	GetInt(settings["Aimbot"]["bone"], &cSettings.Aimbot.bone);
	GetButtonCode(settings["Aimbot"]["aimkey"], &cSettings.Aimbot.aimkey);
	GetBool(settings["Aimbot"]["aimkey_only"], &cSettings.Aimbot.aimkey_only);
	GetBool(settings["Aimbot"]["Smooth"]["enabled"], &cSettings.Aimbot.Smooth.enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["value"], &cSettings.Aimbot.Smooth.value);
	GetBool(settings["Aimbot"]["Smooth"]["Salting"]["enabled"], &cSettings.Aimbot.Smooth.Salting.enabled);
	GetFloat(settings["Aimbot"]["Smooth"]["Salting"]["percentage"], &cSettings.Aimbot.Smooth.Salting.percentage);
	GetBool(settings["Aimbot"]["AutoAim"]["enabled"], &cSettings.Aimbot.AutoAim.enabled);
	GetBool(settings["Aimbot"]["AutoWall"]["enabled"], &cSettings.Aimbot.AutoWall.enabled);
	GetFloat(settings["Aimbot"]["AutoWall"]["value"], &cSettings.Aimbot.AutoWall.value);
	cSettings.Aimbot.AutoWall.bones.clear();
	for (Json::ValueIterator itr = settings["Aimbot"]["AutoWall"]["bones"].begin(); itr != settings["Aimbot"]["AutoWall"]["bones"].end(); itr++)
		cSettings.Aimbot.AutoWall.bones.push_back((Hitbox) settings["Aimbot"]["AutoWall"]["bones"][itr.index()].asInt());
	GetBool(settings["Aimbot"]["AimStep"]["enabled"], &cSettings.Aimbot.AimStep.enabled);
	GetFloat(settings["Aimbot"]["AimStep"]["value"], &cSettings.Aimbot.AimStep.value);
	GetBool(settings["Aimbot"]["RCS"]["enabled"], &cSettings.Aimbot.RCS.enabled);
	GetFloat(settings["Aimbot"]["RCS"]["value"], &cSettings.Aimbot.RCS.value);
	GetBool(settings["Aimbot"]["AutoPistol"]["enabled"], &cSettings.Aimbot.AutoPistol.enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["enabled"], &cSettings.Aimbot.AutoShoot.enabled);
	GetBool(settings["Aimbot"]["AutoShoot"]["autoscope"], &cSettings.Aimbot.AutoShoot.autoscope);
	GetBool(settings["Aimbot"]["AutoCrouch"]["enabled"], &cSettings.Aimbot.AutoCrouch.enabled);
	GetBool(settings["Aimbot"]["AutoStop"]["enabled"], &cSettings.Aimbot.AutoStop.enabled);

	GetBool(settings["Triggerbot"]["enabled"], &cSettings.Triggerbot.enabled);
	GetButtonCode(settings["Triggerbot"]["key"], &cSettings.Triggerbot.key);
	GetBool(settings["Triggerbot"]["Filter"]["friendly"], &cSettings.Triggerbot.Filter.friendly);
	GetBool(settings["Triggerbot"]["Filter"]["head"], &cSettings.Triggerbot.Filter.head);
	GetBool(settings["Triggerbot"]["Filter"]["chest"], &cSettings.Triggerbot.Filter.chest);
	GetBool(settings["Triggerbot"]["Filter"]["stomach"], &cSettings.Triggerbot.Filter.stomach);
	GetBool(settings["Triggerbot"]["Filter"]["arms"], &cSettings.Triggerbot.Filter.arms);
	GetBool(settings["Triggerbot"]["Filter"]["legs"], &cSettings.Triggerbot.Filter.legs);
	GetBool(settings["Triggerbot"]["Delay"]["enabled"], &cSettings.Triggerbot.Delay.enabled);
	GetInt(settings["Triggerbot"]["Delay"]["value"], &cSettings.Triggerbot.Delay.value);

	GetBool(settings["AntiAim"]["enabled_Y"], &cSettings.AntiAim.enabled_Y);
	GetBool(settings["AntiAim"]["enabled_X"], &cSettings.AntiAim.enabled_X);
	GetInt(settings["AntiAim"]["type_Y"], &cSettings.AntiAim.type_Y);
	GetInt(settings["AntiAim"]["type_X"], &cSettings.AntiAim.type_X);

	GetBool(settings["ESP"]["enabled"], &cSettings.ESP.enabled);
	GetColor(settings["ESP"]["ally_color"], &cSettings.ESP.ally_color);
	GetColor(settings["ESP"]["enemy_color"], &cSettings.ESP.enemy_color);
	GetColor(settings["ESP"]["enemy_visible_color"], &cSettings.ESP.enemy_visible_color);
	GetColor(settings["ESP"]["bones_color"], &cSettings.ESP.bones_color);
	GetColor(settings["ESP"]["bomb_color"], &cSettings.ESP.bomb_color);
	GetBool(settings["ESP"]["visibility_check"], &cSettings.ESP.visibility_check);
	GetBool(settings["ESP"]["friendly"], &cSettings.ESP.friendly);
	GetBool(settings["ESP"]["Glow"]["enabled"], &cSettings.ESP.Glow.enabled);
	GetColor(settings["ESP"]["Glow"]["ally_color"], &cSettings.ESP.Glow.ally_color);
	GetColor(settings["ESP"]["Glow"]["enemy_color"], &cSettings.ESP.Glow.enemy_color);
	GetColor(settings["ESP"]["Glow"]["enemy_visible_color"], &cSettings.ESP.Glow.enemy_visible_color);
	GetColor(settings["ESP"]["Glow"]["weapon_color"], &cSettings.ESP.Glow.weapon_color);
	GetBool(settings["ESP"]["Tracer"]["enabled"], &cSettings.ESP.Tracer.enabled);
	GetInt(settings["ESP"]["Tracer"]["type"], &cSettings.ESP.Tracer.type);
	GetBool(settings["ESP"]["Walls"]["enabled"], &cSettings.ESP.Walls.enabled);
	GetInt(settings["ESP"]["Walls"]["type"], &cSettings.ESP.Walls.type);
	GetBool(settings["ESP"]["Info"]["showName"], &cSettings.ESP.Info.showName);
	GetBool(settings["ESP"]["Info"]["showHealth"], &cSettings.ESP.Info.showHealth);
	GetColor(settings["ESP"]["Info"]["ally_color"], &cSettings.ESP.Info.ally_color);
	GetColor(settings["ESP"]["Info"]["enemy_color"], &cSettings.ESP.Info.enemy_color);
	GetColor(settings["ESP"]["Info"]["enemy_visible_color"], &cSettings.ESP.Info.enemy_visible_color);
	GetBool(settings["ESP"]["Bones"]["enabled"], &cSettings.ESP.Bones.enabled);
	GetBool(settings["ESP"]["Bomb"]["enabled"], &cSettings.ESP.Bomb.enabled);
	GetBool(settings["ESP"]["Weapons"]["enabled"], &cSettings.ESP.Weapons.enabled);
	GetBool(settings["ESP"]["FOVCrosshair"]["enabled"], &cSettings.ESP.FOVCrosshair.enabled);
	GetBool(settings["ESP"]["Chams"]["players"], &cSettings.ESP.Chams.players);
	GetBool(settings["ESP"]["Chams"]["visibility_check"], &cSettings.ESP.Chams.visibility_check);
	GetBool(settings["ESP"]["Chams"]["Arms"]["enabled"], &cSettings.ESP.Chams.Arms.enabled);
	GetInt(settings["ESP"]["Chams"]["Arms"]["type"], &cSettings.ESP.Chams.Arms.type);
	GetColor(settings["ESP"]["Chams"]["players_ally_color"], &cSettings.ESP.Chams.players_ally_color);
	GetColor(settings["ESP"]["Chams"]["players_enemy_color"], &cSettings.ESP.Chams.players_enemy_color);
	GetColor(settings["ESP"]["Chams"]["players_enemy_visible_color"], &cSettings.ESP.Chams.players_enemy_visible_color);
	GetColor(settings["ESP"]["Chams"]["Arms"]["color"], &cSettings.ESP.Chams.Arms.color);
	GetInt(settings["ESP"]["Chams"]["type"], &cSettings.ESP.Chams.type);

	GetBool(settings["Dlights"]["enabled"], &cSettings.Dlights.enabled);
	GetFloat(settings["Dlights"]["radius"], &cSettings.Dlights.radius);
	GetColor(settings["Dlights"]["ally_color"], &cSettings.Dlights.ally_color);
	GetColor(settings["Dlights"]["enemy_color"], &cSettings.Dlights.enemy_color);

	GetBool(settings["Spammer"]["PositionSpammer"]["enabled"], &cSettings.Spammer.PositionSpammer.enabled);
	GetBool(settings["Spammer"]["KillSpammer"]["enabled"], &cSettings.Spammer.KillSpammer.enabled);
	GetCString(settings["Spammer"]["KillSpammer"]["message"], &cSettings.Spammer.KillSpammer.message);
	GetBool(settings["Spammer"]["NormalSpammer"]["enabled"], &cSettings.Spammer.NormalSpammer.enabled);

	GetBool(settings["BHop"]["enabled"], &cSettings.BHop.enabled);

	GetBool(settings["AutoStrafe"]["enabled"], &cSettings.AutoStrafe.enabled);

	GetBool(settings["Noflash"]["enabled"], &cSettings.Noflash.enabled);
	GetFloat(settings["Noflash"]["value"], &cSettings.Noflash.value);

	GetBool(settings["Radar"]["enabled"], &cSettings.Radar.enabled);

	GetBool(settings["Recoilcrosshair"]["enabled"], &cSettings.Recoilcrosshair.enabled);

	GetBool(settings["FOVChanger"]["enabled"], &cSettings.FOVChanger.enabled);
	GetFloat(settings["FOVChanger"]["value"], &cSettings.FOVChanger.value);
	GetBool(settings["FOVChanger"]["viewmodel_enabled"], &cSettings.FOVChanger.viewmodel_enabled);
	GetFloat(settings["FOVChanger"]["viewmodel_value"], &cSettings.FOVChanger.viewmodel_value);

	GetBool(settings["Airstuck"]["enabled"], &cSettings.Airstuck.enabled);
	GetButtonCode(settings["Airstuck"]["key"], &cSettings.Airstuck.key);

	cSettings.Skinchanger.enabled = false;
	cSettings.Skinchanger.skins.clear();

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

		Skin skin = Skin(
				skinSetting["PaintKit"].asInt(),
				defIndex,
				skinSetting["Seed"].asInt(),
				skinSetting["Wear"].asFloat(),
				skinSetting["StatTrak"].asInt(),
				skinSetting["CustomName"].asString(),
				skinSetting["Model"].asString()
		);

		cSettings.Skinchanger.skins[weaponID] = skin;
	}

	SkinChanger::ForceFullUpdate = true;

	GetBool(settings["Skinchanger"]["enabled"], &cSettings.Skinchanger.enabled);

	GetBool(settings["ShowRanks"]["enabled"], &cSettings.ShowRanks.enabled);

	GetBool(settings["ShowSpectators"]["enabled"], &cSettings.ShowSpectators.enabled);

	GetString(settings["ClanTagChanger"]["value"], &cSettings.ClanTagChanger.value);
	GetBool(settings["ClanTagChanger"]["enabled"], &cSettings.ClanTagChanger.enabled);
	GetBool(settings["ClanTagChanger"]["animation"], &cSettings.ClanTagChanger.animation);

	GetBool(settings["View"]["NoPunch"]["enabled"], &cSettings.View.NoPunch.enabled);

	GetBool(settings["NameChanger"]["enabled"], &cSettings.NameChanger.enabled);
	GetBool(settings["NameChanger"]["last_blank"], &cSettings.NameChanger.last_blank);

	GetBool(settings["Teleport"]["enabled"], &cSettings.Teleport.enabled);
	GetButtonCode(settings["Teleport"]["key"], &cSettings.Teleport.key);

	GetBool(settings["FakeLag"]["enabled"], &cSettings.FakeLag.enabled);
}
