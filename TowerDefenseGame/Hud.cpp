#include "Hud.h"
#include <iostream>

void Hud::hudInit(const Texture& hudMaskTexture, const Font& font, int currentWave)
{
	hudMask.setTexture(hudMaskTexture);

	specialStateText.setFont(font);
	specialStateText.setCharacterSize(25);
	specialStateText.setFillColor(Color::White);
	specialStateText.setPosition(TEXT_POSITION_X, 10);

	//Utilisation sans honte du constructeur de copie
	manaText = specialStateText;
	scoreText = specialStateText;
	killsText = specialStateText;
	waveText = specialStateText;
	highScoreText = specialStateText;

	waveText.setPosition(TEXT_POSITION_X, 110);
	manaText.setPosition(TEXT_POSITION_X, 210);
	killsText.setPosition(TEXT_POSITION_X, 250);
	scoreText.setPosition(TEXT_POSITION_X, 290);
	highScoreText.setPosition(TEXT_POSITION_X, 330);

	waveText.setString("Wave - " + std::to_string(currentWave));
	manaText.setString("Mana - 0");
	killsText.setString("Kills - 0");
	scoreText.setString("Score - 0");
	highScoreText.setString("HighScore - 0");

	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
	{
		instructionTexts[i] = specialStateText;
		instructionTexts[i].setPosition(TEXT_POSITION_X, 430 + i * 40);
	}

	instructionTexts[0].setStyle(Text::Underlined);
	instructionTexts[0].setString("Instructions");
	instructionTexts[1].setString("Z: Create archer tower (70 manas)");
	instructionTexts[2].setString("X: Create mage tower (100 manas)");
	instructionTexts[3].setString("A: Plague spell (20 manas)");
	instructionTexts[4].setString("S: Sacred light spell (60 manas)");
	instructionTexts[5].setString("P: Pause");

	specialStateText.setCharacterSize(35);

	pressCommandText = specialStateText;
	pressCommandText.setPosition(TEXT_POSITION_X, 60);
}

void Hud::updateHud(int mana, int kills, int score, int highScore)
{
	manaText.setString("Mana - " + std::to_string(mana));
	killsText.setString("Kills - " + std::to_string(kills));
	scoreText.setString("Score - " + std::to_string(score));
	highScoreText.setString("HighScore - " + std::to_string(highScore));
}

void Hud::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(hudMask);
	renderWindow.draw(specialStateText);
	renderWindow.draw(pressCommandText);
	renderWindow.draw(manaText);
	renderWindow.draw(scoreText);
	renderWindow.draw(killsText);
	renderWindow.draw(highScoreText);
	renderWindow.draw(waveText);

	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
		renderWindow.draw(instructionTexts[i]);
}

void Hud::handleActiveAction(const ActiveAction activeAction)
{
    resetColors();
    instructionTexts[activeAction + 1].setColor(Color(212, 175, 55, 255));
}

void Hud::changeToEndGameHud(bool isVictory)
{
	endGame = true;
	if (isVictory)
		specialStateText.setString("Victory!");
	else
		specialStateText.setString("Game Over!");

	pressCommandText.setString("Press Enter to Continue");
}

void Hud::resetColors()
{
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
        instructionTexts[i].setColor(Color::White);
}
