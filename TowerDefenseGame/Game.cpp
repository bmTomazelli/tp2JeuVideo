#include "Game.h"
#include "ContentPipeline.h"
#include "SceneTitle.h"
#include "SceneTransition.h"
#include "Level1.h"
#include "Level2.h"
#include "SceneEnd.h"
#include <iostream>
#include <fstream>


Game::Game()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner
	renderWindow.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tower Defense Game");  // , Style::Titlebar); / , Style::FullScreen);

	renderWindow.setKeyRepeatEnabled(false);
	srand((int)time(0));
	
	//Nouveau: toujours la même chose pour avoir un icon dans l'explorateur Windows
	icon.loadFromFile("Ressources\\Sprites\\Misc\\Icon.png");
	renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int Game::run()
{
    if (!ContentPipeline::getInstance().loadContent()) return EXIT_FAILURE;

    //Un enum et un pointeur de scene pour faire la manipulation de scène
    Scene::scenes sceneSelector = Scene::scenes::TITLE;
    Scene::levels levelSelector = Scene::levels::LEVEL1;

    Scene* activeScene = nullptr; //Pointeur de la super-classe, peut pointer sur n'importe quelle scène

    //On essaie de désérialiser les scores
    deserializeScores();

    //Les variables de passage d'information entre scènes devraient être déclarés ici
    int currentWave = 1;
    int score = 0;
    int highScore = highScoreData.score;
    int highWave = highScoreData.wave;
    bool victory = false;

    while (true)
    {
        //Seules conditions de sortie de toute l'app, une pour les sorties normales, une pour les erreurs
        //On est au seul point de sortie
        if (sceneSelector == Scene::scenes::EXIT) return EXIT_SUCCESS;
        if (sceneSelector == Scene::scenes::FAIL) return EXIT_FAILURE;

        //Vous allez ajouter d'autre scènes, alors elles devront
        //être ajoutées ici
        switch (sceneSelector)
        {
        case Scene::scenes::TITLE:
            //Les deux attributs sont récessaire et passés par référence
            activeScene = new SceneTitle(renderWindow, event);
            break;
        case Scene::scenes::TRANSITION:
            //Les deux attributs sont récessaire et passés par référence
            activeScene = new SceneTransition(renderWindow, event, currentWave);
            break;
        case Scene::scenes::GAME:
            if (levelSelector == Scene::levels::LEVEL1)
            {
                activeScene = new Level1(renderWindow, event, currentWave, score, highScore);
                break;
            }
            else if (levelSelector == Scene::levels::LEVEL2)
            {
                activeScene = new Level2(renderWindow, event, currentWave, score, highScore);
                break;
            }
        case Scene::scenes::END:
            activeScene = new SceneEnd(renderWindow, event, score, highScore, currentWave, highWave, victory);
            break;
        }

        if (activeScene->init()) 
        {
            sceneSelector = activeScene->run();

            SceneGame* tempScene = dynamic_cast<SceneGame*>(activeScene);

            if (tempScene != nullptr)
            {
                score = tempScene->getScore();
                highScore = tempScene->getHighScore();

                if (tempScene->isGameEnded()) {//verifie si le score actuel est plus haut que le score enregistré
                    saveScore(score, currentWave);

                    if (currentWave == MAX_WAVES)
                    {
                        victory = tempScene->isVictory();
                    }
                    else
                    {
                        currentWave++;
                        if (typeid(*tempScene) == typeid(Level1))
                            levelSelector = Scene::levels::LEVEL2;
                        else if (typeid(*tempScene) == typeid(Level2))
                            levelSelector = Scene::levels::LEVEL1;
                    }
                }
            }

            delete activeScene;
            activeScene = nullptr;
        }
        else
        {
            sceneSelector = Scene::scenes::FAIL;
        }
    }
}

void Game::serializeScores()
{
    // Créer la structure binaire pour la sauvegarde
    ScoreBinary scoreBinary;
    scoreBinary.scores[0] = highScoreData;

    // Convertir en tableau d'octets pour la sérialisation
    char binaryData[sizeof(ScoreBinary)];
    memcpy(binaryData, &scoreBinary, sizeof(ScoreBinary));

    // Écrire dans le fichier
    std::ofstream file(dataFile, std::ios::binary);
    if (file.is_open())
    {
        file.write(binaryData, sizeof(ScoreBinary));
        file.close();
    }
}


bool Game::saveScore(int score, int wave) {
    //On sauvegarde le score dans la structure
    if (score > highScoreData.score) {
    highScoreData.score = score;
    highScoreData.wave = wave;

    //On sérialise les scores
    serializeScores();
    return true;
    }

    return false;
}

bool Game::deserializeScores()
{
    std::ifstream file(dataFile, std::ios::binary);
    if (!file.is_open())
        return false;

    ScoreBinary scoreBinary = {}; // Réinitialise la struct

    // Vérifie si la taille du fichier est bonne
    file.read(reinterpret_cast<char*>(&scoreBinary), sizeof(ScoreBinary));
    if (!file)
    {
        // Erreur dans la lecture (Fichier trop petit)
        file.close();
        return false;
    }

    file.close();
    highScoreData = scoreBinary.scores[0];
    return true;
}

