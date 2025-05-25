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
    totalHp = DEFAULT_TOWER_HP;
    hp = totalHp;

    healthGauge.init();
    recoil = ARROW_RECOIL;
    recoilTimer = recoil;

    float radius = static_cast<float>(ARCHER_WIDTH) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);
}

void ArcherTower::spawn(const sf::Vector2f& position)
{
    setPosition(position);
    resetStatus();
    hp = DEFAULT_TOWER_HP;
    healthGauge.reset();
    healthGauge.setPosition(Vector2f(getPosition().x - 30.f, getPosition().y - 75.f));
    activate();
}

void ArcherTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    if (!isActive()) return;

    updateStatus(deltaTime);
    updateSpell(deltaTime);
    manageRecoil(deltaTime);
}

void ArcherTower::updateSpell(float deltaTime)
{
    if (spellTimer > 0.f)
    {
        setColor(spellColor);
        spellTimer -= deltaTime;
    }
    else
    {
        fireSpell = 1.f;
        setColor(sf::Color::White);
    }
}

void ArcherTower::notify(Subject* subject)
{
    Tower::notify(subject);
}
