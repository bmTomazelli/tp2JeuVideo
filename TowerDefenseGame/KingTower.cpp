#include "KingTower.h"
#include "ContentPipeline.h"

KingTower::KingTower() {}

void KingTower::init()
{
    setTexture(ContentPipeline::getInstance().getKingTowerTexture());

    int w = getTexture()->getSize().x;
    int h = getTexture()->getSize().y;

    setOrigin(w / 2.f, h / 2.f);
    hp = KING_TOWER_HP;
    range = 0.0f;

    healthGauge.init();

    float radius = static_cast<float>(w) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);

    Subject::addObserver(this);
}

void KingTower::spawn(const Vector2f& position)
{
    setPosition(position);
    healthGauge.setPosition(Vector2f(getPosition().x - 25.f, getPosition().y - 100.f));
    activate();
}

void KingTower::update(float deltaTime, std::vector<Demon*>& demons)
{
}

void KingTower::updateSpell(float deltaTime)
{
    // Ça fait rien
}

void KingTower::draw(RenderWindow& renderWindow) const
{
    if (isActive())
    {
        GameObject::draw(renderWindow);
        healthGauge.draw(renderWindow);
    }
}
