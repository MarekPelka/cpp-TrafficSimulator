#pragma once
#include <iostream>
#include "Position.h"
class Node
{
public:
	Node();
	Node(int x, int y);
	Node(Position p);
	Position getPosition();
	int getNumber();
	std::string getName();
	Position position;
	int number;
	std::string name;
private:
	static int all_Nodes;
};