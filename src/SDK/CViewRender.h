#pragma once

struct CViewSetup
{
	char pad_0000[16];
	int32_t width;
	int32_t unscaledWidth;
	int32_t height;
	int32_t unscaledHeight;
	char pad_0020[152];
	float fov;
	float fovViewModel;
	Vector origin;
	Vector angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	float m_nDoFQuality;
	int32_t m_nMotionBlurMode;
};

class CViewRender
{
};
