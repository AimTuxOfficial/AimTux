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
	AimbotPanel* pl_aimbot;
	Panel* pl_triggerbot;
	Panel* pl_hvh;
	Panel* pl_misc;
	Panel* pl_skin;
	Panel* pl_config;
public:
	MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};
