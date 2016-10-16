#include "chantagchanger.h"

char* Settings::ClanTagChanger::value = (char *) "";
bool Settings::ClanTagChanger::animation = false;
int Settings::ClanTagChanger::animation_speed = 500;

const char* animationKeyframes[] = {
		"A", "Ai", "Aim", "AimT", "AimTu", "AimTux"
};
long animationKeyframesSize = sizeof(animationKeyframes) / sizeof(animationKeyframes[0]);
int lastKeyframe = 0;

void ClanTagChanger::CreateMove(CUserCmd* cmd)
{
	if (!engine->IsInGame())
		return;

	if (strlen(Settings::ClanTagChanger::value) == 0 && !Settings::ClanTagChanger::animation)
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp > Settings::ClanTagChanger::animation_speed)
	{
		timeStamp = currentTime_ms;
		lastKeyframe++;

		if (lastKeyframe == animationKeyframesSize)
			lastKeyframe = 0;
	}

	if (Settings::ClanTagChanger::animation)
		SendClanTag(animationKeyframes[lastKeyframe], "");
	else
		SendClanTag(Settings::ClanTagChanger::value, "");
}