#pragma once

#include "UI/stdui.h"

#include "WINDOWS/menu_window.h"
#include "PANELS/aimbot_panel.h"
#include "PANELS/triggerbot_panel.h"
#include "PANELS/visuals_panel.h"
#include "PANELS/hvh_panel.h"
#include "PANELS/misc_panel.h"
#include "PANELS/skinchanger_panel.h"
#include "WINDOWS/main_window.h"
#include "WINDOWS/popup_window.h"

extern MainWindow* main_window;
extern MenuWindow* menu_window;

void SetupUI();
