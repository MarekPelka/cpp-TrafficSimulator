#pragma once
#include <iostream>
#include <list>
#include <memory>
#include "../Enums.h"
#include "MovingObject.h"
#include "Node.h"

typedef std::shared_ptr<Node> PNode;

class Vehicle : MovingObject {
public:
    Vehicle();
    ~Vehicle();
    Vehicle(VehicleType type, Position pos);
    Vehicle(VehicleType type, std::list<Node> nodes);
    Vehicle(VehicleType type, std::list<PNode> nodes);
    void move(int time);
    Position getPosition();
    VehicleType getType();
    bool updatePosition(int time);
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
    VehicleType type;
    double speed;
    std::list<Node> nodes;
    Direction orientation;
    std::list<int> vehicleColor(double veh_speed);
};
