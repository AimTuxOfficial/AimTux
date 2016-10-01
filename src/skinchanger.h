#ifndef __SKINCHANGER_H
#define __SKINCHANGER_H

#include "SDK.h"
#include "interfaces.h"
#include "settings.h"
#include <unordered_map>

namespace SkinChanger {
	struct Skin
	{
		int PaintKit;
		int ItemDefinitionIndex;
		float Wear;
		int StatTrak;
		const char* CustomName;
		const char* Model;

		Skin (int PaintKit, int ItemDefinitionIndex, float Wear, int StatTrak, const char* CustomName, const char* Model)
		{
			this->PaintKit = PaintKit;
			this->ItemDefinitionIndex = ItemDefinitionIndex;
			this->Wear = Wear;
			this->StatTrak = StatTrak;
			this->CustomName = CustomName;
			this->Model = Model;
		}

		Skin() { };
	};

	extern std::unordered_map<int, Skin> skins;

	void FrameStageNotify(ClientFrameStage_t stage);
};

#endif
