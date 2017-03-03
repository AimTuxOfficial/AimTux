#include "skins.h"

void Skins::Localize()
{
	static bool isLocalized = false;
	if (isLocalized)
		return;

	if (itemSkins.size() == 0)
		return;

	isLocalized = true;
}
