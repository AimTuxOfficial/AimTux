#ifndef __ICLIENTENTITYLIST_H
#define __ICLIENTENTITYLIST_H

class IClientEntityList {
public:
	C_BaseEntity* GetClientEntity(int index)
	{
		typedef C_BaseEntity* (* oGetClientEntity)(void*, int);
		return getvfunc<oGetClientEntity>(this, 3)(this, index);
	}

	int GetHighestEntityIndex()
	{
		typedef int (* oGetHighestEntityIndex)(void*);
		return getvfunc<oGetHighestEntityIndex>(this, 6)(this);
	}
};

#endif