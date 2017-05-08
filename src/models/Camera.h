#pragma once
#define _USE_MATH_DEFINES
#include <list>
#include <map>
#include <math.h>
#include "../Enums.h"
#include "../models/Position.h"
#include "../models/MovingObject.h"

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
    double getAngleBetweenPoints(Position p1, Position p2);
    bool checkIfInZone(double angle);
    bool checkIfBuilding(Position p1, Position p2);
    bool static LineIntersectsLine(Position l1p1, Position l1p2, Position l2p1, Position l2p2);
    double getDistanceBetweenPoints(Position p1, Position p2);

private:
    Position position;
    int angle;
    Direction direction;
    std::list<std::pair<int, int>> observation;
};
