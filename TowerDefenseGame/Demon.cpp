#include "Demon.h"
#include "Constants.h"
#include "ContentPipeline.h"
#include "TwoPathWaypoint.h"
#include "Tower.h"
#include "TowerEmplacement.h"
#include "Plague.h"
#include "SacredLight.h"
#include "Projectile.h"
#include "SceneGame.h"
#include <iostream>

Demon::Demon()
{
}

Demon::~Demon()
{
	delete[] imagesFlying;
	delete[] imagesDying;
}

void Demon::init(const int wave) 
{
	setTexture(ContentPipeline::getInstance().getDemonTexture());

	attackSound.setBuffer(ContentPipeline::getInstance().getDemonAttackSoundBuffer());
	attackSound.setVolume(50);

	imagesFlying = new IntRect[ANIM_DEMON];
	imagesDying = new IntRect[ANIM_DEMON];

	int imageWidth = getTexture()->getSize().x / 5;
	int imageHeight = getTexture()->getSize().y / 2;

	// Rectangle d'animation pour FLYING
	for (int i = 0; i < ANIM_DEMON; i++)
	{
		imagesFlying[i].left = imageWidth * i;
		imagesFlying[i].top = 0;
		imagesFlying[i].height = imageHeight;
		imagesFlying[i].width = imageWidth;
	}

	// Rectangle d'animation pour DYING
	for (int i = 0; i < ANIM_DEMON; i++)
	{
		imagesDying[i].left = imageWidth * i;
		imagesDying[i].top = imageHeight;
		imagesDying[i].height = imageHeight;
		imagesDying[i].width = imageWidth;
	}

	setTextureRect(imagesFlying[0]);
	setOrigin(imageWidth / 2, imageHeight / 2);

    targetDetectionBox = FloatRect(
        getPosition().x - TARGET_DETECTION_BOX_SIZE / 2,
        getPosition().y - TARGET_DETECTION_BOX_SIZE / 2,
        TARGET_DETECTION_BOX_SIZE,
        TARGET_DETECTION_BOX_SIZE
    );

	Subject::addObserver(this);
	healthGauge.init();

	this->wave = wave;
	speed = DEFAULT_DEMON_SPEED + (SPEED_WAVE_MULTIPLIER * wave);

    recoil = MAX_RECOIL - 0.05f * wave;
    recoilTimer = recoil;
	setDemonState(DemonState::FLYING);
}

void Demon::update(const float deltaTime)
{
	checkStatus();
    manageRecoil(deltaTime);
    manageSpellEffect(deltaTime);
	manageMovement(deltaTime);
	manageAnimation(deltaTime);
}

void Demon::notify(Subject* subject)
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

            speed /= sl->getSpeedMultiplier();
            setColor(sl->getColor());
        }
        else if (spell->getType() == SpellType::plague)
        {
            Plague* plague = static_cast<Plague*>(spell);

            loseHealth(plague->getDamageAmount()); // initial damage
            setColor(plague->getColor());
            plagueDamageMultiplier = plague->getDamageMultiplier(); // ex: 2.0f
            plagueTickTimer = 0.f;
        }
    }

    if (typeid(*subject) == typeid(Projectile))
    {
        Projectile* projectile = static_cast<Projectile*>(subject);
        if (projectile && projectile->getTarget() == this)
        {
            int towerDamage = projectile->generateRandomDamage();
            loseHealth(towerDamage);
            sceneGame->updateScore(towerDamage);
        }
    }
}

void Demon::assignWaypointToFollow(Waypoint* waypoint)
{
	waypointToFollow = waypoint;
}

void Demon::spawnDemon(const Vector2f position)
{
	setPosition(position);
	healthGauge.setPosition(Vector2f(getPosition().x - HEALTHGAUGE_OFFSET_X, getPosition().y - HEALTHGAUGE_OFFSET_Y));
	setDemonState(DemonState::FLYING);
	health = MAX_DEMON_HEALTH;
    healthGauge.reset();
    recoilTimer = recoil;
    resetStatus();
	activate();
}

void Demon::loseHealth(const int damage)
{
	health -= damage;
	healthGauge.removeHealth((health * 100.0f / MAX_DEMON_HEALTH) / 100.0f);
}

void Demon::prepareShooting()
{
    recoilTimer = 0.0f;
}

Waypoint* Demon::getWaypointToFollow() const
{
	return waypointToFollow;
}

FloatRect Demon::getTargetDetectionBox() const
{
	return targetDetectionBox;
}

const float Demon::getRangeOfFire() const
{
    return rangeOfFire;
}

void Demon::resetStatus()
{
    spellTimer = 0.0f;
}

void Demon::setSceneGame(SceneGame* sceneGame)
{
    this->sceneGame = sceneGame;
}

void Demon::checkStatus()
{
    if (health <= 0 && !isDying()) 
    {
        sceneGame->updateScore(SCORE_DEAD_DEMON);
        sceneGame->updateKill();
        
        setDemonState(DemonState::DYING);
    }

	if (isDying() && currentImage == ANIM_DEMON - 1) deactivate();
}

void Demon::manageMovement(const float deltaTime)
{
	if (isDying()) return;

	if (waypointToFollow == nullptr) return;
		
	// Déplacement
	moveAngle = atan2f((waypointToFollow->getPosition().y - getPosition().y), (waypointToFollow->getPosition().x - getPosition().x));

	float offsetX = cos(moveAngle) * deltaTime * speed;
	float offsetY = sin(moveAngle) * deltaTime * speed;
	move(offsetX, offsetY);
	healthGauge.move(offsetX, offsetY);

	// Réflection
	if (cos(moveAngle) >= 0)
	{
		setScale(1, 1); // Vise vers la droite
	}
	else
	{
		setScale(-1, 1); // Vise vers la gauche
	}

	checkCollisionWithWaypoint();
}

void Demon::manageRecoil(const float deltaTime)
{
    if (recoilTimer >= recoil)
    {
        recoilTimer = recoil;
        return;
    }

    recoilTimer += deltaTime;
}

void Demon::manageSpellEffect(const float deltaTime)
{
    if (spellTimer > 0.0f) {
        spellTimer -= deltaTime;

        if (plagueDamageMultiplier > 1.0f) {
            plagueTickTimer += deltaTime;

            if (plagueTickTimer >= 1.0f) // hit a chaque 1 seconde
            {
                loseHealth(1 * plagueDamageMultiplier); //hit initiel
                plagueTickTimer = 0.0f; //resset pour le prochain tick de 1 seconde
            }
        }
    }
    else
    {
        setColor(sf::Color::White);
        plagueDamageMultiplier = 1.0f;

        speed = DEFAULT_DEMON_SPEED + (SPEED_WAVE_MULTIPLIER * wave);
    }
}

void Demon::checkCollisionWithWaypoint()
{
	float dx = waypointToFollow->getPosition().x - getPosition().x;
	float dy = waypointToFollow->getPosition().y - getPosition().y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < 1.0f)
	{
		notifyAllObservers();
	}
}

void Demon::manageAnimation(const float deltaTime)
{
	switch (demonState)
	{
	case DemonState::FLYING:
		runAnimation(deltaTime, TIME_PER_FRAME, ANIM_DEMON, false, imagesFlying);
		break;
	case DemonState::DYING:
		runAnimation(deltaTime, TIME_PER_FRAME, ANIM_DEMON, true, imagesDying);
		break;
	}
}

void Demon::runAnimation(const float deltaTime, const float timePerFrame, const int imageNumber, const bool linear, IntRect* images)
{
	timeCounter += deltaTime;

	if (timeCounter >= timePerFrame) 
	{
		timeCounter -= timePerFrame;

		if (++currentImage == imageNumber)
		{
			if (linear) currentImage = imageNumber - 1; 
			else currentImage = 0;
		}

		setTextureRect(images[currentImage]);
	}
}

void Demon::drawDemonHealth(RenderWindow& renderWindow) const
{
	healthGauge.draw(renderWindow);
}

void Demon::setDemonState(DemonState animationState)
{
	this->demonState = animationState;
	timeCounter = 0.0f;
	currentImage = 0;
}

bool Demon::isDying() const
{
	return demonState == DemonState::DYING;
}

bool Demon::canShoot() const
{
    return recoilTimer == recoil;
}
