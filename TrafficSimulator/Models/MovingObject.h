#pragma once
#include "Position.h"

class MovingObject
{
	public:
		int speed;
		Position position;
		virtual void move();
};
