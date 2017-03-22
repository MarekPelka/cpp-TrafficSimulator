#include "CityController.h"

CityController::CityController() {
	streets = {};
	nodes = {};
}

CityController::CityController(MainWindow * mw) {
	mainWindow = mw;
	streets = {};
	nodes = {};
}

void CityController::setMainWindow(MainWindow * mw) {
	mainWindow = mw;
}

void CityController::addStreet(Position start, Position end, bool twoWay) {
	//DONE: Bad node creation, we do not check if that node already exists
	//Check if beginning and end already exists
	//TODO: Check if streets cross
	Node *s = nullptr, *e = nullptr;
	for (Node *n : nodes) {
		if (n->getPosition() == start) {
			s = n;
			continue;
		} else if (n->getPosition() == end) {
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
	if (twoWay)
		streets.push_back(new Street(e, s));
}

std::pair<bool, std::map<Street*, Position>> CityController::isStreetsCross(Position start, Position end) {
	Direction d = Street::getPredictedDirection(start, end);
	std::pair<bool, std::map<Street*, Position>> output;// = new std::pair<bool, Position>();
	output.first = false;
	output.second = {};
	for (Street *s : streets) {
		Direction ccStreetDir = s->getDirection();
		//Streets are perpendicular
		if (ccStreetDir == d + 1 % 4 || ccStreetDir == d + 3 % 4) {
			if (d == N) {
				if (s->getStartEndPositions().first.y < end.y &&
					s->getStartEndPositions().first.y > start.y) {
					output.first = true;
					output.second[s] = Position(start.x, s->getStartEndPositions().first.y);
				} else
					continue;
			} else if (d == E) {
				if (s->getStartEndPositions().first.x < end.x &&
					s->getStartEndPositions().first.x > start.x) {
					output.first = true;
					output.second[s] = Position(s->getStartEndPositions().first.x, start.y);
				} else
					continue;
			} else if (d == W) {
				if (s->getStartEndPositions().first.x < start.x &&
					s->getStartEndPositions().first.x > end.x) {
					output.first = true;
					output.second[s] = Position(s->getStartEndPositions().first.x, start.y);
				} else
					continue;
			} else if (d == S) {
				if (s->getStartEndPositions().first.y < start.y &&
					s->getStartEndPositions().first.y > end.y) {
					output.first = true;
					output.second[s] = Position(start.x, s->getStartEndPositions().first.y);
				} else
					continue;
			}
		} else { //Streets are parallel
			if (d == N || d == S) {
				if(s->getStartEndPositions().first.x == start.x)
					output.first = true;
			} else {
				if (s->getStartEndPositions().first.y == start.y)
					output.first = true;
			}
		}
	}
	return output;
}

std::list<Street*> CityController::getStreets() {
	return streets;
}

std::list<Node*>* CityController::getNodes() {
	return &nodes;
}
