#include "Tower.h"

Tower::Tower() : active(false), range(TOWER_RANGE)
{
}

Tower::~Tower()
{
	Subject::removeObserver(this);
}

void Tower::draw(RenderWindow& renderWindow) const
{
    if (active)
        GameObject::draw(renderWindow);
}

void Tower::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0) {
        deactivate();
        notifyAllObservers();
    }
}

Demon* Tower::findNearestTarget(const std::vector<Demon*>& demons)
{
    Demon* closest = nullptr;
    float closestDistanceSq = range * range;

    for (Demon* d : demons)
    {
        if (!d->isActive()) continue;
        float dx = d->getPosition().x - getPosition().x;
        float dy = d->getPosition().y - getPosition().y;
        float distSq = dx * dx + dy * dy;

        if (distSq < closestDistanceSq)
        {
            closestDistanceSq = distSq;
            closest = d;
        }
    }

    return closest;
}
