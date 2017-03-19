#include "Street.h"

Street::Street()
{
}

Street::Street(Node *nodeFrom, Node *nodeTo)
{
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
}

std::pair<Node*, Node*> Street::getNodes()
{
	return {nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions()
{
	return{ nodeFrom->getPosition(), nodeTo->getPosition() };
}
