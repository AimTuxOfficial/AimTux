#ifndef __IGAMEEVENT_H
#define __IGAMEEVENT_H

class IGameEventManager2 { };

class IGameEvent
{
public:
	const char* GetName() {
		typedef void (* oGetName)(void*);
		getvfunc<oGetName>(this, 2)(this);
	}

	int GetInt(const char* Key, int Default = 0) {
		typedef void (* oGetInt)(void*, const char*, int);
		getvfunc<oGetInt>(this, 7)(this, Key, Default);
	}

	const char* GetString(const char* Key) {
		typedef void (* oGetString)(void*, const char*);
		getvfunc<oGetString>(this, 10)(this, Key);
	}

	void SetString(const char* Key, const char* Value) {
		typedef void (* oGetString)(void*, const char*, const char*);
		getvfunc<oGetString>(this, 17)(this, Key, Value);
	}
};

#endif