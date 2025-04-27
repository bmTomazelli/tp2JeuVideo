#pragma once
#include <SFML/Graphics.hpp>

struct Inputs
{
	Inputs()
	{
		reset();
	}

	void reset()
	{
		mousePosition = Vector2f(0.0f, 0.0f);
		mouseLeftButtonClicked = false;
		toggleWaypoints = false;
	}

	Vector2f mousePosition;
	bool mouseLeftButtonClicked;
	bool toggleWaypoints;
};
