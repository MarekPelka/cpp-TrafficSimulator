#include "Vehicle.h"

Vehicle::Vehicle()
{
    type = CAR;
    width = carWidth;
    acceleration = carAcceleration;
    slowdown = carSlowdown;
}

Vehicle::Vehicle(vehicleType typ)
{
	type = typ;
	if (type == CAR)
	{
		width = carWidth;
		acceleration = carAcceleration;
		slowdown = carSlowdown;
	}
	else if(type == TRUCK)
	{
		width = truckWidth;
		acceleration = truckAcceleration;
		slowdown = truckSlowdown;
	}
}

void Vehicle::move(void) {
	return;
}

Vehicle::~Vehicle()
{
    type = NOTHING;
}
