#pragma once

#include <string>
#include "../SDK/IInputSystem.h"
#include "../SDK/IMaterial.h"

namespace Util
{
	char GetButtonString(ButtonCode_t key);
	std::string GetButtonName(ButtonCode_t buttonCode);
	ButtonCode_t GetButtonCode(std::string buttonName);

	IMaterial* CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert);
}