#include "Street.h"

Street::Street() {}

Street::Street(Node *nodeFrom, Node *nodeTo, bool sidewalk) {
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
	this->sidewalk = sidewalk;
	this->direction = getPredictedDirection(this->nodeFrom->getPosition(), this->nodeTo->getPosition());
    this->length = abs(getStartEndPositions().first.y - getStartEndPositions().second.y) >
            abs(getStartEndPositions().first.x - getStartEndPositions().second.x) ?
            abs(getStartEndPositions().first.y - getStartEndPositions().second.y) :
            abs(getStartEndPositions().first.x - getStartEndPositions().second.x);
}

Direction Street::getDirection() {
	return this->direction;
}

int Street::getLength() {
	return length;
}

Direction Street::getPredictedDirection(Position start, Position end) {
    if (start.x == end.x) {
        if (start.y > end.y) {
            return N;
        }
        else {
            return S;
        }
    }
    else if (start.y == end.y) {
        if (start.x > end.x) {
            return W;
        }
        else {
            return E;
        }
    }
	return NONE;
}

void Street::alterStart(Node * n) {
	nodeFrom = n;
}

void Street::alterEnd(Node * n) {
	nodeTo = n;
}

std::pair<Node*, Node*> Street::getNodes() {
	return{nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions() {
	return{nodeFrom->getPosition(), nodeTo->getPosition()};
}
