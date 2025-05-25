#pragma once
#include "Spell.h"

class SacredLight : public Spell
{
public:
    SacredLight();
    void init() override;
    int getHealAmount() const;
    int getDamageAmount() const;
    float getSpeedMultiplier() const;

    void draw(sf::RenderWindow& window) override;
private:
    static const sf::Color SACRED_LIGHT_COLOR;
    static const int MIN_HEAL;
    static const int MAX_HEAL;
    static const float TOWER_SPEED_MULTIPLIER;
    static const float DEMONS_SPEED_MULTIPLIER;
};
