#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

static const int SCORE_MAX_ENTRIES = 2; // Nombre maximum d'entrées de score

struct ScoreEntry {
    int score;
    int wave;
};

struct ScoreBinary {
    ScoreEntry scores[1];//le meilleur score
};

class Game
{
public:
	Game();
	int run();

    bool saveScore(int score, int wave);

private:
	//Ces deux attributs viennent de Windows
	//il faut les garder unique et constant durant tout le jeu
	//et les passer aux différentes scènes.
	RenderWindow renderWindow;
	Event event;

	Image icon;

    char* dataFile = "Ressources\\Data\\HighScore.data";
    void serializeScores();
    bool deserializeScores();
    ScoreEntry highScoreData;
};