/**
* \class Pedestrian
* \ingroup models
* \details class representing pedestrian object
* \author Michal Krzeminski
*/

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
    /** constructor with parameter
    * \param list of nodes pedestrian will go through
    */
    Pedestrian(std::list<PNode> nodes);
    /** change object position depending on time interval
    * \param time interval
    */
    void move(int time);
    ///return object position
    Position getPosition();
    ///return object orientation
    Direction getOrientation();
    ///return list of nodes object will go through
    std::list<Node> getNodes();
    /** specify if move() object or do nothing, false will result in object deletion
    * \param time interval
    * \return status
    */
    bool updatePosition(int time);
    ///state of object
    bool isMoving = false;
    ///equal to operator
    bool operator==(const Pedestrian &p);
private:
    ///object position
    Position position;
    ///object orientation
    Direction orientation;
    ///list of nodes
    std::list<Node> nodes;
    /** predict direction of object with start end positions
    * \param start position
    * \param end position
    * \return direction
    */
    Direction predictDirection(Position start, Position end);
};
#endif