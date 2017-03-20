#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Street.h"
#include "Enums.h"
#include "Node.h"
#include <list>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class CityController
{
public:
	CityController();
	CityController(MainWindow *mw);
	void setMainWindow(MainWindow *mw);
	void addStreet(Position start, Position end, bool twoWay = false);
	std::list<Street*> getStreets();
	//TODO: Move to mainwindow
	std::list<Node*>* getNodes();
private:
	MainWindow *mainWindow;
	std::list<Street*> streets;
	std::list<Node*> nodes;
};
