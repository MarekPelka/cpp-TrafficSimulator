#pragma once
#include <iostream>
#include <list>
#include "../Enums.h"
#include "MovingObject.h"
#include "Node.h"

class Vehicle : MovingObject
{
    public:
        Vehicle();
        ~Vehicle();
        Vehicle(vehicleType type, Position pos);
        Vehicle(vehicleType type, std::list<Node> nodes);
		Vehicle(vehicleType type, std::list<Node*> nodes);
        void move(int time);
        Position getPosition();
        vehicleType getType();
        void updatePosition(int time);
        Direction getOrientation();
        bool checkSlowdown(Position step);
        bool checkMaxSpeed(Position step);
        std::list<int> color;
        bool isMoving = false;
        bool operator==(const Vehicle &v);
    private:
        float length;
        float acceleration;
        float slowdown;
        vehicleType type;
        float speed;
        std::list<Node> nodes;
        Direction orientation;
        std::list<int> vehicleColor(float speed);
};
