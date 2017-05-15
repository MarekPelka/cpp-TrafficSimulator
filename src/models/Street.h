#ifndef STREET_H
#define STREET_H
#include "Position.h"
#include "Node.h"
#include "../Enums.h"
#include <utility>
#include <memory>
#include <vector>
#include "Vehicle.h"
typedef std::shared_ptr<Node> PNode;

class Street : std::enable_shared_from_this<Street> {
public:
    Street();
    Street(PNode nodeFrom, PNode nodeTo, bool sidewalk = false);
    std::pair <PNode, PNode> getNodes();
    std::pair <Position, Position> getStartEndPositions();
    Direction getDirection();
    int getLength();
    static Direction getPredictedDirection(Position start, Position end);
	std::vector<Vehicle> * getVehicles();
    bool hasSidewalk();
    void alterStart(PNode n);
    void alterEnd(PNode n);
	void addVehicleToStreet(Vehicle v);
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
	bool swichS(std::shared_ptr<Street> s, int spaceNeeded);
};
#endif