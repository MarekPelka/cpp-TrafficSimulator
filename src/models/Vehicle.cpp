#include "Vehicle.h"
#include "../viewmodels/VehicleController.h"

Vehicle::Vehicle()
{
    type = CAR;
    length = CAR_LENGTH;
    acceleration = CAR_ACCELERATION;
    slowdown = CAR_SLOWDOWN;
    speed = 0;
    orientation = N;
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
    orientation = N;
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
    orientation = N;
    speed = 0;
}

Vehicle::Vehicle(vehicleType typ, std::list<Node*> nods)
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
	position = nods.front()->getPosition();
	nods.pop_front();
	for(auto n : nods)
		nodes.push_back(*n);
	orientation = N;
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
        else if (!checkMaxSpeed())
        {
            speed += acceleration * time / 1000;
        }
        else
        {
            speed = MAX_SPEED;
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
        case NONE:
        {
            //Do nothing
            break;
        }
        }
    }
    return false;
}

bool Vehicle::checkMaxSpeed() {
    if (speed >= MAX_SPEED)
        return true;
    else
        return false;
}

bool Vehicle::operator==(const Vehicle & v)
{
    return type == v.type && speed == v.speed && orientation == v.orientation && position == v.position;
}

Position Vehicle::getPosition() {
    return position;
}

vehicleType Vehicle::getType() {
    return type;
}

void Vehicle::updatePosition(int time) {
    if (isMoving == false && nodes.size() == 0)
    {
        VehicleController *vehC = VehicleController::getInstance();
        vehC->deleteVehicle(*this);
    }
    else
    {
        move(time);
        color = vehicleColor(speed);
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

std::list<int> Vehicle::vehicleColor(double veh_speed)
{
    //scaling
    veh_speed *= 100;
    veh_speed += 30;

    int r, g, b;
    double d = 256.0 / 20.0;

    if (veh_speed < 0) { //nadfiolet
        r = g = b = 0;
    }
    else if (veh_speed < 20)
    {
        r = 255 - d * veh_speed;
        g = 0;
        b = 255;
    }
    else if (veh_speed < 40)
    {
        r = 0;
        g = d * (veh_speed - 20);
        b = 255;
    }
    else if (veh_speed < 60)
    {
        r = 0;
        g = 255;
        b = 255 - d * (veh_speed - 40);
    }
    else if (veh_speed < 80)
    {
        r = d * (veh_speed - 60);
        g = 255;
        b = 0;
    }
    else if (veh_speed < 100)
    {
        r = 255;
        g = 255 - d * (veh_speed - 80);
        b = 0;
    }
    else { //podczerwieñ
        r = g = b = 0;
    }
    return std::list<int>{r, g, b};
}