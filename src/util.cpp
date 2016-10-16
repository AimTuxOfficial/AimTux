#include "util.h"

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

char Util::GetUpperValueOf(ButtonCode_t key)
{
	switch (key)
	{
		case KEY_0:
			return ')';
		case KEY_1:
			return '!';
		case KEY_2:
			return '@';
		case KEY_3:
			return '#';
		case KEY_4:
			return '$';
		case KEY_5:
			return '%';
		case KEY_6:
			return '^';
		case KEY_7:
			return '&';
		case KEY_8:
			return '*';
		case KEY_9:
			return '(';
		case KEY_LBRACKET:
			return '{';
		case KEY_RBRACKET:
			return '}';
		case KEY_SEMICOLON:
			return ':';
		case KEY_APOSTROPHE:
			return '"';
		case KEY_BACKQUOTE:
			return '~';
		case KEY_COMMA:
			return '<';
		case KEY_PERIOD:
			return '>';
		case KEY_SLASH:
			return '?';
		case KEY_BACKSLASH:
			return '|';
		case KEY_MINUS:
			return '_';
		case KEY_EQUAL:
			return '+';
		default:
			return (char) std::toupper(input->ButtonCodeToString(key)[0]);
	}
}