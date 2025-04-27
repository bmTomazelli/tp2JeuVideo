#pragma once
#include "SceneGame.h"

/*
Metrics de sceneGame OU du level 1 (� effacer � la fin)
- Position de la tour du roi: 1138, 600
- Position des emplacements de tour: (470, 170), (770, 250), (440, 370), (650, 520), (120, 650), (470, 700), (850, 710), (660, 950)
- Position des waypoints: (610, 8), (630, 222), (595, 444), (478, 514), (320, 558), (260, 620), (280, 720), (348, 812), (720, 830), (968, 850), (1110, 682)
- Position de d�part des d�mons: 610, -100
- Nombre de d�mons : 20 (m�me si on doit en spawer 50, � 20 � la fois, le joueur en a plein les bras).
- Nombre et de chacun des types de projectiles: � vous de le d�cider mais il doit �tre raisonnable ET on ne doit jamais en manquer
- Temps de spawn entre les d�mons: de 1 � 3 secondes (60 � 180 rafraichissements) au hasard.
- Mana: 500 au d�part, + 1 par 0.2 secondes (12 rafraichissements), + 25 mana par �limination de d�mon.
- Score: 50 par d�mon abbattu.  les dommages fait par les projectiles sont transf�r�s en points.

- 50 �liminations de d�mons (donc 50 spawns pour gagner la sc�ne)
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

