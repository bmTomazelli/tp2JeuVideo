#include "Level2.h"
#include "ContentPipeline.h"

Level2::Level2(RenderWindow& renderWindow, Event& event) : SceneGame::SceneGame(renderWindow, event)
{
}

bool Level2::init()
{
	if (!SceneGame::init()) return false;
	map.setTexture(ContentPipeline::getInstance().getMapTexture(map2));

	return true;
}

void Level2::initWaypoints()
{
	// Initialisation de chaque waypoints
	for (int i = 0; i < TOTAL_WAYPOINTS_AMOUNT; i++)
	{
		// Au sixième waypoints (index 5 du tableau de positions), la double sortie est initialisé 
		if (i == 5)
		{
			TwoPathWaypoint* twoPathWaypoint = new TwoPathWaypoint();
			twoPathWaypoint->init(WAYPOINT_POSITIONS[i]);
			waypoints.push_back(twoPathWaypoint);
			continue;
		}

		Waypoint* newWaypoint = new Waypoint();
		newWaypoint->init(WAYPOINT_POSITIONS[i]);
		waypoints.push_back(newWaypoint);
	}

	// Routage de la route avant la séparation
	for (int i = 0; i < 5; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}

	// Mise en place de la séparation
	waypoints[5]->setNextWaypoint(waypoints[6]);
	static_cast<TwoPathWaypoint*>(waypoints[5])->setOtherWaypoint(waypoints[11]); // Cast en TwoPathWaypoint pour utiliser la méthode setOtherWaypoint

	// Routage du haut
	for (int i = 6; i < 10; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}

	// Routage du bas
	for (int i = 11; i < TOTAL_WAYPOINTS_AMOUNT - 1; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}
}

void Level2::draw()
{
	renderWindow.clear();
	SceneGame::draw();

	if (showWaypoints)
	{
		for (int i = 0; i < TOTAL_WAYPOINTS_AMOUNT; i++)
		{
			waypoints[i]->draw(renderWindow);
		}
	}

	renderWindow.display();
}

bool Level2::unload()
{
	for (int i = 0; i < TOTAL_WAYPOINTS_AMOUNT; i++)
	{
		delete waypoints[i];
	}
	waypoints.clear();
	return true;
}

const Waypoint* Level2::assignPathToDemon() const
{
	int random = rand() % 2;
	if (random == 0)
	{
		return waypoints[6];
	}
	else
	{
		return waypoints[11];
	}
}
