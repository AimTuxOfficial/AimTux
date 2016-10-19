#pragma once

class IClientEntityList {
public:
	C_BaseEntity* GetClientEntity(int index)
	{
		typedef C_BaseEntity* (* oGetClientEntity)(void*, int);
		getvfunc<oGetClientEntity>(this, 3)(this, index);
	}

	C_BaseEntity* GetClientEntityFromHandle(void* handle)
	{
		typedef C_BaseEntity* (* oGetClientEntityFromHandle)(void*, void*);
		getvfunc<oGetClientEntityFromHandle>(this, 4)(this, handle);
	}

	int GetHighestEntityIndex()
	{
		typedef int (* oGetHighestEntityIndex)(void*);
		getvfunc<oGetHighestEntityIndex>(this, 6)(this);
	}
};