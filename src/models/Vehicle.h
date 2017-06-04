/**
* \class Vehicle
* \ingroup models
* \details class representing vehicle object
* \author Michal Krzeminski
* \author Marek Pelka
*/

#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <list>
#include <memory>
#include "../Enums.h"
#include "Node.h"
#include "MovingObject.h"

typedef std::shared_ptr<Node> PNode;

class Vehicle : MovingObject {
public:
	~Vehicle();
    /** constructor with parameters
    * \param type car or truck
    * \param nodes list of nodes that vehicle will go through
    */
	Vehicle(VehicleType type, std::list<Node> nodes);
    /** constructor with parameters
    * \param type car or truck
    * \param nodes list of nodes that vehicle will go through
    */
	Vehicle(VehicleType type, std::list<PNode> nodes);
    ///return object position
	Position getPosition();
    ///set object position
    void setPosition(Position &pos);
    ///return object type
	VehicleType getType();
    ///return list of nodes that vehicle will go through 
	std::list<Node> getNodes();
    /** specify if move() object or do nothing, false will result in object deletion
    * \param s street that vehicle belongs to
    * \param time interval
    * \param place in queue
    * \return status
    */
	bool updatePosition(Street * const s, int time, int place);
    ///return object orientation
	Direction getOrientation();
    ///check if object need to start to brake
	bool checkSlowdown(Position step);
    /// check if current speed is equal or greater than maximum speed
	bool checkMaxSpeed();
    ///equal to operator
	bool operator==(const Vehicle &v);
    ///return state of object to clear
	bool getToSwitch();
    ///set state of object to switch street
	void setToSwitch(bool t);
	double getSpeed();
	//std::list<int> * getColor();
    ///return pointer to street to which object will be switched
	std::shared_ptr<Street> getStreetToSwitch();
    ///set pointer to street to which object will be switched
	void setStreetToSwitch(std::shared_ptr<Street> t);
private:
    ///object length
	int length;
    ///object acceleration
	double acceleration;
    ///object slowdown
	double slowdown;
    ///state of object to clear
	bool toClear = false;
    ///object type
	VehicleType type;
    ///object speed
	double speed;
    /// list of nodes that vehicle will go through 
	std::list<Node> nodes;
    ///object orientation
	Direction orientation;
	///object color
	//std::list<int> color;
	///state of object
	bool isMoving = false;
	/** change object position depending on time interval
	* \param s street that vehicle belongs to
	* \param time interval
	* \param place in queue
	*/
	void move(Street * const s, int time, int place);
    /** predict direction of object with start end positions
    * \param start position
    * \param end position
    * \return direction
    */
	Direction getPredictedDirection(Position start, Position end);
    /** update object speed
    * \param d flag
    * \param time interval
    * \param inFront interval
    */
	void calculateSpeed(int d, int time, Vehicle inFront);
};
#endif