/**
* \class Camera
* \ingroup models
* \details class representing camera object
* \author Michal Krzeminski
*/

#ifndef CAMERA_H
#define CAMERA_H

#define _USE_MATH_DEFINES
#include <list>
#include <map>
#include <math.h>
#include "../Enums.h"
#include "../models/Position.h"

class Camera {
public:
    ///default constructor
    Camera();
    /** constructor with parameter
    * \param position of object
    */
    Camera(Position position);
    /** constructor with parameters
    * \param position of object
    * \param angle object
    * \param direction of object
    */
    Camera(Position position, int angle, Direction direction);
    ///set object angle
    void setAngle(int angle);
    ///return object angle
    int getAngle();
    ///set object direction
    void setDirection(Direction direction);
    ///return object direction
    Direction getDirection();
    ///clear object observations
    void clearObservation();
    void updateObservation();
    ///return list of observtions
    std::list<std::pair<int,int>> getView();
    ///equal to operator
    bool operator==(const Camera &v);
    /**
    * method calulating angle between two points
    * \param p1 start point position
    * \param p2 end point position
    * \return double angle
    */
    double getAngleBetweenPoints(Position p1, Position p2);
    /**
    * method checking if parameter angle is in camera field of view
    * taking int account object's direction and angle
    * \param angle
    * \return bool status
    */
    bool checkIfInZone(double angle);
    /**
    * method calulating distance to square between two points
    * \param p1 start point position
    * \param p2 end point position
    * \return double distance to square
    */
    double getDistanceBetweenPoints(Position p1, Position p2);

	Position getPosition();
    ///unique camera identifier
    int id;
    ///counter for indentifier
    static int counter;

private:
    ///object position
    Position position;
    ///object angle
    int angle;
    ///object direction
    Direction direction;
    ///list of observed points in camera field of view
    std::list<std::pair<int, int>> observation;
};
#endif