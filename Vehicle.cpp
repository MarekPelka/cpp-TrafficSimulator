#include "Vehicle.h"

Vehicle::Vehicle()
{
    type = CAR;
    length = CAR_LENGTH;
    acceleration = CAR_ACCELERATION;
    slowdown = CAR_SLOWDOWN;
}

Vehicle::Vehicle(vehicleType typ, Position pos)
{
	type = typ;
	if (type == CAR)
	{
		length = CAR_LENGTH;
		acceleration = CAR_ACCELERATION;
		slowdown = CAR_SLOWDOWN;
	}
	else if(type == TRUCK)
	{
		length = TRUCK_LENGTH;
		acceleration = TRUCK_ACCELERATION;
		slowdown = TRUCK_SLOWDOWN;
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

void Vehicle::updatePosition(int time) {
	//TODO matematyka zwiazana z predkoscia o ile trzeba zmienic wspolrzedne samochodu
	int temp = position.x;
	temp+=2;
	position = Position(temp,position.y);
}

Vehicle::~Vehicle()
{
    type = NOTHING;
}
