#pragma once
#include "Spell.h"

class Plague : public Spell
{
public:
    Plague();
    void init() override;
    int getDamageAmount() const;
    float getDamageMultiplier() const;

    void draw(sf::RenderWindow& window) override;

private:
    static const sf::Color PLAGUE_COLOR;
    static const int MIN_DMG;
    static const int MAX_DMG;
    static const float DAMAGE_MULTIPLIER;
};
