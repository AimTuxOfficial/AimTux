#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"

namespace Util
{
	char GetButtonString(ButtonCode_t key);
	std::string GetButtonName(ButtonCode_t buttonCode);
	ButtonCode_t GetButtonCode(std::string buttonName);
}