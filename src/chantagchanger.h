#pragma once

#include <chrono>
#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"

namespace ClanTagChanger
{
	struct Frame
	{
		unsigned int time;
		std::string text;

		Frame (std::string text, unsigned int time)
		{
			this->text = text;
			this->time = time;
		}
	};

	enum AnimationLoopType
	{
		ANIM_LOOP,
		ANIM_LOOP_BACK
	};

	struct Animation
	{
		std::string name;
		unsigned int currentFrame;
		std::vector<Frame> frames;
		AnimationLoopType loopType;

		Animation(std::string name, std::vector<Frame> frames, AnimationLoopType loopType)
		{
			currentFrame = 0;
			this->name = name;
			this->frames = frames;
			this->loopType = loopType;
		}

		Frame GetCurrentFrame()
		{
			return frames[currentFrame];
		}

		void NextFrame()
		{
			currentFrame++;

			if (currentFrame >= frames.size())
				currentFrame = 0;
		}
	};

	extern std::vector<Animation> animations;
	extern Animation* animation;
	void CreateMove(CUserCmd* cmd);
}

extern SendClanTagFn SendClanTag;