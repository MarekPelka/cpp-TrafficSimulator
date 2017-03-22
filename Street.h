#pragma once
#include "Position.h"
#include "Node.h"
#include "Enums.h"
#include <utility>

class Street
{
public:
	Street();
	Street(Node *nodeFrom, Node *nodeTo, bool sidewalk = false);
	std::pair <Node*, Node*> getNodes();
	std::pair <Position, Position> getStartEndPositions();
    Direction getDirection();
    static Direction getPredictedDirection(Position start, Position end);
private:
	Node *nodeFrom;
	Node *nodeTo;
	bool sidewalk;
	Direction direction;
};
