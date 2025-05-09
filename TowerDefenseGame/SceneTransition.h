#pragma once
#include "Scene.h"

using namespace sf;

class SceneTransition : public Scene
{
public:
	SceneTransition(RenderWindow& renderWindow, Event& event, int currentWave);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	const float TRANSITION_TIMER = 3.0f;

	View view;

	Font font;
	Text message;

	float timer = 0.0f;
	int currentWave;
};