#pragma once

class IGameEventManager2
{
};

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
