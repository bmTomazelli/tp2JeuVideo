#pragma once
#include "GameObject.h"
#include "Subject.h"

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
    void deactivateProjectile();

    //methodes pour le score
    void setSceneGame(SceneGame* sceneGame);
    void notifyDamageForScore(int damage);

private:
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
    Sound hitSound;

    SceneGame* sceneGame = nullptr; // Référence à la scène de jeu pour notifier les observateurs
};

