#include "ArcherTower.h"
#include "ContentPipeline.h"

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

    float radius = static_cast<float>(ARCHER_WIDTH) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);
}

void ArcherTower::spawn(const sf::Vector2f& position)
{
    setPosition(position);
    activate();
}

void ArcherTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    if (!isActive()) return;

    fireTimer += deltaTime;

    if (fireTimer >= fireCooldown)
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
    if (isActive())
        GameObject::draw(renderWindow);
}

void ArcherTower::notify(Subject* subject)
{
    // Reagir a spell se necessário
}
