#include "Waypoint.h"
#include "ContentPipeline.h"
#include "Subject.h"
#include "Demon.h"


Waypoint::Waypoint()
{
}

Waypoint* Waypoint::getNextWaypoint() const
{
	return nextWaypoint;
}

void Waypoint::init(const Vector2f position)
{
	const Texture& texture = ContentPipeline::getInstance().getWaypointTexture();
	Sprite::setTexture(texture);
	Sprite::setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

	setPosition(position);
}

void Waypoint::setNextWaypoint(Waypoint* next)
{
	nextWaypoint = next;
}

void Waypoint::draw(RenderWindow& renderWindow) const
{
	renderWindow.draw(*this);
}
