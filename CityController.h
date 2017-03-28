#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Street.h"
#include "Enums.h"
#include "Node.h"
#include <list>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace boost;

class CityController {
public:

	void setMainWindow(MainWindow *mw);
	bool addStreet(Position start, Position end, bool twoWay = false);
	bool isInIntervalX(Position point, Street * range);
	bool isInIntervalY(Position point, Street * range);
	std::list<Street*> getStreets();
	std::list<Node*> getNodes();
	std::list<Node*> getWay(Position start, Position End);
	std::pair<bool, std::map<Street*, Position>> isStreetsCross(Position start, Position end);
	std::pair<bool, std::pair<Position, Position>> isStreetsOverlap(Position start, Position end);
	static CityController* getInstance();
private:
	Node* findNode(Position p);
	void createStreet(Node * start, Node * end, bool twoWay);
	typedef adjacency_list<boost::vecS, boost::hash_setS, boost::directedS, uint32_t, uint32_t, boost::no_property> Graph_d;
	CityController();
	CityController(MainWindow *mw);
	Graph_d gh;
	void filterList(std::list<Node *>*);
	MainWindow *mainWindow;
	std::list<Street*> streets;
	std::list<Node*> nodes;
	static CityController* instance;
};
