#include "Street.h"

Street::Street() {}

Street::Street(Node *nodeFrom, Node *nodeTo, bool sidewalk) {
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
	this->sidewalk = sidewalk;
	this->direction = getPredictedDirection(this->nodeFrom->getPosition(), this->nodeTo->getPosition());
}

Direction Street::getDirection() {
	return this->direction;
}

Direction Street::getPredictedDirection(Position start, Position end) {
	if (start.x == end.x)
		if (start.y > end.y)
			return N;
		else
			return S;
	else if (start.y == end.y)
		if (start.x > end.x)
			return W;
		else
			return E;
	return NONE;
}

std::pair<Node*, Node*> Street::getNodes() {
	return{nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions() {
	return{nodeFrom->getPosition(), nodeTo->getPosition()};
}