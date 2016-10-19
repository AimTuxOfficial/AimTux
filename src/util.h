#ifndef __UTIL_H
#define __UTIL_H

#include <string>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Util {
	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	char GetButtonString(ButtonCode_t key);
	char GetUpperValueOf(ButtonCode_t key);
    void StdReplaceStr(std::string&, const std::string&, const std::string&);
}

#endif
