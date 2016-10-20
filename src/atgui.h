#pragma once

#include "UI/stdui.h"

#include "WINDOWS/menu_window.h"
#include "PANELS/aimbot_window.h"
#include "PANELS/triggerbot_window.h"
#include "PANELS/esp_window.h"
#include "PANELS/hvh_window.h"
#include "PANELS/misc_window.h"
#include "WINDOWS/main_window.h"

extern MainWindow* main_window;
extern MenuWindow* menu_window;
extern TriggerbotWindow* triggerbot_window;
extern ESPWindow* esp_window;
extern HVHWindow* hvh_window;
extern MiscWindow* misc_window;

void SetupUI();