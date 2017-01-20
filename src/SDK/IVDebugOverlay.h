#pragma once

class IVDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool (* oScreenPosition)(void*, const Vector&, Vector&);
		return getvfunc<oScreenPosition>(this, 11)(this, vIn, vOut);
	}
};