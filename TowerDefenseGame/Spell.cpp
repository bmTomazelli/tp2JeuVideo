#include "Spell.h"
#include "ContentPipeline.h"

const float Spell::DEFAULT_RANGE = 400.0f;
const float Spell::DEFAULT_DURATION = 5.0f;

Spell::Spell() {}

Spell::~Spell() {}

void Spell::init()
{
    lifeTime = 0.0f;
    range = DEFAULT_RANGE;
    duration = DEFAULT_DURATION;
    rotationSpeed = 0.0f;

    rune.setTexture(ContentPipeline::getInstance().getRunesTexture());

    //load the spell circle texture
    spellCircle.setTexture(ContentPipeline::getInstance().getMagicCircleTexture());
    spellCircle.setScale(0.0f, 0.0f);
}

void Spell::activate(sf::Vector2f position)
{
    if (isActive()) return;

    GameObject::setPosition(position);
    lifeTime = 0.0f;
    rotationSpeed = 0.0f;
    currentScale = 0.0f;

    rune.setPosition(position);
    rune.setOrigin(rune.getLocalBounds().width / 2.f, rune.getLocalBounds().height / 2.f);

    //set the scale of the spell circle
    spellCircle.setPosition(position);
    spellCircle.setOrigin(spellCircle.getLocalBounds().width / 2.f, spellCircle.getLocalBounds().height / 2.f);

    GameObject::activate();
    notifyAllObservers();
}

void Spell::update(float deltaTime)
{
    if (!isActive()) return;

    lifeTime += deltaTime;
    if (lifeTime < duration)
    {
        rotationSpeed += deltaTime / 15.0f;
        rune.rotate(rotationSpeed*(lifeTime*5.0f));
        spellCircle.rotate(deltaTime * 50.0f);

        //scale-in dans l'init
        if (currentScale < scaleInTime) {
            currentScale += deltaTime;
            float t = std::min(currentScale / scaleInTime, 1.f);
            float scaleFactor = (range * 2.f) / spellCircle.getLocalBounds().width;
            spellCircle.setScale(scaleFactor * t, scaleFactor * t);
        }
    }
    else
    {
        deactivate();
    }
}

float Spell::getRange() const
{
    return this->range;
}

SpellType Spell::getType() const
{
    return this->type;
}

float Spell::getDuration() const
{
    return this->duration;
}

sf::Color Spell::getColor() const
{
    return this->color;
}

void Spell::draw(sf::RenderWindow& window)
{
    if (isActive()) {
       window.draw(rune);
       window.draw(spellCircle);
    }
}

void Spell::deactivate()
{
    GameObject::deactivate();
}