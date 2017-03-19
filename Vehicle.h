#pragma once
#include <iostream>
#include "Enums.h"
#include "MovingObject.h"


class Vehicle : MovingObject
{
	public:
        Vehicle();
		~Vehicle();
        Vehicle(vehicleType type, Position pos);
        void move(void);
		Position getPosition();
		vehicleType getType();
    private:
		float width;
		float acceleration;
		float slowdown;
		vehicleType type;
		std::string color;
};
