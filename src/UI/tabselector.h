#pragma once

#include "component.h"
#include "button.h"
#include "panel.h"
#include "../settings.h"

struct TabElement
{
	std::string name;
	Panel* panel;
	
	TabElement ()
	{
	}
	
	TabElement (std::string name, Panel* panel)
	{
		this->name = name;
		this->panel = panel;
	}
};

class TabSelector : public Panel
{
	std::vector<Panel*> tabbedPanels;
	Panel* currentPanel;
public:
	TabSelector (Vector2D position, Vector2D size, std::vector<TabElement> tabs);
};

class Tab : public Button
{
	Panel** targetPanel;
	TabElement info;
public:
	Tab (Vector2D position, Vector2D size, Panel** targetPanel, TabElement info);
	
	void OnClicked ();
	void Draw ();
};