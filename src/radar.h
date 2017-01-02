#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Radar
{
	enum EntityShape_t : int
	{
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_TRIANGLE
	};
	void DrawWindow();
};