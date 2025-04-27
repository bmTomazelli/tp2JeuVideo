#pragma once
#include "SceneGame.h"

/*
Metrics de sceneGame OU du level 1 (à effacer à la fin)
- Position de la tour du roi: 1138, 600
- Position des emplacements de tour: (470, 170), (770, 250), (440, 370), (650, 520), (120, 650), (470, 700), (850, 710), (660, 950)
- Position des waypoints: (610, 8), (630, 222), (595, 444), (478, 514), (320, 558), (260, 620), (280, 720), (348, 812), (720, 830), (968, 850), (1110, 682)
- Position de départ des démons: 610, -100
- Nombre de démons : 20 (même si on doit en spawer 50, à 20 à la fois, le joueur en a plein les bras).
- Nombre et de chacun des types de projectiles: à vous de le décider mais il doit être raisonnable ET on ne doit jamais en manquer
- Temps de spawn entre les démons: de 1 à 3 secondes (60 à 180 rafraichissements) au hasard.
- Mana: 500 au départ, + 1 par 0.2 secondes (12 rafraichissements), + 25 mana par élimination de démon.
- Score: 50 par démon abbattu.  les dommages fait par les projectiles sont transférés en points.

- 50 éliminations de démons (donc 50 spawns pour gagner la scène)
*/

class Level1 : public SceneGame
{
public:
	Level1(RenderWindow& renderWindow, Event& event);
	bool init() override;
private:
	void initWaypoints() override;
	void draw() override;
	bool unload() override;

	// Waypoints
	static const int WAYPOINTS_AMOUNT = 11;
	const Vector2f WAYPOINT_POSITIONS[WAYPOINTS_AMOUNT] =
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
};

