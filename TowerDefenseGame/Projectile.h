#pragma once

/*
Metrics du Projectile (� effacer � la fin)

- Vitesse de d�placement (framerate 60 fps): Arrow: 15, blast 8, fireball: 10
(Si utilisation du DeltaTime, faire x60 � ces valeurs)

- Dommages: les projectiles font les dommages random suivants
  Arrow: 1 � 4, blast 1 � 12, fireball: 1 � 10

- Cadence de tir: un tir � tous les 
  Arrow: 48 rafraichissements / 0.8 secondes
  Blast: 90 rafraichissements / 1.5 secondes
  Fireball: 63 - 3 * wave / 1.05 secondes - 0.05 * wave
*/

class Projectile
{
public:
	Projectile();

private:
};

