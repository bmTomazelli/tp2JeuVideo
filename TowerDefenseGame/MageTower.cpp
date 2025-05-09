#include "MageTower.h"
#include "ContentPipeline.h"

MageTower::MageTower() {}

void MageTower::init()
{
    setTexture(ContentPipeline::getInstance().getMageTowerTexture());

    setupAnimation();

    animationSpeed = frameDuration;
    animationTimer = 0.f;
    currentFrame = 0;
    animating = false;
    target = nullptr;

    range = TOWER_RANGE;
    hp = DEFAULT_TOWER_HP;

    fireCooldown = MAGE_FIRE_RATE;
    fireTimer = 0.f;

    float radius = static_cast<float>(MAGE_FRAME_WIDTH) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);

    setTextureRect(animationFrames[0]);
    setOrigin(MAGE_FRAME_WIDTH / 2.f, MAGE_FRAME_HEIGHT / 2.f);
}

void MageTower::spawn(const Vector2f& position)
{
    setPosition(position);
    activate();
}


void MageTower::setupAnimation()
{
    for (int i = 0; i < 3; ++i)
    {
        animationFrames.emplace_back(IntRect(i * MAGE_FRAME_WIDTH, 0, MAGE_FRAME_WIDTH, MAGE_FRAME_HEIGHT));
    }

    frameDuration = { 0.6f,0.2f,0.2f };
    setTextureRect(animationFrames[0]);
}


void MageTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    if (!isActive()) return;

    takeDamage(2);

    if (!animating)
    {
        target = findNearestTarget(demons);
        if (target)
        {
            float dx = target->getPosition().x - getPosition().x;
            if(dx<=0)
                setScale(1.f, 1.f);
            else
                setScale(-1.f, 1.f);

            animating = true;
            currentFrame = 0;
            animationTimer = 0.f;
        }
    }

    if (animating)
    {
        animationTimer += deltaTime;
        if (animationTimer >= frameDuration[currentFrame])
        {
            animationTimer = 0.f;
            currentFrame++;

            if (currentFrame >= animationFrames.size())
            {
                shoot();
                animating = false;
                currentFrame = 0;
            }

            setTextureRect(animationFrames[currentFrame]);
        }
    }
}

void MageTower::shoot()
{
    //projectile
}

void MageTower::draw(RenderWindow& renderWindow) const
{
    if (isActive())
        GameObject::draw(renderWindow);
}

void MageTower::notify(Subject* subject)
{
   //reaction aux spells
}

void MageTower::setLife()
{
    hp = 0;
}