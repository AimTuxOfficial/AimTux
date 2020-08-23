#include "util.h"
#include "../interfaces.h"

#include <sstream>
#include <chrono>
#include <codecvt>
#include <locale> //wstring_convert

#pragma GCC diagnostic ignored "-Wformat-security"

void Util::Log(char const * const format, ...)
{
    char buffer[4096];
    static bool bFirst = true;
    FILE *logFile;

    if ( bFirst ) {
        logFile = fopen(Util::logFileName, "w"); // create new log
        fprintf(logFile, "--Start of log--\n");
        bFirst = false;
    } else {
        logFile = fopen(Util::logFileName, "a"); // append to log
    }
    setbuf( logFile, nullptr ); // Turns off buffered I/O; decreases performance, but no unflushed buffer if crash occurs.
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 4096, format, args);
    fprintf(logFile, buffer);
    va_end(args);
    fclose(logFile);
}

std::string Util::ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;

	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}

	return subject;
}

int Util::RandomInt(int min, int max)
{
	return rand()%(max-min + 1) + min;
}
void Util::StdReplaceStr(std::string& replaceIn, const std::string& replace, const std::string& replaceWith)
{
	size_t const span = replace.size();
	size_t const step = replaceWith.size();
	size_t index = 0;

	while (true)
	{
		index = replaceIn.find(replace, index);

		if (index == std::string::npos)
			break;

		replaceIn.replace(index, span, replaceWith);
		index += step;
	}
}

const char* Util::PadStringRight(std::string text, size_t value)
{
	text.insert(text.length(), value - text.length(), ' ');

	return text.c_str();
}

bool Util::Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string Util::ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int (*)(int))std::tolower);

	return str;
}

std::string Util::ToUpper(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int (*)(int))std::toupper);

	return str;
}

std::string Util::WstringToString(std::wstring wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.to_bytes(wstr);
	}
	catch (std::range_error&)
	{
		std::stringstream s;
		s << wstr.c_str();
		return s.str();
	}
}

std::wstring Util::StringToWstring(std::string str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.from_bytes(str);
	}
	catch (std::range_error&)
	{
		std::wostringstream s;
		s << str.c_str();
		return s.str();
	}
}
/* Get Epoch timestamp in ms */
long Util::GetEpochTime()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

ImColor Util::GetRainbowColor(float speed)
{
	speed = 0.002f * speed;
	long now = Util::GetEpochTime();
	float hue = (now % (int)(1.0f / speed)) * speed;

	return ImColor::HSV(hue, 1.0f, 1.0f);
}

Color Util::GetHealthColor(int hp)
{
	return Color(
			std::min(510 * (100 - hp) / 100, 255),
			std::min(510 * hp / 100, 255),
			25
	);
}

Color Util::GetHealthColor(C_BasePlayer* player)
{
	return Color(
			std::min(510 * (100 - player->GetHealth()) / 100, 255),
			std::min(510 * player->GetHealth() / 100, 255),
			25
	);
}
