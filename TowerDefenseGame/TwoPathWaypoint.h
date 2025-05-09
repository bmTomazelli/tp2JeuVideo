#pragma once
#include "Waypoint.h"

class TwoPathWaypoint : public Waypoint
{
public:
	TwoPathWaypoint();
	
	void setOtherWaypoint(Waypoint* other);
	Waypoint* getOtherWaypoint() const;

private:
	Waypoint* otherWaypoint = nullptr;
};