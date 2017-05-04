#include "namechanger.h"

std::string NameChanger::origName = "";
int NameChanger::changes = -1;
NameChanger::NC_Type NameChanger::type = NC_Type::NC_NORMAL;
NameChanger::Colors NameChanger::color = Colors::LIGHT_RED;
std::vector<std::pair<NameChanger::Colors, const char*>> NameChanger::colors = {
		{ NameChanger::Colors::WHITE, "White" },
		{ NameChanger::Colors::DARK_RED, "Dark Red" },
		{ NameChanger::Colors::LIGHT_PURPLE, "Light Purple" },
		{ NameChanger::Colors::DARK_GREEN, "Dark Green" },
		{ NameChanger::Colors::LIGHT_GREEN, "Light Green" },
		{ NameChanger::Colors::GREEN, "Green" },
		{ NameChanger::Colors::LIGHT_RED, "Light Red" },
		{ NameChanger::Colors::GRAY, "Gray" },
		{ NameChanger::Colors::YELLOW, "Yellow" },
		{ NameChanger::Colors::LIGHT_BLUE, "Light Blue" },
		{ NameChanger::Colors::BLUE, "Blue" },
		{ NameChanger::Colors::DARK_BLUE, "Dark Blue" },
		{ NameChanger::Colors::DARK_GRAY, "Dark Gray" },
		{ NameChanger::Colors::PURPLE, "Purple" },
		{ NameChanger::Colors::RED, "Red" },
		{ NameChanger::Colors::ORANGE, "Orange" },
};

std::string NameChanger::GetName()
{
	IEngineClient::player_info_t playerInfo;
	engine->GetPlayerInfo(engine->GetLocalPlayer(), &playerInfo);
	return std::string(playerInfo.name);
}

std::string Rainbowify(const std::string& name)
{
	std::string base = " \x01\x0B";
	std::vector<char> rainbow = {
			(char)(NameChanger::Colors::RED),
			(char)(NameChanger::Colors::ORANGE),
			(char)(NameChanger::Colors::YELLOW),
			(char)(NameChanger::Colors::GREEN),
			(char)(NameChanger::Colors::BLUE),
			(char)(NameChanger::Colors::PURPLE),
	};

	size_t color = 0;
	for (char c : name)
	{
		if (color > rainbow.size() - 1)
			color = 0;
		base.push_back(rainbow[color]);
		base.push_back(c);
		color++;
	}

	base.append("\230");
	return base;
}

std::string Colorize(const std::string& name, NameChanger::Colors color = NameChanger::Colors::LIGHT_RED)
{
	std::string res = " \x01\x0B";
	res += (char)(color);
	res.append(name);
	res.append("\230");
	return res;
}

void NameChanger::BeginFrame(float frameTime)
{
	if (!engine->IsInGame())
		return;

	if (changes == -1)
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 150)
		return;

	timeStamp = currentTime_ms;
	changes++;

	SetName("\n\xAD\xAD\xAD");

	if (changes >= 5)
	{
		switch (NameChanger::type)
		{
			case NC_Type::NC_NORMAL:
				SetName(Util::PadStringRight("\n", strlen("\n") + RandomInt(10, 50)));
				break;
			case NC_Type::NC_RAINBOW:
				SetName(Util::PadStringRight(Rainbowify(origName), origName.size() + RandomInt(10, 50)));
				break;
			case NC_Type::NC_SOLID:
				SetName(Util::PadStringRight(Colorize(origName, NameChanger::color), origName.size() + RandomInt(10, 50)));
				break;
		}

		changes = -1;

		return;
	}

	SetName(Util::PadStringRight("Hello!", strlen("Hello!") + changes));
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}

void NameChanger::InitColorChange(NameChanger::NC_Type type, NameChanger::Colors color /*= NameChanger::Colors::LIGHT_RED*/)
{
	NameChanger::changes = 0;
	NameChanger::origName = NameChanger::GetName();
	NameChanger::type = type;
	NameChanger::color = color;
}
