#include "CityController.h"

CityController* CityController::instance = nullptr;

CityController* CityController::getInstance() {
	if (!instance)
		instance = new CityController;
	return instance;
}

CityController::CityController() {
	//graph;
	gh = Graph_d(10);
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

Node * CityController::findNode(Position p) {
	Node *out = nullptr;

	for (Node *n : nodes) {
		if (n->getPosition() == p) {
			out = n;
			continue;
		}
		if (out != nullptr)
			break;
	}
	return out;
}

void CityController::createStreet(Node * start, Node * end, bool twoWay) {
	Graph_d::vertex_descriptor s = boost::vertex(start->getNumber(), gh);
	Graph_d::vertex_descriptor e = boost::vertex(end->getNumber(), gh);
	streets.push_back(new Street(start, end));
	boost::add_edge(s, e, 0, gh);
	if (twoWay) {
		streets.push_back(new Street(end, start));
		boost::add_edge(e, s, 0, gh);
	}
}

//DONE: Bad node creation, we do not check if that node already exists
//Check if beginning and end already exists
//TODO: Change return of IsCross and isOverlap to std::map(s, pos) -> bool change to map.empty()
bool CityController::addStreet(Position start, Position end, bool twoWay) {

	Node *s = findNode(start);
	Node *e = findNode(end);

	for (Street *stre : streets) {
		if (stre->getNodes().first == s && stre->getNodes().second == e)
			return false;
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
			//???
			if (cStreetPositions.first == crossingStreet.second ||
				cStreetPositions.second == crossingStreet.second)
				continue;

			Node *middle = findNode(crossingStreet.second);

			if (middle == nullptr) {
				middle = new Node(crossingStreet.second);;
				nodes.push_back(middle);
			}

			crossingNodes.push_back(middle);
			streets.push_back(new Street(middle, crossingStreet.first->getNodes().second));
			Graph_d::vertex_descriptor s = boost::vertex(middle->getNumber(), gh);
			Graph_d::vertex_descriptor e = boost::vertex(crossingStreet.first->getNodes().second->getNumber(), gh);
			boost::add_edge(s, e, 0, gh);
			crossingStreet.first->alterEnd(middle);
			boost::add_edge(e, s, 0, gh);

		}

		crossingNodes.sort([](const Node *a, const Node *b)
		{
			if (a->position.x == b->position.x)
				return a->position.y < b->position.y;
			else
				return a->position.x < b->position.x;
		});
		filterList(&crossingNodes);


		if (s == nullptr) {
			s = new Node(start);
			nodes.push_back(s);
		}
		if (e == nullptr) {
			e = new Node(end);
			nodes.push_back(e);
		}
		//TODO: Another possibility, if you like using the BOOST_FOREACH macro is to use the BOOST_REVERSE_FOREACH macro introduced in Boost 1.36.0.
		if (Street::getPredictedDirection(start, end) == E || Street::getPredictedDirection(start, end) == S) {
			
			createStreet(s, crossingNodes.front(), twoWay);
			createStreet(crossingNodes.back(), e, twoWay);
			for (auto it = crossingNodes.begin(); it != crossingNodes.end(); ++it) {

				createStreet(*it, *std::next(it), twoWay);
				if (std::next(it, 2) == crossingNodes.end()) {
					break;
				}
			}
		} else if (Street::getPredictedDirection(start, end) == W || Street::getPredictedDirection(start, end) == N) {
			createStreet(s, crossingNodes.back(), twoWay);
			createStreet(crossingNodes.front(), e, twoWay);
			for (auto it = crossingNodes.end(); it != crossingNodes.begin(); --it) {

				createStreet(*it, *std::prev(it), twoWay);

				if (std::prev(it, 2) == crossingNodes.begin()) {
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
	createStreet(s, e, twoWay);
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

std::list<Node*> CityController::getWay(Position start, Position End) {
	
	struct my_visitor : boost::default_bfs_visitor {

		void initialize_vertex(const Graph_d::vertex_descriptor &s, const Graph_d &g) const {
			std::cout << "Initialize: " << g[s] << std::endl;
		}
		void discover_vertex(const Graph_d::vertex_descriptor &s, const Graph_d &g) const {
			std::cout << "Discover: " << g[s] << std::endl;
		}
		void examine_vertex(const Graph_d::vertex_descriptor &s, const Graph_d &g) const {
			std::cout << "Examine vertex: " << g[s] << std::endl;
		}
		void examine_edge(const Graph_d::edge_descriptor &e, const Graph_d &g) const {
			std::cout << "Examine edge: " << g[e] << std::endl;
		}
		void tree_edge(const Graph_d::edge_descriptor &e, const Graph_d &g) const {
			std::cout << "Tree edge: " << g[e] << std::endl;
		}
		void non_tree_edge(const Graph_d::edge_descriptor &e, const Graph_d &g) const {
			std::cout << "Non-Tree edge: " << g[e] << std::endl;
		}
		void gray_target(const Graph_d::edge_descriptor &e, const Graph_d &g) const {
			std::cout << "Gray target: " << g[e] << std::endl;
		}
		void black_target(const Graph_d::edge_descriptor &e, const Graph_d &g) const {
			std::cout << "Black target: " << g[e] << std::endl;
		}
		void finish_vertex(const Graph_d::vertex_descriptor &s, const Graph_d &g) const {
			std::cout << "Finish vertex: " << g[s] << std::endl;
		}
	};

	my_visitor vis;

	boost::breadth_first_search(gh, boost::vertex(0, gh), boost::visitor(vis).vertex_index_map(get(boost::vertex_bundle, gh)));

	//boost::breadth_first_search(gh, , boost::visitor(my_visitor));
	
	return std::list<Node*>();
}

bool CityController::isInIntervalX(Position point, Street * range) {
	return false;
}
bool CityController::isInIntervalY(Position point, Street * range) {
	return false;
}
