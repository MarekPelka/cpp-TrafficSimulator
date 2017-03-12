#include "Position.h"

Position::Position(int posx, int posy)
{
	x = posx;
	y = posy;
}
std::pair <int, int> Position::getCoordinates(Position pos)
{
	return { pos.x, pos.y };
}