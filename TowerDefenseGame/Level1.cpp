#include "Level1.h"
#include "ContentPipeline.h"
#include "Subject.h"

Level1::Level1(RenderWindow& renderWindow, Event& event, int currentWave, int score, int highScore) : SceneGame::SceneGame(renderWindow, event, currentWave, score, highScore)
{
}

bool Level1::init()
{
	waypointsAmount = LEVEL1_WAYPOINTS_AMOUNT;
	demonDefaultPosition = LEVEL1_DEMON_POSITION;
	towerEmplacementAmount = LEVEL_1_MAX_NUMBER_OF_TOWERS;

	if (!SceneGame::init()) return false;
	
	map.setTexture(ContentPipeline::getInstance().getMapTexture(map1));

    initTowersEmplacements();
    kingTower.spawn(Vector2f(1138, 564));

    Subject::addObserver(&kingTower);

	return true;
}

void Level1::initWaypoints()
{
	for (int i = 0; i < LEVEL1_WAYPOINTS_AMOUNT; i++)
	{
		Waypoint* newWaypoint = new Waypoint();
		newWaypoint->init(WAYPOINT_POSITIONS[i]);
		waypoints.push_back(newWaypoint);
	}

	for (int i = 0; i < LEVEL1_WAYPOINTS_AMOUNT - 1; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}
}

void Level1::initTowersEmplacements()
{
	for (int i = 0; i < towerEmplacementAmount; ++i)
	{
		TowerEmplacement* towerEmplacement = new TowerEmplacement();
		towerEmplacement->init(TOWER_POSITIONS[i]);
		listTowerEmplacements.push_back(towerEmplacement);
	}
}

void Level1::draw()
{
	// Au cas où le niveau aurait ces propres élément à dessiner, c'est celui-ci qui s'occupera de nettoyer et d'afficher la fenêtre.
	renderWindow.clear();
	SceneGame::draw();
	renderWindow.display();
}

bool Level1::unload()
{
	SceneGame::unload();
	return true;
}

