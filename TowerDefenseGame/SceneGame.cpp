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
    initTowersEmplacements();

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
	{
		demons[i].init(currentWave);
        demons[i].setSceneGame(this);
        Subject::addObserver(&demons[i]);
	}

    // Initialisation des projectiles
    for (int i = 0; i < MAX_TOWERS_PROJECTILES; i++)
    {
        arrows[i].init(Projectile::ARROW);
        arrows[i].setSceneGame(this);

        blasts[i].init(Projectile::BLAST);
        blasts[i].setSceneGame(this);
    }

    for (int i = 0; i < MAX_FIREBALL_AMOUNT; i++)
    {
        fireballs[i].init(Projectile::FIREBALL);
    }

    kingTower.init();

    for (int i = 0; i < MAX_ARCHER_TOWERS; i++)
    {
        archerTowers[i].init();
    }

    for (int i = 0; i < MAX_MAGE_TOWERS; i++)
    {
        mageTowers[i].init();
    }

    hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont(), currentWave);

    sacredLight.init();
    plague.init();

    mana = DEFAULT_MANA_AMOUNT;

	Subject::addObserver(this);

	music.setVolume(DESIRED_MUSIC_VOLUME);
	music.play();
	return true;
}

const int SceneGame::getScore() const
{
    return score;
}

const int SceneGame::getHighScore() const
{
    return highScore;
}

const bool SceneGame::isVictory() const
{
    return !isKingDead;
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
            if (event.key.code == Keyboard::Z)
            {
                inputs.activeActionChanged = true;
                inputs.buildArcherTower = true;
            }

            if (event.key.code == Keyboard::X)
            {
                inputs.activeActionChanged = true;
                inputs.buildMageTower = true;
            }

            if (event.key.code == Keyboard::A)
            {
                inputs.activeActionChanged = true;
                inputs.castPlague = true;
            }

            if (event.key.code == Keyboard::S)
            {
                inputs.activeActionChanged = true;
                inputs.castSacredLight = true;
            }

            if (event.key.code == Keyboard::P)
            {
                inputs.togglePause = true;
            }

            if (event.key.code == Keyboard::Enter)
            {
                if (isGameEnd)
                    transitionToNextScene();
            }
		}

        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                inputs.clickOnScreen = true;
                inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
            }
        }
	}

	if (Joystick::isConnected(0))
	{

	}
	else
	{

	}
}

void SceneGame::update()
{
	if (isGameEnd) return;

    managePause();

    if (isInPause) return;

    if (inputs.activeActionChanged) manageActiveActionChange();

    if (inputs.clickOnScreen) manageActiveAction();

	manageWaypoints();

    std::vector<Demon*> activeDemons;

    for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++) 
    {
        if (demons[i].isActive())
        {
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

    handleArchersAttackingDemons();
    handleDemonsTargets();
    handleProjectilesOnScreen();

    sacredLight.update(deltaTime);

    plague.update(deltaTime);

	hud.updateHud(mana, kills, score, highScore);

	manageDemonsSpawning();
    manageTimedManaGain();
	manageGameOver();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.draw(map);

    std::cout << "Is Occupied : " << listTowerEmplacements[0]->isOccupied() << "\n";
    std::cout << "Is Active : " << listTowerEmplacements[0]->isActive() << "\n";
	for (TowerEmplacement* towerEmplacement : listTowerEmplacements)
    {
        towerEmplacement->draw(renderWindow);
	}

    for (int i = 0; i < MAX_ARCHER_TOWERS; i++)
    {
        if (archerTowers[i].isActive())
            archerTowers[i].draw(renderWindow);
    }

    for (int i = 0; i < MAX_MAGE_TOWERS; i++)
    {
        if (mageTowers[i].isActive()) 
            mageTowers[i].draw(renderWindow);
    }

    kingTower.draw(renderWindow);

    for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
    {
        if (demons[i].isActive())
            demons[i].draw(renderWindow);
    }

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
	{
		if (demons[i].isActive())
			demons[i].drawDemonHealth(renderWindow);
	}

    if (showWaypoints)
    {
        for (int i = 0; i < waypointsAmount; i++)
            waypoints[i]->draw(renderWindow);
    }

    for (int i = 0; i < MAX_FIREBALL_AMOUNT; i++)
    {
        if (fireballs[i].isActive())
            fireballs[i].draw(renderWindow);
    }

    for (int i = 0; i < MAX_TOWERS_PROJECTILES; i++)
    {
        if (arrows[i].isActive())
            arrows[i].draw(renderWindow);

        if (blasts[i].isActive())
            blasts[i].draw(renderWindow);
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

void SceneGame::manageActiveAction()
{
    switch (activeAction)
    {
    case BUILD_ARCHER:
        if (mana < BUILD_ARCHER_TOWER_COST) return;

        selectedEmplacement = getTowerEmplacementFromClickedPosition(inputs.mousePosition);

        if (selectedEmplacement)
        {
            for (int i = 0; i < MAX_ARCHER_TOWERS; i++)
            {
                if (!archerTowers[i].isActive())
                {
                    archerTowers[i].spawn(selectedEmplacement->getPosition());
                    selectedEmplacement->occupyTower(&archerTowers[i]);
                    mana -= BUILD_ARCHER_TOWER_COST;
                    break;
                }
            }
        }

        selectedEmplacement = nullptr;
        break;
    case BUILD_MAGE:
        if (mana < BUILD_MAGE_TOWER_COST) return;

        selectedEmplacement = getTowerEmplacementFromClickedPosition(inputs.mousePosition);

        if (selectedEmplacement)
        {
            for (int i = 0; i < MAX_MAGE_TOWERS; i++)
            {
                if (!mageTowers[i].isActive())
                {
                    mageTowers[i].spawn(selectedEmplacement->getPosition());
                    selectedEmplacement->occupyTower(&mageTowers[i]);
                    mana -= BUILD_MAGE_TOWER_COST;
                    break;
                }
            }
        }

        selectedEmplacement = nullptr;
        break;
    case CAST_PLAGUE:
        if (mana < CAST_PLAGUE_SPELL_COST) return;

        plague.activate(inputs.mousePosition);
        
        if (plague.isActive())
            mana -= CAST_PLAGUE_SPELL_COST;

        break;
    case CAST_SACRED_LIGHT:
        if (mana < CAST_SACRED_LIGHT_COST) return;

        sacredLight.activate(inputs.mousePosition);

        if (sacredLight.isActive())
            mana -= CAST_SACRED_LIGHT_COST;

        break;
    }
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

void SceneGame::managePause()
{
    if (inputs.togglePause)
    {
        if (isInPause)
        {
            isInPause = false;
            music.play();
        }
        else
        {
            isInPause = true;
            music.pause();
        }
    }
}

void SceneGame::manageGameOver()
{
	if (kills == MAX_DEMONS_AMOUNT)
	{
		hud.changeToEndGameHud(true);
        isGameEnd = true;
	}
	
    if (isKingDead)
	{
		hud.changeToEndGameHud(false);
        isGameEnd = true;
	}
}

void SceneGame::manageActiveActionChange()
{
    if (inputs.buildArcherTower) activeAction = ActiveAction::BUILD_ARCHER;

    if (inputs.buildMageTower) activeAction = ActiveAction::BUILD_MAGE;

    if (inputs.castPlague) activeAction = ActiveAction::CAST_PLAGUE;

    if (inputs.castSacredLight) activeAction = ActiveAction::CAST_SACRED_LIGHT;

    hud.handleActiveAction(activeAction);
}

void SceneGame::manageTimedManaGain()
{
    manaGainTimer += deltaTime;

    if (manaGainTimer >= MANA_GAIN_TIMER)
    {
        mana += 1;
        manaGainTimer = 0.0f;
    }
}

void SceneGame::transitionToNextScene()
{
    if (isKingDead || currentWave == MAX_WAVES)
    {
        transitionToScene = Scene::scenes::END;
    }
    else
    {
        transitionToScene = Scene::scenes::TRANSITION;
    }

    isRunning = false;
}

void SceneGame::handleArchersAttackingDemons()
{
    for (TowerEmplacement* towerEmplacement : listTowerEmplacements)
    {
        std::vector<Demon*> demonPointers;
        for (int i = 0; i < demonsAmount; ++i)
        {
            if (demons[i].isActive())
                demonPointers.push_back(&demons[i]);
        }

        if (towerEmplacement->isOccupied())
        {
            Tower* tower = towerEmplacement->getTower();
            Demon* demon = tower->findNearestTarget(demonPointers);
            if (demon && tower->canShoot())
            {
                if (dynamic_cast<ArcherTower*>(tower))
                {
                    for (int i = 0; i < MAX_TOWERS_PROJECTILES; ++i)
                    {
                        if (!arrows[i].isActive())
                        {
                            arrows[i].shoot(tower->getPosition(), demon);
                            tower->prepareShooting();
                            break;
                        }
                    }
                }
            }
        }
    }
}

void SceneGame::handleDemonsTargets()
{
    for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
    {
        if (demons[i].isActive() && demons[i].canShoot())
        {
            Tower* nearestTarget = findNearestTowerFromDemon(&demons[i], listTowerEmplacements);
            if (nearestTarget)
            {
                for (int j = 0; j < MAX_FIREBALL_AMOUNT; j++)
                {
                    if (!fireballs[j].isActive())
                    {
                        fireballs[j].shoot(demons[i].getPosition(), nearestTarget);
                        demons[i].prepareShooting();
                        break;
                    }
                }
            }
        }
    }
}

void SceneGame::updateScore(int dmgPoints)
{
    this->score += dmgPoints;

    if (this->highScore < this->score)
        this->highScore = score;
}

void SceneGame::updateKill() 
{
    this->kills++;
    this->mana += MANA_GAIN_AFTER_KILL;
}

void SceneGame::handleProjectilesOnScreen()
{
    for (int i = 0; i < MAX_FIREBALL_AMOUNT; i++)
    {
        if (fireballs[i].isActive())
            fireballs[i].moveToTarget(deltaTime);
    }

    for (int i = 0; i < MAX_TOWERS_PROJECTILES; i++)
    {
        if (arrows[i].isActive())
            arrows[i].moveToTarget(deltaTime);

        if (blasts[i].isActive())
            blasts[i].moveToTarget(deltaTime);
    }
}

Waypoint* SceneGame::getNextWaypointForDemon(Demon* demon) const
{
	return demon->getWaypointToFollow()->getNextWaypoint();
}

Tower* SceneGame::findNearestTowerFromDemon(const Demon* demon, const std::vector<TowerEmplacement*>& towers)
{
    Tower* closest = nullptr;
    const float demonRangeSq = demon->getRangeOfFire() * demon->getRangeOfFire();
    float closestDistance = demonRangeSq;

    // Validation de s'il est proche de la tour du roi
    float distanceFromKingX = kingTower.getPosition().x - demon->getPosition().x;
    float distanceFromKingY = kingTower.getPosition().y - demon->getPosition().y;
    float distanceFromKingSq = distanceFromKingX * distanceFromKingX + distanceFromKingY * distanceFromKingY;

    if (distanceFromKingSq <= demonRangeSq)
        return &kingTower;

    // Validation de s'il est proche s'un des emplacements de tours
    for (TowerEmplacement* towerEmplacement : towers)
    {
        if (!towerEmplacement->isOccupied()) 
            continue;

        float dx = towerEmplacement->getPosition().x - demon->getPosition().x;
        float dy = towerEmplacement->getPosition().y - demon->getPosition().y;
        float distSq = dx * dx + dy * dy;

        if (distSq <= closestDistance)
        {
            closestDistance = distSq;
            closest = towerEmplacement->getTower();
        }
    }

    return closest;
}

TowerEmplacement* SceneGame::getTowerEmplacementFromClickedPosition(const Vector2f clickedPosition)
{
    for (TowerEmplacement* emplacement : listTowerEmplacements)
    {
        if (!emplacement->isOccupied() && emplacement->getGlobalBounds().contains(clickedPosition))
        {
            return emplacement;
        }
    }

    return nullptr;
}

void SceneGame::notify(Subject* subject)
{
    if (typeid(*subject) == typeid(Demon))
    {
        Demon* demon = static_cast<Demon*>(subject);
        Waypoint* nextWaypoint = getNextWaypointForDemon(demon);
        demon->assignWaypointToFollow(nextWaypoint);
    }

    if (typeid(*subject) == typeid(MageTower))
    {
        MageTower* mage = static_cast<MageTower*>(subject);
        for (int i = 0; i < MAX_TOWERS_PROJECTILES; ++i)
        {
            if (!blasts[i].isActive())
            {
                blasts[i].shoot(mage->getPosition(), mage->getTarget());
                mage->prepareShooting();
                break;
            }
        }
    }

    if (typeid(*subject) == typeid(KingTower))
    {
        isKingDead = true;
    }
}

bool SceneGame::isGameEnded() const
{
    return isGameEnd;
}
