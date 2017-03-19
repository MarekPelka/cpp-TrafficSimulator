#include "Node.h"
Node::Node(int x, int y)
{
	position = new Position(x, y);
	number = 0;
	name = "";
}
Node::Node(Position * p)
{
	position = p;
}
Position Node::getPosition()
{
	return *position;
}
int Node::getNumber()
{
	return number;
}
std::string Node::getName()
{
	return name;
}