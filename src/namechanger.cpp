#include "namechanger.h"

bool Settings::NameChanger::enabled = false;
bool Settings::NameChanger::last_blank = false;

int NameChanger::changes = -1;
const char* atom[] = { "Aim", "Tux", "Owns", "Me", "And All" };

void NameChanger::CreateMove ()
{
	if (!Settings::NameChanger::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (changes > 4)
	{
		Settings::NameChanger::enabled = false;
		return;
	}

	changes++;
	
	if (changes == 4 && Settings::NameChanger::last_blank)
		SetName("\n");
	else if (changes < 4)
		SetName(atom[changes]);
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
