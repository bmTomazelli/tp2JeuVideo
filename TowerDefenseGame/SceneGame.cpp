#include "SceneGame.h"
#include "ContentPipeline.h"

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event, int currentWave, int score, int highScore) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->currentWave = currentWave;
	this->score = score;
	this->highScore = highScore;
}

Scene::scenes SceneGame::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;

	return transitionToScene;
}

bool SceneGame::init()
{	
	if (!music.openFromFile(MUSIC_FILENAMES[rand() % 3])) return false;

	initWaypoints();

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
	{
		demons[i].init(currentWave);
        Subject::addObserver(&demons[i]);
	}

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont(), currentWave);



    sacredLight.init();
    plague.init();

	Subject::addObserver(this);

    //Initialisation des emplacements de tours

	music.setVolume(DESIRED_MUSIC_VOLUME);
	music.play();
	return true;
}

void SceneGame::getInputs()
{
	inputs.reset();

	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::W)
				inputs.toggleWaypoints = true;

            if (event.key.code == Keyboard::Z) {
                inputs.buildArcherTower = true;
                inputs.buildMageTower = false;
            }
            if (event.key.code == Keyboard::X) {
                inputs.buildMageTower = true;
                inputs.buildArcherTower = false;
            }
				
            if (event.key.code == Keyboard::C) {
                inputs.castSacredLight = true;
                inputs.castPlague = false;
            }

            if (event.key.code == Keyboard::V) {
                inputs.castPlague = true;
                inputs.castSacredLight = false;
            }
                
            
		}

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            inputs.mouseLeftButtonClicked = true;
            inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
        }
	}

	if (Joystick::isConnected(0))
	{

	}
}

void SceneGame::update()
{
	if (isKingDead) return;

	manageWaypoints();
    std::vector<Demon*> activeDemons;

    //Pour la gestion des tours, si le joueur clique sur un emplacement de tour, on vérifie s'il est libre et on construit la tour
    if (inputs.mouseLeftButtonClicked) {
        for (TowerEmplacement* emplacement : listTowerEmplacements) {
            if (!emplacement->isOccupied()) {
                // On vérifie si le clic est dans l'emplacement de la tour
                if (emplacement->getGlobalBounds().contains(inputs.mousePosition)) {
                    // On vérifie si l'emplacement est de type archertower ou magetower
                    //on ajoutera plus tard la valeur de la mana dans cet if
                    if (inputs.buildArcherTower) {
                        for (int i = 0; i < MAX_ARCHER_TOWERS; ++i) {
                            if (!archerTowers[i].isActive()) {
                                archerTowers[i].init();
                                archerTowers[i].spawn(emplacement->getPosition());
                                emplacement->occupyTower(&archerTowers[i]);

                                Subject::addObserver(&archerTowers[i]);
                                break;
                            }
                        }
                        inputs.buildArcherTower = false;
                    }

                    //plus tard, on ajoutera la valeur de la mana dans cet if
                    else if (inputs.buildMageTower) {
                        for (int i = 0; i < MAX_MAGE_TOWERS; ++i) {
                            if (!mageTowers[i].isActive()) {
                                mageTowers[i].init();
                                mageTowers[i].spawn(emplacement->getPosition());
                                emplacement->occupyTower(&mageTowers[i]);

                                Subject::addObserver(&mageTowers[i]);
                                break;
                            }
                        }
                        inputs.buildMageTower = false;
                    }

                    break;
                }
            }
        }
    }


    for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++) {
        if (demons[i].isActive()) {
            demons[i].update(deltaTime);
            activeDemons.push_back(&demons[i]);
        }
    }

    for (int i = 0; i < MAX_ARCHER_TOWERS; i++)
    {
        if (archerTowers[i].isActive())
            archerTowers[i].update(deltaTime, activeDemons);
    }

    for (int i = 0; i < MAX_MAGE_TOWERS; i++)
    {
        if (mageTowers[i].isActive())
            mageTowers[i].update(deltaTime, activeDemons);
    }

    //Update pour les magies
    //si le joueur clique sur la souris gauche, on active la magie
    //plus tard, on ajoutera la valeur de la mana dans cet if
    if (inputs.castSacredLight && inputs.mouseLeftButtonClicked)
    {
        sacredLight.activate(inputs.mousePosition);
        inputs.castSacredLight = false;
    }

    sacredLight.update(deltaTime);

    //plus tard, on ajoutera la valeur de la mana dans cet if
    if (inputs.castPlague && inputs.mouseLeftButtonClicked)
    {
        plague.activate(inputs.mousePosition);
        inputs.castPlague = false;
    }

    plague.update(deltaTime);
	
	hud.updateHud(mana, kills, score, highScore);

	manageDemonsSpawning();
	manageGameOver();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.draw(map);

	for (TowerEmplacement* towerEmplacement : listTowerEmplacements)
    {
        towerEmplacement->draw(renderWindow);
	}

    for (int i = 0; i < MAX_ARCHER_TOWERS; i++)
    {
        if (archerTowers[i].isActive()) {
            archerTowers[i].draw(renderWindow);
        }
    }
    for (int i = 0; i < MAX_MAGE_TOWERS; i++)
    {
        if (mageTowers[i].isActive()) {
            mageTowers[i].draw(renderWindow);
        }
    }

    kingTower.draw(renderWindow);

    for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
    {
        if (demons[i].isActive())
        {
            demons[i].draw(renderWindow);
        }
    }

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
	{
		if (demons[i].isActive())
		{
			demons[i].drawDemonHealth(renderWindow);
		}
	}

    if (showWaypoints)
    {
        for (int i = 0; i < waypointsAmount; i++)
        {
            waypoints[i]->draw(renderWindow);
        }
    }

    sacredLight.draw(renderWindow);
    plague.draw(renderWindow);

	hud.draw(renderWindow);

}

bool SceneGame::unload()
{
	for (int i = 0; i < waypointsAmount; i++)
	{
		delete waypoints[i];
	}

    waypoints.clear();

    for (TowerEmplacement* towerEmplacement : listTowerEmplacements)
    {
        delete towerEmplacement;
    }
    listTowerEmplacements.clear();

	waypoints.clear();

	//Important: n’oubliez pas d’enlever tous les observateurs en fin de scène (unload) sinon vous aurez des crashs à travailler sur des observateurs désormais absents en mémoire.
	Subject::removeAllObservers();
	return true;
}

void SceneGame::manageWaypoints()
{
	if (inputs.toggleWaypoints)
	{
		if (showWaypoints)
			showWaypoints = false;
		else
			showWaypoints = true;
	}
}

void SceneGame::manageDemonsSpawning()
{
	if (demonsAmount == MAX_DEMONS_AMOUNT) 
		return;

	demonSpawningTimer += deltaTime;

	if (demonSpawningTimer >= nextDemonSpawnTime)
	{
		demonSpawningTimer = 0.0f;

		for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
		{
			if (!demons[i].isActive())
			{
				demonsAmount++;
				demons[i].spawnDemon(demonDefaultPosition);
				demons[i].assignWaypointToFollow(waypoints[0]);
				break;
			}
		}

		// Algorithme de génération aléatoire de secondes proposé par ChatGPT
		nextDemonSpawnTime = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f);
	}
}

void SceneGame::manageGameOver()
{
	if (kills == MAX_DEMONS_AMOUNT)
	{
		hud.changeToEndGameHud(true);
	}

	if (isKingDead)
	{
		hud.changeToEndGameHud(false);
	}
}

Waypoint* SceneGame::getNextWaypointForDemon(Demon* demon) const
{
	return demon->getWaypointToFollow()->getNextWaypoint();
}

void SceneGame::notify(Subject* subject)
{
	if (typeid(*subject) == typeid(Demon))
	{
		Demon* demon = static_cast<Demon*>(subject);
		Waypoint* nextWaypoint = getNextWaypointForDemon(demon);
		demon->assignWaypointToFollow(nextWaypoint);
	}
}
