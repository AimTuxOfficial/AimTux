#include "namechanger.h"

std::string NameChanger::origName = "";
int NameChanger::changes = -1;
NC_Type NameChanger::type = NC_NORMAL;

enum class Colors
{
	WHITE = 1,
	DARK_RED,
	LIGHT_PURPLE,
	DARK_GREEN,
	LIGHT_GREEN,
	GREEN,
	LIGHT_RED,
	GRAY,
	YELLOW,
	LIGHT_BLUE,
	BLUE,
	DARK_BLUE,
	DARK_GRAY,
	PURPLE,
	RED,
	ORANGE,
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
			(char)(Colors::RED),
			(char)(Colors::ORANGE),
			(char)(Colors::YELLOW),
			(char)(Colors::GREEN),
			(char)(Colors::BLUE),
			(char)(Colors::PURPLE),
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

std::string Colorize(const std::string& name, Colors color = Colors::LIGHT_RED)
{
	// TODO: Add color customization
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

	if (changes >= 5)
	{
		switch (NameChanger::type)
		{
			case NC_NORMAL:
				SetName(Util::PadStringRight("\230AIMTUX.NET", strlen("\230AIMTUX.NET") + RandomInt(10, 50)));
				break;
			case NC_RAINBOW:
				SetName(Util::PadStringRight(Rainbowify(origName), origName.size() + RandomInt(10, 50)));
				break;
			case NC_SOLID:
				SetName(Util::PadStringRight(Colorize(origName), origName.size() + RandomInt(10, 50)));
				break;
		}

		changes = -1;

		return;
	}

	SetName(Util::PadStringRight("AIMTUX.NET", strlen("AIMTUX.NET") + changes));
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
