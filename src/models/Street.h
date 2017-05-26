#ifndef STREET_H
#define STREET_H
#include "Position.h"
#include "Node.h"
#include "../Enums.h"
#include <utility>
#include <memory>
#include <vector>
#include "Pedestrian.h"
#include "Vehicle.h"
#include "../viewmodels/MovementController.h"

typedef std::shared_ptr<Node> PNode;
//class VehicleController;
class Street {
public:
	Street();
	Street(PNode nodeFrom, PNode nodeTo, bool sidewalk = false);
	std::pair <PNode, PNode> getNodes();
	std::pair <Position, Position> getStartEndPositions();
	Direction getDirection();
	int getLength();
	static Direction getPredictedDirection(Position start, Position end);
	std::vector<Vehicle> * getVehicles();
	std::vector<Pedestrian> * getPedestrians();
	bool hasSidewalk();
	void alterStart(PNode n);
	void alterEnd(PNode n);
	void addVehicleToStreet(Vehicle v);
	void addPedestrianToStreet(Pedestrian p);
	bool updatePositions(int interval);
	bool swichStreet(std::weak_ptr<Street> s, int spaceNeeded);
	bool operator==(const Street &v);
private:
	Direction direction;
	PNode nodeFrom;
	PNode nodeTo;
	bool sidewalk;
	int length;
	std::vector<Vehicle> vehOnStreet;
	std::vector<Pedestrian> pedOnStreet;
	bool swichS(std::shared_ptr<Street> s);
};
#endif