#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#define _USE_MATH_DEFINES
#include <list>
#include <math.h>
#include "../Enums.h"
#include "Node.h"

typedef std::shared_ptr<Node> PNode;

class Pedestrian{
public:
    Pedestrian(std::list<PNode> nodes);
    void move(int time);
    Position getPosition();
    Direction getOrientation();
    std::list<Node> getNodes();
    bool updatePosition(int time);
    bool isMoving = false;
    bool operator==(const Pedestrian &p);
private:
    Position position;
    Direction orientation;
    std::list<Node> nodes;
    Direction predictDirection(Position start, Position end);
};
#endif