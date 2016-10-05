#ifndef __ATGUI_H_
#define __ATGUI_H_

#include "UI/stdui.h"

#include "WINDOWS/main_window.h"
#include "WINDOWS/aimbot_window.h"
#include "WINDOWS/esp_window.h"
#include "WINDOWS/misc_window.h"

extern MainWindow* main_window;
extern Window* aimbot_window;
extern Window* esp_window;
extern Window* misc_window;

void SetupUI ();

#endif