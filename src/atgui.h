#pragma once

#include "UI/stdui.h"

#include "WINDOWS/menu_window.h"
#include "PANELS/aimbot_panel.h"
#include "PANELS/triggerbot_panel.h"
#include "PANELS/esp_panel.h"
#include "PANELS/hvh_panel.h"
#include "PANELS/misc_window.h"
#include "WINDOWS/main_window.h"

extern MainWindow* main_window;
extern MenuWindow* menu_window;
extern MiscWindow* misc_window;

void SetupUI();