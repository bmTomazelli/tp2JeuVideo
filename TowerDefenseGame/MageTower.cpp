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

    totalHp = DEFAULT_TOWER_HP;
    hp = totalHp;

    recoil = BLAST_RECOIL;
    recoilTimer = recoil;

    float radius = static_cast<float>(MAGE_FRAME_WIDTH) * TOWER_COLLISION_RADIUS_SCALE;
    setCollisionCircleRadius(radius);

    healthGauge.init();

    setTextureRect(animationFrames[0]);
    setOrigin(MAGE_FRAME_WIDTH / 2.f, MAGE_FRAME_HEIGHT / 2.f);
}

void MageTower::spawn(const Vector2f& position)
{
    setPosition(position);
    resetStatus();
    hp = DEFAULT_TOWER_HP;
    recoil = BLAST_RECOIL;
    recoilTimer = recoil;
    healthGauge.reset();
    healthGauge.setPosition(Vector2f(getPosition().x - 30.f, getPosition().y - 75.f));
    activate();
}

void MageTower::setupAnimation()
{
    for (int i = 0; i < 3; ++i)
    {
        animationFrames.emplace_back(IntRect(i * MAGE_FRAME_WIDTH, 0, MAGE_FRAME_WIDTH, MAGE_FRAME_HEIGHT));
    }

    frameDuration = { 0.0f,0.2f,0.1f };
    setTextureRect(animationFrames[0]);
}


void MageTower::update(float deltaTime, std::vector<Demon*>& demons)
{
    if (!isActive()) return;

    updateStatus(deltaTime);
    updateSpell(deltaTime);
    manageRecoil(deltaTime);
    
    if (canShoot()) handleTargeting(demons);
    
    handleAnimation(deltaTime);
}

void MageTower::updateSpell(float deltaTime)
{
    if (hitBySpell)
    {
        if (spellTimer > 0.f)
        {
            setColor(spellColor);
            spellTimer -= deltaTime;
        }
        else
        {
            fireSpell = 1.0f;
            setColor(sf::Color::White);
            recoil = BLAST_RECOIL;
            recoilTimer = 0.0f;
            hitBySpell = false;
        }
    }
}

void MageTower::handleTargeting(const std::vector<Demon*>& demons)
{
    if (!animating)
    {
        target = findNearestTarget(demons);
        if (target)
        {
            float dx = target->getPosition().x - getPosition().x;
            setScale((dx <= 0.f) ? 1.f : -1.f, 1.f);

            animating = true;
            currentFrame = 0;
            animationTimer = 0.f;
        }
    }
}

void MageTower::handleAnimation(float deltaTime)
{
    if (animating)
    {
        animationTimer += deltaTime * fireSpell;

        if (animationTimer >= frameDuration[currentFrame])
        {
            animationTimer = 0.f;
            currentFrame++;

            if (currentFrame == animationFrames.size() - 1)
            {
                notifyAllObservers();
                prepareShooting();
            }

            if (currentFrame >= animationFrames.size())
            {
                animating = false;
                currentFrame = 0;
            }

            setTextureRect(animationFrames[currentFrame]);
        }
    }
}

void MageTower::notify(Subject* subject)
{
    Tower::notify(subject);
}

Demon* MageTower::getTarget() const
{
    return target;
}
