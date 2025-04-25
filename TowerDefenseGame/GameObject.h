#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CollisionCircle.h"

using namespace sf;

class GameObject : public Sprite
{
public:
	GameObject();
	void setTexture(const Texture& texture, const bool useVerticalAxisForCircleCollision = false);

	void activate();
	void deactivate();
	bool isActive() const;

	void setPosition(const float x, const float y);
	void setPosition(const Vector2f& position);

	void move(const float offsetX, const float offsetY);
	void move(const Vector2f& offset);
	void moveBack();

	const CollisionCircle& getCollisionCircle() const;
	float getCollisionCircleRadius() const;
	bool isCircleColliding(const GameObject& other) const;
	void setCollisionCircleRadius(const float radius);

	float getRotationInRadians() const;
	void setRotationWithRadians(const float angle);

	virtual void draw(RenderWindow& renderWindow) const;

protected:
	static const float PI;

private:
	static const float RADIANS_TO_DEGREE;

	bool active = false;
	CollisionCircle collisionCircle;
	Vector2f backupPosition;	
};