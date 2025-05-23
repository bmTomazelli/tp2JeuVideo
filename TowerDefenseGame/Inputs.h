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
        buildArcherTower = false;
        buildMageTower = false;
        activeActionChanged = false;
        clickOnScreen = false;
	}

	Vector2f mousePosition;
	bool mouseLeftButtonClicked;
	bool toggleWaypoints;
    bool activeActionChanged;
    bool buildArcherTower = false;
    bool buildMageTower = false;
    bool clickOnScreen;
};
