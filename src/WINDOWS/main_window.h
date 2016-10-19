#pragma once

class MainWindow;

#include "../UI/stdui.h"
#include "../atgui.h"

class MainWindow : public Window
{
private:
	Panel* currentTab;
//Components
	TabSelector* tabSelector;
//Panels
	Panel* pl_visuals;
	Panel* pl_aimbot;
	Panel* pl_triggerbot;
	Panel* pl_hvh;
	Panel* pl_misc;
public:
	MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};