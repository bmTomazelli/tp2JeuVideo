#include "Level2.h"
#include "ContentPipeline.h"

Level2::Level2(RenderWindow& renderWindow, Event& event, int currentWave) : SceneGame::SceneGame(renderWindow, event, currentWave)
{
}

bool Level2::init()
{
	waypointsAmount = LEVEL2_WAYPOINTS_AMOUNT;
	demonDefaultPosition = LEVEL2_DEMON_POSITION;

	if (!SceneGame::init()) return false;
	map.setTexture(ContentPipeline::getInstance().getMapTexture(map2));

	return true;
}

void Level2::initWaypoints()
{
	// Initialisation de chaque waypoints
	for (int i = 0; i < waypointsAmount; i++)
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

	// Routage du haut (Position 6 à 10 dans le tableau waypoints)
	for (int i = 6; i < 10; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}

	// Routage du bas (Position 11 à 14 dans le tableau waypoints)
	for (int i = 11; i < LEVEL2_WAYPOINTS_AMOUNT - 1; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}
}

void Level2::draw()
{
	// Au cas où le niveau aurait ces propres élément à dessiner, c'est celui-ci qui s'occupera de nettoyer et d'afficher la fenêtre.
	renderWindow.clear();
	SceneGame::draw();
	renderWindow.display();
}

bool Level2::unload()
{
	SceneGame::unload();
	return true;
}

Waypoint* Level2::getNextWaypointForDemon(Demon* demon) const
{
	Waypoint* currentWaypoint = demon->getWaypointToFollow();

	if (typeid(*currentWaypoint) == typeid(TwoPathWaypoint))
	{
		TwoPathWaypoint* twoPathWaypoint = static_cast<TwoPathWaypoint*>(currentWaypoint);

		int random = rand() % 2;
		if (random == 0)
			return twoPathWaypoint->getNextWaypoint();
		else
			return twoPathWaypoint->getOtherWaypoint();
	}

	return SceneGame::getNextWaypointForDemon(demon);
}
