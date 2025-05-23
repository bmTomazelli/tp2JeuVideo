#include "Plague.h"
#include "ContentPipeline.h"

const sf::Color Plague::PLAGUE_COLOR = sf::Color(96, 241, 76, 255);
const float Plague::DAMAGE_MULTIPLIER = 2.0f;
const int Plague::MIN_DMG = 1;
const int Plague::MAX_DMG = 5;

Plague::Plague()
{
    type = SpellType::plague;
    color = PLAGUE_COLOR;
}

void Plague::init()
{
    Spell::init();
    setTexture(ContentPipeline::getInstance().getPlagueTexture());
    rune.setColor(color);
    spellCircle.setColor(sf::Color(96, 241, 76, 128));
}

void Plague::draw(sf::RenderWindow& window)
{
    if (isActive())
    {
        Spell::draw(window);
        window.draw(*this);
    }
}

int Plague::getDamageAmount() const
{
    return MIN_DMG + rand() % (MAX_DMG - MIN_DMG + 1);
}

float Plague::getDamageMultiplier() const
{
    return DAMAGE_MULTIPLIER;
}
