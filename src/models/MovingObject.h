#pragma once
#include "Position.h"
#include <memory>

class Street;
class MovingObject {
public:
    int speed;
    Position position;
    virtual void move(Street * const, int, int) = 0;
};
