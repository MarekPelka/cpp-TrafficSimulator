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
    ~Vehicle();
    Vehicle(VehicleType type, std::list<Node> nodes);
    Vehicle(VehicleType type, std::list<PNode> nodes);
	void move(Street * const s, int time, int place);
    Position getPosition();
    VehicleType getType();
	std::list<Node> getNodes();
	bool updatePosition(Street * const s, int time, int place);
    Direction getOrientation();
    bool checkSlowdown(Position step);
    bool checkMaxSpeed();
    std::list<int> color;
    bool isMoving = false;
    bool operator==(const Vehicle &v);
	bool getToClear();
private:
    int length;
    double acceleration;
    double slowdown;
	bool toClear = false;
    VehicleType type;
    double speed;
    std::list<Node> nodes;
    Direction orientation;
    std::list<int> vehicleColor(double veh_speed);
	Direction getPredictedDirection(Position start, Position end);
	void calculateSpeed(int d, int time, Vehicle inFront);
};
