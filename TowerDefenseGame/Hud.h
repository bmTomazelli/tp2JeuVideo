#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

/*
À NOTER: La couleur Gold pour le texte de "l'action active" : Color(212, 175, 55, 255)
*/
class Hud
{
public:
	Hud() {}
	void hudInit(const Texture& hudMaskTexture, const Font& font, int currentWave);
	void updateHud(int mana, int kills, int score, int highScore);
	void draw(sf::RenderWindow& renderWindow);

    void handleActiveAction(const ActiveAction activeAction);
	void changeToEndGameHud(bool isVictory);

private:
	static const int INSTRUCTIONS_NUMBER = 6;
	static const int TEXT_POSITION_X = 1250;

    void resetColors();

	bool endGame = false;
	bool useGamePad = false;

	sf::Text specialStateText;
	sf::Text pressCommandText;

	sf::Text manaText;
	sf::Text scoreText;
	sf::Text killsText;

	sf::Text instructionTexts[INSTRUCTIONS_NUMBER];

	sf::Text highScoreText;
	sf::Text waveText;

	Sprite hudMask;
};
