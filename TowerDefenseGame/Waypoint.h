#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Waypoint : public Sprite
{
public:
	Waypoint();

	void init(const Vector2f position);

	void setNextWaypoint(Waypoint* next);

	virtual void draw(RenderWindow& renderWindow) const;
	Waypoint* getNextWaypoint() const;

protected:
	Waypoint* nextWaypoint = nullptr;
};

