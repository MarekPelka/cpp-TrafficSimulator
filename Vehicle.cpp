#include "Vehicle.h"

Vehicle::Vehicle()
{
    type = CAR;
    length = CAR_LENGTH;
    acceleration = CAR_ACCELERATION;
    slowdown = CAR_SLOWDOWN;
    speed = 0;
}

Vehicle::Vehicle(vehicleType typ, Position pos)
{
	type = typ;
	if (type == CAR)
	{
		length = CAR_LENGTH;
		acceleration = CAR_ACCELERATION;
		slowdown = CAR_SLOWDOWN;
	}
	else if(type == TRUCK)
	{
		length = TRUCK_LENGTH;
		acceleration = TRUCK_ACCELERATION;
		slowdown = TRUCK_SLOWDOWN;
	}
	position = pos;
    speed = 0;
}

Vehicle::Vehicle(vehicleType typ, std::list<Node> nods)
{
    type = typ;
    if (type == CAR)
    {
        length = CAR_LENGTH;
        acceleration = CAR_ACCELERATION;
        slowdown = CAR_SLOWDOWN;
    }
    else if (type == TRUCK)
    {
        length = TRUCK_LENGTH;
        acceleration = TRUCK_ACCELERATION;
        slowdown = TRUCK_SLOWDOWN;
    }
    position = nods.front().getPosition();
    nods.pop_front();
    nodes = nods;
    speed = 0;
}

void Vehicle::move(int time) {
    if (nodes.size() != 0)
    {
        isMoving = true;
        Position step = nodes.front().getPosition();
        if (checkSlowdown(step))
        {
            if (speed - slowdown*time / 1000 > 0)
            {
                speed -= slowdown * time / 1000;
            }
        }
        else if (!checkMaxSpeed(step))
        {
            speed += acceleration * time / 1000;
        }
        int temp = speed*time;
        if (position.x != step.x || position.y != step.y)
        {
            if (position.x < step.x)
            {
                orientation = E;
                if (temp + position.x > step.x)
                {
                    temp = step.x;
                }
                else
                {
                    temp += position.x;
                }
                position = Position(temp, position.y);
            }
            else if (position.x > step.x)
            {
                orientation = W;
                if (position.x - temp < step.x)
                {
                    temp = step.x;
                }
                else
                {
                    temp = position.x - temp;
                }
                position = Position(temp, position.y);
            }
            else if (position.y < step.y)
            {
                orientation = S;
                if (temp + position.y > step.y)
                {
                    temp = step.y;
                }
                else
                {
                    temp += position.y;
                }
                position = Position(position.x, temp);
            }
            else if (position.y > step.y)
            {
                orientation = N;
                if (position.y - temp < step.y)
                {
                    temp = step.y;
                }
                else
                {
                    temp = position.y - temp;
                }
                position = Position(position.x, temp);
            }
        }
        else
        {
            nodes.pop_front();
        }
    }
    else
    {
        isMoving = false;
        //wyslac sygnal ze graphicFab moze usunac samochod
    }
}

bool Vehicle::checkSlowdown(Position step) {
    if (nodes.size() == 1)
    {
        switch (orientation) {
        case N:
        {
            if (position.y - BRAKING_DISTANCE < step.y)
            {
                return true;
            }
            break;
        }
        case S:
        {
            if (position.y + BRAKING_DISTANCE > step.y)
            {
                return true;
            }
            break;
        }
        case E:
        {
            if (position.x + BRAKING_DISTANCE > step.x)
            {
                return true;
            }
            break;
        }
        case W:
        {
            if (position.x - BRAKING_DISTANCE < step.x)
            {
                return true;
            }
            break;
        }
        }
    }
    return false;
}

bool Vehicle::checkMaxSpeed(Position step) {
    //TODO check for this street what is max speed
    return false;
}

Position Vehicle::getPosition() {
	return position;
}

vehicleType Vehicle::getType() {
	return type;
}

void Vehicle::updatePosition(int time) {
	//TODO matematyka zwiazana z predkoscia o ile trzeba zmienic wspolrzedne samochodu
    if (isMoving == false && nodes.size() == 0)
    {
       //sedn signal to destroy this vehicle
    }
    else
    {
        move(time);
    }
}

Direction Vehicle::getOrientation()
{
    return orientation;
}

Vehicle::~Vehicle()
{
    type = NOTHING;
}
