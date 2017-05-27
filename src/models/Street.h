/**
* \class Street
* \ingroup models
* \details class representing street object
* \author Marek Pelka
*/

#ifndef STREET_H
#define STREET_H
#include "Position.h"
#include "Node.h"
#include "../Enums.h"
#include <utility>
#include <memory>
#include <vector>
#include "Pedestrian.h"
#include "Vehicle.h"
#include "../viewmodels/MovementController.h"

typedef std::shared_ptr<Node> PNode;

class Street {
public:
    ///default constructor
	Street();
    /** constructor with parameters
    * \param nodeFrom start position
    * \param nodeTo end position
    * \param sidewalk if has sidewalk
    */
	Street(PNode nodeFrom, PNode nodeTo, bool sidewalk = false);
    ///return pair of nodes that are start and end of object
	std::pair <PNode, PNode> getNodes();
    ///return pair of objects start and end position
	std::pair <Position, Position> getStartEndPositions();
    ///return object orientation
	Direction getDirection();
    //return object length
	int getLength();
    /** predict direction of object with start end positions
    * \param start position
    * \param end position
    * \return direction
    */
	static Direction getPredictedDirection(Position start, Position end);
    ///return vector vehicles assigned to this object
	std::vector<Vehicle> * getVehicles();
    ///return vector pedestrians assigned to this object
	std::vector<Pedestrian> * getPedestrians();
    ///if object has sidewalk
	bool hasSidewalk();
    ///change street start position
	void alterStart(PNode n);
    ///change street end position
	void alterEnd(PNode n);
    ///add vehicle
	void addVehicleToStreet(Vehicle v);
    ///add pedestrian
	void addPedestrianToStreet(Pedestrian p);
    ///update positions all movable objects assigned to this object
	bool updatePositions(int interval);
	bool swichStreet(std::weak_ptr<Street> s, int spaceNeeded);
    ///equal to operator
	bool operator==(const Street &v);
private:
    ///object direction
	Direction direction;
    ///object start position
	PNode nodeFrom;
    ///object end position
	PNode nodeTo;
    ///if object has sidewalk
	bool sidewalk;
    ///object length
	int length;
    ///vector vehicles assigned to this object
	std::vector<Vehicle> vehOnStreet;
    ///vector pedestrians assigned to this object
	std::vector<Pedestrian> pedOnStreet;
	bool swichS(std::shared_ptr<Street> s);
};
#endif