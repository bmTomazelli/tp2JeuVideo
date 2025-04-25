#pragma once
#include "Scene.h"
#include "Hud.h"
#include "Inputs.h"

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

/*
Metrics de du level 2 (� effacer � la fin)
- Position de la tour du roi: 1138, 564
- Position des emplacements de tour: (110, 620), (228, 320), (444, 780), (362, 530), (610, 222), (998, 270), (630, 460), (935, 520), (798, 760),
- Position des waypoints: (88.f, 412.f), (168.f, 465.f), (222.f, 588.f), (308.f, 670.f), (424.f, 668.f), (double sortie: 510.f, 590.f);  
                          (478.f, 468.f), (516.f, 380.f), (594.f, 360.f), (806.f, 368.f), (1140.f, 450.f), (660.f, 598.f), (804.f, 650.f), (1140.f, 680.f),
- Position de d�part des d�mons: -100, 410

- Le reste est identique � la sc�ne 1
*/

class SceneGame : public Scene
{
public:
	SceneGame(RenderWindow& renderWindow, Event& event);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	View view;
	Hud hud;
	Inputs inputs;

	Sprite map;
};