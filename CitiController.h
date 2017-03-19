#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Street.h"
#include "Node.h"
#include <list>
#include <QGraphicsItem>

class CitiController
{
public:
	CitiController();
	CitiController(MainWindow *mw);
	void setMainWindow(MainWindow *mw);
	void addStreet(Position start, Position end, bool twoWay = false);
	std::list<Street*>* getStreets();
	std::list<QGraphicsItem*> getStreetsGraphics();
	std::list<Node*>* getNodes();
private:
	MainWindow *mainWindow;
	std::list<Street*> streets;
	std::list<Node*> nodes;
};
