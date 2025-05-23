#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "Constants.h"

/*
Metrics du Spell (à effacer à la fin)
- Portée des deux types de Spell: 400
- Durée de vie des deux spells: 5 secondes
- Vitesse de rotation:
  augmente de 

va de 0 à 20, progressivement en avancant dans le temps
- Ajoute 1/15 à la rotation à chaque rafraichissement d'écran.
- Ajoute deltaTime / 15 à chaque update si on utilise le deltaTime

- Couleur transmise par la peste: Color(96, 241, 76, 255);
- Couleur transmise par la sacred light: Color(214, 172, 2, 255);

*/

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

