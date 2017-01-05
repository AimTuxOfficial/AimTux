#pragma once

class IVPanel
{
public:
	const char *GetName(VPANEL vguiPanel)
	{
		typedef const char* (* oGetName)(void*, VPANEL);
		return getvfunc<oGetName>(this, 37)(this, vguiPanel);
	}
};