#include "clantagchanger.h"

char* Settings::ClanTagChanger::value = strdup("");
bool Settings::ClanTagChanger::animation = false;
int Settings::ClanTagChanger::animation_speed = 650;
bool Settings::ClanTagChanger::enabled = false; // TODO find a way to go back to the "official" clan tag for the player? -- Save the current clan tag, before editing, then restore it later
int Settings::ClanTagChanger::type = STATIC;

ClanTagChanger::Animation ClanTagChanger::Marquee(std::string name, std::wstring text, int width /*= 15*/)
{
	text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());

	std::wstring cropString = std::wstring(width, ' ') + text + std::wstring(width - 1, ' ');

	std::vector<ClanTagChanger::Frame> frames;
	for (unsigned long i = 0; i < text.length() + width; i++)
		frames.push_back(ClanTagChanger::Frame(cropString.substr(i, width + i), Settings::ClanTagChanger::animation_speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

std::vector<std::wstring> splitWords(std::wstring text)
{
	std::wistringstream stream(text);
	std::wstring word;
	std::vector<std::wstring> words;
	while (stream >> word)
		words.push_back(word);

	return words;
}

ClanTagChanger::Animation ClanTagChanger::Words(std::string name, std::wstring text)
{
	// Outputs a word by word animation
	std::vector<std::wstring> words = splitWords(text);
	std::vector<ClanTagChanger::Frame> frames;
	for (unsigned long i = 0; i < words.size(); i++)
		frames.push_back(Frame(words[i], Settings::ClanTagChanger::animation_speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

ClanTagChanger::Animation ClanTagChanger::Letters(std::string name, std::wstring text)
{
	// Outputs a letter incrementing animation
	std::vector<ClanTagChanger::Frame> frames;
	for (unsigned long i = 1; i <= text.length(); i++)
		frames.push_back(Frame(text.substr(0, i), Settings::ClanTagChanger::animation_speed));

	for (unsigned long i = text.length() - 2; i > 0; i--)
		frames.push_back(Frame(frames[i].text, Settings::ClanTagChanger::animation_speed));

	return ClanTagChanger::Animation(name, frames, ClanTagChanger::ANIM_LOOP);
}

std::vector<ClanTagChanger::Animation> ClanTagChanger::animations = {
	ClanTagChanger::Marquee("NOVAC", L"NO VAC ON LINUX"),
	ClanTagChanger::Words("USPINME", L"You spin me right round baby right round like a record baby right round _round __round"),
	ClanTagChanger::Letters("ILOVELINUX", L"Suck my Tux!")
};
ClanTagChanger::Animation* ClanTagChanger::animation = &ClanTagChanger::animations[0];

void ClanTagChanger::UpdateClanTagCallback()
{
	if (strlen(Settings::ClanTagChanger::value) > 0 && Settings::ClanTagChanger::type > STATIC)
	{
		std::wstring wc = Util::StringToWstring(Settings::ClanTagChanger::value);

		switch (Settings::ClanTagChanger::type)
		{
			case MARQUEE:
				*ClanTagChanger::animation = ClanTagChanger::Marquee("CUSTOM", wc);
				break;
			case WORDS:
				*ClanTagChanger::animation = ClanTagChanger::Words("CUSTOM", wc);
				break;
			case LETTERS:
				*ClanTagChanger::animation = ClanTagChanger::Letters("CUSTOM", wc);
				break;
		}

		return;
	}

	ClanTagChanger::animations = {
			ClanTagChanger::Marquee("NOVAC", L"NO VAC ON LINUX"),
			ClanTagChanger::Words("USPINME", L"You spin me right round baby right round like a record baby right round _round __round"),
			ClanTagChanger::Letters("ILOVELINUX", L"Suck my Tux!")
	};

	int current_animation = Settings::ClanTagChanger::type - 1;
	if (current_animation >= 0)
		ClanTagChanger::animation = &ClanTagChanger::animations[current_animation];
}

void ClanTagChanger::BeginFrame(float frameTime)
{
	if (!Settings::ClanTagChanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp > ClanTagChanger::animation->GetCurrentFrame().time)
	{
		timeStamp = currentTime_ms;
		ClanTagChanger::animation->NextFrame();
	}

	std::string ctWithEscapesProcessed = std::string(strdup(Settings::ClanTagChanger::value));
	Util::StdReplaceStr(ctWithEscapesProcessed, "\\n", "\n"); // compute time impact? also, referential so i assume RAII builtin cleans it up...

	if (Settings::ClanTagChanger::type == STATIC)
		SendClanTag(ctWithEscapesProcessed.c_str(), "");
	else
		SendClanTag(Util::WstringToString(ClanTagChanger::animation->GetCurrentFrame().text).c_str(), "");
}
