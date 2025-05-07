#pragma once
#include "SceneGame.h"
#include "TwoPathWaypoint.h"

/*
Metrics de du level 2 (à effacer à la fin)
- Position de la tour du roi: 1138, 564
- Position des emplacements de tour: (110, 620), (228, 320), (444, 780), (362, 530), (610, 222), (998, 270), (630, 460), (935, 520), (798, 760),
- Position des waypoints: (88.f, 412.f), (168.f, 465.f), (222.f, 588.f), (308.f, 670.f), (424.f, 668.f), (double sortie: 510.f, 590.f);
                          (478.f, 468.f), (516.f, 380.f), (594.f, 360.f), (806.f, 368.f), (1140.f, 450.f), (660.f, 598.f), (804.f, 650.f), (1140.f, 680.f),
- Position de départ des démons: -100, 410

- Le reste est identique à la scène 1
*/

class Level2 : public SceneGame
{
public:
	Level2(RenderWindow& renderWindow, Event& event, int currentWave, int score, int highScore);
	bool init() override;
private:
	void initWaypoints() override;
	void draw() override;
	bool unload() override;

	Waypoint* getNextWaypointForDemon(Demon* demon) const override;

	// Toutes les constantes relatives au niveau devraient être stockés dans le fichier du niveau plutôt que Constants.h
	// Le fichier du niveau ne deviendra pas trop costaud à cause de ça car le meat du projet se fera de toute façon dans SceneGame.h

	// Waypoints.h
	static const int WAYPOINTS_AMOUNT_HIGH = 5;
	static const int WAYPOINTS_AMOUNT_BOTTOM = 9;

	static const int LEVEL2_WAYPOINTS_AMOUNT = 14;
	const Vector2f WAYPOINT_POSITIONS[LEVEL2_WAYPOINTS_AMOUNT] = 
	{
		Vector2f(88.f, 412.f),
		Vector2f(168.f, 465.f),
		Vector2f(222.f, 588.f),
		Vector2f(308.f, 670.f),
		Vector2f(424.f, 668.f),
		Vector2f(510.f, 590.f), // double sortie
		Vector2f(478.f, 468.f), // début du chemin du haut
		Vector2f(516.f, 380.f),
		Vector2f(594.f, 360.f),
		Vector2f(806.f, 368.f),
		Vector2f(1140.f, 450.f),
		Vector2f(660.f, 598.f), // début du chemin du bas
		Vector2f(804.f, 650.f),
		Vector2f(1140.f, 680.f),
	};

	// Démons
	const Vector2f LEVEL2_DEMON_POSITION = Vector2f(-100.0f, 410.0f);
};

