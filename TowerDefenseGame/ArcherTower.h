#pragma once
#include "Tower.h"

class ArcherTower : public Tower
{
public:
    const float ARCHER_FIRE_RATE = 0.8f;
    const int ARCHER_WIDTH = 150;
    const int ARCHER_HEIGHT = 150;

    ArcherTower();
    void init();
    void spawn(const sf::Vector2f& position);
    void update(float deltaTime, std::vector<Demon*>& demons) override;
    void draw(sf::RenderWindow& renderWindow) const override;
    void notify(Subject* subject) override;
    void updateSpell(float deltaTime) override;
    void handleFiring(float deltaTime, std::vector<Demon*>& demons);

private:
    float fireCooldown;
    float fireTimer;
    void shoot(Demon* target);
};
