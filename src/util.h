#pragma once

#include <string>
#include <sys/mman.h>
#include <zconf.h>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Util {
	char GetButtonString(ButtonCode_t key);
	char GetUpperValueOf(ButtonCode_t key);
	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	void StdReplaceStr(std::string&, const std::string&, const std::string&);
	void ProtectAddr(void* address, int prot);
	bool ReadSendPacket();
	void WriteSendPacket(bool value);
}