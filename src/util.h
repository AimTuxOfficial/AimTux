#pragma once

#include <string>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Util {
	char GetButtonString(ButtonCode_t key);
	char GetUpperValueOf(ButtonCode_t key);
	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	void StdReplaceStr(std::string&, const std::string&, const std::string&);
}