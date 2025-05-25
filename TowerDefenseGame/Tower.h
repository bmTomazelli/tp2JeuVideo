#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "IObserver.h"
#include "Demon.h"
#include "Spell.h"
#include "Plague.h"
#include "SacredLight.h"
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
    void draw(RenderWindow& renderWindow) const;
    void takeDamage(int damage);
    void notify(Subject* subject) override;
    void manageRecoil(const float deltaTime);
    void prepareShooting();
    void resetStatus();
    
    Demon* findNearestTarget(const std::vector<Demon*>& demons);
    bool canShoot() const;
    bool isDead() const;

protected:
    void updateStatus(float deltaTime);
    virtual void updateSpell(float deltaTime) =0;

    bool active;
    int hp;
    int totalHp;
    float range;
    HealthGauge healthGauge;
    float spellTimer;
    float fireSpell;
    Color spellColor;
    float plagueTimer = 0.f;
    float plagueTickTimer = 0.f;
    float plagueDamageMultiplier = 1.f;
    float recoil = 0.0f;
    float recoilTimer = 0.0f;
};
