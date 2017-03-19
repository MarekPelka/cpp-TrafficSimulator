#include "Vehicle.h"

Vehicle::Vehicle()
{
    type = CAR;
    width = carWidth;
    acceleration = carAcceleration;
    slowdown = carSlowdown;
}

Vehicle::Vehicle(vehicleType typ, Position pos)
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
	position = pos;
}

void Vehicle::move(void) {
	return;
}

Position Vehicle::getPosition() {
	return position;
}

vehicleType Vehicle::getType() {
	return type;
}

Vehicle::~Vehicle()
{
    type = NOTHING;
}
