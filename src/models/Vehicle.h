#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <list>
#include <memory>
#include "../Enums.h"
#include "Node.h"

typedef std::shared_ptr<Node> PNode;

class Vehicle{
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
	void setToClear(bool t);
	bool getToSwitch();
	void setToSwitch(bool t);
	std::shared_ptr<Street> getStreetToSwitch();
	void setStreetToSwitch(std::shared_ptr<Street> t);
private:
    Position position;
	int length;
	double acceleration;
	double slowdown;
	bool toClear = false;
	bool toSwich = false;
	std::shared_ptr<Street> streetToSwitch;
	VehicleType type;
	double speed;
	std::list<Node> nodes;
	Direction orientation;
	std::list<int> vehicleColor(double veh_speed);
	Direction getPredictedDirection(Position start, Position end);
	void calculateSpeed(int d, int time, Vehicle inFront);
};
#endif