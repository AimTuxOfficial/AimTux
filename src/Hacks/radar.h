#pragma once

#include <set>
#include "../settings.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"

namespace Radar
{
	enum EntityShape_t : int
	{
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_TRIANGLE,
		SHAPE_TRIANGLE_UPSIDEDOWN
	};
	ImColor GetRadarPlayerColor(C_BasePlayer* player, bool visible);
	void RenderWindow();
	void InGameRadar(C_BasePlayer* player);
	void BeginFrame();
};
