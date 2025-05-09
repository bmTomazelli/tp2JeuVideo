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
    range = 0.f;

    float radius = static_cast<float>(w) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);

}

void KingTower::spawn(const Vector2f& position)
{
    setPosition(position);
    activate();
}

void KingTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    // Ça fait rien
}

void KingTower::notify(Subject* subject)
{
    // Ça fait rien
}
