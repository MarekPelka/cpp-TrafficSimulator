#pragma once
#define _USE_MATH_DEFINES
#include <list>
#include <map>
#include <math.h>
#include "../Enums.h"
#include "Position.h"
#include "MovingObject.h"

class Camera {
public:
    Camera();
    Camera(Position position);
    Camera(Position position, int angle, Direction direction);
    void setAngle(int angle);
    int getAngle();
    void setDirection(Direction direction);
    Direction getDirection();
    void clearObservation();
    void updateObservation();
    std::list<std::pair<int,int>> getView();
    bool operator==(const Camera &v);
private:
    double getAngleBetweenPoints(Position p1, Position p2);
    bool checkIfInZone(double angle);
    double distanceBetweenPoints(Position p1, Position p2);

    Position position;
    int angle;
    Direction direction;
    std::list<std::pair<int, int>> observation;
};
