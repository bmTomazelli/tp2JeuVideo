#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "Constants.h"

class Spell : public Subject, public GameObject
{
public:
    Spell();
    virtual ~Spell();

    virtual void init();
    virtual void activate(sf::Vector2f position);
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    float getRange() const;
    SpellType getType() const;
    float getDuration() const;
    Color getColor() const;

    void deactivate();

protected:
    static const float DEFAULT_RANGE;
    static const float DEFAULT_DURATION;

    float lifeTime;
    float range;
    float duration;
    float rotationSpeed;

    float scaleInTime = 0.2f;
    float currentScale = 0.0f;

    SpellType type;
    sf::Color color;
    sf::Sprite rune;
    sf::Sprite spellCircle;
};

