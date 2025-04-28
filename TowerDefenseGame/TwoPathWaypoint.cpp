#include "TwoPathWaypoint.h"

TwoPathWaypoint::TwoPathWaypoint()
{
}

void TwoPathWaypoint::setOtherWaypoint(Waypoint* other)
{
	this->otherWaypoint = other;
}

Waypoint* TwoPathWaypoint::getOtherWaypoint() const
{
	return this->otherWaypoint;
}
