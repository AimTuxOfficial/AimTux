#pragma once

#include <vector>
#include "component.h"
#include "button.h"
#include "panel.h"
#include "../settings.h"

class Tab;

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
	std::vector<Tab*> tabs;
	void UpdateTabColors (int id);
	int tab_size;
	TabSelector (Vector2D position, Vector2D size, std::vector<TabElement> tabs);
};

class Tab : public Button
{
	Panel** targetPanel;
	TabSelector* parent;
public:
	TabElement info;
	Color backgroundColor;
	int id = 0;
	Tab (Vector2D position, Vector2D size, Panel** targetPanel, TabElement info, TabSelector* parent);
	
	void OnClicked ();
	void Draw ();
};