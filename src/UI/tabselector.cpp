#include "tabselector.h"

TabSelector::TabSelector (Vector2D position, Vector2D size, std::vector<TabElement> tabs)
{
	this->position = position;
	this->size = size;
	
	this->currentPanel = tabs[0].panel;
	
	int tab_width = size.x / tabs.size();
	for (int i = 0; i < tabs.size(); i++)
	{
		TabElement element = tabs[i];
		
		element.panel->shown = false;
		
		Tab* new_tab = new Tab (LOC ((i * tab_width), 0), LOC (tab_width, size.y), &this->currentPanel, element);
		AddComponent (new_tab);
	}
	this->currentPanel->shown = true;
}


Tab::Tab (Vector2D position, Vector2D size, Panel** targetPanel, TabElement info)
	: Button (info.name, position, size)
{
	this->info = info;
	this->targetPanel = targetPanel;
	this->OnClickedEvent = MFUNC (&Tab::OnClicked, this);
}

void Tab::Draw ()
{
	if (info.panel->shown)
	{
		Clear (Settings::UI::mainColor);
	}
	else
	{
		DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
	}
	
	DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
}

void Tab::OnClicked ()
{
	(*this->targetPanel)->shown = false;
	(*this->targetPanel) = this->info.panel;
	(*this->targetPanel)->shown = true;
}
