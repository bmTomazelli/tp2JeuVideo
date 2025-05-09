#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "IObserver.h"
#include "Demon.h"
#include <vector>

class Tower : public GameObject, public Subject, public IObserver
{
public:
    // Range
    const float TOWER_RANGE = 300.f;
    // Collision
    const float TOWER_COLLISION_RADIUS_SCALE = 0.25f; 

    // HP
    const int KING_TOWER_HP = 500;
    const int DEFAULT_TOWER_HP = 250;

    Tower();
    virtual ~Tower();

    virtual void update(float deltaTime, std::vector<Demon*>& demons) = 0;
    virtual void draw(RenderWindow& renderWindow) const;

    void takeDamage(int damage);

protected:
    Demon* findNearestTarget(const std::vector<Demon*>& demons);
    bool active;
    int hp;
    float range;
};
