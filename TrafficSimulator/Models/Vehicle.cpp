#include "Vehicle.h"

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