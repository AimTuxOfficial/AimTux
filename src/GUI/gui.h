#pragma once

#include "../settings.h"

namespace GUI
{
	/* CSGO Panels */
	extern panorama::IUIPanel* menuRoot;
	extern panorama::IUIPanel* hudRoot;
	/* Custom Panels */
	extern panorama::IUIPanel* fuzionMain;

	void ToggleUI();
}