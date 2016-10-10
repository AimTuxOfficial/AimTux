#ifndef __DLIGHTS_H
#define __DLIGHTS_H

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Dlights
{
	void PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force);
}

#endif