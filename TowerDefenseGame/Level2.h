#pragma once
#include "SceneGame.h"
#include "TwoPathWaypoint.h"

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

	// Toutes les constantes relatives au niveau devraient �tre stock�s dans le fichier du niveau plut�t que Constants.h
	// Le fichier du niveau ne deviendra pas trop costaud � cause de �a car le meat du projet se fera de toute fa�on dans SceneGame.h

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
		Vector2f(478.f, 468.f), // d�but du chemin du haut
		Vector2f(516.f, 380.f),
		Vector2f(594.f, 360.f),
		Vector2f(806.f, 368.f),
		Vector2f(1140.f, 450.f),
		Vector2f(660.f, 598.f), // d�but du chemin du bas
		Vector2f(804.f, 650.f),
		Vector2f(1140.f, 680.f),
	};

	// D�mons
	const Vector2f LEVEL2_DEMON_POSITION = Vector2f(-100.0f, 410.0f);

	// Tower emplacement
	const Vector2f TOWER_POSITIONS[9] =
	{
		Vector2f(110.f, 620.f),
		Vector2f(228.f, 320.f),
		Vector2f(444.f, 780.f),
		Vector2f(362.f, 530.f),
		Vector2f(610.f, 222.f),
		Vector2f(998.f, 270.f),
		Vector2f(630.f, 460.f),
		Vector2f(935.f, 520.f),
		Vector2f(798.f, 760.f)
	};

	const int MAX_NUMBER_OF_TOWERS = 9;

    void initTowersEmplacements() override;
};

