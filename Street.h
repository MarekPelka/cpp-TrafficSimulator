#pragma once
#include "Position.h"
#include "Node.h"
#include "Enums.h"
#include <utility>

class Street
{
public:
	Street();
	//DEBUG
	//Street(Position *start, Position *end);
	//END DEBUG
	Street(Node *nodeFrom, Node *nodeTo, bool sidewalk = false);
	std::pair <Node*, Node*> getNodes();
	std::pair <Position, Position> getStartEndPositions();
private:
	Node *nodeFrom;
	Node *nodeTo;
	bool sidewalk;
	Direction direction;
};