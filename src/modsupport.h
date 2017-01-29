#pragma once

#include "interfaces.h"

enum ModType : int
{
	NO_MOD,
	CSCO
};

namespace ModSupport
{
	extern ModType current_mod;
	void OnInit();
}