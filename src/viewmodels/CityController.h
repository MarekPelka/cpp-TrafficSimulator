#ifndef CITYCONTROLLER_H
#define CITYCONTROLLER_H

#include "../models/Position.h"
#include "../models/Street.h"
#include "../Enums.h"
#include "../models/Node.h"
#include <list>
#include <map>
#include <algorithm>
#include <memory>

typedef std::shared_ptr<Node> PNode;
typedef std::shared_ptr<Street> PStreet;

class CityController {
public:
    static CityController* getInstance();
    static bool isInIntervalX(Position point, PStreet range);
    static bool isInIntervalY(Position point, PStreet range);
    bool isStreetExist(PNode start, PNode end);
    bool addStreet(Position start, Position end, bool twoWay = false);
    //bool isStreetsCross(Position start, Position end);
    PNode findNode(Position p);
    PNode findAndCreateNode(Position p);
    std::list<PStreet> getStreets();
    std::list<PNode> getNodes();
    std::list<PNode> getParkings();
    std::list<std::list<PNode>> getWay(PNode start);
    std::list<PNode> findWay(PNode start, PNode end);
    std::list<PNode> findNeighbors(PNode n);
    std::map<PStreet, Position> isStreetsCross(Position start, Position end);
    bool isStreetsOverlap(Position start, Position end);
    void clearController();

    bool upgradeToParking(PNode n);
    bool downgradeFromParking(PNode n);
private:

    CityController();
    static CityController* instance;
    bool handleCrossSteets(Position start, Position end, bool twoWay, std::map<PStreet, Position> map);
    void createStreet(PNode start, PNode end, bool twoWay);
    void filterList(std::list<PNode>*);
    std::list<PStreet> streets;
    std::list<PNode> nodes;
    std::list<PNode> parkings;
};
#endif
