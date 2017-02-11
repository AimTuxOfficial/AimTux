#pragma once

class IClient;
class INetMessage;
class IRecipientFilter;
typedef void* netpacket_t;

class IConnectionlessPacketHandler
{
public:
	virtual ~IConnectionlessPacketHandler(void) {};

	virtual bool ProcessConnectionlessPacket(netpacket_t* packet) = 0; // process a connectionless packet
};

class IServer : public IConnectionlessPacketHandler
{
public:
	virtual	~IServer() {}

	virtual int GetNumClients(void) const = 0; // returns current number of clients
	virtual int GetNumProxies(void) const = 0; // returns number of attached HLTV proxies
	virtual int GetNumFakeClients() const = 0; // returns number of fake clients/bots
	virtual int GetMaxClients(void) const = 0; // returns current client limit
	virtual IClient* GetClient(int index) = 0; // returns interface to client
	virtual int GetClientCount() const = 0; // returns number of clients slots (used&  unused)
	virtual int GetUDPPort(void) const = 0; // returns current used UDP port
	virtual float GetTime(void) const = 0; // returns game world time
	virtual int GetTick(void) const = 0; // returns game world tick
	virtual float GetTickInterval(void) const = 0; // tick interval in seconds
	virtual float GetTimescale( void ) const = 0; // returns the game time scale (multiplied in conjunction with host_timescale)
	virtual const char* GetName(void) const = 0; // public server name
	virtual const char* GetMapName(void) const = 0; // current map name (BSP)
	virtual int GetSpawnCount(void) const = 0;
	virtual int GetNumClasses(void) const = 0;
	virtual int GetClassBits(void) const = 0;
	virtual void GetNetStats(float& avgIn, float& avgOut) = 0; // total net in/out in bytes/sec
	virtual int GetNumPlayers() = 0;
	virtual	bool GetPlayerInfo(int nClientIndex, IEngineClient::player_info_t* pinfo) = 0;

	virtual bool IsActive(void) const = 0;
	virtual bool IsLoading(void) const = 0;
	virtual bool IsDedicated(void) const = 0;
	virtual bool IsPaused(void) const = 0;
	virtual bool IsMultiplayer(void) const = 0;
	virtual bool IsPausable() const = 0;
	virtual bool IsHLTV() const = 0;
	virtual bool IsReplay() const = 0;

	virtual const char* GetPassword() const = 0; // returns the password or NULL if none set

	virtual void SetPaused(bool paused) = 0;
	virtual void SetTimescale(float flTimescale) = 0;
	virtual void SetPassword(const char* password) = 0; // set password (NULL to disable)

	virtual void BroadcastMessage(INetMessage& msg, bool onlyActive = false, bool reliable = false) = 0;
	virtual void BroadcastMessage(INetMessage& msg, IRecipientFilter& filter) = 0;

	virtual void DisconnectClient(IClient* client, const char* reason) = 0;
};

class CGameServer : public IServer
{

};