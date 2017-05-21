#ifndef CITYCONTROLLER_H
#define CITYCONTROLLER_H

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
	static CityController* getInstance();
	static bool isInIntervalX(Position point, PStreet range);
	static bool isInIntervalY(Position point, PStreet range);
	bool addStreet(Position start, Position end, bool twoWay = false);
	bool isStreetsOverlap(Position start, Position end);
	bool isStreetExist(PNode start, PNode end);
	bool downgradeFromParking(PNode n);
	bool upgradeToParking(PNode n);
	PNode findNode(Position p);
	PNode findAndCreateNode(Position p);
	std::list<PStreet> getStreets();
	std::list<PNode> getNodes();
	std::list<PNode> getParkings();
	std::list<std::list<PNode>> getWay(PNode start);
	std::list<PNode> findWay(PNode start, PNode end);
	std::list<PNode> findNeighbors(PNode n);
	std::map<PStreet, Position> isStreetsCross(Position start, Position end);
	void clearController();

private:
	CityController();
	static CityController* instance;
	std::list<PStreet> streets;
	std::list<PNode> parkings;
	std::list<PNode> nodes;

	PNode createNode(Position p);
	bool handleCrossStreets(Position start, Position end, bool twoWay, std::map<PStreet, Position> map);
	bool handleNewCrossStreets(PNode s, PNode e, bool twoWay, std::list<PNode> crossingNodes);
	std::list<PNode> handleExistingCrossStreets(std::map<PStreet, Position> map);
	std::list<PNode> sortNodeList(std::list<PNode> list);
	void createStreet(PNode start, PNode end, bool twoWay);
	void filterList(std::list<PNode>*);
};
#endif
