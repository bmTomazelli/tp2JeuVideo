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


    healthGauge.init();

    setTextureRect(animationFrames[0]);
    setOrigin(MAGE_FRAME_WIDTH / 2.f, MAGE_FRAME_HEIGHT / 2.f);
}

void MageTower::spawn(const Vector2f& position)
{
    setPosition(position);
    healthGauge.setPosition(Vector2f(getPosition().x - 30.f, getPosition().y - 75.f));
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

    updateStatus(deltaTime);
    updateSpell(deltaTime);
    handleTargeting(demons);
    handleAnimation(deltaTime);
}

void MageTower::updateSpell(float deltaTime)
{
    if (spellTimer > 0.f)
    {
        setColor(spellColor);
        spellTimer -= deltaTime;
        if (spellTimer <= 0.f)
        {
            fireSpell = 1.f;
            setColor(sf::Color::White);
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
    if (isActive()) {
        GameObject::draw(renderWindow);
        healthGauge.draw(renderWindow);
    }
}

void MageTower::notify(Subject* subject)
{
    Tower::notify(subject);
    Spell* spell = dynamic_cast<Spell*>(subject);

    if (!spell) return;

    float dx = spell->getPosition().x - getPosition().x;
    float dy = spell->getPosition().y - getPosition().y;
    float distSq = dx * dx + dy * dy;

    if (distSq > spell->getRange() * spell->getRange()) return;

    if (spell->getType() == SpellType::sacredLight)
    {
        //speed boost

    }
}
