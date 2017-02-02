#pragma once

class CBaseHandle;

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int entindex) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle handle) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle(CBaseHandle handle) = 0;
	// FIXME: GetClientEntity should return an IClientEntity pointer.
	virtual C_BaseEntity* GetClientEntity(int entindex) = 0;
	// FIXME: GetClientEntityFromHandle should accept a CBaseHandle.
	virtual IClientEntity* GetClientEntityFromHandle(void* handle) = 0;
	virtual int NumberOfEntities(bool include_non_networkable) = 0;
	virtual int GetHighestEntityIndex(void) = 0;
	virtual void SetMaxEntities(int max_entities) = 0;
	virtual int GetMaxEntities() = 0;
};
