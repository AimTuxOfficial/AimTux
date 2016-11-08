#include "util_input.h"

namespace Util {
	namespace Input {
		using b = enum ButtonCode_t;
		const std::map<std::string, enum ButtonCode_t> ButtonCodeNames = {
			{"BUTTON_CODE_INVALID",			b::BUTTON_CODE_INVALID},
			{"BUTTON_CODE_NONE",			b::BUTTON_CODE_NONE},
			{"KEY_NONE",					b::KEY_FIRST},
			{"KEY_0",						b::KEY_0},
			{"KEY_1",						b::KEY_1},
			{"KEY_2",						b::KEY_2},
			{"KEY_3",						b::KEY_3},
			{"KEY_4",						b::KEY_4},
			{"KEY_5",						b::KEY_5},
			{"KEY_6",						b::KEY_6},
			{"KEY_7",						b::KEY_7},
			{"KEY_8",						b::KEY_8},
			{"KEY_9",						b::KEY_9},
			{"KEY_A",						b::KEY_A},
			{"KEY_B",						b::KEY_B},
			{"KEY_C",						b::KEY_C},
			{"KEY_D",						b::KEY_D},
			{"KEY_E",						b::KEY_E},
			{"KEY_F",						b::KEY_F},
			{"KEY_G",						b::KEY_G},
			{"KEY_H",						b::KEY_H},
			{"KEY_I",						b::KEY_I},
			{"KEY_J",						b::KEY_J},
			{"KEY_K",						b::KEY_K},
			{"KEY_L",						b::KEY_L},
			{"KEY_M",						b::KEY_M},
			{"KEY_N",						b::KEY_N},
			{"KEY_O",						b::KEY_O},
			{"KEY_P",						b::KEY_P},
			{"KEY_Q",						b::KEY_Q},
			{"KEY_R",						b::KEY_R},
			{"KEY_S",						b::KEY_S},
			{"KEY_T",						b::KEY_T},
			{"KEY_U",						b::KEY_U},
			{"KEY_V",						b::KEY_V},
			{"KEY_W",						b::KEY_W},
			{"KEY_X",						b::KEY_X},
			{"KEY_Y",						b::KEY_Y},
			{"KEY_Z",						b::KEY_Z},

			{"KEY_PAD_0",					b::KEY_PAD_0},
			{"KEY_PAD_1",					b::KEY_PAD_1},
			{"KEY_PAD_2",					b::KEY_PAD_2},
			{"KEY_PAD_3",					b::KEY_PAD_3},
			{"KEY_PAD_4",					b::KEY_PAD_4},
			{"KEY_PAD_5",					b::KEY_PAD_5},
			{"KEY_PAD_6",					b::KEY_PAD_6},
			{"KEY_PAD_7",					b::KEY_PAD_7},
			{"KEY_PAD_8",					b::KEY_PAD_8},
			{"KEY_PAD_9",					b::KEY_PAD_9},
			{"KEY_PAD_DIVIDE",				b::KEY_PAD_DIVIDE},
			{"KEY_PAD_MULTIPLY",			b::KEY_PAD_MULTIPLY},
			{"KEY_PAD_MINUS",				b::KEY_PAD_MINUS},
			{"KEY_PAD_PLUS",				b::KEY_PAD_PLUS},
			{"KEY_PAD_ENTER",				b::KEY_PAD_ENTER},
			{"KEY_PAD_DECIMAL",				b::KEY_PAD_DECIMAL},

			{"KEY_LBRACKET",				b::KEY_LBRACKET},
			{"KEY_RBRACKET",				b::KEY_RBRACKET},
			{"KEY_SEMICOLON",				b::KEY_SEMICOLON},
			{"KEY_APOSTROPHE",				b::KEY_APOSTROPHE},
			{"KEY_BACKQUOTE",				b::KEY_BACKQUOTE},
			{"KEY_COMMA",					b::KEY_COMMA},
			{"KEY_PERIOD",					b::KEY_PERIOD},
			{"KEY_SLASH",					b::KEY_SLASH},
			{"KEY_BACKSLASH",				b::KEY_BACKSLASH},
			{"KEY_MINUS",					b::KEY_MINUS},
			{"KEY_EQUAL",					b::KEY_EQUAL},
			{"KEY_ENTER",					b::KEY_ENTER},
			{"KEY_SPACE",					b::KEY_SPACE},
			{"KEY_BACKSPACE",				b::KEY_BACKSPACE},
			{"KEY_TAB",						b::KEY_TAB},
			{"KEY_CAPSLOCK",				b::KEY_CAPSLOCK},
			{"KEY_NUMLOCK",					b::KEY_NUMLOCK},
			{"KEY_ESCAPE",					b::KEY_ESCAPE},
			{"KEY_SCROLLLOCK",				b::KEY_SCROLLLOCK},
			{"KEY_INSERT",					b::KEY_INSERT},
			{"KEY_DELETE",					b::KEY_DELETE},
			{"KEY_HOME",					b::KEY_HOME},
			{"KEY_END",						b::KEY_END},
			{"KEY_PAGEUP",					b::KEY_PAGEUP},
			{"KEY_PAGEDOWN",				b::KEY_PAGEDOWN},
			{"KEY_BREAK",					b::KEY_BREAK},
			{"KEY_LSHIFT",					b::KEY_LSHIFT},
			{"KEY_RSHIFT",					b::KEY_RSHIFT},
			{"KEY_LALT",					b::KEY_LALT},
			{"KEY_RALT",					b::KEY_RALT},
			{"KEY_LCONTROL",				b::KEY_LCONTROL},
			{"KEY_RCONTROL",				b::KEY_RCONTROL},
			{"KEY_LWIN",					b::KEY_LWIN},
			{"KEY_RWIN",					b::KEY_RWIN},
			{"KEY_APP",						b::KEY_APP},
			{"KEY_UP",						b::KEY_UP},
			{"KEY_LEFT",					b::KEY_LEFT},
			{"KEY_DOWN",					b::KEY_DOWN},
			{"KEY_RIGHT",					b::KEY_RIGHT},
			{"KEY_F1",						b::KEY_F1},
			{"KEY_F2",						b::KEY_F2},
			{"KEY_F3",						b::KEY_F3},
			{"KEY_F4",						b::KEY_F4},
			{"KEY_F5",						b::KEY_F5},
			{"KEY_F6",						b::KEY_F6},
			{"KEY_F7",						b::KEY_F7},
			{"KEY_F8",						b::KEY_F8},
			{"KEY_F9",						b::KEY_F9},
			{"KEY_F10",						b::KEY_F10},
			{"KEY_F11",						b::KEY_F11},
			{"KEY_F12",						b::KEY_F12},
			{"KEY_CAPSLOCKTOGGLE",			b::KEY_CAPSLOCKTOGGLE},
			{"KEY_NUMLOCKTOGGLE",			b::KEY_NUMLOCKTOGGLE},
			{"KEY_SCROLLLOCKTOGGLE",		b::KEY_SCROLLLOCKTOGGLE},

			{"MOUSE_RIGHT",					b::MOUSE_RIGHT},
			{"MOUSE_MIDDLE",				b::MOUSE_MIDDLE},
			{"MOUSE_4",						b::MOUSE_4},
			{"MOUSE_5",						b::MOUSE_5},
			{"MOUSE_WHEEL_UP",				b::MOUSE_WHEEL_UP},
			{"MOUSE_WHEEL_DOWN",			b::MOUSE_WHEEL_DOWN},

			{"JOYSTICK_FIRST_POV_BUTTON",	b::JOYSTICK_FIRST_POV_BUTTON},
			{"JOYSTICK_FIRST_AXIS_BUTTON",	b::JOYSTICK_FIRST_AXIS_BUTTON},

			{"BUTTON_CODE_LAST",			b::BUTTON_CODE_LAST},

			{"KEY_XBUTTON_RIGHT",			b::KEY_XBUTTON_RIGHT},
			{"KEY_XBUTTON_DOWN",			b::KEY_XBUTTON_DOWN},
			{"KEY_XBUTTON_LEFT",			b::KEY_XBUTTON_LEFT},
			{"KEY_XBUTTON_B",				b::KEY_XBUTTON_B},
			{"KEY_XBUTTON_X",				b::KEY_XBUTTON_X},
			{"KEY_XBUTTON_Y",				b::KEY_XBUTTON_Y},
			{"KEY_XBUTTON_LEFT_SHOULDER",	b::KEY_XBUTTON_LEFT_SHOULDER},
			{"KEY_XBUTTON_RIGHT_SHOULDER",	b::KEY_XBUTTON_RIGHT_SHOULDER},
			{"KEY_XBUTTON_BACK",			b::KEY_XBUTTON_BACK},
			{"KEY_XBUTTON_START",			b::KEY_XBUTTON_START},
			{"KEY_XBUTTON_STICK1",			b::KEY_XBUTTON_STICK1},
			{"KEY_XBUTTON_STICK2",			b::KEY_XBUTTON_STICK2},
			{"KEY_XBUTTON_INACTIVE_START",	b::KEY_XBUTTON_INACTIVE_START},
			{"KEY_XSTICK1_LEFT",			b::KEY_XSTICK1_LEFT},
			{"KEY_XSTICK1_DOWN",			b::KEY_XSTICK1_DOWN},
			{"KEY_XSTICK1_UP",				b::KEY_XSTICK1_UP},
			{"KEY_XBUTTON_LTRIGGER",		b::KEY_XBUTTON_LTRIGGER},
			{"KEY_XBUTTON_RTRIGGER",		b::KEY_XBUTTON_RTRIGGER},
			{"KEY_XSTICK2_RIGHT",			b::KEY_XSTICK2_RIGHT},
			{"KEY_XSTICK2_LEFT",			b::KEY_XSTICK2_LEFT},
			{"KEY_XSTICK2_DOWN",			b::KEY_XSTICK2_DOWN},
			{"KEY_XSTICK2_UP",				b::KEY_XSTICK2_UP}
		};  // ButtonCodeNames

		const std::string GetButtonName(const enum ButtonCode_t buttonCode)
		{
			auto iterator = std::find_if(ButtonCodeNames.begin(), ButtonCodeNames.end(), 
					[buttonCode](const std::pair<std::string, enum ButtonCode_t>& pair) {
						return pair.second == buttonCode;
					});

			if (iterator == ButtonCodeNames.end())
				return "BUTTON_CODE_INVALID";

			return iterator->first;
		}

		const enum ButtonCode_t GetButtonCode(const std::string buttonName)
		{
			auto result = ButtonCodeNames.find(buttonName);
			if (result != ButtonCodeNames.end())
				return result->second;

			return ButtonCode_t::BUTTON_CODE_INVALID;
		}

	}
}
