#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "Position.h"
#include <memory>

class Street;
class MovingObject {
public:
    Position position;
    virtual void move(Street * const, int, int) = 0;
};
#endif