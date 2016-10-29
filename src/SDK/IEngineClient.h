#pragma once

class IEngineClient
{
public:
	typedef struct player_info_s {
		int64_t __pad0;
		union {
			int64_t xuid;
			struct {
				int xuidlow;
				int xuidhigh;
			};
		};
		char name[128];
		int userid;
		char guid[128];
		unsigned int friendsid;
		char friendsname[128];
		bool fakeplayer;
		bool ishltv;
		unsigned int customfiles[4];
		unsigned char filesdownloaded;
	} player_info_t;

	void GetScreenSize(int& width, int& height)
	{
		typedef void (* oGetScreenSize)(void*, int&, int&);
		getvfunc<oGetScreenSize>(this, 5)(this, width, height);
	}

	bool GetPlayerInfo(int iIndex, player_info_t *pInfo)
	{
		typedef bool (* oGetPlayerInfo)(void*, int, player_info_t*);
		getvfunc<oGetPlayerInfo>(this, 8)(this, iIndex, pInfo);
	}

	bool GetPlayerForUserID(int UserID)
	{
		typedef bool (* oGetPlayerForUserID)(void*, int);
		getvfunc<oGetPlayerForUserID>(this, 9)(this, UserID);
	}

	int GetLocalPlayer(void)
	{
		typedef int (* oGetLocalPlayer)(void*);
		getvfunc<oGetLocalPlayer>(this, 12)(this);
	}

	void GetViewAngles(QAngle& angle)
	{
		typedef void (* oGetViewAngles)(void*, QAngle&);
		getvfunc<oGetViewAngles>(this, 18)(this, angle);
	}

	void SetViewAngles(QAngle& angle)
	{
		typedef void (* oSetViewAngles)(void*, QAngle&);
		getvfunc<oSetViewAngles>(this, 19)(this, angle);
	}

	int GetMaxClients()
	{
		typedef int (* oGetMaxClients)(void*);
		getvfunc<oGetMaxClients>(this, 20)(this);
	}

	bool IsInGame()
	{
		typedef bool (* oIsInGame)(void*);
		getvfunc<oIsInGame>(this, 26)(this);
	}

	void ExecuteClientCmd(const char* szCmdString)
	{
		typedef void (* oExecuteClientCmd)(void*, const char*);
		getvfunc<oExecuteClientCmd>(this, 108)(this, szCmdString);
	}

	void ClientCmd_Unrestricted(const char* szCmdString)
	{
		typedef void (* oClientCmd_Unrestricted)(void*, const char*);
		getvfunc<oClientCmd_Unrestricted>(this, 113)(this, szCmdString);
	}

	void Print(const char* message)
	{
		char buffer[256];
		sprintf (buffer, "echo %s", message);

		ExecuteClientCmd(buffer);
	}
};