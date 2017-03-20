#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Position pos, int angl, Direction dir)
{
	position = pos;
    angle = angl;
	direction = dir;
}
std::map <int, int> Camera::getView()
{
    std::map <int, int> observation;
	//TODO
	return observation;
}
