/**
* \class CityController
* \ingroup viewmodels
* \details class controlling city
* \author Marek Pelka
*/

#ifndef CITYCONTROLLER_H
#define CITYCONTROLLER_H

#include "CameraController.h"

#include "../models/Position.h"
#include "../models/Street.h"
#include "../models/Node.h"
#include "../Enums.h"

#include <algorithm>
#include <memory>
#include <list>
#include <map>

typedef std::shared_ptr<Node> PNode;
typedef std::shared_ptr<Street> PStreet;

class CityController {

public:
    ///destructor
    void DescCityController();
    ///singleton getInstance method
	static CityController* getInstance();
	/**Checks if point is between street start/end on X cord
	* \param point
	* \param street
	*/
	static bool isInIntervalX(Position point, PStreet range);
	/**Checks if point is between street start/end on Y cord
	* \param point
	* \param street
	*/
	static bool isInIntervalY(Position point, PStreet range);
	/**Adds street to City
	* \param start
	* \param end
	* \param twoWay
	*/
	bool addStreet(Position start, Position end, bool twoWay = false);
	/**Checks if streets overlap
	* \param start
	* \param end
	*/
	bool isStreetsOverlap(Position start, Position end);
	/**Checks if street exist
	* \param start
	* \param end
	*/
	bool isStreetExist(PNode start, PNode end);
	/**Checks if street intersects
	* \param Position
	*/
	bool checkIfIntersectStreet(Position p);
	/**Downgrades node from parking
	* \param node
	*/
	bool downgradeFromParking(PNode n);
	/**Upgrade node to parking
	* \param node
	*/
	bool upgradeToParking(PNode n);
	/**Finds node on in a given position
	* \param Position
	*/
	PNode findNode(Position p);
	/**Finds node on in a given position, if node does not exist create it
	* \param Position
	*/
	PNode findAndCreateNode(Position p);
	///Returns all streets
	std::list<PStreet> getStreets();
	///Returns all nodes
	std::list<PNode> getNodes();
	///Returns all parkings
	std::list<PNode> getParkings();
	/**Finds ways from starting node to all others reachable nodes
	* \param startingNode
	*/
	std::list<std::list<PNode>> getWay(PNode start);
	/**Finds ways from node A to node B
	* \param startingNode
	* \param destinationNode
	*/
	std::list<PNode> findWay(PNode start, PNode end);
	/**Finds all neighbors of a given node
	* \param node
	*/
	std::list<PNode> findNeighbors(PNode n);
	/**Finds ways from position A to position B
	* \param startingPosition
	* \param destinationPosition
	*/
	std::list<PNode> nodesPath(Position start, Position end);
	/**Checks if streets cross
	* \param startOfStreet
	* \param endOfStreet
	*/
	std::map<PStreet, Position> isStreetsCross(Position start, Position end);
    ///clearing controller
	void clearController();

	void deleteStuff(Position p);
private:
    ///default constructor
	CityController();
    ///singleton instance pointer
	static CityController* instance;
    ///all streets list
	std::list<PStreet> streets;
    ///all parkings list
	std::list<PNode> parkings;
    ///all nodes list
	std::list<PNode> nodes;
	/**creates node on given position
	* \param position
	*/
	PNode createNode(Position p);
	/**handles street crossing of existing streets
	* \param startStreet
	* \param endStreet
	* \param isStreetTwoWay
	* \param mapOfStreetCrossing
	*/
	bool handleCrossStreets(Position start, Position end, bool twoWay, std::map<PStreet, Position> map);
	/**handles street crossing of new parts of street
	* \param startStreet
	* \param endStreet
	* \param isStreetTwoWay
	* \param mapOfNodeCrossing
	*/
	bool handleNewCrossStreets(PNode s, PNode e, bool twoWay, std::list<PNode> crossingNodes);
	/**handles street crossing
	* \param streetCrossings
	*/
	std::list<PNode> handleExistingCrossStreets(std::map<PStreet, Position> map);
	/**Sorts node list by postion - first by X then by Y
	* \param list
	*/
	std::list<PNode> sortNodeList(std::list<PNode> list);
	/**Adds street to list
	* \param startStreet
	* \param endStreet
	* \param isStreetTwoWay
	*/
	void createStreet(PNode start, PNode end, bool twoWay);
	/**Removes duplicate nodes from list 
	* \param listToFilter
	*/
	void filterList(std::list<PNode>*);
};
#endif
