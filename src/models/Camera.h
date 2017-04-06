#pragma once
#include <map>
#include "src/Enums.h"
#include "src/models/Position.h"
#include "src/models/MovingObject.h"

class Camera
{
    public:
        Camera();
        Camera(Position position);
        Camera(Position position, int angle, Direction direction);
        void setAngle(int angle);
        int getAngle();
        void setDirection(Direction direction);
        Direction getDirection();

    private:
        Position position;
        int angle = 0;
        Direction direction = N;

        //return observation - position of objects in eyeshot
        std::map<int, int> getView();
};
