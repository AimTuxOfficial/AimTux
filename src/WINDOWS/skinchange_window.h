#pragma once

class SkinChangeWindow;

#include "../UI/stdui.h"
#include "../atgui.h"

class SkinChangeWindow : public Window
{
private:
//Components
	TabSelector* tabSelector;
//Panels
	Panel* pl_knife;
public:
	SkinChangeWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};
