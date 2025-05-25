#pragma once
#include "SceneGame.h"

class Level1 : public SceneGame
{
public:
	Level1(RenderWindow& renderWindow, Event& event, int currentWave, int score, int highScore);
	bool init() override;
private:
	void initWaypoints() override;
	void draw() override;
	bool unload() override;

	// Toutes les constantes relatives au niveau devraient être stockés dans le fichier du niveau plutôt que Constants.h
	// Le fichier du niveau ne deviendra pas trop costaud à cause de ça car le meat du projet se fera de toute façon dans SceneGame.h

	// Waypoints
	static const int LEVEL1_WAYPOINTS_AMOUNT = 11;
	const Vector2f WAYPOINT_POSITIONS[LEVEL1_WAYPOINTS_AMOUNT] =
	{
		Vector2f(610, 8),
		Vector2f(630, 222),
		Vector2f(595, 444),
		Vector2f(478, 514),
		Vector2f(320, 558),
		Vector2f(260, 620),
		Vector2f(280, 720),
		Vector2f(348, 812),
		Vector2f(720, 830),
		Vector2f(968, 850),
		Vector2f(1110, 682),
	};

	// Démons
	const Vector2f LEVEL1_DEMON_POSITION = Vector2f(610, -100);

	// Tower emplacement
	const Vector2f TOWER_POSITIONS[8] =
	{
		Vector2f(470, 170),
		Vector2f(770, 250),
		Vector2f(440, 370),
		Vector2f(650, 520),
		Vector2f(120, 650),
		Vector2f(470, 700),
		Vector2f(850, 710),
		Vector2f(660, 950)
	};

	const int LEVEL_1_MAX_NUMBER_OF_TOWERS = 8;

	void initTowersEmplacements() override;
};

