#include "window.h"
#include "button.h"
#include "radiobutton.h"
#include "label.h"
#include "toggle.h"
#include "slider.h"
#include "listbox.h"
#include "banner.h"
#include "textbox.h"

#define BELOW(c) Vector2D (10, c->position.y + c->size.y + 10)
#define STACK(c) Vector2D (c->position.x + c->size.x + 10, c->position.y)