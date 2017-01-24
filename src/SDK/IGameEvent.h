#pragma once

#define EVENT_DEBUG_ID_INIT 42
#define EVENT_DEBUG_ID_SHUTDOWN 13

class IGameEvent
{
public:
	const char* GetName()
	{
		typedef const char* (* oGetName)(void*);
		return getvfunc<oGetName>(this, 2)(this);
	}

	int GetInt(const char* Key, int Default = 0)
	{
		typedef int (* oGetInt)(void*, const char*, int);
		return getvfunc<oGetInt>(this, 7)(this, Key, Default);
	}

	const char* GetString(const char* Key)
	{
		typedef const char* (* oGetString)(void*, const char*);
		return getvfunc<oGetString>(this, 10)(this, Key);
	}

	void SetString(const char* Key, const char* Value)
	{
		typedef void (* oGetString)(void*, const char*, const char*);
		return getvfunc<oGetString>(this, 17)(this, Key, Value);
	}
};

class IGameEventListener2
{
public:
	virtual ~IGameEventListener2(void) {};

	virtual void FireGameEvent(IGameEvent *event) = 0;
	virtual int GetEventDebugID(void) = 0;
};

class IGameEventManager2
{
public:
	bool AddListener(IGameEventListener2 *listener, const char *name, bool bServerSide)
	{
		typedef bool (* oAddListener)(void*, IGameEventListener2*, const char*, bool);
		return getvfunc<oAddListener>(this, 4)(this, listener, name, bServerSide);
	}

	void RemoveListener(IGameEventListener2 *listener)
	{
		typedef void (* oRemoveListener)(void*, IGameEventListener2*);
		return getvfunc<oRemoveListener>(this, 6)(this, listener);
	}
};
