class CInput
{
public:
	char _pad0[0xAC];
	bool m_fCameraInterceptingMouse;
	bool m_fCameraInThirdPerson;
	bool m_fCameraMovingWithMouse;
	Vector m_vecCameraOffset;
	bool m_fCameraDistanceMove;
	int m_nCameraOldX;
	int m_nCameraOldY;
	int m_nCameraX;
	int m_nCameraY;
	bool m_CameraIsOrthographic;
};