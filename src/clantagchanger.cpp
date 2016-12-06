#include "clantagchanger.h"
#include "util.h"

std::string Settings::ClanTagChanger::value = "";
bool Settings::ClanTagChanger::animation = false;
bool Settings::ClanTagChanger::enabled = false; // TODO find a way to go back to the "official" clan tag for the player? -- Save the current clan tag, before editing, then restore it later
ClanTagType Settings::ClanTagChanger::type = MARQUEE;

ClanTagChanger::Animation ClanTagChanger::Marquee(std::string name, std::string text, int width /*= 15*/, int speed /*= 650*/)
{
	// Outputs cool scrolling text animation

	char empty = '_';
	std::replace(text.begin(), text.end(), ' ', empty);

	std::string cropString = std::string(width, empty) + text + std::string(width - 1, empty);

	std::vector<ClanTagChanger::Frame> frames;
	for (int i = 0; i < text.length() + width; i++)
		frames.push_back(ClanTagChanger::Frame(cropString.substr(i, width + i), speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

std::vector<std::string> splitWords(std::string text)
{
	std::istringstream stream(text);
	std::string word;
	std::vector<std::string> words;
	while (stream >> word)
		words.push_back(word);

	return words;
}

ClanTagChanger::Animation ClanTagChanger::Words(std::string name, std::string text, int speed /*= 1000*/)
{
	// Outputs a word by word animation

	std::vector<std::string> words = splitWords(text);
	std::vector<ClanTagChanger::Frame> frames;
	for (int i = 0; i < words.size(); i++)
		frames.push_back(Frame(words[i], speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

ClanTagChanger::Animation ClanTagChanger::Letters(std::string name, std::string text, int speed /*= 1000*/)
{
	// Outputs a letter incrementing animation

	std::vector<ClanTagChanger::Frame> frames;
	for (int i = 1; i <= text.length(); i++)
		frames.push_back(Frame(text.substr(0, i), speed));

	for (int i = text.length() - 2; i > 0; i--)
		frames.push_back(Frame(frames[i].text, speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

std::vector<ClanTagChanger::Animation> ClanTagChanger::animations =
{
	ClanTagChanger::Marquee("NOVAC", "NO VAC ON LINUX"),
	ClanTagChanger::Words("USPINME", "You spin me right round baby right round like a record baby right round _round __round")
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
