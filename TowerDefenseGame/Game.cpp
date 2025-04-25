#include "Game.h"
#include "ContentPipeline.h"
#include "SceneTitle.h"
#include "SceneTransition.h"
#include "SceneGame.h"
#include "SceneEnd.h"


Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner
	renderWindow.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tower Defense Game");  // , Style::Titlebar); / , Style::FullScreen);

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	//renderWindow.setVerticalSyncEnabled(true);  //De plus en plus d'�crans sont rafraichis � plus de 60 frames par seconde, alors attention.
	renderWindow.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.6/window-window.php

	renderWindow.setKeyRepeatEnabled(false);
	srand((int)time(0));
	
	//Nouveau: toujours la m�me chose pour avoir un icon dans l'explorateur Windows
	icon.loadFromFile("Ressources\\Sprites\\Misc\\Icon.png");
	renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int Game::run()
{
	if (!ContentPipeline::getInstance().loadContent()) return EXIT_FAILURE;

	//Un enum et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes sceneSelector = Scene::scenes::LEVEL1;
	Scene* activeScene = nullptr; //Pointeur de la super-classe, peut pointer sur n'importe quelle sc�ne

	//Les variables de passage d'information entre sc�nes devraient �tre d�clar�s ici

	while (true)
	{
		//Seules conditions de sortie de toute l'app, une pour les sorties normales, une pour les erreurs
		//On est au seul point de sortie
		if (sceneSelector == Scene::scenes::EXIT) return EXIT_SUCCESS;
		if (sceneSelector == Scene::scenes::FAIL) return EXIT_FAILURE;
		

		//Vous allez ajouter d'autre sc�nes, alors elles devront
		//�tre ajout�es ici
		switch (sceneSelector)
		{
		case Scene::scenes::TITLE:
			//Les deux attributs sont r�cessaire et pass�s par r�f�rence
			activeScene = new SceneTitle(renderWindow, event);
			break;
		case Scene::scenes::TRANSITION:
			//Les deux attributs sont r�cessaire et pass�s par r�f�rence
			activeScene = new SceneTransition(renderWindow, event);
			break;
		case Scene::scenes::LEVEL1:
			//Les deux attributs sont r�cessaire et pass�s par r�f�rence
			activeScene = new SceneGame(renderWindow, event);
			break;
		case Scene::scenes::END:
			activeScene = new SceneEnd(renderWindow, event);
			break;
		}
		
		if (activeScene->init()) //Si l'initilisation s'est bien pass�, on entre dans ce bloc
		{
			//Run est la boucle de jeu de la sc�ne
			//� la fin de cette m�thode, elle retourne la sc�ne
			//Laquelle on transition
			sceneSelector = activeScene->run();

			//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
			//C'est possible de les faire l�.
			/*SceneGame* tempScene = dynamic_cast<SceneGame*>(activeScene);
			if (tempScene != nullptr)//Donc si le cast a r�ussi.
			{

			}*/			
		}
		else //Si l'initialisation rate (exemple: pour assets mal charg�s), on fail et on nettoie ce qui est � nettoyer
		{
			sceneSelector = Scene::scenes::FAIL;
			//clean-up �ventuel � faire pour s'assurer 
			//de ne pas avoir de leak (malgr� l'�chec)
		}		

		//N�cessaire tout ce qui est cr�e avec new doit �tre effac�.
		delete activeScene;
		activeScene = nullptr;
	}
}