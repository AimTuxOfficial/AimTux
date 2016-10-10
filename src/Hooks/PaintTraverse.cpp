#include "hooks.h"

static bool IsButtonPressed(ButtonCode_t code)
{
	static long buttonPressedTick = 0;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

	if (input->IsButtonDown(code) && (currentTime_ms - buttonPressedTick) > 300)
	{
		buttonPressedTick = currentTime_ms;
		return true;
	}

	return false;
}

void Hooks::PaintTraverse(void* thisptr, VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	panel_vmt->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vgui_panel, force_repaint, allow_force);

	static unsigned long long int panelID;
	if (!panelID && !strcmp(panel->GetName(vgui_panel), "FocusOverlayPanel"))
		panelID = vgui_panel;

	if (vgui_panel != panelID)
		return;

	if (IsButtonPressed(ButtonCode_t::KEY_INSERT))
		gui->Toggle();

	ESP::PaintTraverse(vgui_panel, force_repaint, allow_force);
	Recoilcrosshair::PaintTraverse(vgui_panel, force_repaint, allow_force);

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	std::list<std::string> observators = Entity::GetObservervators(localplayer);
	int index = 1;

	if (engine->IsInGame() && observators.size() > 1)
	{
		Draw::DrawString(L"Spectators:", LOC(10, 500), Color(255, 255, 255), normal_font, false);

		for (std::string name : observators)
		{
			std::wstring wstr(name.begin(), name.end());

			Draw::DrawString(wstr.c_str(), LOC(10, 500 + 20 * index), Color(255, 255, 255), normal_font, false);
			index++;
		}
	}

	gui->Draw();
}