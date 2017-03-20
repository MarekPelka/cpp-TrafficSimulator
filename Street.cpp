#include "Street.h"

Street::Street()
{
}

Street::Street(Node *nodeFrom, Node *nodeTo, bool sidewalk)
{
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
	this->sidewalk = sidewalk;
	Position start = this->nodeFrom->getPosition();
	Position end = this->nodeTo->getPosition();

	if (start.x == end.x)
		if (start.y > end.y)
			this->direction = N;
		else
			this->direction = S;
	else if(start.y == end.y)
		if(start.x > end.x)
			this->direction = W;
		else
			this->direction = E;
}

std::pair<Node*, Node*> Street::getNodes()
{
	return {nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions()
{
	return{ nodeFrom->getPosition(), nodeTo->getPosition() };
}
