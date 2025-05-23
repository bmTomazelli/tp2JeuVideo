#include "SacredLight.h"
#include "ContentPipeline.h"

const sf::Color SacredLight::SACRED_LIGHT_COLOR = sf::Color(214, 172, 2, 255);
const float SacredLight::TOWER_SPEED_MULTIPLIER = 2.0f;
const float SacredLight::DEMONS_SPEED_MULTIPLIER = 0.5f;
const int SacredLight::MIN_HEAL = 6;
const int SacredLight::MAX_HEAL = 15;

SacredLight::SacredLight()
{
    type = SpellType::sacredLight;
    color = SACRED_LIGHT_COLOR;
}

void SacredLight::init()
{
    Spell::init();
    setTexture(ContentPipeline::getInstance().getSacredLightTexture());
    rune.setColor(color);
    spellCircle.setColor(Color(214, 172, 2, 128));
}

void SacredLight::draw(sf::RenderWindow& window)
{
    if (isActive())
    {
        Spell::draw(window);
        window.draw(*this);
    }
}

int SacredLight::getHealAmount() const
{
    return MIN_HEAL + rand() % (MAX_HEAL - MIN_HEAL + 1);
}

float SacredLight::getSpeedMultiplier() const
{
    return TOWER_SPEED_MULTIPLIER;
}
