#include "namechanger.h"

bool Settings::NameChanger::enabled = false;
bool Settings::NameChanger::last_blank = false;

int NameChanger::changes = -1;
const char* atom[] = { "AIMTUX.NET", "AIMTUX.NET ", "AIMTUX.NET", "AIMTUX.NET ", "AIMTUX.NET" };
int atomSize = sizeof(atom) / sizeof(atom[0]);

void NameChanger::CreateMove(CUserCmd* cmd)
{
	if (!Settings::NameChanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (changes > atomSize - 1)
	{
		Settings::NameChanger::enabled = false;
		return;
	}
	
	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;
	
	if (currentTime_ms - timeStamp < 100)
		return;
	
	timeStamp = currentTime_ms;
	
	changes++;
	
	if (changes == atomSize - 1 && Settings::NameChanger::last_blank)
		SetName("\n");
	else if (changes < atomSize - 1)
		SetName(atom[changes]);
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
