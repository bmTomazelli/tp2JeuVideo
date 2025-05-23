#include "ArcherTower.h"
#include "ContentPipeline.h"
#include <iostream>

ArcherTower::ArcherTower() {}

void ArcherTower::init()
{
    setTexture(ContentPipeline::getInstance().getArcherTowerTexture());

    // Ajuste visual único
    setTextureRect(sf::IntRect(0, 0, ARCHER_WIDTH, ARCHER_HEIGHT));
    setOrigin(ARCHER_WIDTH / 2.f, ARCHER_HEIGHT / 2.f);

    range = TOWER_RANGE;
    hp = DEFAULT_TOWER_HP;

    fireCooldown = ARCHER_FIRE_RATE;
    fireTimer = 0.f;

    healthGauge.init();

    float radius = static_cast<float>(ARCHER_WIDTH) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);
}

void ArcherTower::spawn(const sf::Vector2f& position)
{
    setPosition(position);
    healthGauge.setPosition(Vector2f(getPosition().x - 30.f, getPosition().y - 75.f));
    activate();
}

void ArcherTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    if (!isActive()) return;

    updateStatus(deltaTime); // plague, boost etc.
    updateSpell(deltaTime);
    handleFiring(deltaTime, demons);
}

void ArcherTower::updateSpell(float deltaTime)
{
    if (spellTimer > 0.f)
    {
        setColor(spellColor);
        spellTimer -= deltaTime;
        if (spellTimer <= 0.f)
        {
            fireCooldown = ARCHER_FIRE_RATE;
            fireSpell = 1.f;
            setColor(sf::Color::White);
        }
    }
}

void ArcherTower::handleFiring(float deltaTime, std::vector<Demon*>& demons)
{
    fireTimer += deltaTime;

    if (fireTimer >= fireCooldown / fireSpell)
    {
        Demon* target = findNearestTarget(demons);
        if (target)
        {
            shoot(target);
            fireTimer = 0.f;
        }
    }
}



void ArcherTower::shoot(Demon* target)
{
    // Criar arrow, exibir som, etc.
}

void ArcherTower::draw(sf::RenderWindow& renderWindow) const
{
    if (isActive()) {
        GameObject::draw(renderWindow);
        healthGauge.draw(renderWindow);
    }
}

void ArcherTower::notify(Subject* subject)
{
    Tower::notify(subject);
}
