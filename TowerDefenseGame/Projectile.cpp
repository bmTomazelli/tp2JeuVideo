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
        maxDamage = 4;
        break;
    case BLAST:
        setTexture(ContentPipeline::getInstance().getBlastTexture());
        projectileSound.setBuffer(ContentPipeline::getInstance().getMageAttackSoundBuffer());
        speed = BLAST_SPEED * DESIRED_FRAMERATE;
        maxDamage = 12;
        break;
    case FIREBALL:
        setTexture(ContentPipeline::getInstance().getFireballTexture());
        projectileSound.setBuffer(ContentPipeline::getInstance().getDemonAttackSoundBuffer());
        speed = FIREBALL_SPEED * DESIRED_FRAMERATE;
        maxDamage = 10;
        break;
    }
}

void Projectile::shoot(const Vector2f startingPosition, GameObject* actorToTarget)
{
    setPosition(startingPosition);
    target = actorToTarget;
    activate();
}

void Projectile::moveToTarget(const float deltaTime)
{
    if (target == nullptr) return;

    if (!target->isActive()) deactivateProjectile();

    moveAngle = atan2f(target->getPosition().y - getPosition().y, target->getPosition().x - getPosition().x);

    float angleInDegrees = moveAngle * RAD_TO_DEGREES_RATIO;
    setRotation(angleInDegrees);

    move(cos(moveAngle) * deltaTime * speed, sin(moveAngle) * deltaTime * speed);
}

void Projectile::deactivateProjectile()
{
    target = nullptr;
    deactivate();
}
