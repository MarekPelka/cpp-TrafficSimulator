#include "CitiController.h"

CitiController::CitiController()
{
	streets = {};
	nodes = {};
}

CitiController::CitiController(MainWindow * mw)
{
	mainWindow = mw;
	streets = {};
	nodes = {};
}

void CitiController::setMainWindow(MainWindow * mw)
{
	mainWindow = mw;
}

void CitiController::addStreet(Position *start, Position *end, bool twoWay)
{
	//TO DO: Bad node creation, we do not check if that node already exists
	Node *a = new Node(start);
	Node *b = new Node(end);
	nodes.push_back(a);
	nodes.push_back(b);
	streets.push_back(new Street(a, b));
}

std::list<Street*>* CitiController::getStreets()
{
	return &streets;
}

std::list<QGraphicsItem*> CitiController::getStreetsGraphics()
{
	std::list<QGraphicsItem*> out = {};
	for (Street* s : streets)
	{
		out.push_back(new QGraphicsLineItem(
			s->getStartEndPositions().first.x,
			s->getStartEndPositions().first.y,
			s->getStartEndPositions().second.x,
			s->getStartEndPositions().second.y));
	}
	return out;
}

std::list<Node*>* CitiController::getNodes()
{
	return &nodes;
}
