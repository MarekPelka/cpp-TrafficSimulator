#pragma once
#include "Position.h"
#include "Street.h"
#include "Enums.h"
#include "Node.h"
#include <list>
#include <map>
#include <algorithm>

class CityController {
public:

	static CityController* getInstance();
	
	static bool isInIntervalX(Position point, Street * range);
	static bool isInIntervalY(Position point, Street * range);
	bool isStreetExist(Node * start, Node * end);
	bool addStreet(Position start, Position end, bool twoWay = false);
	//bool isStreetsCross(Position start, Position end);
	Node* findNode(Position p);
	Node* findAndCraeteNode(Position p);
	std::list<Street*> getStreets();
	std::list<Node*> getNodes();
	std::list<std::list<Node*>> getWay(Node * start);
	std::list<Node*> findNeighbors(Node * n);
	std::map<Street*, Position> isStreetsCross(Position start, Position end);
	bool isStreetsOverlap(Position start, Position end);
	
private:
	
	CityController();
	static CityController* instance;
	bool handleCrossSteets(Position start, Position end, bool twoWay, std::map<Street*, Position> map);
	void createStreet(Node * start, Node * end, bool twoWay);
	void filterList(std::list<Node *>*);
	std::list<Street*> streets;
	std::list<Node*> nodes;
};
