#pragma once
#include <map>
#include "Enums.h"
#include "Position.h"
#include "MovingObject.h"

class Camera
{
	public:
		Camera();
		Camera(Position position, int angle, Direction direction);
		Position position;
		int angle;
		Direction direction;

        std::map<int, int> getView();
};
