#pragma once

/*
Metrics du Demon (� effacer � la fin)
- Rectangle d'animation: 100 X 50
- Rayon du cercle de collision: hauteur du rectangle d'animation (50) divis� par 2
- Vitesse d'animation: 1 frame par 0.1 /secs
- Vitesse de d�placement: 0.9 + 0.1 X Num�ro de vague (Si utilisation du DeltaTime, faire x60)
- Points de vie: 60 (50 pour la version � un d�veloppeur);
- Cadence de tir: un tir par (1.05 - 0.05 * num�ro de vague) seconde.
- Port�e du tir: 250
- Position de d�part des d�mons au niveau 1: 610, -100
- Position de d�part des d�mons au niveau 2: -100, 410
*/

class Demon
{
public:
	Demon();

private:
};

