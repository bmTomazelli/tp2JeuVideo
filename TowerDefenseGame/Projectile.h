#pragma once
#include "GameObject.h"
#include "Subject.h"

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

class SceneGame;

class Projectile: public GameObject, public Subject
{
public:
    enum ProjectileType { ARROW, BLAST, FIREBALL };

	Projectile();

    void init(const ProjectileType projectileType );
    void shoot(const Vector2f startingPosition, GameObject* actorToTarget);
    void moveToTarget(const float deltaTime);
    GameObject* getTarget() const;
    const int generateRandomDamage() const;

    //methodes pour le score
    void setSceneGame(SceneGame* sceneGame);
    void notifyDamageForScore(int damage);

private:
    void deactivateProjectile();
    void checkCollisionWithTarget();

    const float ARROW_SPEED = 15.0f;
    const float BLAST_SPEED = 8.0f;
    const float FIREBALL_SPEED = 10.0f;
    const float HIT_RADIUS = 30.0f;

    float speed;
    int maxDamage;

    float moveAngle;
    GameObject* target = nullptr;
    Sound projectileSound;

    SceneGame* sceneGame = nullptr; // R�f�rence � la sc�ne de jeu pour notifier les observateurs
};

