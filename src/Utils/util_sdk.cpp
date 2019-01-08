#include "util_sdk.h"

#include <sstream>
#include "../interfaces.h"
#include <algorithm>

char Util::GetButtonString(ButtonCode_t key)
{
	switch (key)
	{
		case KEY_PAD_0:
			return '0';
		case KEY_PAD_1:
			return '1';
		case KEY_PAD_2:
			return '2';
		case KEY_PAD_3:
			return '3';
		case KEY_PAD_4:
			return '4';
		case KEY_PAD_5:
			return '5';
		case KEY_PAD_6:
			return '6';
		case KEY_PAD_7:
			return '7';
		case KEY_PAD_8:
			return '8';
		case KEY_PAD_9:
			return '9';
		case KEY_PAD_DIVIDE:
			return '/';
		case KEY_PAD_MULTIPLY:
			return '*';
		case KEY_PAD_MINUS:
			return '-';
		case KEY_PAD_PLUS:
			return '+';
		case KEY_SEMICOLON:
			return ';';
		default:
			return inputSystem->ButtonCodeToString(key)[0];
	}
}

std::string Util::GetButtonName(ButtonCode_t buttonCode)
{
	return inputSystem->ButtonCodeToString(buttonCode);
}

ButtonCode_t Util::GetButtonCode(std::string buttonName)
{
	for (int i = 0; i < ButtonCode_t::KEY_XSTICK2_UP; i++)
	{
		const char* currentButton = inputSystem->ButtonCodeToString((ButtonCode_t) i);
		if (strcmp(currentButton, buttonName.c_str()) == 0)
			return (ButtonCode_t) i;
	}

	return ButtonCode_t::BUTTON_CODE_INVALID;
}

IMaterial* Util::CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert)
{
	static int matNum = 1;
	std::stringstream materialData;
	materialData << "\"" + type + "\"\n"
			"{\n"
			"\t\"$basetexture\" \"" + texture + "\"\n"
			"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
			"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
			"\t\"$model\" \"" + std::to_string(model) + "\"\n"
			"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
			"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
			"}\n" << std::flush;

    char randomLetter = 'a' + rand()%26;
	std::string time = randomLetter + std::string( __TIME__ ); // compile time XX:XX:XX
	time.erase( std::remove(time.begin(), time.end(), ':'), time.end() ); // remove colons
	std::string materialName = time + "_" + std::to_string( matNum );
    cvar->ConsoleDPrintf("MatName: %s\n", materialName.c_str());
	matNum++;

	KeyValues* keyValues = new KeyValues(materialName.c_str());
	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, materialName.c_str(), materialData.str().c_str(), nullptr, NULL, nullptr);

	return material->CreateMaterial(materialName.c_str(), keyValues);
}