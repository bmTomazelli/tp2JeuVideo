#include "Waypoint.h"
#include "ContentPipeline.h"

Waypoint::Waypoint()
{
}

const Waypoint* Waypoint::getNextWaypoint() const
{
	return nextWaypoint;
}

void Waypoint::init(const Vector2f position)
{
	const Texture& texture = ContentPipeline::getInstance().getWaypointTexture();
	Sprite::setTexture(texture);
	Sprite::setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

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
