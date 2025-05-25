#pragma once
#include "Tower.h"

class KingTower : public Tower
{
public:
    KingTower();
    void init();
    void spawn(const Vector2f& position);
    void draw(RenderWindow& renderWindow) const override;
    void notify(Subject* subject) override;

    void update(float deltaTime, std::vector<Demon*>& demons) override;
    void updateSpell(float deltaTime) override;
};
