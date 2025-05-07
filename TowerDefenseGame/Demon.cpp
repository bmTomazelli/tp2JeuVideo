#include "Demon.h"
#include "ContentPipeline.h"
#include "TwoPathWaypoint.h"
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

	Subject::addObserver(this);

	this->wave = wave;
	speed = DEFAULT_DEMON_SPEED + (SPEED_WAVE_MULTIPLIER * wave);
	setDemonState(DemonState::FLYING);
}

void Demon::update(const float deltaTime)
{
	if (isActive())
	{
		checkStatus();
		manageMovement(deltaTime);
		manageAnimation(deltaTime);
	}
}

void Demon::notify(Subject* subject)
{
}

void Demon::assignWaypointToFollow(Waypoint* waypoint)
{
	waypointToFollow = waypoint;
}

void Demon::spawnDemon(const Vector2f position)
{
	setPosition(position);
	setDemonState(DemonState::FLYING);
	health = MAX_DEMON_HEALTH;
	activate();
}

Waypoint* Demon::getWaypointToFollow() const
{
	return waypointToFollow;
}

void Demon::checkStatus()
{
	if (health < 0 && !isDying()) setDemonState(DemonState::DYING);

	if (isDying() && currentImage == ANIM_DEMON - 1) deactivate();
}

void Demon::manageMovement(const float deltaTime)
{
	if (isDying()) return;

	if (waypointToFollow == nullptr) return;
		
	// Déplacement
	moveAngle = atan2f((waypointToFollow->getPosition().y - getPosition().y), (waypointToFollow->getPosition().x - getPosition().x));
	move(cos(moveAngle) * deltaTime * speed, sin(moveAngle) * deltaTime * speed);

	// Réflection
	if (cos(moveAngle) >= 0)
	{
		setScale(1, 1); // Vise vers la droite
	}
	else
	{
		setScale(-1, 1); // Vise vers la gauche
	}

	// Rotation continue 
	//angle++;
	//setRotation(angle);
	//if (angle > 360)
	//{
	//	angle = 0;
	//}

	checkCollisionWithWaypoint();
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
