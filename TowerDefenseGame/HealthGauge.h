#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Subject.h"

using namespace sf;

class HealthGauge: public Subject
{
public:
	void init();
    void reset();
	void setPosition(const Vector2f position);
	void move(const float offsetX, const float offsetY);
	void draw(RenderWindow& renderWindow) const;

	void addHealth(const float healthToAdd);
	void removeHealth(const float healthToRemove);

private:
	Sprite greenHealth;
	Sprite redHealth;

	float health = 1.0f;
};

