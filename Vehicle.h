#pragma once
#include <iostream>
#include <list>
#include "Enums.h"
#include "MovingObject.h"
#include "Node.h"


class Vehicle : MovingObject
{
	public:
        Vehicle();
		~Vehicle();
        Vehicle(vehicleType type, Position pos);
        Vehicle(vehicleType type, std::list<Node> nodes);
        void move(int time);
		Position getPosition();
		vehicleType getType();
		void updatePosition(int time);
        Direction getOrientation();
        bool checkSlowdown(Position step);
        bool checkMaxSpeed(Position step);
    private:
		float length;
		float acceleration;
		float slowdown;
		vehicleType type;
		std::string color;
        bool isMoving = false;
        float speed;
        std::list<Node> nodes;
        Direction orientation;
};
