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
		
		Tab* new_tab = new Tab (LOC ((i * tab_width), 0), LOC (tab_width, size.y), &this->currentPanel, element, this);
		this->tabs.push_back (new_tab);
		AddComponent (new_tab);
	}
	
	UpdateTabColors (0);
	
	this->currentPanel->shown = true;
}

void TabSelector::UpdateTabColors (int id)
{
	for (int i = 0; i < tabs.size(); i++)
	{
		float n = abs(i - id) + 1;
		Tab* tab = tabs[i];
		if (n > 1) n -= (0.75f * (n-1));
		tab->backgroundColor = Color (255 / n, 100 / n, 100 / n);
	}
}


Tab::Tab (Vector2D position, Vector2D size, Panel** targetPanel, TabElement info, TabSelector* parent)
	: Button (info.name, position, size)
{
	this->parent = parent;
	
	backgroundColor = Settings::UI::mainColor;
	
	static int id = -1;
	id++;
	this->id = id;
	this->info = info;
	this->targetPanel = targetPanel;
	this->OnClickedEvent = MFUNC (&Tab::OnClicked, this);
}

void Tab::Draw ()
{
	Clear (backgroundColor);
	
	DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
}

void Tab::OnClicked ()
{
	(*this->targetPanel)->shown = false;
	(*this->targetPanel) = this->info.panel;
	(*this->targetPanel)->shown = true;
	
	parent->UpdateTabColors (id);
}
