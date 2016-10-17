#ifndef __IVDEBUGOVERLAY_H
#define __IVDEBUGOVERLAY_H

class IVDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(* oScreenPosition)(void*, const Vector&, Vector&);
		getvfunc<oScreenPosition>(this, 11)(this, vIn, vOut);
	}
};

#endif
