#include "Tower.h"
#include "Projectile.h"
#include <iostream>

Tower::Tower() : active(false), range(TOWER_RANGE), fireSpell(1.0f), spellTimer(0.0f)
{
    Subject::addObserver(this);
}

Tower::~Tower()
{
	Subject::removeObserver(this);
}

void Tower::draw(RenderWindow& renderWindow) const
{
    if (isActive()) {
        GameObject::draw(renderWindow);
        healthGauge.draw(renderWindow);
    }
}

void Tower::takeDamage(int damage)
{
    damage *= plagueDamageMultiplier; // multiplicateur de dégâts pendant la durée de la plague

    hp -= damage;
    float hpRatio = float(hp) / float(totalHp);
    healthGauge.removeHealth(hpRatio);

    if (isDead()) 
    {
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

bool Tower::canShoot() const
{
    return recoilTimer == recoil;
}

bool Tower::isDead() const
{
    return hp <= 0;
}

void Tower::updateStatus(float deltaTime)
{
    if (plagueTimer > 0.f)//pendant l'effet de la plague
    {
        plagueTimer -= deltaTime; //reduit la durée du timer de la plague
        plagueTickTimer += deltaTime;//augmente le timer de tick

        if (plagueTickTimer >= 1.0f) // si le tick est égal ou supérieur à 1 seconde
        {
            takeDamage(1.f * plagueDamageMultiplier);  //hit de plague
            plagueTickTimer = 0.f; //reset le timer de tick
        }

        setColor(spellColor); //couleur du spell
    }
    else
    {
        plagueDamageMultiplier = 1.f; //reset le multiplicateur de la plague
        setColor(sf::Color::White);
    }
}


void Tower::notify(Subject* subject)
{
    Spell* spell = dynamic_cast<Spell*>(subject);
    if (spell)
    {
        float dx = spell->getPosition().x - getPosition().x;
        float dy = spell->getPosition().y - getPosition().y;
        float distSq = dx * dx + dy * dy;

        if (distSq > spell->getRange() * spell->getRange()) return;

        spellTimer = spell->getDuration();

        if (spell->getType() == SpellType::sacredLight)
        {
            SacredLight* sl = static_cast<SacredLight*>(spell);

            spellColor = sl->getColor();
            hp += sl->getHealAmount();
            healthGauge.addHealth(float(hp) / float(DEFAULT_TOWER_HP));
            fireSpell = sl->getSpeedMultiplier(); // 2.0f
        }
        else if (spell->getType() == SpellType::plague)
        {
            Plague* p = static_cast<Plague*>(spell);

            spellColor = p->getColor();
            takeDamage(p->getDamageAmount() * p->getDamageMultiplier());  // starter hit
            plagueDamageMultiplier = p->getDamageMultiplier();            // attaque doublé
            plagueTimer = spell->getDuration();                           // durée de l'effet
            plagueTickTimer = 0.f;                                        //hit par tick
        }
    }

    if (typeid(*subject) == typeid(Projectile))
    {
        Projectile* projectile = static_cast<Projectile*>(subject);
        if (projectile && projectile->getTarget() == this)
        {
            takeDamage(projectile->generateRandomDamage());
        }
    }
}

void Tower::manageRecoil(const float deltaTime)
{
    if (recoilTimer >= recoil)
    {
        recoilTimer = recoil;
        return;
    }

    recoilTimer += deltaTime;
}

void Tower::prepareShooting()
{
    recoilTimer = 0.0f;
}

void Tower::resetStatus()
{
    plagueTimer = 0.0f;
    spellTimer = 0.0f;
}

