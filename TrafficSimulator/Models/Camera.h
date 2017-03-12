#pragma once
#include <map>
#include "Enums.h"
#include "Position.h"
#include "MovingObject.h"

class Camera
{
	public:
		Camera();
		Camera(Position position, int angle, directions direction);
		Position position;
		int angle;
		directions direction;

		std::map<MovingObject, Position> getView();

};