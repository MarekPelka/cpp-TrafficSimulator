/**
* \class Node
* \ingroup models
* \details class representing crossroads and parkings
* \author Michal Krzeminski
* \author Marek Pelka
*/


#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "Position.h"
#include <map>
#include "../Enums.h"
#include <memory>

class Street;
class Node {
public:
    ///default destructor
    ~Node();
    ///default constructor
    Node();
    /** constructor with parameter
    * \param x x coordinate
    * \param y y coordinate
    */
    Node(int x, int y);
    /** constructor with parameter
    * \param p position of crossroad
    */
    Node(Position p);
    /// return object position
    Position getPosition();
    ///return object identifier
    int getNumber();
    ///return map with streets connected to this object
	std::map<int, std::weak_ptr<Street>> getStreetsIn();
    ///node position
    Position position;
    ///unique indentifier
    int number;
    /**
    * \return bool if this object is parking
    */
    bool isParking();
    /** set if it is parking
    * \param p bool parking
    */
    void setIsParking(bool p);
    //fill map with street that is connected to this object
	void addStreetIn(Direction d, std::weak_ptr<Street> PWStreet);
private:
    ///flag stating if this object is parking or normal crossroad
    bool _parking = false;
    ///static counter for identifier
    static int all_Nodes;
    ///map with streets connected to this object
	std::map<int, std::weak_ptr<Street>> streetsIn;
};
#endif