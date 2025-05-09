#pragma once
#include "Scene.h"

using namespace sf;

class SceneEnd : public Scene
{
public:
	SceneEnd(RenderWindow& renderWindow, Event& event, int score, int highScore, int waveAmount);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	View view;

	Sprite endGameScreen;
	static const int INSTRUCTIONS_NUMBER = 4;
	Text instructions[INSTRUCTIONS_NUMBER];
	Music themeSong;

	bool isVictory = true;

	bool exit = false;
	bool returnToTitle = false;

	int score;
	int highScore;
	int waveAmount;
};