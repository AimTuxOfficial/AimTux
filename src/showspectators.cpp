#include "showspectators.h"

bool Settings::ShowSpectators::enabled = true;

void ShowSpectators::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::ShowSpectators::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	std::list<std::string> observators = Entity::GetObservervators(localplayer);

	if (observators.size() == 0)
		return;

	int index = 1;
	pstring text;
	text << "Spectators (" << observators.size() << "):";

	Draw::DrawString(text.c_str(), LOC(10, 400), Color(255, 255, 255), normal_font, false);

	for (std::string name : observators)
	{
		Draw::DrawString(name.c_str(), LOC(10, 400 + 20 * index), Color(255, 255, 255), normal_font, false);
		index++;
	}
}