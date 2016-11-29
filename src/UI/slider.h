#pragma once

#include "component.h"
#include "../settings.h"
#include <math.h>

#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

class Slider : public Component
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (60, 60, 60, 255);
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
	void Input ();
};

class Slider_INT : public Component
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (60, 60, 60, 255);
private:
	int* value;
	const int MIN;
	const int MAX;
public:
	std::string text = "slider";

	Slider_INT (std::string text, Vector2D position, Vector2D size, int* value, int MIN, int MAX)
			: MIN (MIN), MAX (MAX)
	{
		this->position = position;
		this->size = size;
		this->text = text;
		this->value = value;
	}

	void MouseTick (PositionContext context);
	void Draw ();
	void Input ();
};
