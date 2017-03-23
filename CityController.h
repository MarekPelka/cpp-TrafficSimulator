#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Street.h"
#include "Enums.h"
#include "Node.h"
#include <list>
#include <map>

class CityController
{
public:
	CityController();
	CityController(MainWindow *mw);
	void setMainWindow(MainWindow *mw);
	bool addStreet(Position start, Position end, bool twoWay = false);
	std::list<Street*> getStreets();
	std::list<Node*>* getNodes();
	std::pair<bool, std::map<Street*, Position>> isStreetsCross(Position start, Position end);
	std::pair<bool, std::pair<Position, Position>> isStreetsOverlap(Position start, Position end);
private:
	void filterList(std::list<Node *>*);
	MainWindow *mainWindow;
	std::list<Street*> streets;
	std::list<Node*> nodes;
};
