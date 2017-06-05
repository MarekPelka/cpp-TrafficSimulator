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

void CityController::DescCityController() {
    if (instance) {
        streets.clear();
        nodes.clear();
        parkings.clear();
        delete instance;
    }
}

bool CityController::isInIntervalX(Position point, PStreet range) {

	int upper = range->getStartEndPositions().first.x > range->getStartEndPositions().second.x ? range->getStartEndPositions().first.x : range->getStartEndPositions().second.x;
	int lower = range->getStartEndPositions().first.x < range->getStartEndPositions().second.x ? range->getStartEndPositions().first.x : range->getStartEndPositions().second.x;
	if (abs(point.x - lower) <= (upper - lower))
		if (point.x >= lower)
			return true;
	return false;
}

bool CityController::isInIntervalY(Position point, PStreet range) {
	int upper = range->getStartEndPositions().first.y > range->getStartEndPositions().second.y ? range->getStartEndPositions().first.y : range->getStartEndPositions().second.y;
	int lower = range->getStartEndPositions().first.y < range->getStartEndPositions().second.y ? range->getStartEndPositions().first.y : range->getStartEndPositions().second.y;
	if (abs(point.y - lower) <= (upper - lower))
		if (point.y >= lower)
			return true;
	return false;
}

bool CityController::isStreetExist(PNode start, PNode end) {
	if (start == nullptr || end == nullptr)
		return false;
	else
		for (PStreet stre : streets) {
			if (stre->getNodes().first == start && stre->getNodes().second == end)
				return true;
		}
	return false;
}

bool CityController::checkIfIntersectStreet(Position p) {
	for (auto street : CityController::getInstance()->getStreets()) {
		//TODO if street twoway check two edges of street (main line +- STREET_WIDTH)
		//TODO if street not twoway check correct edge and main line
		int offset = STREET_WIDTH;
		if (street->hasSidewalk()) {
			offset += SIDEWALK_WIDTH;
		}

		//check middle line
		Position p1 = street->getStartEndPositions().first;
		Position p2 = street->getStartEndPositions().second;
		if (CameraController::getInstance()->LineIntersectsLine(p1, p2, p, Position(p.x + 2 * FULL_STREET_WIDTH, p.y)) ||
			CameraController::getInstance()->LineIntersectsLine(p1, p2, p, Position(p.x, p.y + 2 * FULL_STREET_WIDTH)) ||
			CameraController::getInstance()->LineIntersectsLine(p1, p2, Position(p.x + 2 * FULL_STREET_WIDTH, p.y + 2 * FULL_STREET_WIDTH), Position(p.x + 2 * FULL_STREET_WIDTH, p.y)) ||
			CameraController::getInstance()->LineIntersectsLine(p1, p2, Position(p.x + 2 * FULL_STREET_WIDTH, p.y + 2 * FULL_STREET_WIDTH), Position(p.x, p.y + 2 * FULL_STREET_WIDTH))) {
			return true;
		}

		//check outer edge
		Position q1;
		Position q2;
		switch (street->getDirection()) {
			case N:
			{
				q1 = Position(p1.x + offset, p1.y);
				q2 = Position(p2.x + offset, p2.y);
				break;
			}
			case S:
			{
				q1 = Position(p1.x - offset, p1.y);
				q2 = Position(p2.x - offset, p2.y);
				break;
			}
			case E:
			{
				q1 = Position(p1.x, p1.y + offset);
				q2 = Position(p2.x, p2.y + offset);
				break;
			}
			case W:
			{
				q1 = Position(p1.x, p1.y - offset);
				q2 = Position(p2.x, p2.y - offset);
				break;
			}
			default:
			{
				q1 = Position(0, 0);
				q2 = Position(0, 0);
			}
		}
		if (CameraController::getInstance()->LineIntersectsLine(q1, q2, p, Position(p.x + 2 * FULL_STREET_WIDTH, p.y)) ||
			CameraController::getInstance()->LineIntersectsLine(q1, q2, p, Position(p.x, p.y + 2 * FULL_STREET_WIDTH)) ||
			CameraController::getInstance()->LineIntersectsLine(q1, q2, Position(p.x + 2 * FULL_STREET_WIDTH, p.y + 2 * FULL_STREET_WIDTH), Position(p.x + 2 * FULL_STREET_WIDTH, p.y)) ||
			CameraController::getInstance()->LineIntersectsLine(q1, q2, Position(p.x + 2 * FULL_STREET_WIDTH, p.y + 2 * FULL_STREET_WIDTH), Position(p.x, p.y + 2 * FULL_STREET_WIDTH))) {
			return true;
		}
	}
	return false;
}

bool CityController::addStreet(Position start, Position end, bool twoWay) {
	PNode s = findNode(start);
	PNode e = findNode(end);

	if (isStreetExist(s, e)) return false;

	if (isStreetsOverlap(start, end) && e != nullptr) return false;

	std::map<PStreet, Position> cross = isStreetsCross(start, end);
	if (cross.empty()) {
		if (s == nullptr)
			s = createNode(start);
		if (e == nullptr)
			e = createNode(end);
		createStreet(s, e, twoWay);
		return true;
	} else {
		return handleCrossStreets(start, end, twoWay, cross);

			//return false;
	}
}

PNode CityController::createNode(Position p) {
	PNode n = std::make_shared<Node>(p);
	nodes.push_back(n);
	return n;
}

bool CityController::handleCrossStreets(Position start, Position end, bool twoWay, std::map<PStreet, Position> map) {

	PNode s = findAndCreateNode(start);
	PNode e = findAndCreateNode(end);

	std::list<PNode> intersectingNodes = {};

	for (auto inter : map) {
		PNode node = findAndCreateNode(inter.second);
		addStreet(node->getPosition(), inter.first->getStartEndPositions().second);
		inter.first->alterEnd(node);
		intersectingNodes.push_back(node);
	}
	intersectingNodes.push_back(s);
	intersectingNodes.push_back(e);
	intersectingNodes = sortNodeList(intersectingNodes);
	auto iter = intersectingNodes.begin();
	if (iter == intersectingNodes.end()) {
		return true;
	} else if (*iter == s) {
		++iter;
		while (iter != intersectingNodes.end()) {
			PNode a = *std::prev(iter);
			PNode b = *iter;
			addStreet(a->getPosition(), b->getPosition());
			++iter;
		}
	} else if (*iter == e) {
		std::list<PNode>::reverse_iterator rit = intersectingNodes.rbegin();
		++rit;
		while (rit != intersectingNodes.rend()) {
			PNode a = *std::prev(rit);
			PNode b = *rit;
			addStreet(a->getPosition(), b->getPosition());
			++rit;
		}

 }
	return true;
	//std::list<PNode> crossingNodes = handleExistingCrossStreets(map);
	/*if (s == nullptr && e == nullptr)
		return false;
	int size = 0;
	for (auto c : map) {
		if (c.second == start || c.second == end)
			size++;
		else
			return false;
	}
	if (map.size() <= size)
		return true;
	else
		return false;*/
	/*if (crossingNodes.back() == nullptr)
		return false;


	if (s == nullptr)
		s = createNode(start);
	if (e == nullptr)
		e = createNode(end);

	return handleNewCrossStreets(s, e, twoWay, crossingNodes);*/
}

std::list<PNode> CityController::handleExistingCrossStreets(std::map<PStreet, Position> map) {
	std::list<PNode> crossingNodes = {};

	for (std::pair<PStreet, Position> crossingStreet : map) {
		std::pair<Position, Position> cStreetPositions = crossingStreet.first->getStartEndPositions();
		if (cStreetPositions.first == crossingStreet.second ||
			cStreetPositions.second == crossingStreet.second)
			continue;

		PNode middle = findNode(crossingStreet.second);

		if (isStreetExist(middle, crossingStreet.first->getNodes().second))
			if (isStreetExist(crossingStreet.first->getNodes().first, middle)) {
				crossingNodes.push_back(nullptr);
			}

		if (middle == nullptr) {
			middle = createNode(crossingStreet.second);
		}

		crossingNodes.push_back(middle);
		auto cwks = std::make_shared<Street>(middle, crossingStreet.first->getNodes().second, true);
		streets.push_back(cwks);
		crossingStreet.first->getNodes().second->addStreetIn(cwks->getDirection(), cwks);
		crossingStreet.first->alterEnd(middle);
		middle->addStreetIn(crossingStreet.first->getDirection(), crossingStreet.first);
	}

	crossingNodes = sortNodeList(crossingNodes);
	filterList(&crossingNodes);
	return crossingNodes;
}

bool CityController::handleNewCrossStreets(PNode s, PNode e, bool twoWay, std::list<PNode> crossingNodes) {
	//Another possibility, if you like using the BOOST_FOREACH macro is to use the BOOST_REVERSE_FOREACH macro introduced in Boost 1.36.0.
	if (Street::getPredictedDirection(s->getPosition(), e->getPosition()) == E || Street::getPredictedDirection(s->getPosition(), e->getPosition()) == S) {

		createStreet(s, crossingNodes.front(), twoWay);
		createStreet(crossingNodes.back(), e, twoWay);
		if (crossingNodes.size() > 1)
			for (auto it = crossingNodes.begin(); it != crossingNodes.end(); ++it) {
				createStreet(*it, *std::next(it), twoWay);
				if (std::next(it, 2) == crossingNodes.end()) {
					break;
				}
			}
	} else if (Street::getPredictedDirection(s->getPosition(), e->getPosition()) == W || Street::getPredictedDirection(s->getPosition(), e->getPosition()) == N) {
		createStreet(s, crossingNodes.back(), twoWay);
		createStreet(crossingNodes.front(), e, twoWay);
		if (crossingNodes.size() > 1)
			for (auto it = crossingNodes.end(); it != crossingNodes.begin(); --it) {
				createStreet(*it, *std::prev(it), twoWay);
				if (std::prev(it, 2) == crossingNodes.begin()) {
					break;
				}
			}
	}
	return true;
}

std::list<PNode> CityController::sortNodeList(std::list<PNode> list) {
	list.sort([] (const PNode a, const PNode b) {
		if (a->position.x == b->position.x)
			return a->position.y < b->position.y;
		else
			return a->position.x < b->position.x;
	});
	return list;
}

std::map<PStreet, Position> CityController::isStreetsCross(Position start, Position end) {
	Direction d = Street::getPredictedDirection(start, end);
	std::map<PStreet, Position> output;
	output = {};
	for (PStreet s : streets) {
		Direction ccStreetDir = s->getDirection();
		//Streets are perpendicular
		int computedDir1 = d + 1;
		int computedDir2 = d + 3;
		if (ccStreetDir == computedDir1 % 4 || ccStreetDir == computedDir2 % 4) {
			if (d == N) {
				if (s->getStartEndPositions().first.y <= start.y &&
					s->getStartEndPositions().first.y >= end.y) {
					if (isInIntervalX(start, s)) {
						output[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			} else if (d == E) {
				if (s->getStartEndPositions().first.x <= end.x &&
					s->getStartEndPositions().first.x >= start.x) {
					if (isInIntervalY(start, s)) {
						output[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == W) {
				if (s->getStartEndPositions().first.x <= start.x &&
					s->getStartEndPositions().first.x >= end.x) {
					if (isInIntervalY(start, s)) {
						output[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == S) {
				if (s->getStartEndPositions().first.y <= end.y &&
					s->getStartEndPositions().first.y >= start.y) {
					if (isInIntervalX(start, s)) {
						output[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			}
		} else { //Streets are parallel
			  //Nothing happens
		}
	}
	return output;
}

void CityController::createStreet(PNode start, PNode end, bool twoWay) {

	PStreet s = std::make_shared<Street>(start, end, true);
	streets.push_back(s);
	end->addStreetIn(s->getDirection(), s);
	if (twoWay) {
		s = std::make_shared<Street>(end, start, true);
		streets.push_back(s);
		start->addStreetIn(s->getDirection(), s);
	}
}

PNode CityController::findNode(Position p) {
	PNode out = PNode();

	for (PNode n : nodes) {
		if (n->getPosition() == p) {
			out = n;
			continue;
		}
		if (out != nullptr)
			break;
	}
	return out;
}

PNode CityController::findAndCreateNode(Position p) {
	PNode out = nullptr;

	for (PNode n : nodes) {
		if (n->getPosition() == p) {
			out = n;
			continue;
		}
		if (out != nullptr)
			break;
	}
	if (out == nullptr) {
		out = std::make_shared<Node>(p);
		nodes.push_back(out);
	}
	return out;
}

std::list<PStreet> CityController::getStreets() {
	return streets;
}

std::list<PNode> CityController::getNodes() {
	return nodes;
}

std::list<PNode> CityController::getParkings() {
	return parkings;
}

std::list<std::list<PNode>> CityController::getWay(PNode start) {
	std::list<PNode> path = {};
	std::list<PNode> neighbors = {};
	std::list<PNode> listOfWhiteNodes(nodes);
	std::list<PNode> listOfGrayNodes = {};
	std::list<PNode> listOfBlackNodes = {};
	std::list<std::list<PNode>> found = {};

	if (start == NULL)
		return found;

	listOfWhiteNodes.remove(start);
	listOfGrayNodes.push_back(start);
	path.push_back(start);
	found.push_back(path);
	while (!listOfGrayNodes.empty()) {
		std::list<PNode> copyOflistOfGrayNodes(listOfGrayNodes);
		for (PNode nodeInCurrentStep : copyOflistOfGrayNodes) {
			neighbors = findNeighbors(nodeInCurrentStep);
			for (std::list<PNode> pathiInFinder : found) {
				if (pathiInFinder.back() == nodeInCurrentStep)
					path = pathiInFinder;
			}

			for (PNode nodeProcessing : neighbors) {
				if (std::find(listOfWhiteNodes.begin(), listOfWhiteNodes.end(), nodeProcessing) != listOfWhiteNodes.end()) {
					std::list<PNode> newPath(path);
					listOfGrayNodes.push_back(nodeProcessing);
					listOfWhiteNodes.remove(nodeProcessing);
					newPath.push_back(nodeProcessing);
					found.push_back(newPath);
				}
			}
			listOfBlackNodes.push_back(nodeInCurrentStep);
			listOfGrayNodes.remove(nodeInCurrentStep);
		}
	}
	return found;
}

std::list<PNode> CityController::findWay(PNode start, PNode end) {
	for (auto w : getWay(start)) {
		if (w.back() == end)
			return w;
	}
	return std::list<PNode>();
}

std::list<PNode> CityController::findNeighbors(PNode n) {
	std::list<PNode> neighborNodes = {};
	for (PStreet s : streets)
		if (s->getNodes().first == n)
			neighborNodes.push_back(s->getNodes().second);

	/*auto nodeConnections = std::find_if(streets.begin(), streets.end(),[n](Street * m) -> bool { return m->getNodes().first == n; });
	for (auto it = nodeConnections; it != streets.end(); ++it) {
		Street * s = *it;
		neighborNodes.push_back(s->getNodes().second);
	}*/
	return neighborNodes;
}

std::list<PNode> CityController::nodesPath(Position start, Position end) {
	std::list<PNode> nodes = {};
	CityController *cityC = CityController::getInstance();
	std::list<PNode> allNodes = cityC->getNodes();
	PNode s = findNode(start);
	PNode e = findNode(end);
	//finding start node
	
	if (s == NULL || e == NULL)
		return nodes;
	nodes = findWay(s, e);
	return nodes;
}

void CityController::filterList(std::list<PNode> *list) {
	auto it = std::unique(list->begin(), list->end(),
		[] (const PNode a, const PNode b) {
		return a->position.x == b->position.x && a->position.y == b->position.y;
	});
	list->erase(it, list->end());
}

bool CityController::isStreetsOverlap(Position start, Position end) {
	PNode startNode = std::make_shared<Node>(start);
	PNode endNode = std::make_shared<Node>(end);
	PStreet temp = std::make_shared<Street>(startNode, endNode, true);
	if (Street::getPredictedDirection(start, end) == N || Street::getPredictedDirection(start, end) == S)
		for (PStreet s : streets) {
			if (s->getStartEndPositions().first == end && s->getStartEndPositions().second == start)
				return false;
			else if (s->getDirection() == N || s->getDirection() == S)
				if (s->getStartEndPositions().first.x == start.x)
					if (isInIntervalY(start, s) ||
						isInIntervalY(end, s) ||
						isInIntervalY(s->getStartEndPositions().first, temp) ||
						isInIntervalY(s->getStartEndPositions().second, temp)) return true;
		} else
			for (PStreet s : streets)
				if (s->getStartEndPositions().first == end && s->getStartEndPositions().second == start)
					return false;
				else if (s->getDirection() == E || s->getDirection() == W)
					if (s->getStartEndPositions().first.y == start.y)
						if (isInIntervalX(start, s) ||
							isInIntervalX(end, s) ||
							isInIntervalX(s->getStartEndPositions().first, temp) ||
							isInIntervalX(s->getStartEndPositions().second, temp)) return true;
		return false;
}

void CityController::clearController() {
	streets.clear();
	nodes.clear();
	parkings.clear();
}

void CityController::deleteStuff(Position p) {
	PNode node = findNode(p);
	if (node == nullptr) {
		for (auto iter = streets.begin(); iter != streets.end();) {
			if (isInIntervalX(p, *iter) && isInIntervalY(p, *iter))
				iter = streets.erase(iter);
			else
				iter++;
		}
	} else {
		for (auto iter = streets.begin(); iter != streets.end();) {
			if (&*iter->get()->getNodes().first == node.get() || &*iter->get()->getNodes().second == node.get())
				iter = streets.erase(iter);
			else
				iter++;
		}
		for (auto iter = nodes.begin(); iter != nodes.end();) {
			if (*iter == node)
				iter = nodes.erase(iter);
			else
				iter++;
		}
		//getNodes().remove(node);
	}
}

bool CityController::downgradeFromParking(PNode n) {
	if (!n->isParking())
		return false;
	else {
		n->setIsParking(false);
		parkings.remove(n);
		return true;
	}
}

bool CityController::upgradeToParking(PNode n) {
	if (n->isParking())
		return false;
	else {
		n->setIsParking(true);
		parkings.push_back(n);
		return true;
	}
}