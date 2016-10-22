#include "namechanger.h"

bool Settings::NameChanger::enabled = false;
bool Settings::NameChanger::last_blank = false;

const char* atom[] = { "Aim", "Tux", "Owns", "Me", "And All" };

void NameChanger::CreateMove ()
{
	if (!Settings::NameChanger::enabled)
	{
		return;
	}
	
	static int changes = -1;
	
	if (changes > 4)
	{
		Settings::NameChanger::enabled = false;
		return;
	}
	
	changes++;
	
	if (changes == 4 && Settings::NameChanger::last_blank)
	{
		SetName ((char*)"\n");
	}
	else if (changes < 4)
	{
		SetName (atom[changes]);
	}
}

void NameChanger::SetName (const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
