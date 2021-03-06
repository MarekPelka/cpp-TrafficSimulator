/**
 * \class MovingObject
 * \ingroup models
 * \details abstract class representing moving object
 * \author Michal Krzeminski
*/

#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "Position.h"
#include <memory>

class Street;
class MovingObject {
public:
    ///object position
    Position position;
    ///state of object to switch street
    bool toSwitch = false;
    ///pointer to street to which object will be switched
    std::shared_ptr<Street> streetToSwitch;
    /// move object
    virtual void move(Street * const, int, int) = 0;
    /// change object position
    virtual bool updatePosition(Street * const s, int time, int place) = 0;
};
#endif