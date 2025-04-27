#include "Level1.h"
#include "ContentPipeline.h"

Level1::Level1(RenderWindow& renderWindow, Event& event) : SceneGame::SceneGame(renderWindow, event)
{
}

bool Level1::init()
{
	if (!SceneGame::init()) return false;
	
	map.setTexture(ContentPipeline::getInstance().getMapTexture(map1));

	return true;
}

void Level1::initWaypoints()
{
	for (int i = 0; i < WAYPOINTS_AMOUNT; i++)
	{
		Waypoint* newWaypoint = new Waypoint();
		newWaypoint->init(WAYPOINT_POSITIONS[i]);
		waypoints.push_back(newWaypoint);
	}

	for (int i = 0; i < WAYPOINTS_AMOUNT - 1; i++)
	{
		waypoints[i]->setNextWaypoint(waypoints[i + 1]);
	}
}

void Level1::draw()
{
	renderWindow.clear();
	SceneGame::draw();

	if (showWaypoints)
	{
		for (int i = 0; i < WAYPOINTS_AMOUNT; i++)
		{
			waypoints[i]->draw(renderWindow);
		}
	}

	renderWindow.display();
}

bool Level1::unload()
{
	for (int i = 0; i < WAYPOINTS_AMOUNT; i++)
	{
		delete waypoints[i];
	}
	waypoints.clear();
	return true;
}

