#include "HealthGauge.h"
#include "ContentPipeline.h"
#include <iostream>

void HealthGauge::init()
{
	redHealth.setTexture(ContentPipeline::getInstance().getRedBarTexture());
	greenHealth.setTexture(ContentPipeline::getInstance().getGreenBarTexture());
}

void HealthGauge::reset()
{
    health = 1.0f;
    greenHealth.setScale(health, 1);
}

void HealthGauge::setPosition(const Vector2f position)
{
	redHealth.setPosition(position.x, position.y);
	greenHealth.setPosition(position.x, position.y);
}

void HealthGauge::move(const float offsetX, const float offsetY)
{
	redHealth.move(offsetX, offsetY);
	greenHealth.move(offsetX, offsetY);
}

void HealthGauge::addHealth(const float healthToAdd)
{
	health = healthToAdd;
	if (health > 1.0f) 
		health = 1.0f;

	greenHealth.setScale(health, 1);
}

void HealthGauge::removeHealth(const float healthToRemove)
{
	health = healthToRemove;
	if (health <= 0)
	{
		notifyAllObservers();
		health = 0.0f;
	}

	greenHealth.setScale(health, 1);
}

void HealthGauge::draw(RenderWindow& renderWindow) const
{
	renderWindow.draw(redHealth);
	renderWindow.draw(greenHealth);
}
