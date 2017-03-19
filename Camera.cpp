#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Position pos, int angl, directions dir)
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
