cd #include "clantagchanger.h"
#include "util.h"

std::string Settings::ClanTagChanger::value = "";
bool Settings::ClanTagChanger::animation = false;
bool Settings::ClanTagChanger::enabled = false; // TODO find a way to go back to the "official" clan tag for the player? -- Save the current clan tag, before editing, then restore it later

std::vector<ClanTagChanger::Animation> ClanTagChanger::animations =
{
	Animation ("NOVAC",
		std::vector<ClanTagChanger::Frame>
		{
			Frame ("_____________NO", 500),
			Frame ("____________NO_", 500),
			Frame ("___________NO_V", 500),
			Frame ("__________NO_VA", 500),
			Frame ("_________NO_VAC", 500),
			Frame ("________NO_VAC_", 500),
			Frame ("_______NO_VAC_O", 500),
			Frame ("______NO_VAC_ON", 500),
			Frame ("_____NO_VAC_ON_", 500),
			Frame ("____NO_VAC_ON_L", 500),
			Frame ("___NO_VAC_ON_LI", 500),
			Frame ("__NO_VAC_ON_LIN", 500),
			Frame ("_NO_VAC_ON_LINU", 500),
			Frame ("O_VAC_ON_LINUX_", 500),
			Frame ("_VAC_ON_LINUX__", 500),
			Frame ("VAC_ON_LINUX___", 500),
			Frame ("AC_ON_LINUX____", 500),
			Frame ("C_ON_LINUX_____", 500),
			Frame ("_ON_LINUX______", 500),
			Frame ("ON_LINUX_______", 500),
			Frame ("N_LINUX________", 500),
			Frame ("_LINUX_________", 500),
			Frame ("LINUX__________", 500),
			Frame ("INUX___________", 500),
			Frame ("NUX____________", 500),
			Frame ("UX_____________", 500),
			Frame ("X______________", 500),
			Frame ("_______________", 500),
			Frame ("____AimTux!____", 900),
			Frame ("_______________", 500),
			Frame ("____AimTux!____", 900),
			Frame ("_______________", 500),
			Frame ("____AimTux!____", 900),
			Frame ("_______________", 500),
		}, ANIM_LOOP
	),

	Animation ("USPINME",
		std::vector<ClanTagChanger::Frame>
		{
			Frame ("You", 700),
			Frame ("spin", 700),
			Frame ("me", 700),
			Frame ("right", 700),
			Frame ("round,", 700),
			Frame ("baby", 700),
			Frame ("right", 700),
			Frame ("round", 700),
			Frame ("like", 700),
			Frame ("a", 700),
			Frame ("record", 700),
			Frame ("baby", 700),
			Frame ("right", 700),
			Frame ("round", 700),
			Frame ("_round", 700),
			Frame ("__round", 800),
		}, ANIM_LOOP
	)
};
ClanTagChanger::Animation* ClanTagChanger::animation = &ClanTagChanger::animations[0];

void ClanTagChanger::CreateMove(CUserCmd* cmd)
{
	if (!Settings::ClanTagChanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (Settings::ClanTagChanger::value.size() == 0 && !Settings::ClanTagChanger::animation)
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp > ClanTagChanger::animation->GetCurrentFrame().time)
	{
		timeStamp = currentTime_ms;
		ClanTagChanger::animation->NextFrame();
	}

	if (Settings::ClanTagChanger::animation)
	{
		SendClanTag(ClanTagChanger::animation->GetCurrentFrame().text.c_str(), "");
	}
	else
	{
		std::string ctWithEscapesProcessed = std::string(Settings::ClanTagChanger::value);
		Util::StdReplaceStr(ctWithEscapesProcessed, "\\n", "\n"); // compute time impact? also, referential so i assume RAII builtin cleans it up...
		SendClanTag(ctWithEscapesProcessed.c_str(), "");
	}
}
