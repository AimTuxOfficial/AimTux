#pragma once

#include "interfaces.h"

enum class ModType : int
{
	NO_MOD,
	CSCO
};

namespace ModSupport
{
	extern ModType current_mod;
	void OnInit();
}