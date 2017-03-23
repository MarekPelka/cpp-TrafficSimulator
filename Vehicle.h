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
		void updatePosition(int time);
    private:
		float length;
		float acceleration;
		float slowdown;
		vehicleType type;
		std::string color;
};
