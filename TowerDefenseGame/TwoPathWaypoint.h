#pragma once
#include "Waypoint.h"

class TwoPathWaypoint : public Waypoint
{
public:
	TwoPathWaypoint();
	
	void setOtherWaypoint(Waypoint* other);

private:
	Waypoint* otherWaypoint = nullptr;
};