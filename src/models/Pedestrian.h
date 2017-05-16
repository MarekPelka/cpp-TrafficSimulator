#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#define _USE_MATH_DEFINES
#include <list>
#include <math.h>
#include "../Enums.h"
#include "MovingObject.h"
#include "Node.h"

typedef std::shared_ptr<Node> PNode;

class Pedestrian : MovingObject {
public:
    Pedestrian(std::list<PNode> nodes);
    void move(Street * const s, int time, int place);
    Position getPosition();
    Direction getOrientation();
    std::list<Node> getNodes();
    bool updatePosition(Street * const s, int time, int place);
    bool isMoving = false;
    bool operator==(const Pedestrian &p);
private:
    Direction orientation;
    std::list<Node> nodes;
    Direction predictDirection(Position start, Position end);
};
#endif