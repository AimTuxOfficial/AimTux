#include "namechanger.h"

int NameChanger::changes = -1;

void NameChanger::BeginFrame(float frameTime)
{
	if (!engine->IsInGame())
		return;

	if (changes == -1)
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 150)
		return;

	timeStamp = currentTime_ms;
	changes++;

	if (changes >= 5)
	{
		std::string name = "\n";
		char characters[3] = { '\n', '\0', '\t' };

		for (int i = 0; i < 127; i++)
			name += characters[RandomInt(0, 2)];

		SetName(name.c_str());
		changes = -1;

		return;
	}

	SetName(Util::PadStringRight("AIMTUX.NET", strlen("AIMTUX.NET") + changes));
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
