#pragma once

#include "window.h"
#include "button.h"
#include "radiobutton.h"
#include "label.h"
#include "toggle.h"
#include "slider.h"
#include "listbox.h"
#include "banner.h"
#include "textbox.h"
#include "tabselector.h"

#define BELOW(c) LOC (10, c->position.y + c->size.y + 10)
#define STACK(c) LOC (c->position.x + c->size.x + 10, c->position.y)
