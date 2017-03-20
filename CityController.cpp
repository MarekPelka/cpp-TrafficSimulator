#include "CityController.h"

CityController::CityController()
{
	streets = {};
	nodes = {};
}

CityController::CityController(MainWindow * mw)
{
	mainWindow = mw;
	streets = {};
	nodes = {};
}

void CityController::setMainWindow(MainWindow * mw)
{
	mainWindow = mw;
}

void CityController::addStreet(Position start, Position end, bool twoWay)
{
	//DONE: Bad node creation, we do not check if that node already exists
	//Check if beginning and end already exists
	//TODO: Check if streets cross
	Node *s = nullptr, *e = nullptr;
	for (Node *n : nodes)
	{
		if (n->getPosition() == start) {
			s = n;
			continue;
		}
		else if (n->getPosition() == end) {
			e = n;
			continue;
		}
		if (s != nullptr && e != nullptr)
			break;
	}
	if (s == nullptr) {
		s = new Node(start);
		nodes.push_back(s);
	}
	if (e == nullptr) {
		e = new Node(end);
		nodes.push_back(e);
	}
	
	streets.push_back(new Street(s, e));
	if(twoWay)
		streets.push_back(new Street(e, s));
}

std::list<Street*> CityController::getStreets()
{
	return streets;
}

std::list<Node*>* CityController::getNodes()
{
	return &nodes;
}
