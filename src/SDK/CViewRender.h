#pragma once

struct CViewSetup
{
	int x;
	int m_nUnscaledX;
	int y;
	int m_nUnscaledY;
	int width;
	int m_nUnscaledWidth;
	int height;
	char pad_0x0020[0x9C];
	float fov;
	float fovViewmodel;
};

class CViewRender
{
};
