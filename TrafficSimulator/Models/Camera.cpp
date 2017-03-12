#include "Camera.h"

Camera::Camera(Position pos, int angl, directions dir)
{
	position = pos;
	angle = angle;
	direction = dir;
}
std::map <MovingObject, Position> Camera::getView()
{
	std::map <MovingObject, Position> observation;
	//TODO
	return observation;
}