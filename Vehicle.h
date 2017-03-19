#pragma once
#include <iostream>
#include "Enums.h"
#include "MovingObject.h"


class Vehicle : MovingObject
{
	public:
        Vehicle();
        Vehicle(vehicleType type);
        void move(void);
    private:
		float width;
		float acceleration;
		float slowdown;
		vehicleType type;
		std::string color;

        ~Vehicle();
};
