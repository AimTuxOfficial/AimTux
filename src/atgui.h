#ifndef __ATGUI_H_
#define __ATGUI_H_

#include "UI/stdui.h"

#include "WINDOWS/main_window.h"
#include "WINDOWS/aimbot_window.h"
#include "WINDOWS/esp_window.h"
#include "WINDOWS/hvh_window.h"
#include "WINDOWS/misc_window.h"

extern MainWindow* main_window;
extern AimbotWindow* aimbot_window;
extern ESPWindow* esp_window;
extern HVHWindow* hvh_window;
extern MiscWindow* misc_window;

void SetupUI();

#endif