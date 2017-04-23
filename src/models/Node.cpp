#include "Node.h"
int Node::all_Nodes = 0;

Node::Node(int x, int y)
{
	position = Position(x, y);
	number = all_Nodes++;
	name = "";
}
Node::Node(Position p)
{
	position = p;
	number = all_Nodes++;
	name = "";
}
Position Node::getPosition()
{
	return position;
}
int Node::getNumber()
{
	return number;
}
std::string Node::getName()
{
	return name;
}

bool Node::getIsParking()
{
	return isParking;
}

void Node::setIsParking(bool p)
{
	this->isParking = p;
}
