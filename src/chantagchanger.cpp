#include "chantagchanger.h"

char* Settings::ClanTagChanger::value = (char*) "";
bool Settings::ClanTagChanger::animation = false;
std::vector<ClanTagChanger::Animation> ClanTagChanger::animations =
{
	Animation ("NOVAC",
		std::vector<ClanTagChanger::Frame>
		{
			Frame ("NO____", 700),
			Frame ("VAC___", 700),
			Frame ("ON_____", 850),
			Frame ("LINUX", 1700),
			Frame ("______", 600),
			Frame ("AimTux", 3000),
			Frame ("______", 700),
		}, ANIM_LOOP
	)
};
ClanTagChanger::Animation* ClanTagChanger::animation = &ClanTagChanger::animations[0];

void ClanTagChanger::CreateMove(CUserCmd* cmd)
{
	if (!engine->IsInGame())
		return;

	if (strlen(Settings::ClanTagChanger::value) == 0 && !Settings::ClanTagChanger::animation)
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
		SendClanTag(ClanTagChanger::animation->GetCurrentFrame().text.c_str(), "");
	else
		SendClanTag(Settings::ClanTagChanger::value, "");
}