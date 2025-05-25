#include "Projectile.h"
#include "ContentPipeline.h"
#include "Constants.h"
#include <iostream>

Projectile::Projectile()
{
}

void Projectile::init(const ProjectileType projectileType)
{
    switch (projectileType)
    {
    case ARROW:
        setTexture(ContentPipeline::getInstance().getArrowTexture());
        projectileSound.setBuffer(ContentPipeline::getInstance().getArcherAttackSoundBuffer());
        speed = ARROW_SPEED * DESIRED_FRAMERATE;
        maxDamage = ARROW_MAX_DAMAGE;
        break;
    case BLAST:
        setTexture(ContentPipeline::getInstance().getBlastTexture());
        projectileSound.setBuffer(ContentPipeline::getInstance().getMageAttackSoundBuffer());
        speed = BLAST_SPEED * DESIRED_FRAMERATE;
        maxDamage = BLAST_MAX_DAMAGE;
        break;
    case FIREBALL:
        setTexture(ContentPipeline::getInstance().getFireballTexture());
        projectileSound.setBuffer(ContentPipeline::getInstance().getDemonAttackSoundBuffer());
        speed = FIREBALL_SPEED * DESIRED_FRAMERATE;
        maxDamage = FIREBALL_MAX_DAMAGE;
        break;
    }
    projectileSound.setVolume(DESIRED_MUSIC_VOLUME);
}

void Projectile::shoot(const Vector2f startingPosition, GameObject* actorToTarget)
{
    setPosition(startingPosition);
    target = actorToTarget;
    projectileSound.play();
    activate();
}

void Projectile::moveToTarget(const float deltaTime)
{
    if (target == nullptr) return;

    if (!target->isActive())
    {
        deactivateProjectile();
        return;
    }

    moveAngle = atan2f(target->getPosition().y - getPosition().y, target->getPosition().x - getPosition().x);

    float angleInDegrees = moveAngle * RAD_TO_DEGREES_RATIO;
    setRotation(angleInDegrees);

    move(cos(moveAngle) * deltaTime * speed, sin(moveAngle) * deltaTime * speed);

    checkCollisionWithTarget();
}

GameObject* Projectile::getTarget() const
{
    return target;
}

const int Projectile::generateRandomDamage() const
{
    return rand() % maxDamage + 1;
}

void Projectile::deactivateProjectile()
{
    target = nullptr;
    deactivate();
}

void Projectile::checkCollisionWithTarget()
{
    float dx = target->getPosition().x - getPosition().x;
    float dy = target->getPosition().y - getPosition().y;
    float distSq = dx * dx + dy * dy;

    if (distSq <= HIT_RADIUS * HIT_RADIUS)
    {
        notifyAllObservers();
        deactivateProjectile();
    }
}
