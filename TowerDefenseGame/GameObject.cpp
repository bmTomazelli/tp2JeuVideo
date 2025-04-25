#include "GameObject.h"

const float GameObject::RADIANS_TO_DEGREE = 57.295779513f;
const float GameObject::PI = 3.141592653f;

GameObject::GameObject()
{
}

void GameObject::setTexture(const Texture& texture, const bool useVerticalAxisForCircleCollision)
{
	Sprite::setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	if (useVerticalAxisForCircleCollision)
		collisionCircle.setRadius(texture.getSize().y / 2);
	else
		collisionCircle.setRadius(texture.getSize().x / 2);
}

void GameObject::activate()
{
	active = true;
}

void GameObject::deactivate()
{
	active = false;
}

bool GameObject::isActive() const
{
	return active;
}

void GameObject::setPosition(const float x, const float y)
{
	Sprite::setPosition(x, y);
	backupPosition = getPosition();  //Nouveauté, pour éviter un bug potentiel.
	collisionCircle.setPosition(x, y);
}

void GameObject::setPosition(const Vector2f& position)
{
	setPosition(position.x, position.y);
}

void GameObject::move(const float offsetX, const float offsetY)
{
	if (active)
	{
		backupPosition = getPosition();
		Sprite::move(offsetX, offsetY);
		collisionCircle.setPosition(getPosition().x, getPosition().y);
	}
}

void GameObject::move(const Vector2f& offset)
{
	move(offset.x, offset.y);
}

void GameObject::moveBack()
{
	setPosition(backupPosition);
}

const CollisionCircle& GameObject::getCollisionCircle() const
{
	return collisionCircle;
}

float GameObject::getCollisionCircleRadius() const
{
	return collisionCircle.getRadius();
}

bool GameObject::isCircleColliding(const GameObject& other) const
{
	if (active && other.active)
		return this->getCollisionCircle().checkCollision(other.getCollisionCircle());

	return false;
}

void GameObject::setCollisionCircleRadius(const float radius)
{
	collisionCircle.setRadius(radius);
}

float GameObject::getRotationInRadians() const
{
	return getRotation() / RADIANS_TO_DEGREE;
}

void GameObject::setRotationWithRadians(const float angle)
{
	setRotation(angle * RADIANS_TO_DEGREE);
}

void GameObject::draw(RenderWindow& renderWindow) const
{
	if (active) renderWindow.draw(*this);
}