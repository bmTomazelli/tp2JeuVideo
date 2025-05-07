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
		demons[i].assignWaypointToFollow(waypoints[0]);
	}

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont(), currentWave);

	Subject::addObserver(this);

	music.setVolume(DESIRED_MUSIC_VOLUME);
	music.play();
	return true;
}

void SceneGame::getInputs()
{
	inputs.reset();

	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::W)
				inputs.toggleWaypoints = true;
			if (event.key.code == Keyboard::Enter)
			{

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
	if (isKingDead) return;

	manageWaypoints();

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
		demons[i].update(deltaTime);
	
	hud.updateHud(mana, kills, score, highScore);

	manageDemonsSpawning();
	manageGameOver();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'�cran pr�c�dent
	renderWindow.draw(map);

	if (showWaypoints)
	{
		for (int i = 0; i < waypointsAmount; i++)
		{
			waypoints[i]->draw(renderWindow);
		}
	}

	for (int i = 0; i < MAX_DEMONS_ON_SCREEN; i++)
	{
		if (demons[i].isActive())
		{
			demons[i].draw(renderWindow);
		}	
	}

	hud.draw(renderWindow);
}

bool SceneGame::unload()
{
	for (int i = 0; i < waypointsAmount; i++)
	{
		delete waypoints[i];
	}
	waypoints.clear();

	//Important: n�oubliez pas d�enlever tous les observateurs en fin de sc�ne (unload) sinon vous aurez des crashs � travailler sur des observateurs d�sormais absents en m�moire.
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
				break;
			}
		}

		// Algorithme de g�n�ration al�atoire de secondes propos� par ChatGPT
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
