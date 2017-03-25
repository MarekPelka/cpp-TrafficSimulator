#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Street.h"
#include "Enums.h"
#include "Node.h"
#include <list>
#include <map>

class CityController {
public:
	void setMainWindow(MainWindow *mw);
	bool addStreet(Position start, Position end, bool twoWay = false);
	bool isInIntervalX(Position point, Street * range);
	bool isInIntervalY(Position point, Street * range);
	std::list<Street*> getStreets();
	std::list<Node*> getNodes();
	std::pair<bool, std::map<Street*, Position>> isStreetsCross(Position start, Position end);
	std::pair<bool, std::pair<Position, Position>> isStreetsOverlap(Position start, Position end);
	static CityController* getInstance();
private:
	CityController();
	CityController(MainWindow *mw);
	void filterList(std::list<Node *>*);
	MainWindow *mainWindow;
	std::list<Street*> streets;
	std::list<Node*> nodes;
	static CityController* instance;
};
