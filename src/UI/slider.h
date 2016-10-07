#ifndef __SLIDER_H_
#define __SLIDER_H_

#include "component.h"
#include "../settings.h"
#include <math.h>

#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

class Slider : public Component
{
private:
	float* value;
	const float MIN;
	const float MAX;
public:
	std::string text = "slider";
	
	Slider (std::string text, Vector2D position, Vector2D size, float* value, float MIN, float MAX)
			: MIN (MIN), MAX (MAX)
	{
		this->position = position;
		this->size = size;
		this->text = text;
		this->value = value;
	}
	
	void MouseTick (PositionContext context);
	void Draw ();
};

#endif