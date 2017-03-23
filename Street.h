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
	int getLength();
    static Direction getPredictedDirection(Position start, Position end);

	void alterStart(Node *n);
	void alterEnd(Node *n);
private:
	Direction direction;
	Node *nodeFrom;
	Node *nodeTo;
	bool sidewalk;
	int length;
	
};
