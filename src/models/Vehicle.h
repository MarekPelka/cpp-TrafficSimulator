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
        bool checkMaxSpeed();
        std::list<int> color;
        bool isMoving = false;
        bool operator==(const Vehicle &v);
    private:
        int length;
        double acceleration;
        double slowdown;
        vehicleType type;
        double speed;
        std::list<Node> nodes;
        Direction orientation;
        std::list<int> vehicleColor(double veh_speed);
};
