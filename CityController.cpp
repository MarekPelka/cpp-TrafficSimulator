#include "CityController.h"

CityController* CityController::instance = nullptr;

CityController* CityController::getInstance() {
	if (!instance)
		instance = new CityController;
	return instance;
}

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

bool CityController::addStreet(Position start, Position end, bool twoWay) {
	//DONE: Bad node creation, we do not check if that node already exists
	//Check if beginning and end already exists
	//TODO: Change return of IsCross and isOverlap to std::map(s, pos) -> bool change to map.empty()
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
	std::pair<bool, std::pair<Position, Position>> overlap = isStreetsOverlap(start, end);
	if (overlap.first) {
		return false;
	}
	std::pair<bool, std::map<Street*, Position>> cross = isStreetsCross(start, end);
	if (cross.first) {
		std::list<Node*> crossingNodes = {};
		for (std::pair<Street*, Position> crossingStreet : cross.second) {
			std::pair<Position, Position> cStreetPositions = crossingStreet.first->getStartEndPositions();
			if (cStreetPositions.first == crossingStreet.second ||
				cStreetPositions.second == crossingStreet.second)
				continue;
			Node *middle = new Node(crossingStreet.second);
			nodes.push_back(middle);
			crossingNodes.push_back(middle);
			streets.push_back(new Street(middle, crossingStreet.first->getNodes().second));
			crossingStreet.first->alterEnd(middle);
		}
		crossingNodes.sort([](const Node *a, const Node *b)
		{
			if (a->position.x == b->position.x)
				return a->position.y < b->position.y;
			else
				return a->position.x < b->position.x;
		});
		filterList(&crossingNodes);

		//std::list::sort(crossingNodes.begin(), crossingNodes.end(), comp);

		if (s == nullptr) {
			s = new Node(start);
			nodes.push_back(s);
		}
		if (e == nullptr) {
			e = new Node(end);
			nodes.push_back(e);
		}
		//TODO: Another possibility, if you like using the BOOST_FOREACH macro is to use the BOOST_REVERSE_FOREACH macro introduced in Boost 1.36.0.
		if (Street::getPredictedDirection(start, end) == E) {
			streets.push_back(new Street(s, crossingNodes.front()));
			if (twoWay)
				streets.push_back(new Street(crossingNodes.front(), s));
			streets.push_back(new Street(crossingNodes.back(), e));
			if (twoWay)
				streets.push_back(new Street(e, crossingNodes.back()));
			for (auto it = crossingNodes.begin(); it != crossingNodes.end(); ++it) {

				streets.push_back(new Street(*it, *std::next(it)));
				if (twoWay)
					streets.push_back(new Street(*std::next(it), *it));
				if (std::next(it, 2) == crossingNodes.end()) // last element
				{
					break;
				}
			}
		} else if (Street::getPredictedDirection(start, end) == W) {
			streets.push_back(new Street(s, crossingNodes.back()));
			if (twoWay)
				streets.push_back(new Street(crossingNodes.back(), s));
			streets.push_back(new Street(crossingNodes.front(), e));
			if (twoWay)
				streets.push_back(new Street(e, crossingNodes.front()));
			for (auto it = crossingNodes.end(); it != crossingNodes.begin(); --it) {

				streets.push_back(new Street(*it, *std::prev(it)));
				if (twoWay)
					streets.push_back(new Street(*std::prev(it), *it));
				if (std::prev(it, 2) == crossingNodes.begin()) // last element
				{
					break;
				}
			}
		} else if (Street::getPredictedDirection(start, end) == S) {
			streets.push_back(new Street(s, crossingNodes.front()));
			if (twoWay)
				streets.push_back(new Street(crossingNodes.front(), s));
			streets.push_back(new Street(crossingNodes.back(), e));
			if (twoWay)
				streets.push_back(new Street(e, crossingNodes.back()));
			for (auto it = crossingNodes.begin(); it != crossingNodes.end(); ++it) {

				streets.push_back(new Street(*it, *std::next(it)));
				if (twoWay)
					streets.push_back(new Street(*std::next(it), *it));
				if (std::next(it, 2) == crossingNodes.end()) // last element
				{
					break;
				}
			}
		} else if (Street::getPredictedDirection(start, end) == N) {
			streets.push_back(new Street(s, crossingNodes.back()));
			if (twoWay)
				streets.push_back(new Street(crossingNodes.back(), s));
			streets.push_back(new Street(crossingNodes.front(), e));
			if (twoWay)
				streets.push_back(new Street(e, crossingNodes.front()));
			for (auto it = crossingNodes.end(); it != crossingNodes.begin(); --it) {

				streets.push_back(new Street(*it, *std::prev(it)));
				if (twoWay)
					streets.push_back(new Street(*std::prev(it), *it));
				if (std::prev(it, 2) == crossingNodes.begin()) // last element
				{
					break;
				}
			}
		}

		return true;
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
	return true;
}

std::pair<bool, std::map<Street*, Position>> CityController::isStreetsCross(Position start, Position end) {
	Direction d = Street::getPredictedDirection(start, end);
	std::pair<bool, std::map<Street*, Position>> output;
	output.first = false;
	output.second = {};
	for (Street *s : streets) {
		Direction ccStreetDir = s->getDirection();
		//Streets are perpendicular
		int computedDir1 = d + 1;
		int computedDir2 = d + 3;
		if (ccStreetDir == computedDir1 % 4 || ccStreetDir == computedDir2 % 4) {
			if (d == N) {
				if (s->getStartEndPositions().first.y < start.y &&
					s->getStartEndPositions().first.y > end.y) {
					if ((start.x < s->getStartEndPositions().first.x &&
						start.x > s->getStartEndPositions().second.x) ||
						(start.x > s->getStartEndPositions().first.x &&
						start.x < s->getStartEndPositions().second.x)) {
						output.first = true;
						output.second[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			} else if (d == E) {
				if (s->getStartEndPositions().first.x < end.x &&
					s->getStartEndPositions().first.x > start.x) {
					if ((start.y < s->getStartEndPositions().first.y &&
						start.y > s->getStartEndPositions().second.y) ||
						(start.y > s->getStartEndPositions().first.y &&
						start.y < s->getStartEndPositions().second.y)) {
						output.first = true;
						output.second[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == W) {
				if (s->getStartEndPositions().first.x < start.x &&
					s->getStartEndPositions().first.x > end.x) {
					if ((start.y < s->getStartEndPositions().first.y &&
						start.y > s->getStartEndPositions().second.y) ||
						(start.y > s->getStartEndPositions().first.y &&
						start.y < s->getStartEndPositions().second.y)) {
						output.first = true;
						output.second[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == S) {
				if (s->getStartEndPositions().first.y < end.y &&
					s->getStartEndPositions().first.y > start.y) {
					if ((start.x < s->getStartEndPositions().first.x &&
						start.x > s->getStartEndPositions().second.x) ||
						(start.x > s->getStartEndPositions().first.x &&
						start.x < s->getStartEndPositions().second.x)) {
						output.first = true;
						output.second[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			}
		} else { //Streets are parallel
			//Nothing happens
			//output.first = false;
		}
	}
	return output;
}
//TODO: Finish this function
std::pair<bool, std::pair<Position, Position>> CityController::isStreetsOverlap(Position start, Position end) {
	Direction d = Street::getPredictedDirection(start, end);
	std::pair<bool, std::pair<Position, Position>> output;
	output.first = false;
	output.second = {};
	for (Street *s : streets) {
		Direction ccStreetDir = s->getDirection();
		//Streets are parallel
		int computedDir1 = d + 2;
		if (ccStreetDir == d || ccStreetDir == computedDir1 % 4) {
			if (start.x == s->getStartEndPositions().first.x) {
				if ((start.y < s->getStartEndPositions().first.y &&
					start.y > s->getStartEndPositions().second.y) ||
					(start.y > s->getStartEndPositions().first.y &&
					start.y < s->getStartEndPositions().second.y)) {
					output.first = true;
					output.second = {Position(0, 0), Position(0, 0)};
				}
			} else {
				if ((start.x < s->getStartEndPositions().first.x &&
					start.x > s->getStartEndPositions().second.x) ||
					(start.x > s->getStartEndPositions().first.x &&
					start.x < s->getStartEndPositions().second.x)) {
					output.first = true;
					output.second = {Position(0, 0), Position(0, 0)};
				}
			}
		} else { //Streets are perpendicular
			//output.first = false;
		}
	}
	return output;
}

void CityController::filterList(std::list<Node *> *list) {
	auto it = std::unique(list->begin(), list->end(),
						  [](const Node *a, const Node *b)
	{
		return a->position.x == b->position.x && a->position.y == b->position.y;
	});
	list->erase(it, list->end());
}

std::list<Street*> CityController::getStreets() {
	return streets;
}

std::list<Node*> CityController::getNodes() {
	return nodes;
}

bool CityController::isInIntervalX(Position point, Street * range) {
	return false;
}
bool CityController::isInIntervalY(Position point, Street * range) {
	return false;
}
