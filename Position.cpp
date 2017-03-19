#include "Position.h"

Position::Position()
{
    x = 0;
    y = 0;
}

Position::Position(int posx, int posy)
{
	x = posx;
	y = posy;
}
std::pair <int, int> Position::getCoordinates()
{
	return { x, y };
}
