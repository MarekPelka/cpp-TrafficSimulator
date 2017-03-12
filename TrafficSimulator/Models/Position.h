#pragma once
#include <utility>

class Position
{
	public:
		Position();
		Position(int posx, int posy);
		int x;
		int y;
		std::pair <int, int> getCoordinates(Position pos);
};