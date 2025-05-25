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
		castSacredLight = false;
		castPlague = false;
		activeActionChanged = false;
		clickOnScreen = false;
        togglePause = false;
	}

	Vector2f mousePosition;
	bool mouseLeftButtonClicked;
	bool toggleWaypoints;
    bool buildArcherTower = false;
    bool buildMageTower = false;
	bool castSacredLight = false;
	bool castPlague = false;
	bool activeActionChanged;
	bool clickOnScreen;
    bool togglePause;
};
