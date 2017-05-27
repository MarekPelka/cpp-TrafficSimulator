#include "Node.h"
int Node::all_Nodes = 0;

Node::Node(int x, int y) {
    position = Position(x, y);
    number = all_Nodes++;
}
Node::Node(Position p) {
    position = p;
    number = all_Nodes++;
}
Position Node::getPosition() {
    return position;
}
int Node::getNumber() {
    return number;
}

std::map<int, std::weak_ptr<Street>> Node::getStreetsIn()
{
	return streetsIn;
}

bool Node::getIsParking() {
    return isParking;
}

void Node::setIsParking(bool p) {
    this->isParking = p;
}

void Node::addStreetIn(Direction d, std::weak_ptr<Street> PWStreet)
{
	streetsIn.insert(std::make_pair(d, PWStreet));
}
