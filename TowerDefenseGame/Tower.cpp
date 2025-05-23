#include "Tower.h"

Tower::Tower() : active(false), range(TOWER_RANGE), fireSpell(1.0f), spellTimer(0.0f)
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
    damage *= plagueDamageMultiplier; // multiplicateur de dégâts pendant la durée de la plague

    hp -= damage;
    float hpRatio = float(hp) / float(DEFAULT_TOWER_HP);
    healthGauge.removeHealth(hpRatio);

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
    if (!spell) return;

    float dx = spell->getPosition().x - getPosition().x;
    float dy = spell->getPosition().y - getPosition().y;
    float distSq = dx * dx + dy * dy;

    if (distSq > spell->getRange() * spell->getRange()) return;

    spellTimer = spell->getDuration();

    if (spell->getType() == SpellType::sacredLight)
    {
        SacredLight* sl = dynamic_cast<SacredLight*>(spell);
        if (!sl) return;

        spellColor = sl->getColor();
        hp += sl->getHealAmount();
        fireSpell = sl->getSpeedMultiplier(); // 2.0f
    }
    else if (spell->getType() == SpellType::plague)
    {
        Plague* p = dynamic_cast<Plague*>(spell);
        if (!p) return;

        spellColor = p->getColor();
        takeDamage(p->getDamageAmount() * p->getDamageMultiplier());  // starter hit
        plagueDamageMultiplier = p->getDamageMultiplier();            // attaque doublé
        plagueTimer = spell->getDuration();                           // durée de l'effet
        plagueTickTimer = 0.f;                                        //hit par tick
    }
}

